//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_MATH_H
#define EXT_POCKETMINE_MATH_MATH_H

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

    /**
     * Solves a quadratic equation with the given coefficients and returns an array of up to two solutions.
     *
     * @param a
     * @param b
     * @param c
     *
     * @return pointer to an array of possible solutions.
     */
    static std::vector<double> solveQuadratic(double a, double b, double c);
};

/* Define rounding modes (all are round-to-nearest) */
#ifndef POCKETMINE_MATH_ROUND_HALF_UP
#define POCKETMINE_MATH_ROUND_HALF_UP        0x01    /* Arithmetic rounding, up == away from zero */
#endif

#ifndef POCKETMINE_MATH_ROUND_HALF_DOWN
#define POCKETMINE_MATH_ROUND_HALF_DOWN      0x02    /* Down == towards zero */
#endif

#ifndef POCKETMINE_MATH_ROUND_HALF_EVEN
#define POCKETMINE_MATH_ROUND_HALF_EVEN      0x03    /* Banker's rounding */
#endif

#ifndef POCKETMINE_MATH_ROUND_HALF_ODD
#define POCKETMINE_MATH_ROUND_HALF_ODD       0x04
#endif

static inline double pocketmine_math_round_helper(double value, int mode);

static inline double pocketmine_math_round(double value, int places, int mode);

#endif //EXT_POCKETMINE_MATH_MATH_H
