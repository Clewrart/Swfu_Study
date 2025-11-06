#include "marix.h"
int main() {

    Matrix<int>* A = new Matrix<int>({
        {1, 2},
        {3, 4}
    });

    Matrix<int>* B = new Matrix<int>({
        {5, 6},
        {7, 8}
    });


    Matrix<int>* C = new Matrix<int>({
        {1, 2, 3},
        {4, 5, 6}
    });

    Matrix<int>* D = new Matrix<int>({
        {7, 8},
        {9, 10},
        {11, 12}
    });

    //Use to handle pointer of martix
    MatrixPtrArray<int> array;
    array.add(A);
    array.add(B);
    array.add(C);
    array.add(D); 

    cout << "marix" << endl;
    array.printAll();

    cout << "\n+ass" << endl;
    Matrix<int>* resultAdd = array.add(0,1);
    resultAdd->print();
    delete resultAdd;

    cout << "\n-subtract" << endl;
    Matrix<int>* resultSub = array.subtract(0,1);
    resultSub->print();
    delete resultSub;

    cout << "\n*multiply" << endl;
    Matrix<int>* resultMul = array.multiply(2,3);
    resultMul->print();
    delete resultMul;

    return 0;
}
