#ifndef MANAGEMENTUI_H
#define MANAGEMENTUI_H

#include <QTextEdit>
#include <QWidget>
#include "layoutloader.h"

class ManageMentUI : public QWidget
{
    Q_OBJECT
public:
    explicit ManageMentUI(QWidget *parent = nullptr);

private slots:
    void on_pushbutton_pressed();
    void on_error(LayoutParseError error);

private:
    QTextEdit *edit;
    LayoutLoader *loader;
};

#endif // MANAGEMENTUI_H
