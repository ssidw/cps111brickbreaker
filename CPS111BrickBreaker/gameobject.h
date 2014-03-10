#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <QString>
using namespace std;

void collisionUnitTests();

//Abstract class that contains a set of x,y coordinates.

class GameObject
{
protected:
        double x, y;


public:
    GameObject(double newX,double newY): x(newX), y(newY){}

    //Method to save state of objects
    virtual void saveState() = 0;

    //Getter methods
    double getX(){return x;}
    double getY(){return y;}

    //Setter methods
    void setX(double newX){x = newX;}
    void setY(double newY){y = newY;}
};

//Data class for the bricks
class Brick : public GameObject {
private:
    int hitsLeft;
    //For the sake of networking identification I feel that these are neccessary
    int id;
public:
    //constructor
    //unbreakable brick has -1 hits, everytime it hits,
    //it will decrease but not reach 0, so cant be destroyed
    explicit Brick(int numhits, int newId, double BrickX, double BrickY):
        GameObject(BrickX, BrickY), hitsLeft(numhits), id(newId){}

    //accessors
    int getHits(){ return hitsLeft; }

    //Method for incrementing hit counter and check for destruction. if 0 = destroy
    void hit();

    //Method for destroying bricks
    void destroy();

};

//Data class for the paddle
class Paddle : public GameObject{

private:
    bool initialLeft, initialRight;
public:
    Paddle(double newX, double newY): GameObject(newX, newY), initialLeft(false), initialRight(false){}

    //Method used for collision detection on the right side of the screen
    bool checkCollisionRight();

    //Method used for collision detection on the left side of the screen
    bool checkCollisionLeft();

    void saveState();

    //Getter methods
    bool getInitialLeft(){return initialLeft;}
    bool getInitialRight(){return initialRight;}

    //Setter methods
    void setInitialRight(bool value){initialRight = value;}
    void setInitialLeft(bool value){initialLeft = value;}
};

//Data class for the ball
class Ball : public GameObject {

private:
    double xHeading, yHeading;
    Paddle * paddle;
    bool initialPos;
    //score is with the ball
    int highscore;

public:
    Ball(double newX, double newY, double newXHeading, double newYHeading, Paddle * newPaddle): GameObject(newX, newY), xHeading(newXHeading), yHeading(newYHeading), paddle(newPaddle), initialPos(true){}

    //Method used for ball collision detection
    void checkCollision();

    //Method used to update the ball's x,y coordinates
    void updatePosition();

    void saveState();

    //Getter methods
    double getXHeading() {return xHeading;}
    double getYHeading() {return yHeading;}
    bool getInitalPos() {return initialPos;}

    //Setter methods
    void setXHeading(double heading){xHeading = heading;}
    void setYHeading(double heading){yHeading = heading;}
    void hitBrick() {highscore++;}

    //cheat
    void noDeath();
    void slowBallCheat();
    void speedBallCheat();
};

//Data class for power ups
class PowerUp : public GameObject{

public:

};

#endif // GAMEOBJECT_H
