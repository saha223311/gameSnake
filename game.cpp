#include "game.h"

#include <QPixmap>
#include <QGraphicsItem>

Game::Game(QGraphicsScene *scene, Options *options, QObject *parent)
    : QObject(parent), m_scene(scene), m_options(options)
{
    m_snake = new Snake(m_options);
    m_fruit = new Fruit(m_options);
    m_timer = new QTimer;

    connect(m_timer, SIGNAL(timeout()), this, SLOT(drawSnake()));
}

void Game::newGame(){
    score = 0;

    m_scene->addRect(m_snake->getHead().X * m_options->rectSize,
                     m_snake->getHead().Y * m_options->rectSize,
                     m_options->rectSize, m_options->rectSize,
                     QPen(QColor(0, 0, 0, 30)), QBrush(QColor(30,30,30)));

    m_timer->start(170);

    m_fruit->spawn(m_snake->getCoordinates());
    m_scene->addRect(m_fruit->getCoordinate().X * m_options->rectSize,
                     m_fruit->getCoordinate().Y * m_options->rectSize,
                     m_options->rectSize, m_options->rectSize,
                     QPen(QColor(0, 0, 0, 30)), QBrush(QColor(255,99,99)));

    //connect(m_timer, SIGNAL(timeout()), this, SLOT(drawSnake()));
}

void Game::loadGame(){
    score = 0;
    for (auto it : m_snake->getCoordinates()){
        if (it == m_snake->getHead())
            m_scene->addRect(it.X * m_options->rectSize,
                             it.Y * m_options->rectSize,
                             m_options->rectSize, m_options->rectSize,
                             QPen(QColor(0, 0, 0, 30)), QBrush(QColor(30,30,30)));
        else
        m_scene->addRect(it.X * m_options->rectSize,
                         it.Y * m_options->rectSize,
                         m_options->rectSize, m_options->rectSize,
                         QPen(QColor(0, 0, 0, 30)), QBrush(QColor(168,168,168)));
    }


        m_timer->start(170);

        m_scene->addRect(m_fruit->getCoordinate().X * m_options->rectSize,
                         m_fruit->getCoordinate().Y * m_options->rectSize,
                         m_options->rectSize, m_options->rectSize,
                         QPen(QColor(0, 0, 0, 30)), QBrush(QColor(255,99,99)));
}

int Game::getScore(){
    return score;
}

void Game::drawSnake(){

    this->checkDead();
    this->checkIncreased();
    this->checkWin();


    switch (m_snake->getStatus()) {
    case Snake::LIVE:
        this->drawMoveSnake();
        break;

    case Snake::INCREASED:
        score++;
        emit newScore();
        this->spawnNewFruit();
        this->drawIncreaseSnake();
        m_snake->setStatus(Snake::LIVE);
        break;

    case Snake::DEAD:
        this->m_gameOver();
        break;

    case Snake::WIN:
        this->m_happyEnd();
        break;

    default:
        break;
    }
}

void Game::drawMoveSnake(){
    // HEAD<>
       m_scene->removeItem(m_scene->items(QRectF(m_snake->getHead().X * m_options->rectSize + 1,
                                                 m_snake->getHead().Y * m_options->rectSize + 1,
                                                 m_options->rectSize - 2 , m_options->rectSize - 2))[0]);

       m_scene->addRect(m_snake->getHead().X * m_options->rectSize,
                        m_snake->getHead().Y * m_options->rectSize,
                        m_options->rectSize, m_options->rectSize,
                        QPen(QColor(0, 0, 0, 30)), QBrush(QColor(168,168,168)));
       // HEAD</>

    m_scene->removeItem(m_scene->items(QRectF(m_snake->getBack().X * m_options->rectSize + 1,
                                              m_snake->getBack().Y * m_options->rectSize + 1,
                                              m_options->rectSize - 2 , m_options->rectSize - 2))[0]);
    m_snake->Move();
    m_scene->addRect(m_snake->getHead().X * m_options->rectSize,
                     m_snake->getHead().Y * m_options->rectSize,
                     m_options->rectSize, m_options->rectSize,
                     QPen(QColor(0, 0, 0, 30)), QBrush(QColor(30,30,30)));
}

