//
// Created by Jack Noordhuis on 11/11/18.
//

#include "Vector2.h"

#include <cmath>

int Vector2::getFloorX() {
    return (int) ::floor(x);
}

int Vector2::getFloorY() {
    return (int) ::floor(y);
}

Vector2 *Vector2::ceil() {
    return new Vector2((int) ::ceil(x), (int) ::ceil(y));
}

Vector2 *Vector2::floor() {
    return new Vector2((int) ::floor(x), (int) ::floor(y));
}

Vector2 *Vector2::round() {
    return new Vector2((int) ::round(x), (int) ::round(y));
}

Vector2 *Vector2::abs() {
    return new Vector2((int) ::abs(x), (int) ::abs(y));
}

double Vector2::distance(double x, double y) {
    return ::sqrt(distanceSquared(x, y));
}

double Vector2::distanceSquared(double x, double y) {
    return ::pow(this->x - x, 2) + ::pow(this->y - y, 2);
}

double Vector2::length() {
    return ::sqrt(lengthSquared());
}

Vector2 *Vector2::normalize() {
    double length = lengthSquared();
    if(length > 0) {
        return divide(::sqrt(length));
    }

    return new Vector2(0, 0);
}