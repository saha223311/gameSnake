#include "savenamepage.h"

SaveNamePage::SaveNamePage(QDialog *parent)
    : QDialog(parent){
    m_label = new QLabel("Please, enter game name");
    m_error = new QLabel;
    m_lineEdit = new QLineEdit;
    m_save = new QPushButton("Save");
    m_cancel = new QPushButton("Cancel");

    m_labelLayout = new QHBoxLayout;
    m_lineEditLayout  = new QHBoxLayout;
    m_buttonLayout = new QHBoxLayout;
    m_errorLayout = new QHBoxLayout;
    m_verticalLayout = new QVBoxLayout;

    m_labelLayout->addStretch(1);
    m_labelLayout->addWidget(m_label);
    m_labelLayout->addStretch(1);

    m_lineEditLayout->addStretch(1);
    m_lineEditLayout->addWidget(m_lineEdit);
    m_lineEditLayout->addStretch(1);

    m_errorLayout->addStretch(1);
    m_errorLayout->addWidget(m_error);
    m_errorLayout->addStretch(1);

    m_buttonLayout->addStretch(1);
    m_buttonLayout->addWidget(m_cancel);
    m_buttonLayout->addStretch(1);
    m_buttonLayout->addWidget(m_save);
    m_buttonLayout->addStretch(1);

    m_verticalLayout->addLayout(m_labelLayout);
    m_verticalLayout->addStretch(1);
    m_verticalLayout->addLayout(m_lineEditLayout);
    m_verticalLayout->addLayout(m_errorLayout);
    m_verticalLayout->addLayout(m_buttonLayout);

    QFont font(m_error->font());
    QPalette pal(m_error->palette());
    font.setPointSize(7);
    pal.setColor(QPalette::WindowText, Qt::red);
    m_error->setFont(font);
    m_error->setPalette(pal);

    this->setLayout(m_verticalLayout);
    connect(m_save, SIGNAL(clicked()), this, SLOT(saveButton()));
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void SaveNamePage::saveButton(){
    emit saveProcess(m_lineEdit->text());
    this->close();
}

void SaveNamePage::showEvent(QShowEvent*){
    this->setModal(true);
    this->setFixedSize(200, 125);
    this->move((QApplication::desktop()->width() - width()) / 2,
          (QApplication::desktop()->height() - height()) / 2);
}

SaveNamePage::~SaveNamePage(){
    delete m_label;
    delete m_lineEdit;
    delete m_save;
    delete m_cancel;
    delete m_error;
    delete m_labelLayout;
    delete m_lineEditLayout;
    delete m_buttonLayout;
    delete m_errorLayout;
    delete m_verticalLayout;
}


