#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};


struct node *
create_node(int val)
{
    struct node * ret;
    ret = malloc(sizeof(struct node));
    if (ret == NULL)
        return ret;
    ret->val = val;
    ret->next = NULL;
    return ret;
}

struct list {
    struct node *first;
};


struct list *
create_list()
{
    struct list *ret = malloc(sizeof(struct list));
    if (ret == NULL)
        return ret;
    ret->first = NULL;
    return ret;
}

int
is_element_at(struct list *l, int loc)
{
    struct node *t = l->first;
    int i = 0;
    for (;(i < loc) && (t != NULL); i++, t = t->next) ;

    if (t == NULL)
        return 0;
    return 1;
}

int
element_at(struct list *l, int loc)
{
    struct node *t = l->first;
    int i = 0;
    for (;(i < loc) && (t != NULL); i++, t = t->next) ;

    return t->val;
}

void
append(struct list *a, int val)
{
    struct node *tmp = create_node(val);
    if(a->first == NULL) {
        a->first = tmp;
    } else {
        struct node *t = a->first;
        while (t->next) {
            t = t->next;
        }
        t->next = tmp;
    }
}

void
print_list(struct list *l)
{
    struct node *t = l->first;
    while(t) {
        printf(" [%d] ", t->val);
        t = t->next;
    }
    printf("\n");
}




void test_list()
{
    int i;

    struct list *l = create_list();
    for (i = 0; i < 10; i++) {
        append(l, i);
    }

   print_list(l);
   if (is_element_at(l, 10)) {
       printf("element at 7 is %d\n", element_at(l, 7));
   }
}

void test_swap_even_odd_bits()
{
    int a = 54;
    printf("the value of a is %d\n", a);
    int a1 = a << 1;
    int a2 = a >> 1;
    a = (a1 & 0xAAAAAAAA) |
            (a2 & 0x55555555);
    printf("the value of new a is %d\n", a);
}

void get_number_of_bits()
{
   int a = 54;
    printf("the value of a is %d\n", a);
    int i = 0;
    if (a != 0) i++;
    while( (a = (a & (a - 1))) != 0) {
        i++;
        printf("[%d]the number of bits are %d\n", a, i);
    }
    printf("the number of bits are %d\n", i);

}


/* assume that array is sorted but rotated to the right, so left most element is bigger than right most element. If the array is not rotated, we do not need s and n but need just a middle index m.  */
int is_left(int *a, int s, int n, int m, int k)
{
    if (a[s] < a[m-1]) { /* s to m-1 is sorted */
        if (a[s] < k && k < a[m-1])
            return 1;
        else return 0;
    }
    else /* if (a[m + 1] < a[n]) is sorted */{
        if (a[m + 1] < k && k < a[n])
            return 0;
        else return 1;
    }
}

int f(int *a, int s, int n, int k)
{
    if (n < s) return -1;

    int m = (s + n) / 2;
    if (a[m] == k)
        return m;
    else if (is_left(a, s, n, m, k))
        return f(a, s, m - 1, k);
    else return f(a, m + 1, n, k);
}

int find(int *a, int size, int k)
{
    return f(a, 0, size - 1, k);
}

void bin_search_test_1()
{
    /* search a position of an element in a sorted and rotated array*/
    int a[] = {8, 9, 10, 1, 2, 3, 4, 5, 6, 7};
    int size = (int)(sizeof(a) / sizeof(int));
    printf ("the sizeof a is %d\n", size);

    printf("the index of 5 is %d\n", find(a, size, 5));
}

#if 0
/* todo */

int f1(int **a, int min_n, int max_n, int min_m, int max_m, k)
{
    if (min_m > max_m)
        printf("error 1\n");
    int mid_m = (min_m + max_m);
    int found = f(a, min_n, max_n, mid_m, k);
    if (found) print mid_m, found
        else


            }
}
int find(int **a, int n, int m, int k)
{
    int max_n = get_max_n(a[0], n, k);
    int min_n = get_min_n(a[m], n, k);
    int max_m = get_max_m(a, n, m, k);
    int min_m = get_min_m(a, n, m, k);

    return f1(a, min_n, max_n, min_m, max_m, k);
}

void bin_search_test_2()
{
    int a[][3] = {{1,4,7}, {2,5,8}, {3,6,9}};
    int m = (int)(sizeof(a) / sizeof(a[0]));
    int n = (int)((sizeof(a[0]) / sizeof(int)));
    printf ("the sizeof n and m is (%d, %d)\n", n, m);
    find(a, n - 1, m - 1, 5);

}

#endif
void main()
{
    bin_search_test_1();
}

