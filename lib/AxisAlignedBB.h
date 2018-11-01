//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_AXISALIGNEDBB_H
#define EXT_POCKETMINE_MATH_AXISALIGNEDBB_H

class Vector3; // forward declare to avoid include
class RayTraceResult; // forward declare to avoid include

class AxisAlignedBB {
public:
    double minX = 0;
    double minY = 0;
    double minZ = 0;
    double maxX = 0;
    double maxY = 0;
    double maxZ = 0;

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
    AxisAlignedBB(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
        setBounds(minX, minY, minZ, maxX, maxY, maxZ);
    }

    /**
     * Create a clone of an existing AxisAlignedBB.
     *
     * @param old
     */
    explicit AxisAlignedBB(const AxisAlignedBB *old) {
        setBounds(old->minX, old->minY, old->minZ, old->maxX, old->maxY, old->maxZ);
    }

    /**
     * @param minX
     * @param minY
     * @param minZ
     * @param maxX
     * @param maxY
     * @param maxZ
     *
     * @return this
     */
    AxisAlignedBB *setBounds(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);

    /**
     * Sets the bounding box's bounds from another AxisAlignedBB, and returns itself.
     *
     * @param bb
     *
     * @return this
     */
    AxisAlignedBB *setBB(const AxisAlignedBB *bb) {
        return setBounds(bb->minX, bb->minY, bb->minZ, bb->maxX, bb->maxY, bb->maxZ);
    }

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
    AxisAlignedBB *addCoord(double x, double y, double z);

    /**
     * Outsets the bounds of this AxisAlignedBB by the specified X, Y and Z.
     *
     * @param x
     * @param y
     *
     * @return this
     */
    AxisAlignedBB *expand(double x, double y, double z) {
        minX -= x;
        minY -= y;
        minZ -= z;
        maxX += x;
        maxY += y;
        maxZ += z;

        return this;
    }

    /**
     * Returns an expanded clone of this AxisAlignedBB.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return New modified bb.
     */
    AxisAlignedBB *expandedCopy(double x, double y, double z) {
        return (new AxisAlignedBB(this))->expand(x, y, z);
    }

    /**
     * Shifts this AxisAlignedBB by the given X, Y and Z.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return this
     */
    AxisAlignedBB *offset(double x, double y, double z) {
        minX += x;
        minY += y;
        minZ += z;
        maxX += x;
        maxY += y;
        maxZ += z;

        return this;
    }

    /**
     * Returns an offset clone of this AxisAlignedBB.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return New modified bb.
     */
    AxisAlignedBB *offsetCopy(double x, double y, double z) {
        return (new AxisAlignedBB(this))->offset(x, y, z);
    }

    /**
     * Insets the bounds of this AxisAlignedBB by the specified X, Y and Z.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return this
     */
    AxisAlignedBB *contract(double x, double y, double z) {
        minX += x;
        minY += y;
        minZ += z;
        maxX -= x;
        maxY -= y;
        maxZ -= z;

        return this;
    }

    /**
     * Returns a contracted clone of this AxisAlignedBB.
     *
     * @param x
     * @param y
     * @param z
     *
     * @return New modified bb.
     */
    AxisAlignedBB *contractCopy(double x, double y, double z) {
        return (new AxisAlignedBB(this))->contract(x, y, z);
    }

    /**
     * @param bb
     * @param x
     *
     * @return
     */
    double calculateXOffset(const AxisAlignedBB *bb, double x);

    /**
     * @param bb
     * @param y
     *
     * @return
     */
    double calculateYOffset(const AxisAlignedBB *bb, double y);

    /**
     * @param bb
     * @param z
     *
     * @return
     */
    double calculateZOffset(const AxisAlignedBB *bb, double z);

    /**
     * Returns whether any part of the specified AABB is inside (intersects with) this one.
     *
     * @param bb
     * @param epsilon
     *
     * @return
     */
    bool intersectsWith(const AxisAlignedBB *bb, double epsilon = 0.00001);

    /**
     * Returns whether the specified vector is within the bounds of this AABB on all axes.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInside(const Vector3 *vector);

    /**
     * Returns the mean average of the AABB's X, Y and Z lengths.
     *
     * @return
     */
    double getAverageEdgeLength() {
        return (maxX - minX + maxY - minY + maxZ - minZ) / 3;
    }

    /**
     * Returns whether the specified vector is within the Y and Z bounds of this AABB.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInYZ(const Vector3 *vector);

    /**
     * Returns whether the specified vector is within the X and Z bounds of this AABB.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInXZ(const Vector3 *vector);

    /**
     * Returns whether the specified vector is within the X and Y bounds of this AABB.
     *
     * @param vector
     *
     * @return
     */
    bool isVectorInXY(const Vector3 *vector);

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
    RayTraceResult *calculateIntercept(const Vector3 *pos1, const Vector3 *pos2);
};

#endif //EXT_POCKETMINE_MATH_AXISALIGNEDBB_H
