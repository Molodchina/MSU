class C
{
public:
    C() {};
    explicit C(const C, int n) {};
    C(double d) {};
    friend C operator+ (int, C);
    friend int operator~ (C);
    const C operator& (C);
    friend C operator++ (C);
    friend int operator* (C, C []);
};

C operator+ (int a, const C c)
{
    return c;
}
int operator~ (const C c)
{
    return 0;
}

C operator& (const C c)
{
    return c;
}

C operator++ (const C)
{
    C c;
    return c;
}
int operator* (const C c1, C c[])
{
    return 0;
}
