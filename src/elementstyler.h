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

    template<typename T>
    void setPixmap(QString element_id, QString image_path);

    template<typename T>
    void setFixedSize(QString element_id, QString dimensions);

    template<typename T>
    void move(QString element_id, QString position);

    template<typename T>
    void setColor(QString element_id, QString color);

    template<typename T>
    void setFloatOffset(QString element_id, QString offset);

    template<typename T>
    void setFloatBlurRadius(QString element_id, QString radius);
};

#endif // ELEMENTSTYLER_H
