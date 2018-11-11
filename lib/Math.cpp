//
// Created by Jack Noordhuis on 11/11/18.
//

#include "Math.h"

#include <cmath>

std::vector<double> Math::solveQuadratic(double a, double b, double c) {
    double discriminant = pow(b, 2) - 4 * a * c;
    if(discriminant > 0) { // 2 real roots
        double sqrtDiscriminant = sqrt(discriminant);
        return std::vector<double> {
                (-b + sqrtDiscriminant) / (2 * a),
                (-b - sqrtDiscriminant) / (2 * a)
        };
    } else if(discriminant == 0) { // 1 real root
        return std::vector<double> {
                -b / (2 * a)
        };
    }

    return std::vector<double> {};
}

static inline double pocketmine_math_round_helper(double value, int mode) {
    double tmp_value;

    if(value >= 0.0) {
        tmp_value = floor(value + 0.5);
        if(
                (mode == POCKETMINE_MATH_ROUND_HALF_DOWN and value == (-0.5 + tmp_value)) or
                (mode == POCKETMINE_MATH_ROUND_HALF_EVEN and value == (0.5 + 2 * floor(tmp_value / 2.0))) or
                (mode == POCKETMINE_MATH_ROUND_HALF_ODD  and value == (0.5 + 2 * floor(tmp_value / 2.0) - 1.0)))
        {
            tmp_value = tmp_value - 1.0;
        }
    } else {
        tmp_value = ceil(value - 0.5);
        if(
                (mode == POCKETMINE_MATH_ROUND_HALF_DOWN and value == (0.5 + tmp_value)) or
                (mode == POCKETMINE_MATH_ROUND_HALF_EVEN and value == (-0.5 + 2 * ceil(tmp_value / 2.0))) or
                (mode == POCKETMINE_MATH_ROUND_HALF_ODD  and value == (-0.5 + 2 * ceil(tmp_value / 2.0) + 1.0)))
        {
            tmp_value = tmp_value + 1.0;
        }
    }

    return tmp_value;
}

static inline double pocketmine_math_round(double value, int places, int mode) {
    double f1, f2;
    double tmp_value;
    int precision_places;

    if(!isfinite(value)) {
        return value;
    }

    places = places < INT_MIN + 1 ? INT_MIN + 1 : places;
    precision_places = 14 - (int)floor(log10(fabs(value)));

    f1 = pow(10, abs(places));

    if(precision_places > places and precision_places - places < 15) {
        int64_t use_precision = precision_places < INT_MIN + 1 ? INT_MIN + 1 : precision_places;

        f2 = pow(10, abs((int)use_precision));
        if(use_precision >= 0) {
            tmp_value = value * f2;
        } else {
            tmp_value = value / f2;
        }

        tmp_value = pocketmine_math_round_helper(tmp_value, mode);

        use_precision = places - precision_places;
        use_precision = use_precision < INT_MIN + 1 ? INT_MIN + 1 : use_precision;

        f2 = pow(10, abs((int)use_precision));

        tmp_value = tmp_value / f2;
    } else {
        if(places >= 0) {
            tmp_value = value * f1;
        } else {
            tmp_value = value /= f1;
        }

        if(fabs(tmp_value) >= 1e15) {
            return value;
        }
    }

    tmp_value = pocketmine_math_round_helper(tmp_value, mode);

    if(abs(places) < 23) {
        if(places > 0) {
            tmp_value /= f1;
        } else {
            tmp_value *= f1;
        }
    } else {
        char buf[40];
        snprintf(buf, 39, "%15fe%d", tmp_value, -places);
        buf[39] = '\0';
        tmp_value = strtod(buf, NULL);
        if(!isfinite(tmp_value) or isnan(tmp_value)) {
            tmp_value = value;
        }
    }

    return tmp_value;
}