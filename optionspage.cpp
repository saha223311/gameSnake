#include "optionspage.h"

OptionsPage::OptionsPage(QWidget *parent)
    : QWidget(parent){
    this->createWindow();
    connect(m_back, SIGNAL(clicked()), this, SIGNAL(backButton()));
}

void OptionsPage::createWindow(){
    m_verticalLayout = new QVBoxLayout;

    m_pageTitleLayout = new QHBoxLayout;
    m_fieldSizeHeightLayout = new QHBoxLayout;
    m_fieldSizeWidthLayout = new QHBoxLayout;
    m_fieldSizeRectLayout = new QHBoxLayout;
    m_fieldWarpWallsLayout = new QHBoxLayout;
    m_backLayout = new QHBoxLayout;

    m_pageTitle = new QLabel("SNAKE GAME");
    m_back = new QPushButton("Back");
   // QPixmap SNAKE_GAME("E:/QtProjects/gameSnake_2/button.png");
   // m_gameName->setPixmap(SNAKE_GAME);
    m_warpWalls = new QCheckBox("Warp Walls");

    m_height = new QSpinBox;
    m_width = new QSpinBox;
    m_rectSize = new QSpinBox;

    m_heightText = new QLabel("height");
    m_widthText = new QLabel("width ");
    m_rectSizeText = new QLabel("rectSize");

    m_height->setMinimum(3);
    m_width->setMinimum(3);
    m_rectSize->setMinimum(4);

    m_height->setMaximum(100);
    m_width->setMaximum(100);
    m_rectSize->setMaximum(25);

    m_height->setValue(17);
    m_width->setValue(22);
    m_rectSize->setValue(12);

    m_pageTitleLayout->addStretch(1);
    m_pageTitleLayout->addWidget(m_pageTitle);
    m_pageTitleLayout->addStretch(1);

    m_fieldSizeHeightLayout->addStretch(1);
    m_fieldSizeHeightLayout->addWidget(m_heightText);
    m_fieldSizeHeightLayout->addWidget(m_height);
    m_fieldSizeHeightLayout->addStretch(1);

    m_fieldSizeWidthLayout->addStretch(1);
    m_fieldSizeWidthLayout->addWidget(m_widthText);
    m_fieldSizeWidthLayout->addWidget(m_width);
    m_fieldSizeWidthLayout->addStretch(1);

    m_fieldSizeRectLayout->addStretch(1);
    m_fieldSizeRectLayout->addWidget(m_rectSizeText);
    m_fieldSizeRectLayout->addWidget(m_rectSize);
    m_fieldSizeRectLayout->addStretch(1);

    m_fieldWarpWallsLayout->addStretch(1);
    m_fieldWarpWallsLayout->addWidget(m_warpWalls);
    m_fieldWarpWallsLayout->addStretch(1);

    m_backLayout->addStretch(1);
    m_backLayout->addWidget(m_back);
    m_backLayout->addStretch(1);

    m_verticalLayout->addLayout(m_pageTitleLayout);

    m_verticalLayout->addLayout(m_fieldSizeHeightLayout);
    m_verticalLayout->addLayout(m_fieldSizeWidthLayout);
    m_verticalLayout->addLayout(m_fieldSizeRectLayout);
    m_verticalLayout->addLayout(m_fieldWarpWallsLayout);

    m_verticalLayout->addLayout(m_backLayout);

    this->setLayout(m_verticalLayout);
}

void OptionsPage::showEvent(QShowEvent *){
    this->setFixedSize(300, 300);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);
}

int OptionsPage::getHeight() const{
    return m_height->value();
}

int OptionsPage::getWidth() const{
    return m_width->value();
}

int OptionsPage::getRectSize() const{
    return m_rectSize->value();
}

bool OptionsPage::getWarpWallMode() const{
    return m_warpWalls->isChecked();
}

OptionsPage::~OptionsPage(){
    delete m_verticalLayout;

    delete m_pageTitleLayout;
    delete m_fieldSizeHeightLayout;
    delete m_fieldSizeWidthLayout;
    delete m_fieldSizeRectLayout;
    delete m_fieldWarpWallsLayout;
    delete m_backLayout;

    delete m_pageTitle;
    delete m_back;
    delete m_warpWalls;

    delete m_height;
    delete m_width;
    delete m_rectSize;

    delete m_heightText;
    delete m_widthText;
    delete m_rectSizeText;
}

