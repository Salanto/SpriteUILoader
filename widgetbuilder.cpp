#include "widgetbuilder.h"

#include <QDebug>
#include <QLayout>
#include <QMainWindow>
#include <QUiLoader>
#include <QWidget>

WidgetBuilder::WidgetBuilder(QObject *parent)
    : QObject(parent)
{
    loader = new QUiLoader(this);
}

void WidgetBuilder::createRootWidget(const QDomNode &nodes)
{
    QMap<QString, QString> node_attributes = parseAttributes(nodes.attributes());
    root_widget = loader->createWidget(nodes.nodeName(), nullptr, node_attributes.value("id"));
    widget_types.insert(node_attributes.value("id"), nodes.nodeName());
    root_widget_name = node_attributes.value("id");
    if (nodes.hasChildNodes()) {
        createChildElement(nodes.childNodes(), node_attributes.value("id"));
    }
}

void WidgetBuilder::createChildElement(const QDomNodeList &nodes, QString parent_id)
{
    QString parent_type = widget_types.value(parent_id);
    for (int index = 0; index < nodes.size(); ++index) {
        const QDomNode &node = nodes.at(index);
        QMap<QString, QString> node_attributes = parseAttributes(node.attributes());
        widget_types.insert(node_attributes.value("id"), node.nodeName());

        if (node_attributes.value("id").isEmpty()) {
            qDebug() << "Unable to parse hierarchy. All elements need an id!";
            continue;
        }

        if (isWidget(parent_type)) {
            // Parent is a widget. What are we though?
            if (isWidget(node.nodeName())) {
                //So are we!
                appendWidgetToWidget(parent_id, node.nodeName(), node_attributes.value("id"));
            }

            if (isLayout(node.nodeName())) {
                // We are a layout!
                appendLayoutToWidget(parent_id, node.nodeName(), node_attributes.value("id"));
            }
        }

        if (isLayout(parent_type)) {
            // Parent is a layout.
            if (isWidget(node.nodeName())) {
                appendWidgetToLayout(parent_id, node.nodeName(), node_attributes.value("id"));
            }

            if (isLayout(node.nodeName())) {
                appendLayoutToLayout(parent_id, node.nodeName(), node_attributes.value("id"));
            }
        }

        if (node.hasChildNodes()) {
            createChildElement(node.childNodes(), node_attributes.value("id"));
        }
    }
}

bool WidgetBuilder::isWidget(QString class_name)
{
    return loader->availableWidgets().contains(class_name);
}

bool WidgetBuilder::isLayout(QString class_name)
{
    return loader->availableLayouts().contains(class_name);
}

bool WidgetBuilder::isCustom(QString class_name)
{
    return !(isLayout(class_name) || isWidget(class_name));
}

QMap<QString, QString> WidgetBuilder::parseAttributes(QDomNamedNodeMap attribute_nodes)
{
    QMap<QString, QString> attributes;
    for (int attribute = 0; attribute < attribute_nodes.size(); ++attribute) {
        const QDomNode node = attribute_nodes.item(attribute);
        attributes.insert(node.nodeName(), node.nodeValue());
    }
    return attributes;
}

void WidgetBuilder::appendWidgetToWidget(QString parent_widget,
                                         QString widget_type,
                                         QString child_widget)
{
    qDebug() << "Creating object with name" << child_widget;
    QWidget *parent = getObjectPointer<QWidget *>(parent_widget);
    loader->createWidget(widget_type, parent, child_widget);
}

void WidgetBuilder::appendWidgetToLayout(QString parent_layout,
                                         QString widget_type,
                                         QString child_widget)
{
    qDebug() << "Creating object with name" << child_widget;
    QLayout *parent = getObjectPointer<QLayout *>(parent_layout);
    QWidget *widget = loader->createWidget(widget_type, nullptr, child_widget);
    parent->addWidget(widget);
}

void WidgetBuilder::appendLayoutToWidget(QString parent_widget,
                                         QString layout_type,
                                         QString child_layout)
{
    qDebug() << "Creating object with name" << child_layout;
    QWidget *parent = getObjectPointer<QWidget *>(parent_widget);
    QLayout *layout = loader->createLayout(layout_type, parent, child_layout);
    parent->setLayout(layout);
}

void WidgetBuilder::appendLayoutToLayout(QString parent_layout,
                                         QString layout_type,
                                         QString child_layout)
{
    qDebug() << "Creating object with name" << child_layout;
    QLayout *parent = getObjectPointer<QLayout *>(parent_layout);
    QLayout *layout = loader->createLayout(layout_type, parent, child_layout);
    parent->addItem(layout);
}

QWidget *WidgetBuilder::ui()
{
    return root_widget;
}

template<typename T>
T WidgetBuilder::getObjectPointer(QString object_name)
{
    if (object_name == root_widget_name) {
        return dynamic_cast<T>(root_widget);
    }
    return root_widget->findChild<T>(object_name);
}
