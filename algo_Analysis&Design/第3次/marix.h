#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;


template <typename T>
class Matrix {
private:
    vector<vector<T>> data;

public:
    //构造函数
    Matrix(int rows = 0, int cols = 0, T value = T()) {
        data.resize(rows, vector<T>(cols, value));
    }

    //vector2d
    Matrix(const vector<vector<T>>& d) : data(d) {}
    int rows() const { return data.size(); }
    int cols() const { return data.empty() ? 0 : data[0].size(); }

    //修改
    T& at(int i, int j) { return data[i][j]; }

    //访问
    const T& at(int i, int j) const { return data[i][j]; }

    //输出
    void print() const {
        for (const auto& row : data) {
            for (const auto& val : row)
                cout << val << " ";
            cout << "\n";
        }
    }

    //矩阵加法
    Matrix<T> operator+(const Matrix<T>& other) const {
        Matrix<T> result(rows(), cols());
        for (int i = 0; i < rows(); ++i)
            for (int j = 0; j < cols(); ++j)
                result.at(i, j) = this->at(i, j) + other.at(i, j);
        return result;
    }

    //矩阵减法
    Matrix<T> operator-(const Matrix<T>& other) const {
        Matrix<T> result(rows(), cols());
        for (int i = 0; i < rows(); ++i)
            for (int j = 0; j < cols(); ++j)
                result.at(i, j) = this->at(i, j) - other.at(i, j);
        return result;
    }

    //矩阵乘法
    Matrix<T> operator*(const Matrix<T>& other) const {
        Matrix<T> result(rows(), other.cols());
        for (int i = 0; i < rows(); ++i) {
            for (int j = 0; j < other.cols(); ++j) {
                T sum = T();
                for (int k = 0; k < cols(); ++k)
                    sum += this->at(i, k) * other.at(k, j);
                result.at(i, j) = sum;
            }
        }
        return result;
    }
};

//矩阵指针数组类
template <typename T>
class MatrixPtrArray {
private:
    vector<Matrix<T>*> ptrs;

public:
    //Add pointer of matrix in array
    void add(Matrix<T>* m) {
        ptrs.push_back(m);
    }

    //Get index's pointer of matrix 
    Matrix<T>* get(int index) const {
        return ptrs[index];
    }

    //Get Size
    int size() const {
        return ptrs.size();
    }

    //output
    void printAll() const {
        for (int i = 0; i < ptrs.size(); ++i) {
            cout << "martix" << i << ":\n";
            ptrs[i]->print();
        }
    }

    //add+
    Matrix<T>* add(int idx1, int idx2) {
        return new Matrix<T>(*(get(idx1)) + *(get(idx2)));
    }

    //subtract-
    Matrix<T>* subtract(int idx1, int idx2) {
        return new Matrix<T>(*(get(idx1)) - *(get(idx2)));
    }

    //multiply*
    Matrix<T>* multiply(int idx1, int idx2) {
        return new Matrix<T>(*(get(idx1)) * *(get(idx2)));
    }

    //Function of Destructor
    ~MatrixPtrArray() {
        for (auto ptr : ptrs)
            delete ptr;
    }
};
