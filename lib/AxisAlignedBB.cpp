//
// Created by Jack Noordhuis on 25/10/18.
//

#include "AxisAlignedBB.h"

#include "Vector3.h"
#include "RayTraceResult.h"
#include "Facing.h"

#include <stdexcept>
#include <string>

AxisAlignedBB *AxisAlignedBB::setBounds(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    if(minX > maxX) {
        throw std::invalid_argument("minX " + std::to_string(minX) + " is larger than maxX " + std::to_string(maxX));
    }

    if(minY > maxY) {
        throw std::invalid_argument("minY " + std::to_string(minY) + " is larger than maxY " + std::to_string(maxY));
    }

    if(minZ > maxZ) {
        throw std::invalid_argument("minZ " + std::to_string(minZ) + " is larger than maxZ " + std::to_string(maxZ));
    }

    this->minX = minX;
    this->minY = minY;
    this->minZ = minZ;
    this->maxX = maxX;
    this->maxY = maxY;
    this->maxZ = maxZ;

    return this;
}

AxisAlignedBB *AxisAlignedBB::addCoord(float x, float y, float z) {
    float minX = this->minX;
    float minY = this->minY;
    float minZ = this->minZ;
    float maxX = this->maxX;
    float maxY = this->maxY;
    float maxZ = this->maxZ;

    if(x < 0) {
        minX += x;
    } else if(x > 0) {
        maxX += x;
    }

    if(y < 0) {
        minY += y;
    } else if(y > 0) {
        maxY += y;
    }

    if(z < 0) {
        minZ += z;
    } else if(z > 0) {
        maxZ += z;
    }

    return new AxisAlignedBB(minX, minY, minZ, maxX, maxY, maxZ);
}

float AxisAlignedBB::calculateXOffset(const AxisAlignedBB *bb, float x) {
    if(bb->maxY <= minZ or bb->minY >= maxY) {
        return x;
    }

    if(bb->maxZ <= minZ or bb->minZ >= maxZ) {
        return x;
    }

    if(x > 0 and bb->maxX <= minX) {
        float x1 = minX - bb->maxX;
        if(x1 < x) {
            x = x1;
        }
    } else if(x < 0 and bb->minX >= maxX) {
        float x2 = maxX - bb->minX;
        if(x2 > x) {
            x = x2;
        }
    }

    return x;
}

float AxisAlignedBB::calculateYOffset(const AxisAlignedBB *bb, float y) {
    if(bb->maxX <= minX or bb->minX >= maxX) {
        return y;
    }

    if(bb->maxZ <= minZ or bb->minZ >= maxZ) {
        return y;
    }

    if(y > 0 and bb->maxY <= minY) {
        float y1 = minY - bb->maxY;
        if(y1 < y) {
            y = y1;
        }
    } else if(y < 0 and bb->minY >= maxY) {
        float y2 = maxY - bb->minY;
        if(y2 > y) {
            y = y2;
        }
    }

    return y;
}

float AxisAlignedBB::calculateZOffset(const AxisAlignedBB *bb, float z) {
    if(bb->maxX <= minX or bb->minX >= maxX) {
        return z;
    }

    if(bb->maxY <= minY or bb->minY >= maxY) {
        return z;
    }

    if(z > 0 and bb->maxZ <= minZ) {
        float z1 = minZ - bb->maxZ;
        if(z1 < z) {
            z = z1;
        }
    } else if(z < 0 and bb->minZ >= maxZ) {
        float z2 = maxZ - bb->minZ;
        if(z2 > z) {
            z = z2;
        }
    }

    return z;
}

bool AxisAlignedBB::intersectsWith(const AxisAlignedBB *bb, float epsilon) {
    if(bb->maxX - minX > epsilon and maxX - bb->minX > epsilon) {
        if(bb->maxY - minY > epsilon and maxY - bb->minY > epsilon) {
            return bb->maxZ - minZ > epsilon and maxZ - bb->minZ > epsilon;
        }
    }

    return false;
}

bool AxisAlignedBB::isVectorInside(const Vector3 *vector) {
    if(vector->x <= minX or vector->x >= maxX) {
        return false;
    }

    if(vector->y <= minY or vector->y >= maxY) {
        return false;
    }

    return vector->z > minZ and vector->z < maxZ;
}

bool AxisAlignedBB::isVectorInYZ(const Vector3 *vector) {
    return vector->y >= minY and vector->y <= maxY and vector->z >= minZ and vector->z <= maxZ;
}

bool AxisAlignedBB::isVectorInXZ(const Vector3 *vector) {
    return vector->x >= minX and vector->x <= maxX and vector->z >= minZ and vector->z <= maxZ;
}

bool AxisAlignedBB::isVectorInXY(const Vector3 *vector) {
    return vector->x >= minX and vector->x <= maxX and vector->y >= minY and vector->y <= maxY;
}

RayTraceResult *AxisAlignedBB::calculateIntercept(const Vector3 *pos1, const Vector3 *pos2) {
    const Vector3 *v1 = pos1->getIntermediateWithXValue(pos2, minX);
    const Vector3 *v2 = pos1->getIntermediateWithXValue(pos2, maxX);
    const Vector3 *v3 = pos1->getIntermediateWithYValue(pos2, minY);
    const Vector3 *v4 = pos1->getIntermediateWithYValue(pos2, maxY);
    const Vector3 *v5 = pos1->getIntermediateWithZValue(pos2, minZ);
    const Vector3 *v6 = pos1->getIntermediateWithZValue(pos2, maxZ);

    if(v1 != nullptr and !isVectorInYZ(v1)) {
        v1 = nullptr;
    }

    if(v2 != nullptr and !isVectorInYZ(v2)) {
        v2 = nullptr;
    }

    if(v3 != nullptr and !isVectorInXZ(v3)) {
        v3 = nullptr;
    }

    if(v4 != nullptr and !isVectorInXZ(v4)) {
        v4 = nullptr;
    }

    if(v5 != nullptr and !isVectorInXY(v5)) {
        v5 = nullptr;
    }

    if(v6 != nullptr and !isVectorInXY(v6)) {
        v6 = nullptr;
    }

    const Vector3 *vector = nullptr;
    int64_t distance = INT64_MAX;

    const Vector3 *vectors[] = {v1, v2, v3, v4, v5, v6};
    for(const Vector3 *v : vectors) {
        double d = pos1->distanceSquared(v);
        if(v != nullptr and d < distance) {
            vector = v;
            distance = (int64_t)d;
        }
    }

    int f = -1;

    if(vector == v1) {
        f = Facing::WEST;
    } else if(vector == v2) {
        f = Facing::EAST;
    } else if(vector == v3) {
        f = Facing::DOWN;
    } else if(vector == v4) {
        f = Facing::UP;
    } else if(vector == v5) {
        f = Facing::NORTH;
    } else if(vector == v6) {
        f = Facing::SOUTH;
    }

    return new RayTraceResult(this, f, vector);
}