#include "element.h"

Element::Element(QObject *parent) : QObject(parent)
{

}

Element::Element(QString &text, int index, Element::ElementType type, QObject *parent)
    : mText(text)
    , mIndex(index)
    , mType(type)
    , QObject(parent)
{

}

void Element::setText(QString &text)
{
    mText = text;
}

QString Element::getText()
{
    return mText;
}

void Element::setType(Element::ElementType type)
{
    mType = type;
}

Element::ElementType Element::getType()
{
    return mType;
}

void Element::setIndex(int index)
{
    mIndex = index;
}

int Element::getIndex()
{
    return mIndex;
}
