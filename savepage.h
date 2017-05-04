#ifndef SAVEPAGE_H
#define SAVEPAGE_H

#include <QWidget>

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>

#include <QLabel>
#include <QPushButton>
#include <QListWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "structures.h"
#include "savelist.h"
#include "gamepage.h"

class SavePage : public QWidget
{
    Q_OBJECT
public:
    explicit SavePage(QWidget *parent = 0);

    void setGamePage(GamePage* gamePage);

    ~SavePage();

signals:
    void backButton();

public slots:
    void saveGame(SaveParameters saveParameters);

    void loadGame();
    void deleteGame();
private:
    SaveList m_saveList;
    QListWidget* m_listWidget;

    QHBoxLayout* m_listWidgetlLayout;
    QHBoxLayout* m_buttonLayout;
    QVBoxLayout* m_verticalLayout;

    QLabel* m_pageTitle;

    QPushButton* m_back;
    QPushButton* m_load;
    QPushButton* m_delete;

    void showEvent(QShowEvent*);
    void createWindow();

    GamePage* m_gamePage;
};

#endif // SCOREPAGE_H
