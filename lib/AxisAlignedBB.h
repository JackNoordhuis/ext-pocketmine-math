//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_AXISALIGNEDBB_H
#define EXT_POCKETMINE_MATH_AXISALIGNEDBB_H

#include "Vector3.h"
#include "RayTraceResult.h"

class AxisAlignedBB {
public:
    float minX, minY, minZ, maxX, maxY, maxZ;

    /**
     * AxisAlignedBB constructor.
     *
     * @param minX
     * @param minY
     * @param minZ
     * @param maxX
     * @param maxY
     * @param maxZ
     */
    AxisAlignedBB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    /**
     *
     * @param minX
     * @param minY
     * @param minZ
     * @param maxX
     * @param maxY
     * @param maxZ
     *
     * @return this
     */
    AxisAlignedBB setBounds(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    /**
     * Sets the bounding box's bounds from another AxisAlignedBB, and returns itself.
     *
     * @param bb
     *
     * @return this
     */
    AxisAlignedBB setBB(AxisAlignedBB bb);

    /**
     * Returns a new AxisAlignedBB extended by the specified X, Y and Z.
	 * If each of X, Y and Z are positive, the relevant max bound will be increased. If negative, the relevant min
	 * bound will be decreased.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return New modified bb.
     */
    AxisAlignedBB addCoord(float x, float y, float z);

    /**
     * Outsets the bounds of this AxisAlignedBB by the specified X, Y and Z.
     *
     * @param x
     * @param y
     *
     * @return this
     */
    AxisAlignedBB expand(float x, float y, float );

    /**
     * Returns an expanded clone of this AxisAlignedBB.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return New modified bb.
     */
    AxisAlignedBB expandedCopy(float x, float y, float z);

    /**
     * Shifts this AxisAlignedBB by the given X, Y and Z.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return this
     */
    AxisAlignedBB offset(float x, float y, float z);

    /**
     * Returns an offset clone of this AxisAlignedBB.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return New modified bb.
     */
    AxisAlignedBB offsetCopy(float x, float y, float z);

    /**
     * Insets the bounds of this AxisAlignedBB by the specified X, Y and Z.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return this
     */
    AxisAlignedBB contract(float x, float y, float z);

    /**
     * Returns a contracted clone of this AxisAlignedBB.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return New modified bb.
     */
    AxisAlignedBB contractCopy(float x, float y, float z);

    /**
     *
     * @param bb
     * @param x
     *
     * @return
     */
    float calculateXOffset(AxisAlignedBB bb, float x);

    /**
     *
     * @param bb
     * @param y
     *
     * @return
     */
    float calculateYOffset(AxisAlignedBB bb, float y);

    /**
     *
     * @param bb
     * @param z
     *
     * @return
     */
    float calculateZOffset(AxisAlignedBB bb, float z);

    /**
     * Returns whether any part of the specified AABB is inside (intersects with) this one.
     *
     * @param bb
     * @param epsilon
     *
     * @return
     */
    bool intersectsWith(AxisAlignedBB bb, float epsilon = 0.00001);

    /**
     * Returns whether the specified vector is within the bounds of this AABB on all axes.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInside(Vector3 vector);

    /**
     * Returns the mean average of the AABB's X, Y and Z lengths.
     *
     * @return
     */
    float getAverageEdgeLength();

    /**
     * Returns whether the specified vector is within the Y and Z bounds of this AABB.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInYZ(Vector3 vector);

    /**
     * Returns whether the specified vector is within the X and Z bounds of this AABB.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInXZ(Vector3 vector);

    /**
     * Returns whether the specified vector is within the X and Y bounds of this AABB.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInXY(Vector3 vector);

    /**
     * Performs a ray-trace and calculates the point on the AABB's edge nearest the start position that the ray-trace
	 * collided with. Returns a RayTraceResult with colliding vector closest to the start position.
	 * Returns null if no colliding point was found.
     *
     * @param pos1
     * @param pos2
     *
     * @return
     */
    RayTraceResult *calculateIntercept(Vector3 pos1, Vector3 pos2);
};

#endif //EXT_POCKETMINE_MATH_AXISALIGNEDBB_H
