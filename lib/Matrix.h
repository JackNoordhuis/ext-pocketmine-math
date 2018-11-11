//
// Created by Jack Noordhuis on 25/10/18.
//

#ifndef EXT_POCKETMINE_MATH_MATRIX_H
#define EXT_POCKETMINE_MATH_MATRIX_H

#include <map>

class Matrix {
private:
    std::map<int, std::map<int, int>> matrix;
    int rows = 0;
    int columns = 0;
public:

    bool offsetExists(int offset) {
        return matrix.find(offset) == matrix.end();
    }

    std::map<int, int> *offsetGet(int offset) {
        return &matrix.at(offset);
    }

    void offsetSet(int offset, std::map<int, int> *value) {
        matrix[offset] = *value;
    }

    void offsetUnset(int offset) {
        matrix.erase(offset);
    }

    Matrix(int rows, int columns, std::map<int, std::map<int, int>> *set = nullptr) {
        this->rows = rows;
        this->columns = columns;
        this->matrix = *set;
    }

    /**
     * Create a clone of an existing AxisAlignedBB.
     *
     * @param old The matrix to clone from.
     */
    explicit Matrix(const Matrix* old) {
        rows = old->rows;
        columns = old->columns;
        matrix = old->matrix;
    }

    void set(std::map<int, std::map<int, int>> *m) {
        matrix = *m;
    }

    int getRows() {
        return rows;
    }

    int getColumns() {
        return columns;
    }

    bool setElement(int row, int column, int value) {
        if(row > this->rows or row < 0 or column > this->columns or column < 0) {
            return false;
        }
        std::map<int, int> v;
        matrix[row][column] = value;

        return true;
    }

    int *getElement(int row, int column) {
        if(row > this->rows or row < 0 or column > this->columns or column < 0) {
            return nullptr;
        }

        return &matrix.at(row).at(column);
    }

    bool isSquare() {
        return rows == columns;
    }

    Matrix *add(Matrix *matrix) {
        if(rows != matrix->getRows() or columns != matrix->getColumns()) {
            return nullptr;
        }

        auto *result = new Matrix(rows, columns);
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < columns; ++c) {
                result->setElement(r, c, *getElement(r, c) + *matrix->getElement(r, c));
            }
        }

        return result;
    }

    Matrix *subtract(Matrix *matrix) {
        if(rows != matrix->getRows() or columns != matrix->getColumns()) {
            return nullptr;
        }

        auto result = new Matrix(rows, columns);
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < columns; ++c) {
                result->setElement(r, c, *getElement(r, c) - *matrix->getElement(r, c));
            }
        }

        return result;
    }

    Matrix *multiplyScalar(int number) {
        auto *result = new Matrix(this);
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < columns; ++c) {
                result->setElement(r, c, *getElement(r, c) * number);
            }
        }

        return result;
    }

    Matrix *divideScalar(int number) {
        auto *result = new Matrix(this);
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < columns; ++c) {
                result->setElement(r, c, *getElement(r, c) / number);
            }
        }

        return result;
    }

    Matrix *transpose(Matrix *matrix) {
        auto result = new Matrix(rows, columns);
        for(int r = 0; r < rows; ++r) {
            for(int c = 0; c < columns; ++c) {
                result->setElement(r, c, *getElement(r, c));
            }
        }

        return result;
    }

    //Naive Matrix product, O(n^3)
    Matrix *product(Matrix *matrix) {
        if(columns != matrix->getRows()) {
            return nullptr;
        }

        int c = matrix->getColumns();
        auto result = new Matrix(rows, c);
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < c; ++j) {
                int sum = 0;
                for(int k = 0; k < columns; ++k) {
                    sum += *getElement(i, k) * *matrix->getElement(k, j);
                }
                result->setElement(i, j, sum);
            }
        }

        return result;
    }

    //Computation of the determinant of 2x2 and 3x3 matrices
    int *determinant() {
        if(!isSquare()) {
            return nullptr;
        }

        switch(rows) {
            case 1:
                return new int(0);
            case 2:
                return new int(*getElement(0, 0) * *getElement(1, 1) - *getElement(0, 1) * *getElement(1, 0));
            case 3:
                return new int(*getElement(0, 0) * *getElement(1, 1) * *getElement(2, 2) + *getElement(0, 1) * *getElement(1, 2) * *getElement(2, 0) + *getElement(0, 2) * *getElement(1, 0) * *getElement(2, 1) - *getElement(2, 0) * *getElement(1, 1) * *getElement(0, 2) - *getElement(2, 1) * *getElement(1, 2) * *getElement(0, 0) - *getElement(2, 2) * *getElement(1, 0) * *getElement(0, 1));
        }

        return nullptr;
    }
};

#endif //EXT_POCKETMINE_MATH_MATRIX_H
