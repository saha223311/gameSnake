#include "savepage.h"

SavePage::SavePage(QWidget *parent)
    : QWidget(parent)
{
    this->createWindow();
    connect(m_back, SIGNAL(clicked()), this, SIGNAL(backButton()));
}

void SavePage::createWindow(){
    m_verticalLayout = new QVBoxLayout;
    m_listWidgetlLayout = new QHBoxLayout;
    m_buttonLayout = new QHBoxLayout;

    m_listWidget = new QListWidget;

    m_pageTitle = new QLabel("SNAKE GAME");
   // QPixmap SNAKE_GAME("E:/QtProjects/gameSnake_2/button.png");
   // m_gameName->setPixmap(SNAKE_GAME);

    m_back = new QPushButton("Back");

   // m_saveList.addSave(0, SaveParameters());



    m_listWidgetlLayout->addStretch(1);
    m_listWidgetlLayout->addWidget(m_listWidget);
    m_listWidgetlLayout->addStretch(1);

    m_buttonLayout->addStretch(1);
    m_buttonLayout->addWidget(m_pageTitle);
    m_buttonLayout->addWidget(m_back);
    m_buttonLayout->addStretch(1);

    m_verticalLayout->addLayout(m_listWidgetlLayout);
    m_verticalLayout->addLayout(m_buttonLayout);

    this->setLayout(m_verticalLayout);

    //connect(m_listWidget, SIGNAL(clicked(QModelIndex)),
}

void SavePage::showEvent(QShowEvent *){
    this->setFixedSize(300, 300);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);

    m_listWidget->clear();
    for (int i = 0; i < m_saveList.getSaveNumber(); i++){
        m_listWidget->addItem(QString::number(i));
    }
}

void SavePage::saveGame(SaveParameters saveParameters){
    m_saveList.addSave(m_saveList.getSaveNumber() + 1, saveParameters);
}

SavePage::~SavePage(){
    delete m_verticalLayout;
    delete m_listWidgetlLayout;
    delete m_buttonLayout;

    delete m_pageTitle;
    delete m_back;
    delete m_listWidget;
}
