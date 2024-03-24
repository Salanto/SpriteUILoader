#include "elementstyler.h"
#include <QDebug>

#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QListWidget>
#include <QWidget>

ElementStyler::ElementStyler(QObject *parent, QWidget *full_ui)
    : QObject{parent}
    , ui{full_ui}
{
    if (ui == nullptr) {
        qDebug() << "ui pointer is a nullptr.";
    }

    // Widgets
    QMap<QString, ElementStylist> qcheckbox_styler;
    qcheckbox_styler["size"] = &ElementStyler::setFixedSize<QCheckBox>;
    qcheckbox_styler["position"] = &ElementStyler::move<QCheckBox>;
    qcheckbox_styler["visible"] = &ElementStyler::setVisible<QCheckBox>;
    qcheckbox_styler["enabled"] = &ElementStyler::setEnabled<QCheckBox>;
    qcheckbox_styler["text"] = &ElementStyler::setText<QCheckBox>;
    qcheckbox_styler["checkable"] = &ElementStyler::setCheckable<QCheckBox>;
    qcheckbox_styler["checked"] = &ElementStyler::setChecked<QCheckBox>;
    styler["QCheckBox"] = qcheckbox_styler;

    QMap<QString, ElementStylist> qcombobox_styler;
    qcombobox_styler["size"] = &ElementStyler::setFixedSize<QComboBox>;
    qcombobox_styler["position"] = &ElementStyler::move<QComboBox>;
    qcombobox_styler["visible"] = &ElementStyler::setVisible<QComboBox>;
    qcombobox_styler["enabled"] = &ElementStyler::setEnabled<QComboBox>;
    qcombobox_styler["items"] = &ElementStyler::addItems<QComboBox>;
    qcombobox_styler["editable"] = &ElementStyler::setEditable<QComboBox>;
    qcombobox_styler["placeholder"] = &ElementStyler::setPlaceholderText<QComboBox>;
    styler["QComboBox"] = qcombobox_styler;

    QMap<QString, ElementStylist> qwidget_styler;
    qwidget_styler["size"] = &ElementStyler::setFixedSize<QWidget>;
    qwidget_styler["position"] = &ElementStyler::move<QWidget>;
    qwidget_styler["visible"] = &ElementStyler::setVisible<QWidget>;
    qwidget_styler["enabled"] = &ElementStyler::setEnabled<QWidget>;
    styler["QWidget"] = qwidget_styler;

    QMap<QString, ElementStylist> qlistwidget_styler;
    qwidget_styler["size"] = &ElementStyler::setFixedSize<QListWidget>;
    qwidget_styler["position"] = &ElementStyler::move<QListWidget>;
    qwidget_styler["visible"] = &ElementStyler::setVisible<QListWidget>;
    qwidget_styler["enabled"] = &ElementStyler::setEnabled<QListWidget>;
    styler["QListWidget"] = qlistwidget_styler;

    QMap<QString, ElementStylist> qlabel_styler;
    qlabel_styler["text"] = &ElementStyler::setText<QLabel>;
    qlabel_styler["image"] = &ElementStyler::setPixmap<QLabel>;
    qlabel_styler["size"] = &ElementStyler::setFixedSize<QLabel>;
    qlabel_styler["position"] = &ElementStyler::move<QLabel>;
    qlabel_styler["visible"] = &ElementStyler::setVisible<QLabel>;
    qlabel_styler["enabled"] = &ElementStyler::setEnabled<QLabel>;
    styler["QLabel"] = qlabel_styler;

    // Layouts

    // Effects
    // QGraphicsBlurEffect, QGraphicsColorizeEffect, QGraphicsDropShadowEffect, and QGraphicsOpacityEffect
    QMap<QString, ElementStylist> qgraphicsblureffect_styler;
    qgraphicsblureffect_styler["blur"] = &ElementStyler::setFloatBlurRadius<QGraphicsBlurEffect>;
    styler["QGraphicsBlurEffect"] = qgraphicsblureffect_styler;

    QMap<QString, ElementStylist> qgraphicscolorizeeffect_styler;
    qgraphicscolorizeeffect_styler["color"] = &ElementStyler::setColor<QGraphicsColorizeEffect>;
    qgraphicscolorizeeffect_styler["strength"]
        = &ElementStyler::setFloatStrength<QGraphicsColorizeEffect>;
    styler["QGraphicsColorizeEffect"] = qgraphicscolorizeeffect_styler;

    QMap<QString, ElementStylist> qgraphicsdropshadoweffect_styler;
    qgraphicsdropshadoweffect_styler["color"] = &ElementStyler::setColor<QGraphicsDropShadowEffect>;
    qgraphicsdropshadoweffect_styler["offset"]
        = &ElementStyler::setFloatOffset<QGraphicsDropShadowEffect>;
    qgraphicsdropshadoweffect_styler["blur"]
        = &ElementStyler::setFloatBlurRadius<QGraphicsDropShadowEffect>;
    styler["QGraphicsDropShadowEffect"] = qgraphicsdropshadoweffect_styler;

    QMap<QString, ElementStylist> qgraphicsopcacityeffect_styler;
    qgraphicsopcacityeffect_styler["opacity"]
        = &ElementStyler::setFloatOpacity<QGraphicsOpacityEffect>;
    styler["QGraphicsOpacityEffect"] = qgraphicsopcacityeffect_styler;
}

