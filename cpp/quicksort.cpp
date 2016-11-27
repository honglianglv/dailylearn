#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
int partition(int* array, int start, int end);
void qsort(int* array, int start, int end);

void qsort(int* array, int start, int end) {
    if (start >= end) {
        return;
    }
    int pivotIndex = partition(array, start, end);
    //cout << pivotIndex << endl;
    qsort(array, start, pivotIndex-1);
    qsort(array, pivotIndex+1, end);
}

int partition(int* array, int start, int end) {
    if (start == end) {
        return start;
    }
    int pivotValue = array[start];
    while (start < end) {
        while (array[end] >= pivotValue && end >start) {
            end--;
        }
        array[start] = array[end];
        while (array[start] < pivotValue && end > start) {
            start++;
        }
        array[end] = array[start];
    }
    array[start] = pivotValue;
    return start;
}
void printArray(int* array, int length) {
    for (int i=0; i< length; ++i) {
        cout << array[i] << endl;
    }
}

int main(int argc, char** argv) {
    int arrayA[] = {3, 5, 33, 14, 6, 7, 32};
    int arrayB[] = {9, 23, 13, 45, 5, 6, 9};
    int lengthA = sizeof(arrayA) / sizeof(arrayA[0]);
    int lengthB = sizeof(arrayB) / sizeof(arrayB[0]);
    qsort(arrayA, 0, lengthA-1);
    printArray(arrayA, lengthA);
    cout << "***************" << endl;
    qsort(arrayB, 0, lengthB-1);
    printArray(arrayB, lengthB);
}
