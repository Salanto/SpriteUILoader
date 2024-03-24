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
    QMap<QString, QMap<QString, ElementStylist>> styler;
    QWidget *ui;

    template<typename T>
    void setText(QString element_id, QString text);

    template<typename T>
    void setPlaceholderText(QString element_id, QString placeholder);

    template<typename T>
    void setPixmap(QString element_id, QString image_path);

    template<typename T>
    void setFixedSize(QString element_id, QString dimensions);

    template<typename T>
    void move(QString element_id, QString position);

    template<typename T>
    void setColor(QString element_id, QString color);

    template<typename T>
    void setFloatStrength(QString element_id, QString strength);

    template<typename T>
    void setFloatOffset(QString element_id, QString offset);

    template<typename T>
    void setFloatBlurRadius(QString element_id, QString radius);

    template<typename T>
    void setFloatOpacity(QString element_id, QString opacity);

    template<typename T>
    void setVisible(QString element_id, QString visible);

    template<typename T>
    void setEnabled(QString element_id, QString enabled);

    template<typename T>
    void setToolTip(QString element_id, QString tooltip);

    template<typename T>
    void setCheckable(QString element_id, QString checkable);

    template<typename T>
    void setChecked(QString element_id, QString checked);

    template<typename T>
    void setEditable(QString element_id, QString editable);

    template<typename T>
    void setFrame(QString element_id, QString frame_enabled);

    template<typename T>
    void addItems(QString element_id, QString items);

    template<typename T>
    void setMinimum(QString element_id, QString minimum_value);

    template<typename T>
    void setMaximum(QString element_id, QString maximum_value);

    template<typename T>
    void setRange(QString element_id, QString range_list);

    template<typename T>
    void setSuffix(QString element_id, QString suffix);

    template<typename T>
    void setPrefix(QString element_id, QString suffix);
};

#endif // ELEMENTSTYLER_H
