#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
void testStaticVariable(void) {
    static int a = 0;
    a = a + 1;
    printf("The function testStaticVariable is called %d times!\n", a);
    //
}


int main(int argc, char** argv) {
    int b;
    int a = 0;
    b = ++a;
    printf("The value of a is %d !\n", a);
    printf("The value of b is %d !\n", b);
    
    a = ++b;
    b = a++;
    printf("The value of b is %d !\n", b);
    printf("The value of a is %d !\n", a);
    //testStaticVariable();
    //testStaticVariable();
    //testStaticVariable();
}
