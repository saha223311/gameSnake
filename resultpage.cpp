#include "resultpage.h"

ResultPage::ResultPage(QDialog *parent)
    : QDialog(parent){
    m_labelLayout = new QHBoxLayout;
    m_scoreLayout = new QHBoxLayout;
    m_buttonLayout = new QHBoxLayout;
    m_verticalLayout = new QVBoxLayout;

    m_label = new QLabel;
    m_score = new QLabel;

    m_back = new QPushButton("Back to menu");
    m_start = new QPushButton("Start new game");

    m_labelLayout->addStretch(1);
    m_labelLayout->addWidget(m_label);
    m_labelLayout->addStretch(1);

    m_scoreLayout->addStretch(1);
    m_scoreLayout->addWidget(m_score);
    m_scoreLayout->addStretch(1);

    m_buttonLayout->addStretch(1);
    m_buttonLayout->addWidget(m_back);
    m_buttonLayout->addStretch(1);
    m_buttonLayout->addWidget(m_start);
    m_buttonLayout->addStretch(1);

    m_verticalLayout->addLayout(m_labelLayout);
    m_verticalLayout->addLayout(m_scoreLayout);
    m_verticalLayout->addLayout(m_buttonLayout);

    this->setLayout(m_verticalLayout);

    connect(m_back, SIGNAL(clicked()), this, SIGNAL(backButton()));
    connect(m_back, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_start, SIGNAL(clicked()), this, SIGNAL(restartGame()));
    connect(m_start, SIGNAL(clicked()), this, SLOT(close()));
}

void ResultPage::setWinPage(){
    m_label->setText("YOU WIN!");
}

void ResultPage::setLosePage(){
    m_label->setText("YOU LOSE.");
}

void ResultPage::setResult(int score){
    m_score->setText("Your score: " + QString::number(score));
}

void ResultPage::showEvent(QShowEvent*){
    this->setModal(true);
    this->setFixedSize(200, 110);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);
}

ResultPage::~ResultPage(){
    delete m_labelLayout;
    delete m_scoreLayout;
    delete m_buttonLayout;
    delete m_verticalLayout;

    delete m_label;
    delete m_score;

    delete m_back;
    delete m_start;
}
