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
    QFile file("./media/layouts/lobby.spriteui");
    file.open(QIODevice::ReadOnly);
    loader.loadDocument(file.readAll());
    QWidget *foo = loader.ui();
    QLabel *lbl = foo->findChild<QLabel *>("lobby_text");
    lbl->setText("SomeText");
    foo->show();

    return app.exec();
}
