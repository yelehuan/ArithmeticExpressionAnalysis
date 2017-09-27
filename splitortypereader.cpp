#include "splitortypereader.h"

SplitorTypeReader::SplitorTypeReader(QObject *parent)
    : Element(parent)
{

}

SplitorTypeReader::SplitorTypeReader(QString &text, int index, Element::ElementType type, QObject *parent)
    : Element(text, index, type, parent)
{

}
