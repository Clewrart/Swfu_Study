#ifndef ADT_H
#define ADT_H

#include <vector>
#include <string>
#include <bitset>

using namespace std;
class GrayCode {
public:
    // ���� n λ Gray ������
    static vector<string> zuhe(int n) {
        vector<string> grayCodes;
        int total = 1 << n;  // �� 2^n ����

        for (int i = 0; i < total; ++i) {
            int gray = i ^ (i >> 1); // Gray �����ɹ�ʽ
            bitset<1024> bits(gray);
            grayCodes.push_back(bits.to_string().substr(1024 - n));
        }

        return grayCodes;
    }
};

#endif
