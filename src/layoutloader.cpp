#include "layoutloader.h"
#include "widgetbuilder.h"

#include <QDebug>

LayoutLoader::LayoutLoader(QObject *parent)
    : QObject{parent}
{}

void LayoutLoader::loadDocument(const QByteArray file)
{
    reset();
    LayoutParseError error;
    QDomDocument::ParseResult result = document.setContent(file);
    if (!result) {
        error.error = LayoutParseError::XMLError;
        QString l_string("Error: %1\nLine: %2\nColumn%3");
        error.xml_message = l_string.arg(result.errorMessage,
                                         QString::number(result.errorLine),
                                         QString::number(result.errorColumn));
        emit errorOccured(error);
        return;
    }

    QDomNode version_node = document.firstChild();
    if (version_node.isNull() || !version_node.hasAttributes()) {
        error.error = LayoutParseError::NoChildNode;
        emit errorOccured(error);
        return;
    }
    VersionInformation metadata = parseVersion(version_node);

    if (metadata.version != COMPATIBLE_VERSION) {
        error.error = LayoutParseError::VersionUnsupported;
        emit errorOccured(error);
        return;
    }

    if (metadata.style != COMPATIBLE_STYLE) {
        error.error = LayoutParseError::StyleUnsupported;
        emit errorOccured(error);
        return;
    }

    qInfo().noquote() << "Loading" << metadata.toString();
    builder = new WidgetBuilder(this);
    builder->createRootWidget(version_node.firstChild());
}

QWidget *LayoutLoader::ui()
{
    return builder->ui();
}

void LayoutLoader::reset()
{
    document.clear();
}

LayoutLoader::VersionInformation LayoutLoader::parseVersion(QDomNode node)
{
    VersionInformation version;
    version.layout = node.nodeName();
    QDomNamedNodeMap attributes = node.attributes();

    if (attributes.contains("style")) {
        version.style = attributes.namedItem("style").nodeValue().toUpper();
    }
    if (attributes.contains("version")) {
        version.version = attributes.namedItem("version").nodeValue().toInt();
    }
    return version;
}
