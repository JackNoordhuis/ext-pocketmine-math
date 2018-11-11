//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_VECTOR2_H
#define EXT_POCKETMINE_MATH_VECTOR2_H

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

    int getFloorX();

    int getFloorY();

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

    Vector2 *ceil();

    Vector2 *floor();

    Vector2 *round();

    Vector2 *abs();

    Vector2 *multiply(double number) {
        return new Vector2(x * number, y * number);
    }

    Vector2 *divide(double number) {
        return new Vector2(x / number, y / number);
    }

    double distance(double x, double y);

    double distance(const Vector2 *vector) {
        return distance(vector->x, vector->y);
    }

    double distanceSquared(double x, double y);

    double distanceSquared(const Vector2 *vector) {
        return distanceSquared(vector->x, vector->y);
    }

    double length();

    double lengthSquared() {
        return x * x + y * y;
    }

    Vector2 *normalize();

    double dot(const Vector2 *v) {
        return x * v->x +y * v->y;
    }
};
#endif //EXT_POCKETMINE_MATH_VECTOR2_H
