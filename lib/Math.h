//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_MATH_H
#define EXT_POCKETMINE_MATH_MATH_H

#include <cmath>
#include <vector>

class Math {
public:

    /**
     * @param n
     *
     * @return
     */
    static int floorFloat(double n) {
        int i = (int)n;
        return n >= i ? i : i - 1;
    }

    /**
     * @param n
     *
     * @return
     */
    static int ceilFloat(double n) {
        int i = (int)n;
        return n <= i ? i : i + 1;
    }

    /***
     * Solves a quadratic equation with the given coefficients and returns an array of up to two solutions.
     *
     * @param a
     * @param b
     * @param c
     *
     * @return pointer to an array of possible solutions.
     */
    static std::vector<double> solveQuadratic(double a, double b, double c) {
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
};

#endif //EXT_POCKETMINE_MATH_MATH_H
