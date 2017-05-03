#include "savelist.h"
#include <QDebug>

SaveList::SaveList(QObject *parent) : QObject(parent)
{
    //clearAll();
    QSettings setting("MyCompany", "myapp");
    saveNumber = setting.value("saveNumber").toInt();

    setting.beginReadArray("saves");
    for (int i = 0; i < saveNumber; i++){
        setting.setArrayIndex(i);
        m_saves.push_back(setting.value("name").toString());
    }
    setting.endArray();
}

QString SaveList::getSaveName(int index){
    QSettings setting("MyCompany", "myapp");
    setting.beginReadArray("saves");

    setting.setArrayIndex(index);
    QString saveName = setting.value("name").toString();

    setting.endArray();

    return saveName;
}

void SaveList::addSave(QString saveName, SaveParameters saveParameters){
    int arrayCounter;
    QSettings setting("MyCompany", "myapp");
    //saveNumber = setting.value("saveNumber").toInt();
    setting.beginGroup(saveName);
    arrayCounter = 0;
    setting.setValue("snakeSize", saveParameters.snakeCoordinates.size());

    setting.beginWriteArray("snakeCoordinate", saveParameters.snakeCoordinates.size());
    for (auto it : saveParameters.snakeCoordinates){
        setting.setArrayIndex(arrayCounter);
        setting.setValue("xSnakeCoordinate", it.X);
        setting.setValue("ySnakeCoordinate", it.Y);
        arrayCounter++;
    }
    setting.endArray();

    setting.setValue("xFruitCoordinate", saveParameters.fruitCoordinates.X);
    setting.setValue("yFruitCoordinate", saveParameters.fruitCoordinates.Y);

    setting.setValue("height", saveParameters.options.height);
    setting.setValue("width", saveParameters.options.width);
    setting.setValue("rectSize", saveParameters.options.rectSize);
    setting.setValue("warpWallMode", saveParameters.options.warpWallMode);

    setting.endGroup();

    m_saves.push_back(saveName);
    setting.beginWriteArray("saves", m_saves.size());
    setting.setArrayIndex(m_saves.size() - 1); // 0 or 1  ОТСЧЕТ????
    setting.setValue("name", saveName);
    setting.endArray();

    saveNumber++;
    setting.setValue("saveNumber", saveNumber);
}

void SaveList::deleteSave(QString saveName){
    QSettings setting("MyCompany", "myapp");
    setting.beginGroup(saveName);
    setting.remove("");
    setting.endGroup();

    int index;
    QList<QString>::iterator iter = m_saves.begin();
    //for (QList<QString>::iterator it = m_saves.begin(); it != m_saves.end();){
    for (auto it : m_saves){
        if (it == saveName){
            m_saves.erase(iter);
            break;
        }
        iter++;
        index++;
    }

    index = 0;
    setting.beginWriteArray("saves", saveNumber);
    for (auto it : m_saves){
        setting.setArrayIndex(index);
        setting.setValue("name", it);
        index++;
    }
    setting.setArrayIndex(index);
    setting.remove("name");
    setting.endArray();


    /*setting.beginWriteArray("saves", saveNumber);
    for (int i = index - 1; i < saveNumber - 1; i++){
        setting.setArrayIndex(i + 1);
        QString temp = setting.value("name").toString();
        setting.setArrayIndex(i);
        setting.setValue("name", temp);
    }
    setting.setArrayIndex(m_saves.size());
    setting.remove("name");
    setting.endArray();*/
    /*setting.beginWriteArray("saves", m_saves.size() + 1);

    for (int i = 0; i < saveNumber; i++){
        setting.setArrayIndex(i);
        if (setting.value("name").toString() == saveName)
            setting.remove("name");
    }

    setting.endArray();*/


    saveNumber--;
    setting.setValue("saveNumber", saveNumber);
}

SaveParameters SaveList::getSave(QString saveName){
    std::list<Coordinate> snakeCoordinates;
    Coordinate fruitCoordinates;
    Options options;

    int arrayCounter, X, Y, snakeSzie;
    QSettings setting("MyCompany", "myapp");
    setting.beginGroup(saveName);

    arrayCounter = 0;
    snakeSzie = setting.value("snakeSize").toInt();
    setting.beginReadArray("snakeCoordinate");
    for (int i = 0; i < snakeSzie; i++){
        setting.setArrayIndex(arrayCounter);
        X = setting.value("xSnakeCoordinate").toInt();
        Y = setting.value("ySnakeCoordinate").toInt();
        arrayCounter++;
        snakeCoordinates.push_back(Coordinate(X, Y));
    }
    setting.endArray();

    X = setting.value("xFruitCoordinate").toInt();
    Y = setting.value("yFruitCoordinate").toInt();
    fruitCoordinates = Coordinate(X, Y);

    options.height = setting.value("height").toInt();
    options.width = setting.value("width").toInt();
    options.rectSize = setting.value("rectSize").toInt();
    options.warpWallMode = setting.value("warpWallMode").toBool();

    setting.endGroup();

    return SaveParameters(snakeCoordinates, fruitCoordinates, options);
}

int SaveList::getSaveNumber(){
    QSettings setting("MyCompany", "myapp");
    saveNumber = setting.value("saveNumber").toInt();
    return saveNumber;
}

void SaveList::clearAll(){
    QSettings setting("MyCompany", "myapp");
    for (int index = 0; index < 15; index++){
        setting.beginGroup(getSaveName(index));
        setting.remove("");
        setting.endGroup();
    }

   setting.remove("saves");

   setting.setValue("saveNumber", 0);
}
