#ifndef OPERATORTYPEREADER_H
#define OPERATORTYPEREADER_H

#include <QObject>
#include <QMap>
#include "element.h"

class OperatorTypeReader;
typedef QString(OperatorTypeReader::*FUNCTION)(QString, QString);

class OperatorTypeReader : public Element
{
    Q_OBJECT

public:
    OperatorTypeReader(QObject *parent = 0);
    OperatorTypeReader(QString& text, int index = -1, ElementType type = Element::ETOPERATOR, QObject *parent = 0);
    static bool initVector();
    static int setPriority(QString text);
    static bool initFuncMap();
    static FUNCTION getFunction(QString text);
    void setPriority(int index);
    int getPriority();
    int comparePriority(OperatorTypeReader &other);
    QString calculate(QString number1, QString number2);
private:
    QString additionOperator(QString number1, QString number2);
    QString subtractionOperator(QString number1, QString number2);
    QString multiplicationOperator(QString number1, QString number2);
    QString divisionOperator(QString number1, QString number2);
    QString moduloOperation(QString number1, QString number2);
private:
    int mPriority;
    static QVector<QChar> gPriorityTable;
    static bool gInit;
    static QMap<QString, FUNCTION> gFunctionsMap;
    static bool gFuncMapInit;
};

#endif // OPERATORTYPEREADER_H
