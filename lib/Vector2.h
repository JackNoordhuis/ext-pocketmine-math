//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_VECTOR2_H
#define EXT_POCKETMINE_MATH_VECTOR2_H

#include <cmath>

class Vector2 {
public:
    double x;
    double y;

    explicit Vector2(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
    }

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

    int getFloorX() {
        return (int) std::floor(x);
    }

    int getFloorY() {
        return (int) std::floor(y);
    }

    Vector2 *add(double x, double y) {
        return new Vector2(this->x + x, this->y + y);
    }

    Vector2 *add(const Vector2 *vector) {
        return add(vector->x, vector->y);
    }

    Vector2 *subtract(double x, double y) {
        return add(-x, -y);
    }

    Vector2 *subtract(const Vector2 *vector) {
        return add(-vector->x, -vector->y);
    }

    Vector2 *ceil() {
        return new Vector2((int) std::ceil(x), (int) std::ceil(y));
    }

    Vector2 *floor() {
        return new Vector2((int) std::floor(x), (int) std::floor(y));
    }

    Vector2 *round() {
        return new Vector2((int) std::round(x), (int) std::round(y));
    }

    Vector2 *abs() {
        return new Vector2((int) std::abs(x), (int) std::abs(y));
    }

    Vector2 *multiply(double number) {
        return new Vector2(x * number, y * number);
    }

    Vector2 *divide(double number) {
        return new Vector2(x / number, y / number);
    }

    double distance(double x, double y) {
        return std::sqrt(distanceSquared(x, y));
    }

    double distance(const Vector2 *vector) {
        return distance(vector->x, vector->y);
    }

    double distanceSquared(double x, double y) {
        return std::pow(this->x - x, 2) + std::pow(this->y - y, 2);
    }

    double distanceSquared(const Vector2 *vector) {
        return distanceSquared(vector->x, vector->y);
    }

    double length() {
        return std::sqrt(lengthSquared());
    }

    double lengthSquared() {
        return x * x + y * y;
    }

    Vector2 *normalize() {
        double length = lengthSquared();
        if(length > 0) {
            return divide(std::sqrt(length));
        }

        return new Vector2(0, 0);
    }

    double dot(const Vector2 *v) {
        return x * v->x +y * v->y;
    }
};
#endif //EXT_POCKETMINE_MATH_VECTOR2_H
