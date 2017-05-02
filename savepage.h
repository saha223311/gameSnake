#ifndef SAVEPAGE_H
#define SAVEPAGE_H

#include <QWidget>

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>

#include <QLabel>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>

class SavePage : public QWidget
{
    Q_OBJECT
public:
    explicit SavePage(QWidget *parent = 0);
    ~SavePage();

signals:
    void backButton();
public slots:

private:
    QHBoxLayout* m_horizontalLayout;
    QVBoxLayout* m_verticalLayout;

    QLabel* m_pageTitle;

    QPushButton* m_back;

    void showEvent(QShowEvent*);
    void createWindow();
};

#endif // SCOREPAGE_H
