#include "layoutloader.h"
#include "elementbuilder.h"

#include <QDebug>

LayoutLoader::LayoutLoader(QObject *parent)
    : QObject{parent}
{
    builder = new ElementBuilder(this);
}

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
        return emit errorOccured(error);
    }

    QDomNode version_node = document.firstChild();
    if (version_node.isNull() || !version_node.hasAttributes()) {
        error.error = LayoutParseError::NoChildNode;
        return emit errorOccured(error);
    }
    VersionInformation metadata = parseVersion(version_node);

    if (metadata.version != COMPATIBLE_VERSION) {
        error.error = LayoutParseError::VersionUnsupported;
        return emit errorOccured(error);
    }

    if (metadata.style != COMPATIBLE_STYLE) {
        error.error = LayoutParseError::StyleUnsupported;
        return emit errorOccured(error);
    }

    qInfo().noquote() << "Loading" << metadata.toString();
    builder->createRootWidget(version_node.firstChild());
}

QWidget *LayoutLoader::ui()
{
    return builder->ui();
}

void LayoutLoader::reset()
{
    document.clear();
    builder->deleteLater();
    builder = new ElementBuilder(this);
}

LayoutLoader::VersionInformation LayoutLoader::parseVersion(QDomNode node)
{
    VersionInformation version;
    version.layout = node.nodeName();
    QDomNamedNodeMap properties = node.attributes();

    if (properties.contains("style")) {
        version.style = properties.namedItem("style").nodeValue().toUpper();
    }
    if (properties.contains("version")) {
        version.version = properties.namedItem("version").nodeValue().toInt();
    }
    return version;
}
