//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_VECTOR3_H
#define EXT_POCKETMINE_MATH_VECTOR3_H

class Vector3 {
public:
    double x;
    double y;
    double z;

    Vector3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getX();

    double getY();

    double getZ();

    int getFloorX();

    int getFloorY();

    int getFloorZ();

    Vector3 *add(double x, double y, double z);

    Vector3 *subtract(double number);

    Vector3 *multiply(double x, double y);

    Vector3 *divide(double number);

    Vector3 *ceil();

    Vector3 *floor();

    Vector3 *round(double precision);

    Vector3 *abs();

    Vector3 *getSide(int side, int step = 1);

    Vector3 *down(int step = 1);

    Vector3 *up(int step = 1);

    Vector3 *north(int step = 1);

    Vector3 *south(int step = 1);

    Vector3 *west(int step = 1);

    Vector3 *east(int step = 1);

    /**
     *Yields vectors stepped out from this one in directions except those on the given axis.
     *
     * @param axis Facing directions on this axis will be excluded
     * @param step
     *
     * //TODO: Return PHP Generator
     */
    void sidesAroundAxis(int axis, int step = 1);

    /**
     * Return a Vector3 instance.
     *
     * @return
     */
    Vector3 *asVector3();

    double distance(double x, double y);

    double maxPlainDistance(double x, double y, double z);

    double length();

    double lengthSquared();

    Vector3 *normalize();

    double cross(const Vector3 *v);

    bool equals(const Vector3 *v);

    /**
     * Returns a new vector with x value equal to the second parameter, along the line between this vector and the
	 * passed in vector, or null if not possible.
     *
     * @param v
     * @param x
     *
     * @return
     */
    Vector3 *getIntermediateWithXValue(const Vector3 *v, double x);

    /**
     * Returns a new vector with y value equal to the second parameter, along the line between this vector and the
	 * passed in vector, or null if not possible.
     *
     * @param v
     * @param y
     *
     * @return
     */
    Vector3 *getIntermediateWithYValue(const Vector3 *v, double y);

    /**
     * Returns a new vector with z value equal to the second parameter, along the line between this vector and the
	 * passed in vector, or null if not possible.
     *
     * @param v
     * @param z
     *
     * @return
     */
    Vector3 *getIntermediateWithZValue(const Vector3 *v, double z);

    Vector3 *setComponents(double x, double y, double z);
};

#endif //EXT_POCKETMINE_MATH_VECTOR3_H
