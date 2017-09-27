#include "stringtypereader.h"

StringTypeReader::StringTypeReader(QObject *parent)
    : Element(parent)
{

}

StringTypeReader::StringTypeReader(QString &text, int index, ElementType type, QObject *parent)
    : Element(text, index, type, parent)
{

}
