#ifndef SAVELIST_H
#define SAVELIST_H

#include <QObject>
#include <QSettings>
#include <QString>
#include "structures.h"

class SaveList : public QObject
{
    Q_OBJECT
public:
    explicit SaveList(QObject *parent = 0);

    void addSave(int index, SaveParameters saveParameters);
    void deleteSave(int index);
    SaveParameters getSave(int index);

    int getSaveNumber();


signals:

public slots:

private:
    SaveParameters m_saveParameters;
    int saveNumber = 0;
};

#endif // SAVELIST_H
