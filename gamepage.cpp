#include "gamepage.h"

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
{
    this->createWindow();
    connect(m_back, SIGNAL(clicked()), this, SIGNAL(backButton()));
    connect(m_pause, SIGNAL(clicked()), this, SLOT(pauseButton()));
}

void GamePage::createWindow(){
    m_verticalLayout = new QVBoxLayout;
    m_highButtonLayout = new QHBoxLayout;
    m_lowButtonLayout = new QHBoxLayout;
    m_viewLayout = new QHBoxLayout;

    m_back = new QPushButton("STOP THI GAME!!!");
    m_pause = new QPushButton("STOP");
    m_save = new QPushButton("SAVE");

    m_score = new QLabel;
    m_record = new QLabel("Best Score: 0");

    m_view = new QGraphicsView;
    m_view->setBackgroundBrush(QBrush(QColor(235, 235, 176)));

    m_highButtonLayout->addStretch(1);
    m_highButtonLayout->addWidget(m_back);
    m_highButtonLayout->addWidget(m_pause);
    m_highButtonLayout->addWidget(m_save);
    m_highButtonLayout->addStretch(1);

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

    connect(m_save, SIGNAL(clicked()), this, SLOT(startSaveGame()));
}

void GamePage::startSaveGame(){
   emit saveGame(m_game->getSaveParameters());
}

void GamePage::updateScore(){
    m_score->setText("Score: " + QString::number(m_game->getScore()));
}

void GamePage::initilizeGame(){
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
    m_scene = new QGraphicsScene;
    m_view->setScene(m_scene);

    this->initilizeGame();
    m_game = new Game(m_scene, m_options);

    m_score->setText("Score: " + QString::number(m_game->getScore()));

    this->setFixedSize(m_view->width() + 20, m_view->height() + m_back->height() + m_score->height() + 30);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);

    connect(m_game, SIGNAL(newScore()), this, SLOT(updateScore()));
}

void GamePage::closeEvent(QCloseEvent*){
    delete m_scene;
    delete m_game;
}

void GamePage::setOptionsController(OptionsPage *optionsPage){
    m_options = new Options(optionsPage->getHeight(), optionsPage->getWidth(),
                            optionsPage->getRectSize(), optionsPage->getWarpWallMode());
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
    if (!m_game->isPaused()) m_game->pauseGame();
    else m_game->continueGame();
}

void GamePage::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_D:
        if (m_game->getSnakeDirection() != Snake::LEFT){
            m_game->setSnakeDirection(Snake::RIGHT);
        }
        break;
    case Qt::Key_A:
        if (m_game->getSnakeDirection() != Snake::RIGHT){
            m_game->setSnakeDirection(Snake::LEFT);
        }
        break;
    case Qt::Key_W:
        if (m_game->getSnakeDirection() != Snake::DOWN){
            m_game->setSnakeDirection(Snake::UP);
        }
        break;
    case Qt::Key_S:
        if (m_game->getSnakeDirection() != Snake::UP){
            m_game->setSnakeDirection(Snake::DOWN);
        }
        break;
    case Qt::Key_R:
       m_game->setSnakeStatus(Snake::INCREASED);
        break;
    default:
        break;
    }
}
