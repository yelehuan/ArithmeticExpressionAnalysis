#ifndef EXPRESSIONREADER_H
#define EXPRESSIONREADER_H

#include <QObject>

class ExpressionReader : public QObject
{
    Q_OBJECT
public:
    explicit ExpressionReader(QObject *parent = 0);

signals:

public slots:
};

#endif // EXPRESSIONREADER_H