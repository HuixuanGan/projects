#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;
/**
 * Requires: commandString is a valid string
 * Modifies: elevatorId, targetFloor, isPass, isPickup, isSave, isQuit
 * Effects:  creates a Move object based on
 *           the characters in commandString
 *           Ex:
 *           commandString = "e1f4"; // elevatorID of 1 has a targetFloor of 4
 *           commandString = "e1p";  // elevatorID of 1 will pickup people on its current floor
 */
Move::Move(string commandString) : Move() {
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
    // Pass Move
    if (commandString == "") {
        isPass = true;
    } else {
        for (int i = 0; i< commandString.length(); i++) {
            if (i == 0) {
                // Game Move
                if (commandString[i] == 'q' || commandString[i] == 'Q') {
                    isQuit = true;
                } else if (commandString[i] == 's' || commandString[i] == 'S') {
                    isSave = true;
                }
            } else if (i == 1) {
                elevatorId = commandString[i] - 48;
            } else if (i == 2) {
                if (commandString[i] == 'f' || commandString[i] == 'F') {
                    // Service Move
                    targetFloor = commandString[i+1] - 48;
                } else if (commandString[i] == 'p' || commandString[i] == 'P') {
                    // Pickup Move
                    isPickup = true;
                }
            }
        }
    }
}

/**
 * Requires: elevators represents the elevator servicing states
 * Modifies: nothing
 * Effects:  returns true if this Move instance is valid, false otherwise
 *
 *           The following are the criterion for validity:
 *
 *           If a move is a Pass Move, a Quit Move, or a Save Move it is valid
 *           For both Pickup Moves and Servicing Moves:
 *               0 <= elevatorId < NUM_ELEVATORS
 *               The corresponding Elevator is currently not
 *                  servicing a request.
 *           For Servicing Moves only:
 *               0 <= targetFloor < NUM_FLOORS
 *               targetFloor is different from the corresponding
 *                  Elevator's currentFloor
 */
bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    bool valid = false;
    if (isPass || isSave || isQuit) {
        valid = true;
    } else if ((elevatorId < NUM_ELEVATORS && elevatorId >= 0) && !elevators[elevatorId].isServicing()){
        if (isPickup) {
            valid = true;
        } else if ((targetFloor < NUM_FLOORS && targetFloor >= 0) && targetFloor != elevators[elevatorId].getCurrentFloor()) {
            // Service move
            valid = true;
        }
    }
    return valid;
}

/**
 * Requires: pickupList is a valid list of indices
 *           currentFloor is the floor number where the pickup
 *             is taking place
 *           pickupFloor is the Floor instance where the pickup
 *            is taking place
 * Modifies: numPeopleToPickup, peopleToPickup, totalSatisfaction, targetFloor
 * Effects:  sets numPeopleToPickup and totalSatisfaction to 0
 *           adds the indices specified in pickupList to peopleToPickup
 *           increments numPeopleToPickup by 1 for each person being picked up
 *           adds satisfaction gained from each person picked up
 *              to totalSatisfaction
 *           sets targetFloor to be the most extreme floor of those
 *              being picked up (furthest up or down)
 */
void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int currentAnger = 0;
    int angerRate = 0;
    int floorRate = 0;
    int extremeFloor = 0;
    int index = 0;
    index = pickupList[0] - 48;
    targetFloor = pickupFloor.getPersonByIndex(index).getTargetFloor();
    numPeopleToPickup += 1;
    totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(index).getAngerLevel());
    peopleToPickup[0] = index;
    
    // Q: need to judge pickupList.length()>0??
    if (pickupList.length()>1) {
        for (int i = 1; i < pickupList.length(); ++i) {
            peopleToPickup[i] = pickupList[i] - 48;
            index = peopleToPickup[i];
            numPeopleToPickup++;
        
            // anger
            currentAnger = pickupFloor.getPersonByIndex(index).getAngerLevel();
            angerRate = MAX_ANGER - currentAnger;
            totalSatisfaction += angerRate;
            
            // floor
            floorRate = fabs(pickupFloor.getPersonByIndex(index).getTargetFloor() - currentFloor);
            extremeFloor = fabs(targetFloor - currentFloor);
            if (floorRate > extremeFloor) {
                targetFloor = pickupFloor.getPersonByIndex(index).getTargetFloor();
            }
        }
    }
}


//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
