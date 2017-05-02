#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Options{
    Options(){}
    Options(int height, int width, int rectSize, bool warpWallMode)
        : height(height), width(width), rectSize(rectSize), warpWallMode(warpWallMode){}

    int height;
    int width;
    int rectSize;
    bool warpWallMode;
};

struct Coordinate{
    Coordinate(){}
    Coordinate(int coordinateX, int coordinateY)
        : X(coordinateX), Y(coordinateY){}

    int X, Y;

    const bool operator == (const Coordinate& coord){
       if ((this->X == coord.X) && (this->Y == coord.Y)) return true;
       else return false;
    }
};

struct SaveParameters{
    SaveParameters(){}
    SaveParameters(std::list<Coordinate> snakeCoordinates, Coordinate fruitCoordinates, Options options)
        :snakeCoordinates(snakeCoordinates), fruitCoordinates(fruitCoordinates), options(options){}

    std::list<Coordinate> snakeCoordinates;
    Coordinate fruitCoordinates;
    Options options;
};

#endif // STRUCTURES_H
