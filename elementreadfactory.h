#ifndef ELEMENTREADFACTORY_H
#define ELEMENTREADFACTORY_H

#include <QObject>
#include <QSet>
class Element;
class ElementReadFactory : public QObject
{
    Q_OBJECT
public:
    explicit ElementReadFactory(QString &strExpression, QObject *parent = 0);
    Element* createElement(int startPos);
signals:

public slots:
private:
    Element *getNumberType(int startPos);
    Element *getFunctionType(int startPos);
    Element *getVariableType(int startPos);
private:
    QSet<QChar> mSplitChar;
    QSet<QChar> mOperator;
    QSet<QChar> mStopChar;
    QString mExpressionContext;
};

#endif // ELEMENTREADFACTORY_H
