#include "elementreadfactory.h"
#include "element.h"
#include "numbertypereader.h"
#include "functiontypereader.h"
#include "operatortypereader.h"


ElementReadFactory::ElementReadFactory(QString &strExpression, QObject *parent)
    : QObject(parent)
{
    mExpressionContext = strExpression;
    mSplitChar.clear();
    mSplitChar.insert('(');
    mSplitChar.insert(')');
    mSplitChar.insert(',');

    mOperator.clear();
    mOperator.insert('+');
    mOperator.insert('-');
    mOperator.insert('*');
    mOperator.insert('/');
    mOperator.insert('%');

    mStopChar.clear();
    mStopChar.insert('+');
    mStopChar.insert('-');
    mStopChar.insert('*');
    mStopChar.insert('/');
    mStopChar.insert('%');
    mStopChar.insert('<');
    mStopChar.insert('>');
    mStopChar.insert('=');
    mStopChar.insert('&');
    mStopChar.insert('|');
    mStopChar.insert('?');
    mStopChar.insert(':');
    mStopChar.insert('#');
    mStopChar.insert('$');
    mStopChar.insert('(');
    mStopChar.insert(')');
    mStopChar.insert(',');
    mStopChar.insert('[');
    mStopChar.insert(']');
    mStopChar.insert('\"');
    mStopChar.insert('\r');
    mStopChar.insert('\t');
    mStopChar.insert('\n');
}

Element *ElementReadFactory::createElement(int startPos)
{
    int count = mExpressionContext.count();
    Element *resultElement = Q_NULLPTR;
    if (startPos >= 0 && startPos < count) {
        QChar ch = mExpressionContext.at(startPos);
        if (ch.isDigit()) {
            resultElement = getNumberType(startPos);
        } else if (ch == '$') {
            resultElement = getFunctionType(startPos);
        } else if (mSplitChar.contains(ch)) {
            resultElement = new FunctionTypeReader(QString(ch), startPos, Element::ETSPLITOR);
        } else if (mOperator.contains(ch)) {
            resultElement = new OperatorTypeReader(QString(ch), startPos, Element::ETOPERATOR);
        } else {
            resultElement = getVariableType(startPos);
        }
    }

    return resultElement;
}

Element *ElementReadFactory::getNumberType(int startPos)
{
    QString elementText;
    elementText.clear();
    QChar ch;
    Element *numberTypeElement = Q_NULLPTR;
    int count = mExpressionContext.count();
    for (int pos = startPos ; pos <= count; ++pos) {
        if (pos == count) {
            numberTypeElement = new NumberTypeReader(elementText, pos - 1, Element::ETDOUBLE);
            break;
        }
        ch = mExpressionContext.at(pos);
        if (ch.isDigit() || ch == '.') {
            elementText.append(ch);
        } else {
            numberTypeElement = new NumberTypeReader(elementText, pos - 1, Element::ETDOUBLE);
            break;
        }
    }
    return numberTypeElement;
}

Element *ElementReadFactory::getFunctionType(int startPos)
{
    QString elementText;
    elementText.clear();
    QChar ch;
    Element *functionTypeElement = Q_NULLPTR;
    int count = mExpressionContext.count();
    for (int pos = startPos + 1; pos <= count; ++pos) {
        if (pos == count) {
            functionTypeElement = new FunctionTypeReader(elementText, pos, Element::ETFUNCTION);
            break;
        }
        ch = mExpressionContext.at(pos);
        if (ch != ')') {
            elementText.append(ch);
        } else {
            elementText.append(ch);
            functionTypeElement = new FunctionTypeReader(elementText, pos, Element::ETFUNCTION);
            break;
        }
    }
    return functionTypeElement;
}

Element *ElementReadFactory::getVariableType(int startPos)
{
    QString elementText;
    elementText.clear();
    QChar ch;
    Element *variableTypeElement = Q_NULLPTR;
    int count = mExpressionContext.count();
    for (int pos = startPos; pos <= count; ++pos) {
        if (pos == count) {
            variableTypeElement = new OperatorTypeReader(elementText, pos - 1, Element::ETVARIABLE);
            break;
        }
        ch = mExpressionContext.at(pos);
        if (mStopChar.contains(ch)) {
            variableTypeElement = new OperatorTypeReader(elementText, pos - 1, Element::ETVARIABLE);
            break;
        } else {
            elementText.append(ch);
        }
    }
    return variableTypeElement;
}
