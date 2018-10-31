//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_MATH_H
#define EXT_POCKETMINE_MATH_MATH_H

class Math {
public:

    /**
     * @param n
     *
     * @return
     */
    static int floorFloat(double n);

    /**
     * @param n
     *
     * @return
     */
    static int ceilFloat(double n);

    /***
     * Solves a quadratic equation with the given coefficients and returns an array of up to two solutions.
     *
     * @param a
     * @param b
     * @param c
     *
     * @return pointer to an array of possible solutions.
     */
    static double *solveQuadratic(double a, double b, double c);
};

#endif //EXT_POCKETMINE_MATH_MATH_H
