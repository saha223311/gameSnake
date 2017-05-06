#ifndef GAME_H
#define GAME_H

#include <QObject>

#include <QGraphicsScene>
#include <QTimer>
#include <QSettings>

#include "snake.h"
#include "fruit.h"
#include "structures.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QGraphicsScene* scene, Options* options, QObject *parent = 0);

    void startGame();

    void setSnakeDirection(Snake::Direction dir);
    void setSnakeStatus(Snake::Status status);

    void setSaveParameters(SaveParameters saveParameters);
    void setDefaultSaveParameters();

    SaveParameters getSaveParameters();

    int getScore();
    int getBestScore();

    Snake::Direction getSnakeDirection() const;

    bool isPaused();
    void pauseGame();
    void continueGame();

    void checkBestScore();

    ~Game();

signals:
    void winGame();
    void loseGame();

    void newScore();
    void saveGame();

    void endMove();
public slots:

private slots:
    void drawSnake();

private:
    QGraphicsScene* m_scene;
    Options* m_options;

    QTimer* m_timer;
    Snake* m_snake;
    Fruit* m_fruit;

    int score;
    int bestScore;

    void checkDead();
    void checkIncreased();
    void checkWin();

    void drawMoveSnake();
    void drawIncreaseSnake();

    void spawnNewFruit();

    void m_gameOver();
    void m_happyEnd();
};

#endif // GAME_H
