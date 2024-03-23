#ifndef ELEMENTSTYLER_H
#define ELEMENTSTYLER_H

#include <QMap>
#include <QObject>

class QWidget;

class ElementStyler : public QObject
{
    Q_OBJECT
public:
    explicit ElementStyler(QObject *parent = nullptr, QWidget *full_ui = nullptr);
    void styleElement(QString element_id,
                      QString element_class,
                      QMap<QString, QString> element_properties);

private:
    bool canStyleElement(QString element_class);

    using ElementStylist = void (ElementStyler::*)(QString, QString);
    QMap<QString, QMap<QString, ElementStylist>> stylists;
    QWidget *ui;

    template<typename T>
    void setText(QString element_id, QString text);
};

#endif // ELEMENTSTYLER_H
