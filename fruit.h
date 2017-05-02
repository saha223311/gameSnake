#ifndef FRUIT_H
#define FRUIT_H

#include <QObject>

#include "structures.h"

#include <time.h>

class Fruit : public QObject
{
    Q_OBJECT
public:
    explicit Fruit(Options* options, QObject *parent = 0);
    void spawn(const std::list<Coordinate> &body);

    Coordinate getCoordinate() const;

private:
    Coordinate m_fruitCoordinate;

    Options* m_options;
};

#endif // FRUIT_H
