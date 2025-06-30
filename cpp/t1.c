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

void spiral(int n);

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
}

void spiral(int n) {
  int left = 0;
  int right = n - 1;
  int top = 0;
  int bottom = n - 1;
  int direction = 1;
  
  for (int i = 0; i < n; ++i) {
    if (i == top) {
      // print until left
      // print left to rigt
      // print after right
      top += 2; 
      if (left + 1 == right) {
        direction = -1;
      }

      right -= 2;
    } else if (i < top) {
      // print until left
      // print left to rigt
      // print after right
      left += 1;
    }
  }
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
