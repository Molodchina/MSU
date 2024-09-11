#include <iostream>
#include <iomanip>
#include <cmath>

using std::cin, std::cout, std::endl, std::setprecision, std::fixed;


int main()
{
    double sum = 0, mat1 = 0, mat2, temp;
    int amount = 0;
    while (cin >> temp) {
        sum += temp;
        mat1 += temp * temp;
        ++amount;
    }
    if (amount != 0) {
        mat2 = (sum * sum) / (amount * amount);
        mat1 /= amount;
        mat1 -= mat2;
        cout << setprecision(10) << sum / amount << endl;
        cout << setprecision(10) << sqrt(mat1) << endl;
    }
}
