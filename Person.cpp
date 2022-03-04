#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string input_string) {
    stringstream ss(input_string);
    ss >> turn;
    char f;
    ss >> f;
    ss >> currentFloor;
    char t;
    ss >> t;
    ss >> targetFloor;
    char a;
    ss >> a;
    ss >> angerLevel;

    //TODO: Implement non-default constructor
}

bool Person::tick(int currentTime) {
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel = getAngerLevel() + 1;
    }
    if (angerLevel >= MAX_ANGER) {
        return true;
    }
    return false;
}

void Person::print(ostream &outs) {  
    outs << "f" << getCurrentFloor() << "t" << getTargetFloor() << "a" << getAngerLevel();
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
