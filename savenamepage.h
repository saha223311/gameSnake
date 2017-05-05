#ifndef SAVENAMEPAGE_H
#define SAVENAMEPAGE_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QString>

#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>

class SaveNamePage : public QDialog
{
    Q_OBJECT
public:
    explicit SaveNamePage(QDialog *parent = 0);
    ~SaveNamePage();
signals:
    void saveProcess(QString);
public slots:

private slots:
    void saveButton();
private:
    QLabel* m_label;
    QLabel* m_error;
    QLineEdit* m_lineEdit;
    QPushButton* m_save;
    QPushButton* m_cancel;

    QHBoxLayout* m_labelLayout;
    QHBoxLayout* m_lineEditLayout;
    QHBoxLayout* m_buttonLayout;
    QHBoxLayout* m_errorLayout;
    QVBoxLayout* m_verticalLayout;

    void showEvent(QShowEvent*);
};

#endif // SAVENAMEPAGE_H
