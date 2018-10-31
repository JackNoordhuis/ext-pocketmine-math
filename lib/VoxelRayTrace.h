//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_VOXELRAYTRACE_H
#define EXT_POCKETMINE_MATH_VOXELRAYTRACE_H

#include "Vector3.h"

class VoxelRayTrace {
private:

    /**
     * Returns the distance that must be travelled on an axis from the start point with the direction vector component to
	 * cross a block boundary.
	 *
	 * For example, given an X coordinate inside a block and the X component of a direction vector, will return the distance
	 * travelled by that direction component to reach a block with a different X coordinate.
	 *
	 * Find the smallest positive t such that s+t*ds is an integer.
     *
     * @param s Starting coordinate.
     * @param ds Direction vector component of the relevant axis.
     *
     * @return Distance along the ray trace that must be travelled to cross a boundary.
     */
    static double rayTraceDistanceToBoundry(double s, double ds);

public:

    /**
     * Performs a ray trace from the start position in the given direction, for a distance of $maxDistance. This
	 * returns a Generator which yields Vector3s containing the coordinates of voxels it passes through.
     *
     * @param start
     * @param directionViewer
     * @param maxDistance
     *
     * //TODO: Return PHP Generator
     */
    static void inDirection(Vector3 *start, Vector3 *directionViewer, double maxDistance);

    /**
     * Performs a ray trace between the start and end coordinates. This returns a Generator which yields Vector3s
	 * containing the coordinates of voxels it passes through.
     *
     * @param start
     * @param end
     *
     * //TODO: Return PHP Generator
     */
    static void betweenPoints(Vector3 *start, Vector3 *end);
};

#endif //EXT_POCKETMINE_MATH_VOXELRAYTRACE_H
