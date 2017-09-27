#ifndef FUNCTIONTYPEREADER_H
#define FUNCTIONTYPEREADER_H

#include <QObject>
#include "element.h"

class FunctionTypeReader : public Element
{
public:
    FunctionTypeReader(QString& text, int index, ElementType type, QObject *parent = 0);
    FunctionTypeReader(QObject *parent = 0);
};

#endif // FUNCTIONTYPEREADER_H
