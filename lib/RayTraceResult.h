//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_RAYTRACERESULT_H
#define EXT_POCKETMINE_MATH_RAYTRACERESULT_H

#include "AxisAlignedBB.h"

/**
 * Class representing a ray trace collision with an AxisAlignedBB
 */
class RayTraceResult {
public:
    const AxisAlignedBB *bb;
    int hitFace;
    const Vector3 *hitVector;

    RayTraceResult(const AxisAlignedBB *bb, int hitFace, const Vector3 *hitVector) {
        this->bb = bb;
        this->hitFace = hitFace;
        this->hitVector = hitVector;
    }

    const AxisAlignedBB *getBoundingBox();

    int getHitFace();

    const Vector3 *getHitVector();
};

#endif //EXT_POCKETMINE_MATH_RAYTRACERESULT_H
