#include <QCoreApplication>
#include "expressionparse.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ExpressionParse parse;
    parse.expressionExcute(QString("(20/50)*100"));
    return a.exec();
}
