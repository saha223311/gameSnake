#ifndef SAVELIST_H
#define SAVELIST_H

#include <QObject>
#include <QSettings>

class SaveList : public QObject
{
    Q_OBJECT
public:
    explicit SaveList(QObject *parent = 0);

    void addSave();
    void deleteSave();

signals:

public slots:

private:

};

#endif // SAVELIST_H
