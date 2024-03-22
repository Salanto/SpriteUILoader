#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QWidget>

#include "layoutloader.h"
#include "managementui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ManageMentUI *ui = new ManageMentUI();
    ui->show();

    return app.exec();
}
