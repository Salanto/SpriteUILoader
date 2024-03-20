#include "layoutparseerror.h"

QString LayoutParseError::errorString() const
{
    switch (error) {
    case NoError:
        return "no error occured";
    case XMLError:
        return xml_message;
    case NoChildNode:
        return "main entry has no child nodes or attributes";
    case VersionUnsupported:
        return "file version is not supported";
    case StyleUnsupported:
        return "used style is not supported.";
    default:
        return "unknown error occured.";
    }
}
