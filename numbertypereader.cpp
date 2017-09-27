#include "numbertypereader.h"

NumberTypeReader::NumberTypeReader(QObject *parent)
    : Element(parent)
{

}

NumberTypeReader::NumberTypeReader(QString& text, int index, ElementType type, QObject *parent)
    : Element(text, index, type, parent)
{

}
