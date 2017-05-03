#ifndef SAVELIST_H
#define SAVELIST_H

#include <QObject>
#include <QSettings>
#include <QString>
#include "structures.h"

#include <QList>

class SaveList : public QObject
{
    Q_OBJECT
public:
    explicit SaveList(QObject *parent = 0);

    void addSave(QString saveName, SaveParameters saveParameters);
    void deleteSave(QString saveName);
    SaveParameters getSave(QString saveName);

    QString getSaveName(int index);

    int getSaveNumber();


signals:

public slots:

private:
    SaveParameters m_saveParameters;
    int saveNumber = 0;

    QList<QString> m_saves;

    void clearAll();
};

#endif // SAVELIST_H
