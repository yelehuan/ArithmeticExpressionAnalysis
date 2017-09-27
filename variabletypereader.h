#ifndef VARIABLETYPEREADER_H
#define VARIABLETYPEREADER_H

#include <QObject>
#include "element.h"

class VariableTypeReader : public Element
{
public:
    VariableTypeReader(QObject *parent = 0);
    VariableTypeReader(QString& text, int index, ElementType type, QObject *parent = 0);
};

#endif // VARIABLETYPEREADER_H
