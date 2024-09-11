#include <stdio.h>

int main(void)
{
    float a1, a2, b1, b2, c1, c2, m1, m2;
    scanf("%f %f", &a1, &a2);
    scanf("%f %f", &b1, &b2);
    scanf("%f %f", &c1, &c2);
    m1 = (a1+b1+c1)/3;
    m2 = (a2+b2+c2)/3;
    printf("%.4f %.4f", m1, m2);
    return 0;
}
