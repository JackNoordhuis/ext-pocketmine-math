//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_VECTORMATH_H
#define EXT_POCKETMINE_MATH_VECTORMATH_H

class Vector2; // forward declare to avoid include

class VectorMath {
public:
    static Vector2 *getDirection2D(double azimuth);
};

#endif //EXT_POCKETMINE_MATH_VECTORMATH_H
