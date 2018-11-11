//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_VECTOR3_H
#define EXT_POCKETMINE_MATH_VECTOR3_H

#include "Math.h"

class Vector2 {
public:
    double x, y;
}; // forward declare to avoid include

class Vector3 {
public:
    double x;
    double y;
    double z;

    explicit Vector3(double x = 0, double y = 0, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

    double getZ() {
        return z;
    }

    int getFloorX();

    int getFloorY();

    int getFloorZ();

    Vector3 *add(double x, double y, double z) {
        return new Vector3(this->x + x, this->y + y, this->z + z);
    }

    Vector3 *add(const Vector3 *vector) {
        return add(vector->x, vector->y, vector->z);
    }

    Vector3 *subtract(double x, double y, double z) {
        return add(-x, -y, -z);
    }

    Vector3 *subtract(const Vector3 *vector) {
        return add(-vector->x, -vector->y, -vector->z);
    }

    Vector3 *multiply(double number) {
        return new Vector3(x * number, y * number, z * number);
    }

    Vector3 *divide(double number) {
        return new Vector3(x / number, y / number, z / number);
    }

    Vector3 *ceil();

    Vector3 *floor();

    Vector3 *round(int precision = 0, int mode = POCKETMINE_MATH_ROUND_HALF_UP);

    Vector3 *abs();

    /**
     * @param side
     * @param step
     * @return
     */
    Vector3 *getSide(int side, int step = 1);

    Vector3 *down(int step = 1);

    Vector3 *up(int step = 1);

    Vector3 *north(int step = 1);

    Vector3 *south(int step = 1);

    Vector3 *west(int step = 1);

    Vector3 *east(int step = 1);

    /**
    * Yields vectors stepped out from this one in all directions.
    *
    * @param step
    */
    void sides(int step = 1);

    /**
     * Same as sides() but returns a pre-populated array instead of Generator.
     *
     * @param keys
     * @param step
     */
    void sidesArray(bool keys = false, int step = 1);

    /**
     * Yields vectors stepped out from this one in directions except those on the given axis.
     *
     * @param axis Facing directions on this axis will be excluded
     * @param step
     */
    void sidesAroundAxis(int axis, int step = 1);

    /**
     * Return a Vector3 instance.
     *
     * @return
     */
    Vector3 *asVector3() {
        return new Vector3(x, y, z);
    }

    /**
     * @param vector
     * @return
     */
    double distance(const Vector3 *vector);

    /**
     * @param vector
     * @return
     */
    double distanceSquared(const Vector3 *vector);

    /**
     * @param x
     * @param z
     * @return
     */
    double maxPlainDistance(double x, double z);

    /**
     * @param vector
     * @return
     */
    double maxPlainDistance(const Vector2 *vector) {
        return maxPlainDistance(vector->x, vector->y);
    }

    /**
     * @param vector
     * @return
     */
    double maxPlainDistance(const Vector3 *vector) {
        return maxPlainDistance(vector->x, vector->y);
    }

    /**
     * @return
     */
    double length();

    /**
     * @return
     */
    double lengthSquared() {
        return x * x + y * y + z * z;
    }

    /**
     * @return
     */
    Vector3 *normalize();

    /**
     * @param v
     * @return
     */
    Vector3 *cross(const Vector3 *v) {
        return new Vector3(
            y * v->z - z * v->y,
            z * v->x - x * v->z,
            x * v->y - y * v->x
        );
    }

    /**
     * @param v
     * @return
     */
    bool equals(const Vector3 *v) {
        return x == v->x and y == v->y and z == v->z;
    }

    /**
     * Returns a new vector with x value equal to the second parameter, along the line between this vector and the
	 * passed in vector, or null if not possible.
     *
     * @param v
     * @param x
     *
     * @return
     */
    Vector3 *getIntermediateWithXValue(const Vector3 *v, double x) {
        double xDiff = v->x - this->x;
        if((xDiff * xDiff) < 0.0000001) {
            return nullptr;
        }

        double f = (x - this->x) / xDiff;

        if(f < 0 or f > 1) {
            return nullptr;
        }

        return new Vector3(x, this->y + (v->y - this->y) * f, this->z + (v->z - this->z) * f);
    }

    /**
     * Returns a new vector with y value equal to the second parameter, along the line between this vector and the
	 * passed in vector, or null if not possible.
     *
     * @param v
     * @param y
     *
     * @return
     */
    Vector3 *getIntermediateWithYValue(const Vector3 *v, double y) {
        double yDiff = v->y - this->y;
        if((yDiff * yDiff) < 0.0000001) {
            return nullptr;
        }

        double f = (y - this->y) / yDiff;

        if(f < 0 or f > 1) {
            return nullptr;
        }

        return new Vector3(this->x + (v->x - this->x) * f, y, this->z + (v->z - this->z) * f);
    }

    /**
     * Returns a new vector with z value equal to the second parameter, along the line between this vector and the
	 * passed in vector, or null if not possible.
     *
     * @param v
     * @param z
     *
     * @return
     */
    Vector3 *getIntermediateWithZValue(const Vector3 *v, double z) {
        double zDiff = v->z - this->z;
        if((zDiff * zDiff) < 0.0000001) {
            return nullptr;
        }

        double f = (z - this->z) / zDiff;

        if(f < 0 or f > 1) {
            return nullptr;
        }

        return new Vector3(this->x + (v->x - this->x) * f, this->y + (v->y - this->y) * f, z);
    }

    /**
     * @param x
     * @param y
     * @param z
     * @return
     */
    Vector3 *setComponents(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
        return this;
    }
};

#endif //EXT_POCKETMINE_MATH_VECTOR3_H
