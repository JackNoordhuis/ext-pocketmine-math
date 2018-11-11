//
// Created by Jack Noordhuis on 11/11/18.
//

#include "VectorMath.h"

#include "Vector2.h"
#include <cmath>

Vector2 *VectorMath::getDirection2D(double azimuth) {
    return new Vector2(::cos(azimuth), ::sin(azimuth));
}