#include <stdio.h>



char str[][10] = { "abc", "defg", "h", "ijklmn"};

#define STEP(x) \
	if ((x) == true) printf("This is false\n");


bool foo(int y)
{
    if (1)
    {

    }
}

enum  xxx {
    a, b, c, 
};

int main ()
{
    /* int len = sizeof(str[0]); */
    /* printf("the result is %d\n", len); */

	/* STEP(foo(1)); */


    /* unsigned long xxx = 810; */
    /* float yyy = 50; */

    /* float zzz = xxx / yyy; */
    /* char str[20]; */
    /* sprintf(str, "%2.1f", zzz); */
    /* printf("%s\n",str); */
    /* printf("------\n"); */
    char str[31];
    sprintf(str, "%04X%28X", 12345, -1);
    printf("%s\n", str);

}



/* void foo(const char* data, int len) */
/* { */
/*     for (int i = 0; i < len; ++i) */
/*     { */
/*         if (m_enable) */
/*             { */
                    

/*             } */
/*         handlecommand1(data[i]); */
/*     } */
/* } */



/* // how can I know in progress? */
/* void bar(const char* data, int len) */
/* { */
/*     for (int i = 0; i < len; ++i) */
/*     { */
/*         handlecommand2(d[i]);    */
/*         if (m_enable && inprogress) */
/*             { */
                    

/*             } */
/*     } */
/* } */


/* void handlecommand2(char c) */
/* { */
/* } */
