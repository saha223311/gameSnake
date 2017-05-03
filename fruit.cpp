#include "fruit.h"

#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>

Fruit::Fruit(Options *options, QObject *parent)
    : QObject(parent), m_options(options){
    srand(time(NULL));
}

void Fruit::spawn(const std::list<Coordinate>& body){
    bool flag;
    do{
        flag = true;
        m_fruitCoordinate.X = rand() % m_options->width;
        m_fruitCoordinate.Y = rand() % m_options->height;
        for (auto it : body){
            if (it == m_fruitCoordinate) flag = false;
        }
    } while (!flag);
}



Coordinate Fruit::getCoordinate() const{
    return m_fruitCoordinate;
}

void Fruit::setCoordinate(Coordinate coordinate){
    m_fruitCoordinate = coordinate;
}


