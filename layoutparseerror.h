#ifndef LAYOUTPARSEERROR_H
#define LAYOUTPARSEERROR_H

#include <QString>

struct LayoutParseError
{
    enum ParseError { NoError, XMLError, NoChildNode, VersionUnsupported, StyleUnsupported };

    QString errorString() const;

    QString xml_message;
    ParseError error = NoError;
};

#endif // LAYOUTPARSEERROR_H
