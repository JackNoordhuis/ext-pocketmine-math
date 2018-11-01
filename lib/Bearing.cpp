//
// Created by Jack Noordhuis on 25/10/18.
//

#include "Bearing.h"
#include "Facing.h"

#include <stdexcept>
#include <string>
#include <cmath>

int Bearing::toFacing(int bearing) {
    switch (bearing) {
        case NORTH:
            return Facing::NORTH;
        case SOUTH:
            return Facing::SOUTH;
        case WEST:
            return Facing::WEST;
        case EAST:
            return Facing::EAST;
        default:
            throw std::invalid_argument("Unknown 2D direction " + std::to_string(bearing));
    }
}

int Bearing::fromFacing(int facing) {
    switch (facing) {
        case Facing::NORTH:
            return NORTH;
        case Facing::SOUTH:
            return SOUTH;
        case Facing::WEST:
            return WEST;
        case Facing::EAST:
            return EAST;
        default:
            throw std::invalid_argument("Facing " + std::to_string(facing) + " does not have a corresponding 2D direction");
    }
}

int Bearing::fromAngle(double angle) {
    angle = std::fmod(angle, 360);
    if(angle < 0) {
        angle += 360;
    }

    if((angle >= 0 and angle < 45) or (angle >= 315 and angle < 360)) {
        return SOUTH;
    }

    if(angle >= 45 and angle < 135) {
        return WEST;
    }

    if(angle >= 135 and angle < 225) {
        return NORTH;
    }

    return EAST;
}