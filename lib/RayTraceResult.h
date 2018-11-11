//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_RAYTRACERESULT_H
#define EXT_POCKETMINE_MATH_RAYTRACERESULT_H

class AxisAlignedBB; // forward declare to avoid include
class Vector3; // forward declare to avoid include

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

    AxisAlignedBB *getBoundingBox() {
        return (AxisAlignedBB *)bb;
    }

    int getHitFace() {
        return hitFace;
    }

    Vector3 *getHitVector() {
        return (Vector3 *)hitVector;
    }
};

#endif //EXT_POCKETMINE_MATH_RAYTRACERESULT_H