void Game::drawIncreaseSnake(){
    // HEAD<>
        m_scene->removeItem(m_scene->items(QRectF(m_snake->getHead().X * m_options->rectSize + 1,
                                                  m_snake->getHead().Y * m_options->rectSize + 1,
                                                  m_options->rectSize - 2 , m_options->rectSize - 2))[0]);

        m_scene->addRect(m_snake->getHead().X * m_options->rectSize,
                         m_snake->getHead().Y * m_options->rectSize,
                         m_options->rectSize, m_options->rectSize,
                         QPen(QColor(0, 0, 0, 30)), QBrush(QColor(168,168,168)));
        // HEAD</>
    m_snake->Increase();
    m_scene->addRect(m_snake->getHead().X * m_options->rectSize,
                     m_snake->getHead().Y * m_options->rectSize,
                     m_options->rectSize, m_options->rectSize,
                     QPen(QColor(0, 0, 0, 30)), QBrush(QColor(30,30,30)));
}

void Game::checkDead(){
    // DO FOREACH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // КОСТЫЛИ!!!!!
    int k = 0;
    for (auto it : m_snake->getCoordinates()){
        if (it == m_snake->nextMove() && k != 0 && k != m_snake->getCoordinates().size() - 1)
            m_snake->setStatus(Snake::DEAD);
        k++;
    }
    if ((m_snake->nextMove().X < 0) || (m_snake->nextMove().X > m_options->width - 1)
            || (m_snake->nextMove().Y < 0) || (m_snake->nextMove().Y > m_options->height - 1))
        m_snake->setStatus(Snake::DEAD);
}

void Game::checkIncreased(){
    if (m_snake->getHead() == m_fruit->getCoordinate()){
        m_snake->setStatus(Snake::INCREASED);
    }
}

void Game::checkWin(){
    if (m_snake->getCoordinates().size() == m_options->height * m_options->width)
        m_snake->setStatus(Snake::WIN);
}

void Game::spawnNewFruit(){
    m_scene->removeItem(m_scene->items(QRectF(m_fruit->getCoordinate().X * m_options->rectSize + 1,
                                              m_fruit->getCoordinate().Y * m_options->rectSize + 1,
                                              m_options->rectSize - 2 , m_options->rectSize - 2))[1]);
    m_fruit->spawn(m_snake->getCoordinates());

    m_scene->addRect(m_fruit->getCoordinate().X * m_options->rectSize,
                     m_fruit->getCoordinate().Y * m_options->rectSize,
                     m_options->rectSize, m_options->rectSize,
                     QPen(QColor(0, 0, 0, 30)), QBrush(QColor(255,99,99)));

   /* QGraphicsItem* scitem = m_scene->addPixmap(
                QPixmap::fromImage(QImage("E://QtProjects//gameSnake_2_3//fruit.png")));
    scitem->setScale(0.005 * m_options->rectSize / 10);
    scitem->setPos(QPoint(m_fruit->getCoordinate().X * m_options->rectSize,
                          m_fruit->getCoordinate().Y * m_options->rectSize));*/

}

void Game::setSnakeDirection(Snake::Direction dir){
    m_snake->setDirection(dir);
}

void Game::setSnakeStatus(Snake::Status status){
    m_snake->setStatus(status);
}

Snake::Direction Game::getSnakeDirection() const{
    return m_snake->getDirection();
}

void Game::m_gameOver(){
    while (true){}
}

void Game::m_happyEnd(){
    while (true){}
}

bool Game::isPaused(){
    return !(m_timer->isActive());
}

void Game::pauseGame(){
    m_timer->stop();
}

void Game::continueGame(){
    m_timer->start(170);
}

void Game::setSaveParameters(SaveParameters saveParameters){
    m_snake->setCoordinates(saveParameters.snakeCoordinates);
    m_fruit->setCoordinate(saveParameters.fruitCoordinates);
}

SaveParameters Game::getSaveParameters(){
    return SaveParameters(m_snake->getCoordinates(), m_fruit->getCoordinate(), *m_options);
}

Game::~Game(){
    delete m_snake;
    delete m_fruit;
    delete m_timer;
}


