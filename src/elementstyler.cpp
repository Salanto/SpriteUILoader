#include "elementstyler.h"
#include <QDebug>
#include "qfontdatabase.h"
#include "qobjectdefs.h"

#include <QCheckBox>
#include <QComboBox>
#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
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
    qcheckbox_styler["font"] = &ElementStyler::setFont<QCheckBox>;
    qcheckbox_styler["pointsize"] = &ElementStyler::setPointSize<QCheckBox>;
    styler["QCheckBox"] = qcheckbox_styler;

    QMap<QString, ElementStylist> qcombobox_styler;
    qcombobox_styler["size"] = &ElementStyler::setFixedSize<QComboBox>;
    qcombobox_styler["position"] = &ElementStyler::move<QComboBox>;
    qcombobox_styler["visible"] = &ElementStyler::setVisible<QComboBox>;
    qcombobox_styler["enabled"] = &ElementStyler::setEnabled<QComboBox>;
    qcombobox_styler["items"] = &ElementStyler::addItems<QComboBox>;
    qcombobox_styler["editable"] = &ElementStyler::setEditable<QComboBox>;
    qcombobox_styler["placeholder"] = &ElementStyler::setPlaceholderText<QComboBox>;
    qcombobox_styler["frame"] = &ElementStyler::setFrame<QComboBox>;
    qcombobox_styler["font"] = &ElementStyler::setFont<QComboBox>;
    qcombobox_styler["pointsize"] = &ElementStyler::setPointSize<QComboBox>;
    styler["QComboBox"] = qcombobox_styler;

    QMap<QString, ElementStylist> qwidget_styler;
    qwidget_styler["size"] = &ElementStyler::setFixedSize<QWidget>;
    qwidget_styler["position"] = &ElementStyler::move<QWidget>;
    qwidget_styler["visible"] = &ElementStyler::setVisible<QWidget>;
    qwidget_styler["enabled"] = &ElementStyler::setEnabled<QWidget>;
    styler["QWidget"] = qwidget_styler;

    QMap<QString, ElementStylist> qlistwidget_styler;
    qlistwidget_styler["size"] = &ElementStyler::setFixedSize<QListWidget>;
    qlistwidget_styler["position"] = &ElementStyler::move<QListWidget>;
    qlistwidget_styler["visible"] = &ElementStyler::setVisible<QListWidget>;
    qlistwidget_styler["enabled"] = &ElementStyler::setEnabled<QListWidget>;
    qlistwidget_styler["font"] = &ElementStyler::setFont<QListWidget>;
    qlistwidget_styler["pointsize"] = &ElementStyler::setPointSize<QListWidget>;
    styler["QListWidget"] = qlistwidget_styler;

    QMap<QString, ElementStylist> qlineedit_styler;
    qlineedit_styler["size"] = &ElementStyler::setFixedSize<QLineEdit>;
    qlineedit_styler["position"] = &ElementStyler::move<QLineEdit>;
    qlineedit_styler["visible"] = &ElementStyler::setVisible<QLineEdit>;
    qlineedit_styler["enabled"] = &ElementStyler::setEnabled<QLineEdit>;
    qlineedit_styler["placeholder"] = &ElementStyler::setPlaceholderText<QLineEdit>;
    qlineedit_styler["frame"] = &ElementStyler::setFrame<QLineEdit>;
    qlineedit_styler["readonly"] = &ElementStyler::setReadOnly<QLineEdit>;
    qlineedit_styler["font"] = &ElementStyler::setFont<QLineEdit>;
    qlineedit_styler["pointsize"] = &ElementStyler::setPointSize<QLineEdit>;
    styler["QLineEdit"] = qlineedit_styler;

    QMap<QString, ElementStylist> qtextedit_styler;
    qtextedit_styler["size"] = &ElementStyler::setFixedSize<QTextEdit>;
    qtextedit_styler["position"] = &ElementStyler::move<QTextEdit>;
    qtextedit_styler["visible"] = &ElementStyler::setVisible<QTextEdit>;
    qtextedit_styler["enabled"] = &ElementStyler::setEnabled<QTextEdit>;
    qtextedit_styler["placeholder"] = &ElementStyler::setPlaceholderText<QTextEdit>;
    qtextedit_styler["readonly"] = &ElementStyler::setReadOnly<QTextEdit>;
    qtextedit_styler["font"] = &ElementStyler::setFont<QTextEdit>;
    qtextedit_styler["pointsize"] = &ElementStyler::setPointSize<QTextEdit>;
    styler["QTextEdit"] = qtextedit_styler;

    QMap<QString, ElementStylist> qspinbox_styler;
    qspinbox_styler["size"] = &ElementStyler::setFixedSize<QSpinBox>;
    qspinbox_styler["position"] = &ElementStyler::move<QSpinBox>;
    qspinbox_styler["visible"] = &ElementStyler::setVisible<QSpinBox>;
    qspinbox_styler["enabled"] = &ElementStyler::setEnabled<QSpinBox>;
    qspinbox_styler["frame"] = &ElementStyler::setFrame<QSpinBox>;
    qspinbox_styler["minimum"] = &ElementStyler::setMinimum<QSpinBox>;
    qspinbox_styler["maximum"] = &ElementStyler::setMaximum<QSpinBox>;
    qspinbox_styler["range"] = &ElementStyler::setRange<QSpinBox>;
    qspinbox_styler["prefix"] = &ElementStyler::setPrefix<QSpinBox>;
    qspinbox_styler["suffix"] = &ElementStyler::setSuffix<QSpinBox>;
    qspinbox_styler["readonly"] = &ElementStyler::setReadOnly<QSpinBox>;
    qspinbox_styler["font"] = &ElementStyler::setFont<QSpinBox>;
    qspinbox_styler["pointsize"] = &ElementStyler::setPointSize<QSpinBox>;
    styler["QSpinBox"] = qspinbox_styler;

    QMap<QString, ElementStylist> qlabel_styler;
    qlabel_styler["text"] = &ElementStyler::setText<QLabel>;
    qlabel_styler["image"] = &ElementStyler::setPixmap<QLabel>;
    qlabel_styler["size"] = &ElementStyler::setFixedSize<QLabel>;
    qlabel_styler["position"] = &ElementStyler::move<QLabel>;
    qlabel_styler["visible"] = &ElementStyler::setVisible<QLabel>;
    qlabel_styler["enabled"] = &ElementStyler::setEnabled<QLabel>;
    qlabel_styler["font"] = &ElementStyler::setFont<QLabel>;
    qlabel_styler["pointsize"] = &ElementStyler::setPointSize<QLabel>;
    qlabel_styler["color"] = &ElementStyler::setStylesheetColor<QLabel>;
    styler["QLabel"] = qlabel_styler;

    QMap<QString, ElementStylist> qpushbutton_styler;
    qpushbutton_styler["size"] = &ElementStyler::setFixedSize<QPushButton>;
    qpushbutton_styler["position"] = &ElementStyler::move<QPushButton>;
    qpushbutton_styler["visible"] = &ElementStyler::setVisible<QPushButton>;
    qpushbutton_styler["enabled"] = &ElementStyler::setEnabled<QPushButton>;
    qpushbutton_styler["text"] = &ElementStyler::setText<QPushButton>;
    qpushbutton_styler["font"] = &ElementStyler::setFont<QPushButton>;
    qpushbutton_styler["pointsize"] = &ElementStyler::setPointSize<QPushButton>;
    qpushbutton_styler["color"] = &ElementStyler::setStylesheetColor<QPushButton>;
    styler["QPushButton"] = qpushbutton_styler;

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
    if (offsets.size() != 2) {
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

template<typename T>
void ElementStyler::setFrame(QString element_id, QString frame_enabled)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set frame rendering enabled";
        return;
    }
    pointer->setFrame(QVariant::fromValue<QString>(frame_enabled).toBool());
}

