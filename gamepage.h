#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "game.h"
#include "optionspage.h"

#include <QWidget>
#include <QKeyEvent>

#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QPushButton>
#include <QLabel>

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>
#include <QCloseEvent>

#include "structures.h"


class GamePage : public QWidget
{
    Q_OBJECT
public:
    explicit GamePage(QWidget *parent = 0);

    void setOptionsController(OptionsPage* optionsPage);

    ~GamePage();

signals:
    void backButton();
    void saveGame(SaveParameters);
public slots:
    void updateScore();
    void startSaveGame();
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

    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent*);

    void createWindow();
    void initilizeGame();

    void keyPressEvent(QKeyEvent* event);
};

#endif // GAMEPAGE_H
