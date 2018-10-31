//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_BEARING_H
#define EXT_POCKETMINE_MATH_BEARING_H

class Bearing {
public:
    const static int SOUTH = 0;
    const static int WEST = 1;
    const static int NORTH = 2;
    const static int EAST = 3;

    /**
     * Converts a 2D compass direction to a 3D axis direction.
     *
     * @param bearing
     *
     * @return 3D axis direction.
     */
    static int toFacing(int bearing);

    /**
     * Converts a 3D axis direction to a 2D compass direction.
     *
     * @param facing
     *
     * @return 2D compass direction.
     */
    static int fromFacing(int facing);

    static int fromAngle(double angle);

    static int rotate(int bearing, int step);

    static int opposite(int bearing);
};

#endif //EXT_POCKETMINE_MATH_BEARING_H
