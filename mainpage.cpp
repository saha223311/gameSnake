#include "MainPage.h"

#include <QPixmap>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
{
    this->createWindow();

    connect(m_play, SIGNAL(clicked()), this, SLOT(setGamePage()));
    connect(m_options, SIGNAL(clicked()), this, SLOT(setOptionsPage()));
    connect(m_saves, SIGNAL(clicked()), this, SLOT(setSavePage()));
    connect(m_exit, SIGNAL(clicked()), this, SLOT(close()));

    connect(m_optionsPage, SIGNAL(backButton()), this, SLOT(closeOptionsPage()));
    connect(m_savePage, SIGNAL(backButton()), this, SLOT(closeSavePage()));
    connect(m_gamePage, SIGNAL(backButton()), this, SLOT(closeGamePage()));

    connect(m_gamePage, SIGNAL(saveGame(SaveParameters)), m_savePage, SLOT(saveGame(SaveParameters)));
}

void MainPage::createWindow(){
    m_optionsPage = new OptionsPage;
    m_savePage = new SavePage;
    m_gamePage = new GamePage;
    m_savePage->setGamePage(m_gamePage);

    m_verticalLayout = new QVBoxLayout;
    m_horizontalLayout = new QHBoxLayout;

    m_pageTitle = new QLabel("SNAKE GAME");

    //WORKINK STYLEEE !!!!!!!!!!!!!!!!!!!!!!
   /* QPixmap image = QPixmap::fromImage(QImage("E://QtProjects//gameSnake//snake.png"));
    m_pageTitle->setPixmap(image);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);*/

    m_play = new QPushButton("START");
    m_options = new QPushButton("Options");
    m_saves = new QPushButton("Saves");
    m_exit = new QPushButton("Exit");

    m_verticalLayout->addWidget(m_pageTitle);
    m_verticalLayout->addWidget(m_play);
    m_verticalLayout->addWidget(m_options);
    m_verticalLayout->addWidget(m_saves);
    m_verticalLayout->addWidget(m_exit);

    m_horizontalLayout->addStretch(1);
    m_horizontalLayout->addLayout(m_verticalLayout);
    m_horizontalLayout->addStretch(1);

    this->setLayout(m_horizontalLayout);
}

void MainPage::closeOptionsPage(){
    this->show();
    m_optionsPage->close();
}
void MainPage::closeSavePage(){
    this->show();
    m_savePage->close();
}
void MainPage::closeGamePage(){
    this->show();
    m_gamePage->close();
}

void MainPage::setGamePage(){
    m_gamePage->setOptionsController(m_optionsPage);
    m_gamePage->show();
    this->close();
}

void MainPage::setOptionsPage(){
    m_optionsPage->show();
    this->close();
}

void MainPage::setSavePage(){
    m_savePage->show();
    this->close();
}

void MainPage::showEvent(QShowEvent *){
    this->setFixedSize(300, 300);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);
}

MainPage::~MainPage(){
    delete m_optionsPage;
    delete m_savePage;
    delete m_gamePage;

    delete m_verticalLayout;
    delete m_horizontalLayout;

    delete m_pageTitle;

    delete m_play;
    delete m_options;
    delete m_saves;
    delete m_exit;
}
