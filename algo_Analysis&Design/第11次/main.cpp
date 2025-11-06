#include <iostream>
#include "ADT.h"
using namespace std;

int main() {
    int n;
    cout << "������ Gray ���λ�� n: ";
    cin >> n;

    if (n < 1 || n > 1024) {
        cout << "����֧�ֵ�λ��Ϊ 1 �� 1024��" << endl;
        return 1;
    }

    vector<string> grayCodes = GrayCode::zuhe(n);

    cout << "���ɵ� Gray �루�� " << grayCodes.size() << " ����:\n";
    for (const string& code : grayCodes) {
        cout << code << endl;
    }

    return 0;
}
