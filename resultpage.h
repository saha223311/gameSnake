#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QDialog>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLabel>

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>

class ResultPage : public QDialog
{
    Q_OBJECT
public:
    explicit ResultPage(QDialog *parent = 0);

    void setLosePage();
    void setWinPage();
    void setResult(int score);

    ~ResultPage();

signals:
    void backButton();
    void restartGame();
public slots:

private:
    QHBoxLayout* m_labelLayout;
    QHBoxLayout* m_scoreLayout;
    QHBoxLayout* m_buttonLayout;
    QVBoxLayout* m_verticalLayout;

    QLabel* m_label;
    QLabel* m_score;

    QPushButton* m_back;
    QPushButton* m_start;

    void showEvent(QShowEvent*);
};

#endif // RESULTPAGE_H
