#include "elementstyler.h"
#include <QDebug>

#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QWidget>

ElementStyler::ElementStyler(QObject *parent, QWidget *full_ui)
    : QObject{parent}
    , ui{full_ui}
{
    if (ui == nullptr) {
        qDebug() << "ui pointer is a nullptr.";
    }

    QMap<QString, ElementStylist> qlabel_stylists;
    qlabel_stylists["text"] = &ElementStyler::setText<QLabel>;
    qlabel_stylists["image"] = &ElementStyler::setPixmap<QLabel>;
    qlabel_stylists["size"] = &ElementStyler::setFixedSize<QLabel>;
    qlabel_stylists["position"] = &ElementStyler::move<QLabel>;
    stylists["QLabel"] = qlabel_stylists;

    QMap<QString, ElementStylist> qgraphicsdropshadoweffect_stylists;
    qgraphicsdropshadoweffect_stylists["color"] = &ElementStyler::setColor<QGraphicsDropShadowEffect>;
    qgraphicsdropshadoweffect_stylists["offset"]
        = &ElementStyler::setFloatOffset<QGraphicsDropShadowEffect>;
    qgraphicsdropshadoweffect_stylists["blur"]
        = &ElementStyler::setFloatBlurRadius<QGraphicsDropShadowEffect>;
    stylists["QGraphicsDropShadowEffect"] = qgraphicsdropshadoweffect_stylists;
}

void ElementStyler::styleElement(QString element_id,
                                 QString element_class,
                                 QMap<QString, QString> element_properties)
{
    if (!canStyleElement(element_class)) {
        qDebug() << "Unable to style element" << element_id << "of class" << element_class;
        return;
    }

    QMap<QString, ElementStylist> class_stylists = stylists.value(element_class);
    for (const QString &property : element_properties.keys()) {
        if (property == "id") {
            continue;
        }

        if (!class_stylists.contains(property)) {
            qDebug() << "Unhandled property" << property << "for element class" << element_class;
            continue;
        }
        ElementStylist styler = class_stylists[property];
        (this->*styler)(element_id, element_properties[property]);
    }
}

bool ElementStyler::canStyleElement(QString element_class)
{
    return stylists.contains(element_class);
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
