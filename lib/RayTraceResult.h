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
    AxisAlignedBB bb;
    int hitFace;
    Vector3 hitVector;

    RayTraceResult(AxisAlignedBB bb, int hitFace, Vector3 hitVector) {
        RayTraceResult::bb = bb;
        RayTraceResult::hitFace = hitFace;
        RayTraceResult::hitVector = hitVector;
    }

    AxisAlignedBB getBoundingBox();

    int getHitFace();

    Vector3 getHitVector();
};

#endif //EXT_POCKETMINE_MATH_RAYTRACERESULT_H
