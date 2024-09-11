#include <iostream>
#include <iomanip>

using std::cin, std::cout, std::endl, std::setprecision, std::fixed;



struct Point
{
    double x, y;
    Point() {
        cin >> x;
        cin >> y;
    }
    explicit Point(const double tmp_x, const double tmp_y) {
        x = tmp_x;
        y = tmp_y;
    }
    void print() {
        cout << 1 << endl;
        std::cout << std::fixed;
        cout.precision(5);
        cout << x << ' ' << y << endl;
    }
};

struct Line
{
    Point a, b;
    double k = 0, m = 0;
    bool fl = false;
    Line() {
        if (a.x == b.x) {
            fl = true;
        } else {
            k = (a.y - b.y) / (a.x - b.x);
            m = a.y - k * a.x;
        }
    }
};

void cross(Line l1, Line l2) {
    Point res(0.0, 0.0);
    if (l1.fl ^ l2.fl) {
        if (l1.fl) {
            res.x = l1.a.x;
            res.y = l2.k * res.x + l2.m;
            res.print();
            return;
        }
        res.x = l2.a.x;
        res.y = l1.k * res.x + l1.m;
        res.print();
    } else if (l1.fl) {
        if (l1.a.x == l2.a.x) {
            cout << 2 << endl;
            return;
        }
        cout << 0 << endl;
    } else if (l1.k == l2.k) {
        if (l1.m == l2.m) {
            cout << 2 << endl;
            return;
        }
        cout << 0 << endl;
    } else {
        if (l1.k == 0) {
            res.y = l1.m;
            res.x = (res.y - l2.m) / l2.k;
        } else if (l2.k == 0) {
            res.y = l2.m;
            res.x = (res.y - l1.m) / l1.k;
        } else {
            res.x = (l2.m - l1.m) / (l1.k - l2.k);
            res.y = l1.k * res.x + l1.m;
        }
        res.print();
    }
}

int main()
{
    Line l1, l2;
    cross(l1, l2);
    return 0;
}
