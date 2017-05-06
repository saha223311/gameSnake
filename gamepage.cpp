#include "gamepage.h"

GamePage::GamePage(QWidget *parent)
    : QWidget(parent){
    this->createWindow();
    connect(m_back, SIGNAL(clicked()), this, SIGNAL(backButton()));
    connect(m_pause, SIGNAL(clicked()), this, SLOT(pauseButton()));
}

void GamePage::createWindow(){
    m_verticalLayout = new QVBoxLayout;
    m_highButtonLayout = new QHBoxLayout;
    m_lowButtonLayout = new QHBoxLayout;
    m_viewLayout = new QHBoxLayout;

    m_back = new QPushButton("Back");
    m_pause = new QPushButton("Stop");
    m_save = new QPushButton("Save");

    m_score = new QLabel;
    m_record = new QLabel;

    m_view = new QGraphicsView;
    m_view->setBackgroundBrush(QBrush(QColor(235, 235, 176)));

    m_highButtonLayout->addStretch(1);
    m_highButtonLayout->addWidget(m_back);
    m_highButtonLayout->addStretch(1);
    m_highButtonLayout->addWidget(m_save);
    m_highButtonLayout->addStretch(1);

    m_lowButtonLayout->addWidget(m_pause);
    m_lowButtonLayout->addStretch(1);
    m_lowButtonLayout->addWidget(m_score);
    m_lowButtonLayout->addStretch(1);
    m_lowButtonLayout->addWidget(m_record);
    m_lowButtonLayout->addStretch(1);

    m_viewLayout->addStretch(1);
    m_viewLayout->addWidget(m_view);
    m_viewLayout->addStretch(1);

    m_verticalLayout->addLayout(m_highButtonLayout);
    m_verticalLayout->addLayout(m_viewLayout);
    m_verticalLayout->addLayout(m_lowButtonLayout);

    this->setLayout(m_verticalLayout);

    connect(m_save, SIGNAL(clicked()), this, SLOT(setSaveNamePage()));
    connect(&m_saveNamePage, SIGNAL(saveProcess(QString)), this, SLOT(saveProcess(QString)));
    connect(&m_resultPage, SIGNAL(backButton()), this, SIGNAL(backButton()));
    connect(&m_resultPage, SIGNAL(restartGame()), this, SIGNAL(backButton()));
    connect(&m_resultPage, SIGNAL(restartGame()), this, SIGNAL(restartGame()));
}

void GamePage::setSaveNamePage(){
    m_saveNamePage.show();
}

void GamePage::saveProcess(QString saveName){
   SaveParameters parameters(m_game->getSaveParameters());
   parameters.saveName = saveName;
   emit saveGame(parameters);
}

void GamePage::updateScore(){
    m_score->setText("Score: " + QString::number(m_game->getScore()));
    m_record->setText("Best Score: " + QString::number(m_game->getBestScore()));
}

void GamePage::initilizeGame(){
    m_scene = new QGraphicsScene;
    m_view->setScene(m_scene);
    //m_direction = Snake::RIGHT;

    m_scene->setSceneRect(0, 0, m_options->width * m_options->rectSize,
                          m_options->height * m_options->rectSize);

    m_view->setFixedHeight((m_options->height + 1) * m_options->rectSize);
    m_view->setFixedWidth((m_options->width + 1) * m_options->rectSize);

    for (int i = 0; i < m_options->width; i++){
        for (int j = 0; j < m_options->height; j++){
            m_scene->addRect(i * m_options->rectSize, j * m_options->rectSize,
                             m_options->rectSize, m_options->rectSize, QPen(QColor(0, 0, 0, 30)));
        }
    }
}

void GamePage::showEvent(QShowEvent*){
    m_score->setText("Score: " + QString::number(m_game->getScore()));
    m_record->setText("Best Score: " + QString::number(m_game->getBestScore()));
    m_save->setEnabled(false);

    this->setFixedSize(m_view->width() + 20, m_view->height() + m_back->height() + m_score->height() + 30);
    //this->setFixedSize(m_options->width * m_options->rectSize + 30,
    //                   m_options->height * m_options->rectSize + m_back->height() + m_score->height() + 40);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);

    connect(m_game, SIGNAL(newScore()), this, SLOT(updateScore()));
    connect(m_game, SIGNAL(winGame()), this, SLOT(setWinResultPage()));
    connect(m_game, SIGNAL(loseGame()), this, SLOT(setLoseResultPage()));
}

void GamePage::setWinResultPage(){
    m_game->checkBestScore();
    m_resultPage.setWinPage();
    m_resultPage.setResult(m_game->getScore());
    m_resultPage.show();
}

void GamePage::setLoseResultPage(){
    m_game->checkBestScore();
    m_resultPage.setLosePage();
    m_resultPage.setResult(m_game->getScore());
    m_resultPage.show();
}

void GamePage::closeEvent(QCloseEvent*){
    m_game->checkBestScore();
    delete m_scene;
    delete m_game;
}

void GamePage::startNewGame(OptionsPage *optionsPage){
    m_options = new Options(optionsPage->getHeight(), optionsPage->getWidth(),
                            optionsPage->getRectSize(), optionsPage->getWarpWallMode());

    this->initilizeGame();
    m_game = new Game(m_scene, m_options);
    connect(m_game, SIGNAL(endMove()), this, SLOT(checkDirection()));
    m_direction = Snake::NONE;
    m_game->setDefaultSaveParameters();
    m_game->startGame();
}

void GamePage::startSavedGame(SaveParameters saveParameters){
    m_options = new Options(saveParameters.options.height, saveParameters.options.width,
                            saveParameters.options.rectSize, saveParameters.options.warpWallMode);

    this->initilizeGame();
    m_game = new Game(m_scene, m_options);
    connect(m_game, SIGNAL(endMove()), this, SLOT(checkDirection()));
    m_direction = static_cast<Snake::Direction>(saveParameters.snakeDirection);
    m_game->setSaveParameters(saveParameters);
    m_game->startGame();
}

GamePage::~GamePage(){
    delete m_verticalLayout;

    delete m_highButtonLayout;
    delete m_lowButtonLayout;
    delete m_viewLayout;

    delete m_view;
    delete m_scene;
    delete m_game;
    delete m_options;

    delete m_back;
    delete m_pause;

    delete m_score;
    delete m_record;
}

void GamePage::pauseButton(){
    if (!m_game->isPaused()){
        m_game->pauseGame();
        m_save->setEnabled(true);
    }
    else{
        m_game->continueGame();
        m_save->setEnabled(false);
    }
}

void GamePage::checkDirection(){
    m_game->setSnakeDirection(m_direction);
    turnDirection = true;
}

void GamePage::keyPressEvent(QKeyEvent *event){
    if (turnDirection){
    switch (event->key()) {
    case Qt::Key_D:
        if (m_direction != Snake::LEFT){
            m_direction = Snake::RIGHT;
        }
        break;
    case Qt::Key_A:
        if (m_direction != Snake::RIGHT){
            m_direction = Snake::LEFT;
        }
        break;
    case Qt::Key_W:
        if (m_direction != Snake::DOWN){
            m_direction = Snake::UP;
        }
        break;
    case Qt::Key_S:
        if (m_direction != Snake::UP){
            m_direction = Snake::DOWN;
        }
        break;
    default:
        break;
    }
    turnDirection = false;
    }
}
