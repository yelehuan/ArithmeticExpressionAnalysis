#include "functiontypereader.h"

FunctionTypeReader::FunctionTypeReader(QString &text, int index, Element::ElementType type, QObject *parent)
    : Element(text, index, type, parent)
{

}

FunctionTypeReader::FunctionTypeReader(QObject *parent)
    : Element(parent)
{

}
