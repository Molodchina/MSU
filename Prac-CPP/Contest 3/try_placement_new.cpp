#include <iostream>
#include <new>

using std::cout;

class N
{
    int *m;
    size_t len;
public:
    N(const size_t size = 0) {
        len = size;
        m = new int[len];
    }

    ~N() {
        delete [] m;
    }

    void print() const {
        for (size_t i = 0; i < len; ++i) {
            printf("%d ", m[i]);
        }
        printf("\n");
    }

    const N &operator= (const int *other) {
        ++len;
        m = new (m) int[len + 1];
        m[len] = int(len);
        return *this;
    }
};

int main(){
    int a[10];
    for (int i=0; i<10; i++) a[i] = i;
    int *ptr = new (a) int[10];
    for (int i=0; i<10; i++) cout << ptr[i] << ' ';
    cout << "\n" << "---" << '\n';
    for (int i=0; i<10; i++) ptr[i] = 9 - i;
    for (int i : a) cout << i << ' ';
    cout << "\n" << "---" << '\n';
    ptr = new (ptr) int[11];
    ptr[10] = -1;
    for (int i=0; i<10; i++) cout << ptr[i] << ' ';
    cout << "\n";
    N mas(10);
    mas.print();
    mas = ptr;
    mas.print();
    mas = ptr;
    mas.print();
    mas = ptr;
    mas.print();
}