#ifndef STRINGTYPEREADER_H
#define STRINGTYPEREADER_H

#include <QObject>
#include "element.h"

class StringTypeReader : public Element
{
public:
    StringTypeReader(QObject *parent = 0);
    StringTypeReader(QString& text, int index, ElementType type, QObject *parent = 0);
};

#endif // STRINGTYPEREADER_H
