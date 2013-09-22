#include <stdio.h>
#include <assert.h>

struct base
{
    int a;
    int b;
};

struct derived1
{
    struct base base;
    void* c;
};

struct derived2
{
    struct base base;
    double c;
};

union derived_union
{
    struct derived1 d1;
    struct derived2 d2;
};


inline void set_base_a_field(union derived_union* u, int a)
{
    ((struct base*)u)->a = a;
}

int main(void)
{
    struct derived2 d2 = { {5, 5}, 5.0 };
    int d2_a;

    set_base_a_field((union derived_union*)&d2, 0);

    d2_a = d2.base.a;

    if (d2_a != 0) {
        printf("Aliasing is unhappy!  d2.a == %d\n", d2_a);
    }

    return d2_a;
}
