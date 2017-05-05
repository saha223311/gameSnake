#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>
#include <QCloseEvent>
#include <QKeyEvent>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLabel>

#include "game.h"
#include "optionspage.h"
#include "structures.h"
#include "savenamepage.h"


class GamePage : public QWidget
{
    Q_OBJECT
public:
    explicit GamePage(QWidget *parent = 0);

    void startNewGame(OptionsPage* optionsPage);
    void startSavedGame(SaveParameters saveParameters);

    ~GamePage();

signals:
    void backButton();
    void saveGame(SaveParameters);
public slots:
    void updateScore();
    void saveProcess(QString);
    void setSaveNamePage();

    void checkDirection();
private slots:
    void pauseButton();
private:
    QHBoxLayout* m_highButtonLayout;
    QHBoxLayout* m_lowButtonLayout;
    QHBoxLayout* m_viewLayout;
    QVBoxLayout* m_verticalLayout;

    QPushButton* m_back;
    QPushButton* m_pause;
    QPushButton* m_save;

    QLabel* m_score;
    QLabel* m_record;

    QGraphicsScene* m_scene;
    QGraphicsView* m_view;

    Game* m_game;

    Options* m_options;
    SaveNamePage m_saveNamePage;

    Snake::Direction m_direction;
    bool turnDirection = true;

    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent*);

    void createWindow();
    void initilizeGame();

    void keyPressEvent(QKeyEvent* event);
};

#endif // GAMEPAGE_H
