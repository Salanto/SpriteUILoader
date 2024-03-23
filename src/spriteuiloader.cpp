#include "spriteuiloader.h"

#include <QDebug>
#include <QWidget>
#include <QLayout>

#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>

SpriteUiLoader::SpriteUiLoader(QObject *parent)
    : QUiLoader{parent}
{
    qDebug() << "Creating SpriteUiLoader";

    // We may need to create widgets not automatically supproted.
    supported_widgets << availableWidgets();
    supported_layouts << availableLayouts();
    supported_effects << "QGraphicsDropShadowEffect" << "QGraphicsBlurEffect"
                      << "QGraphicsColorizeEffect" << "QGraphicsOpacityEffect";

    effect_builders["QGraphicsDropShadowEffect"] = &SpriteUiLoader::instantiateEffect<QGraphicsDropShadowEffect>;
    effect_builders["QGraphicsBlurEffect"] = &SpriteUiLoader::instantiateEffect<QGraphicsBlurEffect>;
    effect_builders["QGraphicsColorizeEffect"] = &SpriteUiLoader::instantiateEffect<QGraphicsColorizeEffect>;
    effect_builders["QGraphicsOpacityEffect"] = &SpriteUiLoader::instantiateEffect<QGraphicsOpacityEffect>;

    qDebug() << "Supported widgets:" << Qt::endl << supported_widgets;
    qDebug() << "Supported layouts:" << Qt::endl << supported_layouts;
    qDebug() << "Supported effects:" << Qt::endl << supported_effects;
}

QWidget *SpriteUiLoader::createWidget(const QString &className, QWidget *parent, const QString &name)
{
    if (availableWidgets().contains(className)) {
        return QUiLoader::createWidget(className, parent, name);
    }
    return createCustomWidget(className, parent, name);
}

QLayout *SpriteUiLoader::createLayout(const QString &className, QObject *parent, const QString &name)
{
    if (availableLayouts().contains(className)) {
        return QUiLoader::createLayout(className, parent, name);
    }
    return createCustomLayout(className, parent, name);
}

QGraphicsEffect *SpriteUiLoader::createEffect(const QString &className, QWidget *parent, const QString &name)
{
    if (supported_effects.contains(className)) {
        return createCustomEffect(className, parent, name);
    }
    return nullptr;
}

bool SpriteUiLoader::isWidget(QString widget_name)
{
    return supported_widgets.contains(widget_name);
}

bool SpriteUiLoader::isLayout(QString layout_name)
{
    return supported_layouts.contains(layout_name);
}

bool SpriteUiLoader::isEffect(QString effect_name)
{
    return supported_effects.contains(effect_name);
}

bool SpriteUiLoader::canCreateItem(QString class_name)
{
    return (isWidget(class_name) || isLayout(class_name) || isEffect(class_name));
}

QWidget *SpriteUiLoader::createCustomWidget(QString class_name, QWidget *parent, QString widget_name)
{
    if (widget_builders.contains(class_name)) {
        WidgetBuilder builder = widget_builders[class_name];
        return (this->*builder)(parent, widget_name);
    }
    return nullptr;
}

QLayout *SpriteUiLoader::createCustomLayout(QString class_name, QObject *parent, QString layout_name)
{
    if (layout_builders.contains(class_name)) {
        LayoutBuilder builder = layout_builders[class_name];
        return (this->*builder)(parent, layout_name);
    }
    return nullptr;
}

QGraphicsEffect *SpriteUiLoader::createCustomEffect(QString class_name, QWidget *parent, QString object_name)
{
    if (effect_builders.contains(class_name)) {
        EffectBuilder builder = effect_builders[class_name];
        return (this->*builder)(parent, object_name);
    }
    return nullptr;
}

template<typename T>
QWidget *SpriteUiLoader::instantiateWidget(QWidget *parent, QString widget_name)
{
    QWidget* widget = new T(parent);
    widget->setObjectName(widget_name);
    return widget;
}

template<typename T>
QLayout *SpriteUiLoader::instantiateLayout(QObject *parent, QString layout_name)
{
    QLayout* layout = new T(parent);
    layout->setObjectName(layout_name);
    return layout;
}

template<typename T>
QGraphicsEffect *SpriteUiLoader::instantiateEffect(QWidget *parent, QString object_name)
{
    QGraphicsEffect* effect = new T(parent);
    effect->setObjectName(object_name);
    parent->setGraphicsEffect(effect);
    return effect;
}
