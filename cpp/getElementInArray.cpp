#include <cstdio>
#include <cstdlib>

void printArray(int *array, int length) {
    for (int i=0; i<length; ++i) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    int A[] = {4, 5, 6, 5, 6, 7, 8, 9, 10};
    int length = sizeof(A)/sizeof(A[0]);
    int t = atoi(argv[1]);
    int result[10];
    int currentIndex = 0;
    int retIndex = 0;
    int currentElement;
    while (currentIndex <= length-1 ) {
        currentElement = A[currentIndex];
        int step = 0;
        if (currentElement == t) {
            result[retIndex] = currentIndex;
            ++retIndex;
            step = 1;
        } else {
            step = abs(t - currentElement);
        }
        currentIndex += step;
    }
    printf("%d\n", t);
    printArray(result, retIndex);
}
