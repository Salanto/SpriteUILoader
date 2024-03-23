#ifndef XMLINPUTWINDOW_H
#define XMLINPUTWINDOW_H

#include <QTextEdit>
#include <QWidget>
#include "layoutloader.h"

class XMLInputWindow : public QWidget
{
    Q_OBJECT
public:
    explicit XMLInputWindow(QWidget *parent = nullptr);

private slots:
    void on_pushbutton_pressed();
    void on_error(LayoutParseError error);

private:
    QTextEdit *edit;
    LayoutLoader *loader;
};

#endif // XMLINPUTWINDOW_H
