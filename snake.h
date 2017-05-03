#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>

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
    const std::list<Coordinate>& getCoordinates() const;
    void setCoordinates(std::list<Coordinate> coordinates);

    void setDirection(Snake::Direction direction);
    void setStatus(Snake::Status status);

    Snake::Direction getDirection() const;
    Snake::Status getStatus() const;

signals:

public slots:

private:
    Status m_status = LIVE;
    Direction m_direction = RIGHT;
    std::list<Coordinate> m_body;

    Options* m_options;
};

#endif // SNAKE_H
