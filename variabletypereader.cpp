#include "variabletypereader.h"

VariableTypeReader::VariableTypeReader(QObject *parent)
    : Element(parent)
{

}

VariableTypeReader::VariableTypeReader(QString &text, int index, Element::ElementType type, QObject *parent)
    : Element(text, index, type, parent)
{

}
