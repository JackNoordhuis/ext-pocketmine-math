//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_MATRIX_H
#define EXT_POCKETMINE_MATH_MATRIX_H

#include <map>

class Matrix {
private:
    std::map<int, int> matrix;
    int rows = 0;
    int columns = 0;
public:

    bool offsetExists(int offset);

    int offsetGet(int offset);

    void offsetSet(int offset, int value);

    void offsetUnset(int offset);

    Matrix(int rows, int columns, std::map<int, int> *set) {
        Matrix::rows = rows;
        Matrix::columns = columns;
        Matrix::set(set);
    }

    void set(std::map<int, int> *m);

    int getRows();

    int getColumns();

    bool setElement(int row, int column, int value);

    int *getElement(int row, int column);

    bool isSquare();

    Matrix *add(const Matrix *matrix);

    Matrix *subtract(const Matrix *matrix);

    Matrix *multiplyScalar(const Matrix *matrix);

    Matrix *divideScalar(const Matrix *matrix);

    Matrix *transpose(const Matrix *matrix);

    Matrix *determinant(const Matrix *matrix);
};

#endif //EXT_POCKETMINE_MATH_MATRIX_H
