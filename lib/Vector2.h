//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_VECTOR2_H
#define EXT_POCKETMINE_MATH_VECTOR2_H

class Vector2 {
public:
    double x;
    double y;

    Vector2(double x = 0, double y = 0) {
        Vector2::x = x;
        Vector2::y = y;
    }

    double getX();

    double getY();

    int getFloorX();

    int getFloorY();

    Vector2 *add(double x, double y);

    Vector2 *subtract(double x, double y);

    Vector2 *ceil(double x, double y);

    Vector2 *floor(double x, double y);

    Vector2 *round(double x, double y);

    Vector2 *abs(double x, double y);

    Vector2 *multiply(double x, double y);

    Vector2 *divide(double x, double y);

    double distance(double x, double y);

    double distanceSquared(double x, double y);

    double length();

    Vector2 *normalize();

    double dot(Vector2 *v);
};
#endif //EXT_POCKETMINE_MATH_VECTOR2_H
