#ifndef WIDGETBUILDER_H
#define WIDGETBUILDER_H

#include <QDomNode>
#include <QMap>
#include <QObject>

class QUiLoader;

class WidgetBuilder : public QObject
{
    Q_OBJECT
public:
    explicit WidgetBuilder(QObject *parent);
    ~WidgetBuilder(){};

    void createRootWidget(const QDomNode &nodes);
    void createChildElement(const QDomNodeList &nodes, QString parent_id);
    QWidget *ui();

private:
    bool isWidget(QString class_name);
    bool isLayout(QString class_name);
    bool isCustom(QString class_name);

    QMap<QString, QString> parseAttributes(QDomNamedNodeMap attribute_nodes);

    // Improvment: Make this a template?
    void appendWidgetToWidget(QString parent_widget, QString widget_type, QString child_widget);
    void appendWidgetToLayout(QString parent_layout, QString widget_type, QString child_widget);
    void appendLayoutToWidget(QString parent_widget, QString layout_type, QString child_layout);
    void appendLayoutToLayout(QString parent_layout, QString layout_type, QString child_layout);

    template<typename T>
    T getObjectPointer(QString object_name);

    QWidget *root_widget;
    QString root_widget_name;
    QUiLoader *loader;

    // We style after creating the tree. As such we need to know all widget types we created to parse into the right styler.
    QMap<QString, QString> widget_types;
    QMap<QString, QMap<QString, QString>> widget_configuration;
};

#endif // WIDGETBUILDER_H