#include <vector>
#include <fstream>
#include <cmath>

class Matrix {
public:
    Matrix(): N(0), mat(nullptr){}; //Конструктор по умолчанию

    Matrix(int dim, double k): N(dim) { //Конструктор диагональной матрицы с заданным элементом на диагонали
        mat = new double*[N];
        for (int i = 0; i < N; ++i) {
            mat[i] = new double[N];
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i==j) {mat[i][j] = k;}
                else {mat[i][j] = 0;}
            }
        }
    }

    explicit Matrix(int dim): Matrix(dim, 1) {}; //Конструктор единичной матрицы

    Matrix(int dim, std::vector<double> trace): N(dim) { //Конструктор диагональной матрицы
        mat = new double*[N];
        for (int i = 0; i < N; ++i) {
            mat[i] = new double[N];
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i!=j) {
                    mat[i][j] = 0;
                }
                else {
                    mat[i][j] = trace[i];
                }
            }
        }
    }

    Matrix(Matrix const & that) { // Конструктор копий
        //std::cout << "copy" << std::endl;
        N = that.N;
        mat = new double*[N];
        for (int i = 0; i < N; ++i) {
            mat[i] = new double[N];
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                mat[i][j] = that.mat[i][j];
            }
        }
    }

    Matrix& operator=(Matrix copy) { //Оператор присваивания
        swap(*this, copy);
        return *this;
    }

    Matrix operator+(Matrix const & that) { //Сложение
        Matrix result = *this;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result.mat[i][j] += that.mat[i][j];
            }
        }
        return result;
    }

    Matrix operator-(Matrix const & that) { //Вычитание
        Matrix result = *this;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result.mat[i][j] -= that.mat[i][j];
            }
        }
        return result;
    }
    
    bool operator==(Matrix const & that) { //Сравнение
        if (N==that.N) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (mat[i][j] != that.mat[i][j]) { return false; }
                    else { continue; }
                }
            }
            return true;
        }
        else {
            return false;
        }
    }

    Matrix operator*(Matrix const & that) { //Умножение
        Matrix result = *this;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result.mat[i][j] = 0;
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    result.mat[i][j] += mat[i][k]*that.mat[k][j];
                }
            }
        }
        return result;
    }

    Matrix& operator!() { //Транспонирование
        Matrix& result = *this;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i>j) {
                    double temp = result.mat[i][j];
                    result.mat[i][j] = result.mat[j][i];
                    result.mat[j][i] = temp;
                }
            }
        }
        return result;
    }

    Matrix& operator()(int raw, int col) { //Взятие минора
        Matrix& result = *this;
        result.N -= 1;
        for (int i = 0; i < result.N; ++i) {
            for (int j = 0; j < result.N; ++j) {
                if (i < raw && j < col) result.mat[i][j] = mat[i][j];
                if (i < raw && j >= col) result.mat[i][j] = mat[i][j+1];
                if (i >= raw && j < col) result.mat[i][j] = mat[i+1][j];
                if (i >= raw && j >= col) result.mat[i][j] = mat[i+1][j+1];
            }
        }
        return result;
    }



    double* operator[](int raw) {
        return this->mat[raw];
    }

    friend std::ostream& operator<< (std::ostream &out, const Matrix &mat); //Поток ввода
    friend std::istream& operator>> (std::istream &in, Matrix &mat); //Поток вывода
    friend void swap(Matrix & a, Matrix & b); //Поменять две матрицы местами
    friend class Column;

    ~Matrix() { //Деструктор
        for (int i = 0; i < N; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
    }

private:
    int N;
    double ** mat;
};

class Column {
private:
    Matrix & mat;
    int col;
public:
    Column(int c, Matrix & m): col(c), mat(m) {}

    double& operator[](int index) {
        return mat.mat[index][col];
    }
};

std::ostream& operator<< (std::ostream &out, const Matrix &mat) {
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.N; ++j) {
            out << mat.mat[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

std::istream& operator>> (std::istream &in, Matrix &mat) {
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.N; ++j) {
            in >> mat.mat[i][j];
        }
    }
    return in;
}

void swap(Matrix & a, Matrix & b) {
    using std::swap;
    swap(a.N, b.N);
    swap(a.mat, b.mat);
}