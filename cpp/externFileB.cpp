#include <cstdio>
int i = 0;
extern void f(void);
void g(void) {
    f();
    printf("%d\n", i);
}
