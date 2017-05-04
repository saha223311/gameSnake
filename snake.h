#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>

#include <QList>

#include "structures.h"

class Snake : public QObject
{
    Q_OBJECT
public:
    enum Status { INCREASED, LIVE, WIN, DEAD };
    enum Direction { LEFT, UP, RIGHT, DOWN };

    explicit Snake(Options* options, QObject *parent = 0);

    void Move();
    void Increase();

    Coordinate nextMove();

    Coordinate getHead() const;
    Coordinate getBack() const;

    void setCoordinates(QList<Coordinate> coordinates);
    void setDirection(Snake::Direction direction);
    void setStatus(Snake::Status status);

    const QList<Coordinate>& getCoordinates() const;
    Snake::Direction getDirection() const;
    Snake::Status getStatus() const;

private:
    Status m_status = LIVE;
    Direction m_direction = RIGHT;
    QList<Coordinate> m_body;

    Options* m_options;
};

#endif // SNAKE_H
