#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QWidget>

#include "xmlinputwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    XMLInputWindow *ui = new XMLInputWindow();
    ui->show();

    return app.exec();
}
