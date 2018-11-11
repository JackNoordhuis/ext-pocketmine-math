//
// Created by Jack Noordhuis on 11/11/18.
//

#include "Vector3.h"

#include "Facing.h"
#include <cmath>

int Vector3::getFloorX() {
    return (int) std::floor(x);
}

int  Vector3::getFloorY() {
    return (int) std::floor(y);
}

int Vector3::getFloorZ() {
    return (int) std::floor(z);
}

Vector3 *Vector3::ceil() {
    return new Vector3((int) std::ceil(x), (int) std::ceil(y), (int) std::ceil(z));
}

Vector3 *Vector3::floor() {
    return new Vector3((int) std::floor(x), (int) std::floor(y), (int) std::floor(z));
}

Vector3 *Vector3::round(int precision, int mode) {
    if(precision > 0) {
        return new Vector3(pocketmine_math_round(x, precision, mode), pocketmine_math_round(y, precision, mode), pocketmine_math_round(z, precision, mode));
    }
    return new Vector3((int) pocketmine_math_round(x, precision, mode), (int) pocketmine_math_round(y, precision, mode), (int) pocketmine_math_round(z, precision, mode));
}

Vector3 *Vector3::abs() {
    return new Vector3((int) std::abs(x), (int) std::abs(y), (int) std::abs(z));
}

/**
     * @param side
     * @param step
     * @return
     */
Vector3 *Vector3::getSide(int side, int step) {
    switch (side) {
        case Facing::DOWN:
            return new Vector3(x, y - step, z);
        case Facing::UP:
            return new Vector3(x, y + step, z);
        case Facing::NORTH:
            return new Vector3(x, y, z - step);
        case Facing::SOUTH:
            return new Vector3(x, y, z + step);
        case Facing::WEST:
            return new Vector3(x - step, y, z);
        case Facing::EAST:
            return new Vector3(x + step, y, z);
        default:
            return this;
    }
}

Vector3 *Vector3::down(int step) {
    return getSide(Facing::DOWN, step);
}

Vector3 *Vector3::up(int step) {
    return getSide(Facing::UP, step);
}

Vector3 *Vector3::north(int step) {
    return getSide(Facing::NORTH, step);
}

Vector3 *Vector3::south(int step) {
    return getSide(Facing::SOUTH, step);
}

Vector3 *Vector3::west(int step) {
    return getSide(Facing::WEST, step);
}

Vector3 *Vector3::east(int step) {
    return getSide(Facing::EAST, step);
}

void Vector3::sides(int step) {
    //TODO: Return PHP Generator
}

void Vector3::sidesArray(bool keys, int step) {
    //TODO: Convert generator output to array
}

void Vector3::sidesAroundAxis(int axis, int step) {
    //TODO: Return PHP Generator
}

double Vector3::distance(const Vector3 *vector) {
    return sqrt(distanceSquared(vector));
}

double Vector3::distanceSquared(const Vector3 *vector) {
    return pow(x - vector->x, 2) + pow(y - vector->y, 2) + pow(z - vector->z, 2);
}

double Vector3::maxPlainDistance(double x, double z) {
    return fmax(::abs(this->x - x), ::abs(this->z - z));
}

double Vector3::length() {
    return sqrt(lengthSquared());
}

Vector3 *Vector3::normalize() {
    double length = lengthSquared();
    if(length > 0) {
        return divide(sqrt(length));
    }

    return new Vector3();
}