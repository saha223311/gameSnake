#ifndef FRUIT_H
#define FRUIT_H

#include <QObject>

#include <time.h>
#include <QList>

#include "structures.h"

class Fruit : public QObject{
    Q_OBJECT
public:
    explicit Fruit(Options* options, QObject *parent = 0);

    void spawn(const QList<Coordinate> &body);

    void setCoordinate(Coordinate coordinate);
    Coordinate getCoordinate() const;

private:
    Coordinate m_fruitCoordinate;
    Options* m_options;
};

#endif // FRUIT_H
