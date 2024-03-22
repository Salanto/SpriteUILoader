#include "managementui.h"
#include "layoutloader.h"

#include <QDebug>
#include <QErrorMessage>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

ManageMentUI::ManageMentUI(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);
    QLabel *lbl = new QLabel(this);
    lbl->setText("Enter XML here.");
    edit = new QTextEdit(this);
    edit->setPlaceholderText("Add XML here!");
    QPushButton *button = new QPushButton(this);
    button->setText("Spawn UI");
    layout->addWidget(lbl);
    layout->addWidget(edit);
    layout->addWidget(button);

    loader = new LayoutLoader(this);
    connect(loader, &LayoutLoader::errorOccured, this, &ManageMentUI::on_error);
    connect(button, &QPushButton::clicked, this, &ManageMentUI::on_pushbutton_pressed);
}

void ManageMentUI::on_pushbutton_pressed()
{
    loader->loadDocument(edit->toPlainText().toUtf8());
    QWidget *ui = loader->ui();
    if (ui == nullptr) {
        return;
    }
    ui->setAttribute(Qt::WA_DeleteOnClose);
    QLabel *lbl = ui->findChild<QLabel *>("lobby_text");
    lbl->setText("Some Text");
    ui->show();
}

void ManageMentUI::on_error(LayoutParseError error)
{
    QErrorMessage *message = new QErrorMessage(nullptr);
    message->setAttribute(Qt::WA_DeleteOnClose);
    message->showMessage(error.errorString());
}