template<typename T>
void ElementStyler::setMinimum(QString element_id, QString minimum_value)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set minimum value";
        return;
    }
    pointer->setMinimum(QVariant::fromValue<QString>(minimum_value).toInt());
}

template<typename T>
void ElementStyler::setMaximum(QString element_id, QString maximum_value)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set maximum value";
        return;
    }
    pointer->setMaximum(QVariant::fromValue<QString>(maximum_value).toInt());
}

template<typename T>
void ElementStyler::setRange(QString element_id, QString range_list)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set value range";
        return;
    }

    QStringList ranges = range_list.split(",");
    if (ranges.size() != 2) {
        qDebug() << "Provided range string" << range_list << "is not valid.";
        return;
    }
    pointer->setRange(ranges[0].toInt(), ranges[1].toInt());
}

template<typename T>
void ElementStyler::setSuffix(QString element_id, QString suffix)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set suffix";
        return;
    }
    pointer->setSuffix(suffix);
}

template<typename T>
void ElementStyler::setPrefix(QString element_id, QString suffix)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to set prefix";
        return;
    }
    pointer->setPrefix(suffix);
}

template<typename T>
void ElementStyler::setReadOnly(QString element_id, QString readonly)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to readonly state";
        return;
    }
    pointer->setReadOnly(QVariant::fromValue<QString>(readonly).toBool());
}

template<typename T>
void ElementStyler::setFont(QString element_id, QString font_settings)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to readonly state";
        return;
    }
    QStringList font_info = font_settings.split(",");
    if (font_info.size() != 3) {
        qDebug() << "Error parsing the font. Received font configuration is" << font_settings;
        return;
    }

    QFont font = QFontDatabase::font(font_info[0], font_info[1], font_info[2].toInt());
    pointer->setFont(font);
}

template<typename T>
void ElementStyler::setPointSize(QString element_id, QString point_size)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to readonly state";
        return;
    }
    QFont font = pointer->font();
    font.setPointSize(point_size.toInt());
    pointer->setFont(font);
}

template<typename T>
void ElementStyler::setStylesheetColor(QString element_id, QString color)
{
    T *pointer = ui->findChild<T *>(element_id);
    if (pointer == nullptr) {
        qDebug() << "Unable to locate element" << element_id << "to apply text color";
        return;
    }
    QColor l_color = QColor::fromString(color);
    if (!l_color.isValid()) {
        qDebug() << "Unable to parse color. Provided color" << color << "is not valid.";
        return;
    }
    QString stylesheet_entry = QString("%1 {color: %2 }")
                                   .arg(pointer->metaObject()->className(),
                                        QVariant::fromValue<QColor>(l_color).toString());
    QString stylesheet = pointer->styleSheet();
    qDebug() << stylesheet;
    stylesheet.append(stylesheet_entry);
    qDebug() << stylesheet;
    pointer->setStyleSheet(stylesheet);
}
