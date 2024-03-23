#include "elementstyler.h"
#include <QDebug>

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
    stylists["QLabel"] = qlabel_stylists;
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
        qDebug() << "Unable to locate element" << element_id << "for text application";
        return;
    }
    pointer->setText(text);
}
