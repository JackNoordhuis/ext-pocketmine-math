//
// Created by Jack Noordhuis on 11/11/18.
//

#include "VoxelRayTrace.h"

#include <cmath>

double *VoxelRayTrace::rayTraceDistanceToBoundry(double s, double ds) {
    if(ds == 0) {
        return nullptr;
    }

    if(ds < 0) {
        s = -s;
        ds = -ds;

        if(::floor(s) == s) { // exactly at coordinate, will leave the coordinate immediately by moving negatively
            return new double(0);
        }
    }

    return new double(1 - (s - floor(s)) / ds);
}

/**
 * Performs a ray trace from the start position in the given direction, for a distance of $maxDistance. This
 * returns a Generator which yields Vector3s containing the coordinates of voxels it passes through.
 *
 * @param start
 * @param directionViewer
 * @param maxDistance
 */
void VoxelRayTrace::inDirection(const Vector3 *start, const Vector3 *directionViewer, double maxDistance) {
    //TODO: Return PHP Generator
}

/**
 * Performs a ray trace between the start and end coordinates. This returns a Generator which yields Vector3s
 * containing the coordinates of voxels it passes through.
 *
 * @param start
 * @param end
 */
void VoxelRayTrace::betweenPoints(const Vector3 *start, const Vector3 *end) {
    //TODO: Return PHP Generator
}