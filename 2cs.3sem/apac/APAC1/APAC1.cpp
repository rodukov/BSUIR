#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    int e1, e3;
    double r1, r2, r3, r4, r5, r6;

    cout << "Введите значения:" << endl;
    cout << "E1: ";
    cin >> e1;
    cout << "E3: ";
    cin >> e3;

    cout << "R1: ";
    cin >> r1;
    cout << "R2: ";
    cin >> r2;
    cout << "R3: ";
    cin >> r3;
    cout << "R4: ";
    cin >> r4;
    cout << "R5: ";
    cin >> r5;
    cout << "R6: ";
    cin >> r6;

    double r34, r2346, r23456, r_eqv;
    r34 = r3 * r4 / (r3 + r4);
    r2346 = r2 + r6 + r34;
    r23456 = r2346 * r5 / (r2346 + r5);
    r_eqv = r1 + r23456;

    cout << "При E3 = 0" << endl;
    cout << "Расчет сопротивления: " << endl;
    cout << "R34 = " << r34 << endl;
    cout << "R2346 = " << r2346 << endl;
    cout << "R23456 = " << r23456 << endl;
    cout << "Эквивалентное сопротивление = " << r_eqv << endl;

    double i1_1, i2_1, i3_1, i4_1, i5_1, i6_1;
    i1_1 = e1 / r_eqv;
    i5_1 = i1_1 * r2346 / (r5 + r2346);
    i2_1 = i1_1 - i5_1;
    i6_1 = i2_1;
    i4_1 = i2_1 * r3 / (r3 + r4);
    i3_1 = i2_1 - i4_1;

    cout << "Расчет токов для частичной схемы:" << endl;
    cout << "I1' = " << i1_1 << endl;
    cout << "I2' = " << i2_1 << endl;
    cout << "I3' = " << i3_1 << endl;
    cout << "I4' = " << i4_1 << endl;
    cout << "I5' = " << i5_1 << endl;
    cout << "I6' = " << i6_1 << endl;

    double r15, r1256, r12456, r_eqv2;
    r15 = r1 * r5 / (r1 + r5);
    r1256 = r2 + r6 + r15;
    r12456 = r1256 * r4 / (r4 + r1256);
    r_eqv2 = r3 + r12456;

    cout << "При E1 = 0" << endl;
    cout << "Расчет  сопротивления: " << endl;
    cout << "R15 = " << r15 << endl;
    cout << "R1256 = " << r1256 << endl;
    cout << "R12456 = " << r12456 << endl;
    cout << "Эквивалентное сопротивление = " << r_eqv2 << endl;

    double i1_2, i2_2, i3_2, i4_2, i5_2, i6_2;
    i3_2 = e3 / r_eqv2;
    i4_2 = i3_2 * r1256 / (r4 + r1256);
    i2_2 = i3_2 - i4_2;
    i6_2 = i2_2;
    i5_2 = i2_2 * r1 / (r1 + r5);
    i1_2 = i2_2 - i5_2;

    cout << "Расчет токов для частичной схемы:" << endl;
    cout << "I1'' = " << i1_2 << endl;
    cout << "I2'' = " << i2_2 << endl;
    cout << "I3'' = " << i3_2 << endl;
    cout << "I4'' = " << i4_2 << endl;
    cout << "I5'' = " << i5_2 << endl;
    cout << "I6'' = " << i6_2 << endl;

    double i1, i2, i3, i4, i5, i6;
    i1 = i1_1 - i1_2;
    i2 = i2_1 - i2_2;
    i3 = i3_2 - i3_1;
    i4 = i4_1 + i4_2;
    i5 = i5_1 + i5_2;
    i6 = i6_1 - i6_2;

    cout << "Расчет токов:" << endl;
    cout << "I1 = " << i1 << endl;
    cout << "I2 = " << i2 << endl;
    cout << "I3 = " << i3 << endl;
    cout << "I4 = " << i4 << endl;
    cout << "I5 = " << i5 << endl;
    cout << "I6 = " << i6 << endl;
    return 0;
}