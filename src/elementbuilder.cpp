#include "ElementBuilder.h"

#include <QDebug>
#include <QLayout>
#include <QMainWindow>
#include <QWidget>

#include "elementstyler.h"
#include "spriteuiloader.h"

ElementBuilder::ElementBuilder(QObject *parent)
    : QObject(parent)
{
    loader = new SpriteUiLoader(this);
    root_widget = new QWidget(nullptr);
}

void ElementBuilder::createRootWidget(const QDomNode &nodes)
{
    QMap<QString, QString> element_properties = parseAttributes(nodes.attributes());
    loader->createWidget(nodes.nodeName(), root_widget, element_properties.value("id"));
    element_classes.insert(element_properties.value("id"), nodes.nodeName());
    root_widget_name = element_properties.value("id");
    if (nodes.hasChildNodes()) {
        createChildElement(nodes.childNodes(), element_properties.value("id"));
    }

    ElementStyler styler(this, root_widget);
    for (const QString &element_id : element_classes.keys()) {
        const QString &element_class = element_classes.value(element_id);
        QMap<QString, QString> element_properties = widget_configuration.value(element_id);
        styler.styleElement(element_id, element_class, element_properties);
    }
}

void ElementBuilder::createChildElement(const QDomNodeList &nodes, QString parent_id)
{
    QString parent_type = element_classes.value(parent_id);
    for (int index = 0; index < nodes.size(); ++index) {

        const QDomNode &node = nodes.at(index);
        QMap<QString, QString> element_properties = parseAttributes(node.attributes());

        if (!loader->canCreateItem(node.nodeName())) {
            qDebug() << "Unable to create interface item. The class" << node.nodeName() << "is not supported.";
            continue;
        }

        if (element_properties.value("id").isEmpty()) {
            qDebug() << "Unable to parse hierarchy. All elements need an id!";
            continue;
        }

        if (element_classes.contains(element_properties.value("id"))) {
            qDebug() << "Unable to create object with same ID as another object. Object names must be unique!";
            continue;
        }

        element_classes.insert(element_properties.value("id"), node.nodeName());
        widget_configuration.insert(element_properties.value("id"), element_properties);

        if (loader->isWidget(parent_type)) {
            // Parent is a widget. What are we though?
            if (loader->isWidget(node.nodeName())) {
                //So are we!
                appendWidgetToWidget(parent_id, node.nodeName(), element_properties.value("id"));
            }

            if (loader->isLayout(node.nodeName())) {
                // We are a layout!
                appendLayoutToWidget(parent_id, node.nodeName(), element_properties.value("id"));
            }

            if (loader->isEffect(node.nodeName())) {
                // We are a effect!
                appendEffectToWidget(parent_id, node.nodeName(), element_properties.value("id"));
            }
        }

        if (loader->isLayout(parent_type)) {
            // Parent is a layout.
            if (loader->isWidget(node.nodeName())) {
                appendWidgetToLayout(parent_id, node.nodeName(), element_properties.value("id"));
            }

            if (loader->isLayout(node.nodeName())) {
                appendLayoutToLayout(parent_id, node.nodeName(), element_properties.value("id"));
            }
        }

        if (node.hasChildNodes()) {
            createChildElement(node.childNodes(), element_properties.value("id"));
        }
    }
}

QMap<QString, QString> ElementBuilder::parseAttributes(QDomNamedNodeMap attribute_nodes)
{
    QMap<QString, QString> attributes;
    for (int attribute = 0; attribute < attribute_nodes.size(); ++attribute) {
        const QDomNode node = attribute_nodes.item(attribute);
        attributes.insert(node.nodeName(), node.nodeValue());
    }
    return attributes;
}

void ElementBuilder::appendWidgetToWidget(QString parent_widget,
                                          QString widget_type,
                                          QString child_widget)
{
    qDebug() << "Creating widget with name" << child_widget;
    QWidget *parent = objectPointer<QWidget *>(parent_widget);
    loader->createWidget(widget_type, parent, child_widget);
}

void ElementBuilder::appendWidgetToLayout(QString parent_layout,
                                          QString widget_type,
                                          QString child_widget)
{
    qDebug() << "Creating widget with name" << child_widget;
    QLayout *parent = objectPointer<QLayout *>(parent_layout);
    QWidget *widget = loader->createWidget(widget_type, nullptr, child_widget);
    parent->addWidget(widget);
}

void ElementBuilder::appendLayoutToWidget(QString parent_widget,
                                          QString layout_type,
                                          QString child_layout)
{
    qDebug() << root_widget;
    qDebug() << "Creating layout with name" << child_layout;
    QWidget *parent = objectPointer<QWidget *>(parent_widget);
    QLayout *layout = loader->createLayout(layout_type, parent, child_layout);
    parent->setLayout(layout);
}

void ElementBuilder::appendLayoutToLayout(QString parent_layout,
                                          QString layout_type,
                                          QString child_layout)
{
    qDebug() << "Creating layout with name" << child_layout;
    QBoxLayout *parent = objectPointer<QBoxLayout *>(parent_layout);
    if (parent == nullptr) {
        qDebug() << "Layout" << parent_layout << "does not support sublayouts.";
        return;
    }
    QLayout *layout = loader->createLayout(layout_type, parent, child_layout);
    parent->addLayout(layout);
}

void ElementBuilder::appendEffectToWidget(QString parent_widget,
                                          QString effect_type,
                                          QString child_effect)
{
    qDebug() << "Creating effect with name" << child_effect;
    QWidget *parent = objectPointer<QWidget *>(parent_widget);
    QGraphicsEffect *effect = loader->createEffect(effect_type, parent, child_effect);
    parent->setGraphicsEffect(effect);
}

QWidget *ElementBuilder::ui()
{
    // This step will be unecessary in production code as we would reparent to a QMainWindow.
    qDebug() << "Main widget name" << root_widget_name;
    QWidget *widget = objectPointer<QWidget *>(root_widget_name);
    if (widget == nullptr) {
        return widget;
    }
    widget->setParent(nullptr);
    return widget;
}

template<typename T>
T ElementBuilder::objectPointer(QString object_name)
{
    return root_widget->findChild<T>(object_name);
}
