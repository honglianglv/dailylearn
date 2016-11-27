#include <cstdlib>
#include <cstdio>
int convertCharToInt(char c) {
    return c - 48;
}
int main(int argc, char** argv) {
    char testArray[] = {'H', 'e', 'l', 'l', '0', '\0'};
    char testAraay[] = "Hello";
    printf("argc : %d\n", argc);
    //char num= '1';
    //int num1 = convertCharToInt(num);
    //printf("num1 is %d\n", num1);
    //int num1 = 1;
    printf("The arguments is:\n");
    for (int i=0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }
}
