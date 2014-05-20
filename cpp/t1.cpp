#include <iostream>
#include <stdio.h>
 
char str[][10] = { "abc", "defg", "h", "ijklmn"};
   
#define STEP(x)                                 \
	if ((x) == true) printf("This is false\n");



class A
{
public:
    A()
    {
        std::cout << "this is world" << std::endl;
    }

private:

    int b[10];
};

int main ()

{
    A a;

    int bb[100] = {0};
}

