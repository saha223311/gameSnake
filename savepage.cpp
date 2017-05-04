#include "savepage.h"

SavePage::SavePage(QWidget *parent)
    : QWidget(parent){
    this->createWindow();
    connect(m_back, SIGNAL(clicked()), this, SIGNAL(backButton()));
}

void SavePage::createWindow(){
    m_verticalLayout = new QVBoxLayout;
    m_listWidgetlLayout = new QHBoxLayout;
    m_buttonLayout = new QHBoxLayout;

    m_listWidget = new QListWidget;

    m_pageTitle = new QLabel("SNAKE GAME");

    m_back = new QPushButton("Back");
    m_load = new QPushButton("Load");
    m_delete = new QPushButton("Delete");

    m_listWidgetlLayout->addStretch(1);
    m_listWidgetlLayout->addWidget(m_listWidget);
    m_listWidgetlLayout->addStretch(1);

    m_buttonLayout->addStretch(1);
    m_buttonLayout->addWidget(m_pageTitle);
    m_buttonLayout->addWidget(m_back);
    m_buttonLayout->addWidget(m_load);
    m_buttonLayout->addWidget(m_delete);
    m_buttonLayout->addStretch(1);

    m_verticalLayout->addLayout(m_listWidgetlLayout);
    m_verticalLayout->addLayout(m_buttonLayout);

    this->setLayout(m_verticalLayout);

    connect(m_load, SIGNAL(clicked()), this, SLOT(loadGame()));
    connect(m_delete, SIGNAL(clicked()), this, SLOT(deleteGame()));
}

void SavePage::loadGame(){
    m_gamePage->startSavedGame(m_saveList.getSave(m_listWidget->currentItem()->text()));
    m_gamePage->show();
    this->close();
}

void SavePage::deleteGame(){
    m_saveList.deleteSave(m_listWidget->currentItem()->text());
    m_listWidget->clear();
    for (int i = 0; i < m_saveList.getSaveNumber(); i++){
        m_listWidget->addItem(m_saveList.getSaveName(i));
    }
}

void SavePage::setGamePage(GamePage *gamePage){
    m_gamePage = gamePage;
}

void SavePage::showEvent(QShowEvent *){
    this->setFixedSize(300, 300);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);

    m_listWidget->clear();
    for (int i = 0; i < m_saveList.getSaveNumber(); i++){
         m_listWidget->addItem(m_saveList.getSaveName(i));
    }
}

void SavePage::saveGame(SaveParameters saveParameters){
    m_saveList.addSave(saveParameters.saveName, saveParameters);
}

SavePage::~SavePage(){
    delete m_verticalLayout;
    delete m_listWidgetlLayout;
    delete m_buttonLayout;

    delete m_pageTitle;
    delete m_back;
    delete m_load;
    delete m_delete;
    delete m_listWidget;
}
