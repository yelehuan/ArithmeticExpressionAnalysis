#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

class Element : public QObject
{
    Q_OBJECT
public:
    typedef enum ElementType {
        ETNONE,
        ETSTRING,
        ETBOOLEAN,
        ETINT,
        ETLONG,
        ETFLOAT,
        ETDOUBLE,
        ETDATE,
        ETVARIABLE,
        ETOPERATOR,
        ETFUNCTION,
        ETSPLITOR
    }ElementType;
    explicit Element(QObject *parent = 0);
    explicit Element(QString& text, int index = -1, ElementType type = ETNONE, QObject *parent = 0);


    void setText(QString& text);
    QString getText();
    void setType(ElementType type);
    ElementType getType();
    void setIndex(int index);
    int getIndex();

signals:

public slots:
private:
    QString mText;
    int mIndex;
    ElementType mType;
};

#endif // ELEMENT_H
