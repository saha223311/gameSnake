#include "savelist.h"
#include <QDebug>

SaveList::SaveList(QObject *parent) : QObject(parent)
{

}

void SaveList::addSave(int index, SaveParameters saveParameters){
    int arrayCounter;
    QSettings setting("MyCompany", "myapp");
    saveNumber = setting.value("saveNumber").toInt();
    setting.beginGroup(QString::number(index));
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

    saveNumber++;
    setting.setValue("saveNumber", saveNumber);
}

void SaveList::deleteSave(int index){
    QSettings setting("MyCompany", "myapp");
    setting.beginGroup(QString::number(index));
    setting.remove("");
    setting.endGroup();
    saveNumber--;
}

SaveParameters SaveList::getSave(int index){
    std::list<Coordinate> snakeCoordinates;
    Coordinate fruitCoordinates;
    Options options;

    int arrayCounter, X, Y, snakeSzie;
    QSettings setting("MyCompany", "myapp");
    setting.beginGroup(QString::number(index));

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
