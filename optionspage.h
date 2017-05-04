#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include <QWidget>

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>

class OptionsPage : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsPage(QWidget *parent = 0);

    int getHeight() const;
    int getWidth() const;
    int getRectSize() const;
    bool getWarpWallMode() const;

    ~OptionsPage();

signals:
    void backButton();
public slots:

private:
    QVBoxLayout* m_verticalLayout;

    QHBoxLayout* m_pageTitleLayout;
    QHBoxLayout* m_fieldSizeHeightLayout;
    QHBoxLayout* m_fieldSizeWidthLayout;
    QHBoxLayout* m_fieldSizeRectLayout;
    QHBoxLayout* m_fieldWarpWallsLayout;
    QHBoxLayout* m_backLayout;

    QLabel* m_pageTitle;
    QPushButton* m_back;

    QLabel* m_heightText;
    QLabel* m_widthText;
    QLabel* m_rectSizeText;
    QSpinBox* m_height;
    QSpinBox* m_width;
    QSpinBox* m_rectSize;

    QCheckBox* m_warpWalls;

    void showEvent(QShowEvent*);
    void createWindow();
};

#endif // OPTIONSPAGE_H
