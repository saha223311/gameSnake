#include "snake.h"

Snake::Snake(Options *options , QObject *parent)
    : QObject(parent), m_options(options){
    m_body.push_front(Coordinate(m_options->width / 2, m_options->height / 2));
}

Coordinate Snake::getHead() const{
    return m_body.front();
}

Coordinate Snake::getBack() const{
    return m_body.back();
}

Coordinate Snake::nextMove(){
    Coordinate temp = m_body.front();
    switch (m_direction) {
    case RIGHT:
        temp.X++;
        break;
    case LEFT:
        temp.X--;
        break;
    case UP:
        temp.Y--;
        break;
    case DOWN:
        temp.Y++;
        break;
    default:
        break;
    }
    if (m_options->warpWallMode){
        if (temp.X == -2) temp.X = m_options->width - 1;
        if (temp.X == -1) temp.X = m_options->width - 1;
        if (temp.X == m_options->width) temp.X = 0;
        if (temp.X == m_options->width + 1) temp.X = 0;

        if (temp.Y == -2) temp.Y = m_options->height - 1;
        if (temp.Y == -1) temp.Y = m_options->height - 1;
        if (temp.Y == m_options->height) temp.Y = 0;
        if (temp.Y == m_options->height + 1) temp.Y = 0;
    }

    return Coordinate(temp);
}

void Snake::Move(){
    Coordinate temp = m_body.front();
    m_body.pop_back();
    switch (m_direction) {
    case RIGHT:
        temp.X++;
        break;
    case LEFT:
        temp.X--;
        break;
    case UP:
        temp.Y--;
        break;
    case DOWN:
        temp.Y++;
        break;
    default:
        break;
    }
    if (m_options->warpWallMode){
        if (temp.X == -2) temp.X = m_options->width - 1;
        if (temp.X == -1) temp.X = m_options->width - 1;
        if (temp.X == m_options->width) temp.X = 0;
        if (temp.X == m_options->width + 1) temp.X = 0;

        if (temp.Y == -2) temp.Y = m_options->height - 1;
        if (temp.Y == -1) temp.Y = m_options->height - 1;
        if (temp.Y == m_options->height) temp.Y = 0;
        if (temp.Y == m_options->height + 1) temp.Y = 0;
    }
    m_body.push_front(temp);
}

void Snake::setDirection(Snake::Direction direction){
    m_direction = direction;
}

void Snake::setStatus(Snake::Status status){
    m_status = status;
}

Snake::Direction Snake::getDirection() const{
    return m_direction;
}

Snake::Status Snake::getStatus() const{
    return m_status;
}

const std::list<Coordinate>& Snake::getCoordinates() const{
    return m_body;
}

void Snake::Increase(){
    Coordinate temp = m_body.front();

    switch (m_direction) {
    case RIGHT:
        temp.X++;
        break;
    case LEFT:
        temp.X--;
        break;
    case UP:
        temp.Y--;
        break;
    case DOWN:
        temp.Y++;
        break;
    default:
        break;
    }

    if (m_options->warpWallMode){
        if (temp.X == -2) temp.X = m_options->width - 1;
        if (temp.X == -1) temp.X = m_options->width - 1;
        if (temp.X == m_options->width) temp.X = 0;
        if (temp.X == m_options->width + 1) temp.X = 0;

        if (temp.Y == -2) temp.Y = m_options->height - 1;
        if (temp.Y == -1) temp.Y = m_options->height - 1;
        if (temp.Y == m_options->height) temp.Y = 0;
        if (temp.Y == m_options->height + 1) temp.Y = 0;
    }
    m_body.push_front(temp);
}
