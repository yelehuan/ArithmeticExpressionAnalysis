#ifndef SPLITORTYPEREADER_H
#define SPLITORTYPEREADER_H

#include <QObject>
#include "element.h"

class SplitorTypeReader : public Element
{
public:
    SplitorTypeReader(QObject *parent = 0);
    SplitorTypeReader(QString& text, int index, ElementType type, QObject *parent = 0);
};

#endif // SPLITORTYPEREADER_H
