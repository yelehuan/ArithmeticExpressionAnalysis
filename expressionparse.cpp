#include "expressionparse.h"
#include "elementreadfactory.h"
#include "element.h"
#include "operatortypereader.h"

#include <QSet>
#include <QDebug>
#include <QStack>
#include <QJSEngine>

ExpressionParse::ExpressionParse(QObject *parent) : QObject(parent)
{

}

bool ExpressionParse::expressionExcute(QString& strExpression)
{
    //test 10*2+3/5-(100+2)+200  10*(2+(3/5-(100+2)+200)) 10*(2+(3/5-(100+2)*10+200*5))
    //(10*(2+3/5-(100+2)*10+200*5/5)+100-200)+2
    strExpression = QStringLiteral("10*(2+(3/5-(100+2)+200))");
    QJSEngine myEngine;
    QJSValue three = myEngine.evaluate(strExpression);
    qDebug() << "js Result: " << three.toNumber() << endl;
    //
    mExpressionContext = strExpression;
    //词法分析
    QList<Element*> resultElement;
    bool success= false;
    lexicalAnalysis(mExpressionContext, resultElement);
    //test
    for (int i = 0; i < resultElement.count(); ++i) {
        qDebug() << "text: " << resultElement.at(i)->getText() << endl;
    }
    //-----
    if (resultElement.isEmpty()) return success;
    //语法分析
    if (!grammarAnalysis(resultElement)) return success;
    //语义分析
    QString resultStr;
    success = semanticAnalysis(resultElement, resultStr);
    qDebug() << "result: " << resultStr << endl;
    //释放空间
    garbageCollection(resultElement);
    return success;
}


///
/// \brief ExpressionParse::lexicalAnalysis
/// \param strExpression
/// \param resultArray
/// \return
///词法分析，将表达式扫描分解成词素
void ExpressionParse::lexicalAnalysis(QString strExpression, QList<Element*>& resultArray)
{
    int charCount = strExpression.count();
    ElementReadFactory *elementFactory = new ElementReadFactory(strExpression);
    for (int position = 0; position < charCount; ++position) {
        Element *elementPtr = elementFactory->createElement(position);
        if (elementPtr != Q_NULLPTR) {
            resultArray.append(elementPtr);
            position = elementPtr->getIndex();
        }
    }
    if (elementFactory != Q_NULLPTR) {
        delete elementFactory;
        elementFactory = Q_NULLPTR;
    }
}

///
/// \brief ExpressionParse::grammarAnalysis
/// \param elements
/// \return false: 语法有误 true: 语法正确
///语法分析
bool ExpressionParse::grammarAnalysis(QList<Element *> &elements)
{
    Q_UNUSED(elements);
    return true;
}

///
/// \brief ExpressionParse::semanticAnalysis
/// \param elements
/// \param strResult
/// \return
///语义分析，将词素按照算术优先级进行运算
bool ExpressionParse::semanticAnalysis(QList<Element*> &elements, QString& strResult)
{
    if (elements.isEmpty()) return false;
    //追加一个分号表示结尾标志
    elements.append(new OperatorTypeReader(QString(';')));
    int elementCount = elements.count();
    QStack<Element*> operatorNumbersStack;
    QStack<Element*> operatorStack;
    Element *splitChar = new OperatorTypeReader(QString('@'));
    operatorStack.push(splitChar);
    for (int elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
        Element *element = elements.at(elementIndex);
        if (element == Q_NULLPTR) return false;
        Element::ElementType type = element->getType();
        if (type == Element::ETVARIABLE || type == Element::ETDOUBLE) {
            operatorNumbersStack.push_back(element);
            continue;
        }
        QString currentElementText = element->getText();
        if (currentElementText == QString("(")) {
            operatorStack.push_back(splitChar);
            continue;
        }
        if (currentElementText == QString(")")) {
            //计算结果
            while (operatorStack.top()->getText() != QString("@")) {
                Element* tempRes = produceCalculate(operatorNumbersStack, operatorStack);
                if (tempRes == Q_NULLPTR) return false;
                operatorNumbersStack.push_back(tempRes);
            }
            //将代表左括号的@符号弹出栈
            operatorStack.pop();
            continue;
        }
        if (currentElementText == QString(";")) {
            //计算结果
            while (operatorStack.count() > 1) {
                if (operatorStack.top()->getText() == QString("@")) {
                    operatorStack.pop();
                    continue;
                }
                Element* tempRes = produceCalculate(operatorNumbersStack, operatorStack);
                if (tempRes == Q_NULLPTR) return false;
                operatorNumbersStack.push_back(tempRes);
            }
            if (operatorNumbersStack.top() != Q_NULLPTR) {
                strResult = operatorNumbersStack.top()->getText();
            }
            return true;
        }
        //判断当前的操作符栈是否有操作符
        OperatorTypeReader *currentElement = qobject_cast<OperatorTypeReader*>(element);
        OperatorTypeReader *topElement = qobject_cast<OperatorTypeReader*>(operatorStack.top());
        if (topElement->getText() != QString('@')) {
            //有操作符, 判断栈中操作符和当前操作符的优先级
            int equal = topElement->comparePriority(*currentElement);
            if (equal == 1 || equal == 0) {
                //计算结果
                do {
                    Element* tempRes = produceCalculate(operatorNumbersStack, operatorStack);
                    if (tempRes == Q_NULLPTR) return false;
                    operatorNumbersStack.push_back(tempRes);
                } while (operatorStack.top()->getText() != QString("@"));
                operatorStack.push_back(element);
            } else if (equal == -1) {
                operatorStack.push_back(element);
            }
            continue;
        }
        operatorStack.push_back(element);
    }
    if (splitChar != Q_NULLPTR) {
        delete splitChar;
        splitChar = Q_NULLPTR;
    }
    return false;
}

void ExpressionParse::garbageCollection(QList<Element*>& elements)
{
    int count = elements.count();
    for (int elementIndex = 0; elementIndex < count; ++elementIndex) {
        Element *item = elements.at(elementIndex);
        if (item != Q_NULLPTR) {
            //qDebug() << "delete Item: " << item->getText() << endl;
            delete item;
            item = Q_NULLPTR;
        }
    }
}

Element* ExpressionParse::produceCalculate(QStack<Element *> &operatorNumStack, QStack<Element *> &operatorStack)
{
    Element *number2 = operatorNumStack.pop();
    Element *number1 = operatorNumStack.pop();
    Element *operatorElement = operatorStack.pop();
    qDebug() << "num1 : " << number1->getText() << "num2: " << number2->getText() << "operator: "<<  operatorElement->getText()<< endl;
    OperatorTypeReader *oper = qobject_cast<OperatorTypeReader*>(operatorElement);
    if (oper == Q_NULLPTR) return Q_NULLPTR;
    QString tempStrRes = oper->calculate(number1->getText(), number2->getText());
    number1->setText(tempStrRes);
    return number1;
}

