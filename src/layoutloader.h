#ifndef LAYOUTLLOADER_H
#define LAYOUTLLOADER_H

#include <QDomDocument>
#include <QDomNode>
#include <QObject>

#include "layoutparseerror.h"

class ElementBuilder;

class LayoutLoader : public QObject
{
    struct VersionInformation
    {
        QString layout;
        QString style;
        int version;

        QString toString()
        {
            return QString("layout %1 using style %2 at ui version %3")
                .arg(layout, style, QString::number(version));
        }
    };

    Q_OBJECT
public:
    explicit LayoutLoader(QObject *parent = nullptr);

Q_SIGNALS:
    void errorOccured(LayoutParseError error);
    void loadingDone(QWidget *widget);

public Q_SLOTS:
    void loadDocument(const QByteArray file);
    QWidget *ui();

private:
    VersionInformation parseVersion(QDomNode node);
    void reset();

    ElementBuilder *builder;
    QDomDocument document;
    const int COMPATIBLE_VERSION = 1;
    const QString COMPATIBLE_STYLE = "SPRITECHAT";
};

#endif // LAYOUTLLOADER_H
