#include "savepage.h"

SavePage::SavePage(QWidget *parent)
    : QWidget(parent)
{
    this->createWindow();
    connect(m_back, SIGNAL(clicked()), this, SIGNAL(backButton()));
}

void SavePage::createWindow(){
    m_verticalLayout = new QVBoxLayout;
    m_horizontalLayout = new QHBoxLayout;

    m_pageTitle = new QLabel("SNAKE GAME");
   // QPixmap SNAKE_GAME("E:/QtProjects/gameSnake_2/button.png");
   // m_gameName->setPixmap(SNAKE_GAME);

    m_back = new QPushButton("Back");

    m_verticalLayout->addWidget(m_pageTitle);
    m_verticalLayout->addWidget(m_back);

    m_horizontalLayout->addStretch(1);
    m_horizontalLayout->addLayout(m_verticalLayout);
    m_horizontalLayout->addStretch(1);

    this->setLayout(m_horizontalLayout);
}

void SavePage::showEvent(QShowEvent *){
    this->setFixedSize(300, 300);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);
}

SavePage::~SavePage(){
    delete m_verticalLayout;
    delete m_horizontalLayout;

    delete m_pageTitle;
    delete m_back;
}
