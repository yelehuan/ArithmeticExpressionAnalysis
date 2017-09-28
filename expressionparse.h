#ifndef EXPRESSIONPARSE_H
#define EXPRESSIONPARSE_H

#include <QObject>
#include <QString>

class Element;
class ExpressionParse : public QObject
{
    Q_OBJECT
public:
    explicit ExpressionParse(QObject *parent = 0);
    bool expressionExcute(QString& strExpression, QString &res);
signals:

public slots:
private:
    void lexicalAnalysis(QString strExpression, QList<Element*>& resultArray);
    bool grammarAnalysis(QList<Element*>& elements);
    bool semanticAnalysis(QList<Element*>& elements, QString& strResult);
    void garbageCollection(QList<Element*>& elements);
    Element* produceCalculate(QStack<Element*>& operatorNumStack, QStack<Element*>& operatorStack);
private:
    QString mExpressionContext;
};

#endif // EXPRESSIONPARSE_H