void ElementStyler::styleElement(QString element_id,
                                 QString element_class,
                                 QMap<QString, QString> element_properties)
{
    if (!canStyleElement(element_class)) {
        qDebug() << "Unable to style element" << element_id << "of class" << element_class;
        return;
    }

    QMap<QString, ElementStylist> class_styler = styler.value(element_class);
    for (const QString &property : element_properties.keys()) {
        if (property == "id") {
            continue;
        }

        if (!class_styler.contains(property)) {
            qDebug() << "Unhandled property" << property << "for element class" << element_class;
            continue;
        }
        ElementStylist styler = class_styler[property];
        (this->*styler)(element_id, element_properties[property]);
    }
}

bool ElementStyler::canStyleElement(QString element_class)
{
    return styler.contains(element_class);
}

template<typename T>
void ElementStyler::setText(QString element_id, QString text)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "for setting the text";
        return;
    }
    pointer->setText(text);
}

template<typename T>
void ElementStyler::setPixmap(QString element_id, QString image_path)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set a pixmap";
        return;
    }
    pointer->setScaledContents(true);
    pointer->setPixmap(QPixmap(image_path));
}

template<typename T>
void ElementStyler::setFixedSize(QString element_id, QString dimensions)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set the size.";
        return;
    }
    QStringList positions = dimensions.split(",");
    if (positions.size() != 2) {
        qDebug() << "Error parsing the size. Received size is" << dimensions;
        return;
    }
    QSize size(positions[0].toInt(), positions[1].toInt());
    pointer->setFixedSize(size);
}

template<typename T>
void ElementStyler::move(QString element_id, QString positions)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "for moving";
        return;
    }

    QStringList position_list = positions.split(",");
    if (position_list.size() != 2) {
        qDebug() << "Error parsing the size. Received position is" << positions;
        return;
    }
    pointer->move(position_list[0].toInt(), position_list[1].toInt());
}

template<typename T>
void ElementStyler::setColor(QString element_id, QString color)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set color";
        return;
    }

    QColor parsed_color = QColor::fromString(color);
    if (!parsed_color.isValid()) {
        qDebug() << "Provided color string" << color << "is not valid.";
        return;
    }

    pointer->setColor(parsed_color);
}

template<typename T>
void ElementStyler::setFloatOffset(QString element_id, QString offset)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to apply float offset";
        return;
    }
    QStringList offsets = offset.split(",");
    if (offsets.size()) {
        qDebug() << "Error parsing the size. Received offset is" << offsets;
    }
    pointer->setOffset(offsets[0].toFloat(), offsets[1].toFloat());
}

template<typename T>
void ElementStyler::setFloatBlurRadius(QString element_id, QString radius)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to apply float offset";
        return;
    }
    pointer->setBlurRadius(radius.toFloat());
}

template<typename T>
void ElementStyler::setFloatStrength(QString element_id, QString strength)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to apply float offset";
        return;
    }
    pointer->setStrength(strength.toFloat());
}

template<typename T>
void ElementStyler::setFloatOpacity(QString element_id, QString opacity)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to apply float offset";
        return;
    }
    pointer->setOpacity(opacity.toFloat());
}

template<typename T>
void ElementStyler::setVisible(QString element_id, QString visible)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set visibility";
        return;
    }
    bool is_visible = QVariant::fromValue<QString>(visible).toBool();
    pointer->setVisible(is_visible);
}

template<typename T>
void ElementStyler::setToolTip(QString element_id, QString tooltip)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set tooltip";
        return;
    }
    pointer->setToolTip(tooltip);
}

template<typename T>
void ElementStyler::setEnabled(QString element_id, QString enabled)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set enabled state";
        return;
    }
    pointer->setEnabled(QVariant::fromValue<QString>(enabled).toBool());
}

template<typename T>
void ElementStyler::setCheckable(QString element_id, QString checkable)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set checkable state";
        return;
    }
    pointer->setCheckable(QVariant::fromValue<QString>(checkable).toBool());
}

template<typename T>
void ElementStyler::setChecked(QString element_id, QString checked)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set checked state";
        return;
    }
    pointer->setChecked(QVariant::fromValue<QString>(checked).toBool());
}

template<typename T>
void ElementStyler::addItems(QString element_id, QString items)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set selectable items";
        return;
    }
    pointer->addItems(items.split(","));
}

template<typename T>
void ElementStyler::setEditable(QString element_id, QString editable)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set editable state";
        return;
    }
    pointer->setEditable(QVariant::fromValue<QString>(editable).toBool());
}

template<typename T>
void ElementStyler::setPlaceholderText(QString element_id, QString placeholder)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set placeholder text";
        return;
    }
    pointer->setPlaceholderText(placeholder);
}
