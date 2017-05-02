#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "optionspage.h"
#include "savepage.h"
#include "gamepage.h"
#include "structures.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>

#include <QWidget>
//#include <QPixmap>

#include <QPushButton>
#include <QLabel>

#include <QVBoxLayout>
#include <QHBoxLayout>

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();
signals:

public slots:

private slots:
    void closeOptionsPage();
    void closeSavePage();
    void closeGamePage();
    void setOptionsPage();
    void setSavePage();
    void setGamePage();
private:
    QLabel* m_pageTitle;

    QPushButton* m_play;
    QPushButton* m_options;
    QPushButton* m_saves;
    QPushButton* m_exit;

    QHBoxLayout* m_horizontalLayout;
    QVBoxLayout* m_verticalLayout;

    OptionsPage* m_optionsPage;
    SavePage* m_savePage;
    GamePage* m_gamePage;

    void showEvent(QShowEvent*);
    void createWindow();
};

#endif // MAINPAGE_H
