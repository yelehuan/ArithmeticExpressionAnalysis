#include "operatortypereader.h"
#include "QVector"

QVector<QChar> OperatorTypeReader::gPriorityTable;
bool OperatorTypeReader::gInit = initVector();
QMap<QString, FUNCTION> OperatorTypeReader::gFunctionsMap;
bool OperatorTypeReader::gFuncMapInit = initFuncMap();
bool OperatorTypeReader::initVector()
{
    gPriorityTable.clear();
    gPriorityTable.append('+');
    gPriorityTable.append('-');
    gPriorityTable.append('*');
    gPriorityTable.append('/');
    gPriorityTable.append('%');
    return true;
}

int OperatorTypeReader::setPriority(QString text)
{
    int index = -1;
    if (!text.isEmpty()) {
        index = gPriorityTable.indexOf(text.at(0));
    }
    return index;
}

bool OperatorTypeReader::initFuncMap()
{
    gFunctionsMap.clear();
    gFunctionsMap.insert("+", &OperatorTypeReader::additionOperator);
    gFunctionsMap.insert("-", &OperatorTypeReader::subtractionOperator);
    gFunctionsMap.insert("*", &OperatorTypeReader::multiplicationOperator);
    gFunctionsMap.insert("/", &OperatorTypeReader::divisionOperator);
    gFunctionsMap.insert("%", &OperatorTypeReader::moduloOperation);
    return true;
}

FUNCTION OperatorTypeReader::getFunction(QString text)
{
    if (gFunctionsMap.contains(text)) {
        return gFunctionsMap.value(text);
    }
    return Q_NULLPTR;
}

void OperatorTypeReader::setPriority(int index)
{
    mPriority = index;
}

int OperatorTypeReader::getPriority()
{
    return mPriority;
}

int OperatorTypeReader::comparePriority(OperatorTypeReader &other)
{
    int result = 0;
    int otherProiority = other.getPriority();
    if (mPriority == otherProiority) {
        result = 0;
    } else if (mPriority > otherProiority) {
        result = 1;
    } else {
        result = -1;
    }
    return result;
}

QString OperatorTypeReader::calculate(QString number1, QString number2)
{
    FUNCTION funPtr = getFunction(getText());
    return (this->*funPtr)(number1, number2);
}

///
/// \brief OperatorTypeReader::AdditionOperator
/// \param number1
/// \param number2
/// \return
///加法
QString OperatorTypeReader::additionOperator(QString number1, QString number2)
{
    return QString("%1").arg(number1.toDouble() + number2.toDouble());
}

///
/// \brief OperatorTypeReader::subtractionOperator
/// \param number1
/// \param number2
/// \return
///减法
QString OperatorTypeReader::subtractionOperator(QString number1, QString number2)
{
    return QString("%1").arg(number1.toDouble() - number2.toDouble());
}

///
/// \brief OperatorTypeReader::multiplicationOperator
/// \param number1
/// \param number2
/// \return
///乘法
QString OperatorTypeReader::multiplicationOperator(QString number1, QString number2)
{
    return QString("%1").arg(number1.toDouble() * number2.toDouble());
}

///
/// \brief OperatorTypeReader::divisionOperator
/// \param number1
/// \param number2
/// \return
///除法
QString OperatorTypeReader::divisionOperator(QString number1, QString number2)
{
    QString result;
    if (number2.toInt() == 0) {
        return QString("-99999999");
    } else {
        result = QString("%1").arg(number1.toDouble() / number2.toDouble());
    }
    return result;
}

///
/// \brief OperatorTypeReader::moduloOperation
/// \param number1
/// \param number2
/// \return
///模运算
QString OperatorTypeReader::moduloOperation(QString number1, QString number2)
{
    QString result;
    if (number2.toInt() == 0) {
        result = QString("-99999999");
    } else {
        result = QString("%1").arg(number1.toInt() % number2.toInt());
    }
    return result;
}

OperatorTypeReader::OperatorTypeReader(QObject *parent)
    : Element(parent)
    , mPriority(-1)
{
}

OperatorTypeReader::OperatorTypeReader(QString &text, int index, ElementType type, QObject *parent)
    : Element(text, index, type, parent)
    , mPriority(-1)
{
    setPriority(OperatorTypeReader::setPriority(text));
}


