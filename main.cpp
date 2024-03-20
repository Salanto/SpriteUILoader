#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QWidget>

#include "layoutloader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LayoutLoader loader(&app);
    QFile file("./lobby.ui");
    file.open(QIODevice::ReadOnly);
    loader.loadDocument(file.readAll());
    QWidget *foo = loader.ui();
    qDebug() << foo;
    QLabel *bar = foo->findChild<QLabel *>("lobby_text");
    bar->setText("Hello World.");
    QLabel *xir = foo->findChild<QLabel *>("lobby_text_2");
    xir->setText("Another hello!");

    foo->show();

    qDebug() << foo->children();

    return app.exec();
}
