#ifndef SPRITEUILOADER_H
#define SPRITEUILOADER_H

#include <QUiLoader>
#include <QMap>

class QWidget;
class QLayout;
class QGraphicsEffect;

class SpriteUiLoader : protected QUiLoader
{
    Q_OBJECT
public:
    explicit SpriteUiLoader(QObject *parent = nullptr);

    QWidget *createWidget(const QString &className, QWidget *parent = nullptr, const QString &name = QString()) override;
    QLayout *createLayout(const QString &className, QObject *parent = nullptr, const QString &name = QString()) override;
    QGraphicsEffect *createEffect(const QString &className, QWidget *parent = nullptr, const QString &name = QString());



    // Since widgets and layouts will have different baseclasses we need to check what the requested class is.
    bool isWidget(QString widget_name);
    bool isLayout(QString layout_name);
    bool isEffect(QString effect_name);

    // A general way to check if we can handle this item.
    bool canCreateItem(QString class_name);

    QWidget *createCustomWidget(QString class_name, QWidget* parent, QString widget_name);
    QLayout *createCustomLayout(QString class_name, QObject *parent, QString layout_name);
    QGraphicsEffect *createCustomEffect(QString class_name, QWidget *parent, QString object_name);

private:
    template<typename T>
    QWidget *instantiateWidget(QWidget* parent, QString widget_name);

    template<typename T>
    QLayout *instantiateLayout(QObject* parent, QString layout_name);

    template<typename T>
    QGraphicsEffect *instantiateEffect(QWidget* parent, QString object_name);

    using WidgetBuilder = QWidget* (SpriteUiLoader::*)(QWidget*, QString);
    using LayoutBuilder = QLayout* (SpriteUiLoader::*)(QObject*, QString);
    using EffectBuilder = QGraphicsEffect* (SpriteUiLoader::*)(QWidget*, QString);

    QMap<QString, WidgetBuilder> widget_builders;
    QMap<QString, LayoutBuilder> layout_builders;
    QMap<QString, EffectBuilder> effect_builders;
    QStringList supported_widgets;
    QStringList supported_layouts;
    QStringList supported_effects;
};

#endif // SPRITEUILOADER_H
