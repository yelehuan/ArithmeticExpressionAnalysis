#ifndef NUMBERTYPEREADER_H
#define NUMBERTYPEREADER_H

#include <QObject>
#include "element.h"

class NumberTypeReader : public Element
{
public:
    explicit NumberTypeReader(QObject *parent = 0);
    NumberTypeReader(QString& text, int index, ElementType type, QObject *parent = 0);
};

#endif // NUMBERTYPEREADER_H
