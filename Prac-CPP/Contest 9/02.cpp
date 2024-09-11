#include <string>
#include <iostream>

using std::cin, std::cout, std::endl;

struct P
{
    size_t z, o;
};

bool f_ch(P base, P cur) {
    return cur.o == base.o && cur.z == base.z;
}

bool e_ch(int c) {
    return c != EOF && !isspace(c);
}

int skip(int c) {
    while(e_ch(c))
        c = getchar();

    cout << 0 << endl;
    return c;
}

int main()
{
    int c = getchar();
    while (c != EOF) {
        P base{};
        bool f = true;

        for (; isspace(c); c = getchar()) {}
        if (c == EOF) {
            break;
        }

        for (; c == '0'; c = getchar(), ++base.z) {}
        for (; c == '1'; c = getchar(), ++base.o) {}
        if (!base.z || !base.o) {
            c = skip(c);
            continue;
        }

        while (e_ch(c)) {
            P cur{};
            for (; c == '0'; c = getchar(), ++cur.z) {}
            for (; c == '1'; c = getchar(), ++cur.o) {}

            if (!f_ch(base, cur)) {
                if (cur.z != 0 || cur.o != 0 || e_ch(c)) {
                    c = skip(c);
                    f = false;
                }
                break;
            }
        }

        if (f)
            cout << 1 << endl;
    }

    return 0;
}