#ifndef ELEMENTREADER_H
#define ELEMENTREADER_H

#include <QObject>

class ElementReader : public QObject
{
    Q_OBJECT
public:
    explicit ElementReader(QObject *parent = 0);

signals:

public slots:
};

#endif // ELEMENTREADER_H