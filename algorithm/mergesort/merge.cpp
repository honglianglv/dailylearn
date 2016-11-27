#include <iostream>
#include <cstdlib>
#include <cmath>
#define IS_DEBUG true 
using namespace std;
void printArray(int* A, int length);
void merge(int* A,  int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L1[n1+1];
    int L2[n2+1];
    for (int i=0; i < n1; ++i) {
        L1[i] = A[p+i];
    }
    L1[n1] = INT_MAX;
    if (IS_DEBUG) {
        printArray(L1, n1+1);
    }
    for (int j=0; j < n2; ++j) {
        L2[j] = A[q+j+1];
    }
    L2[n2] = INT_MAX;
    if (IS_DEBUG) {
        printArray(L2, n2+1);
    }
    int i = 0;
    int j = 0;
    for (int k=p; k <= r; ++k) {
        if (L1[i] <= L2[j]) {
            A[k] = L1[i];
            ++i;
        } else {
            A[k] = L2[j];
            ++j;
        }
    }
    if (IS_DEBUG) {
        printArray(A, r-p+1);
    }
}

void printArray(int* A, int length) {
    if (A == NULL) {
        return;
    }
    cout << "the length of the array: " << length << endl;
    for (int i=0; i<length; ++i) {
        cout << A[i] << '\t';
    }
    cout << endl;

}

void mergeSort(int* A, int p, int r) {
    if (p < r) {
        int q = (p+r)/2;
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
    } else {
        return;
    }
}
int main(void) {
    int A[10] = {2, 4, 7, 9, 10, 3, 6, 7, 9, 20};
    int length = sizeof(A)/sizeof(A[0]);
    printArray(A, length); 
    merge(A, 0, 4, 9);
    /*
    int B[10] = {3, 20, 7, 9, 10, 2, 6, 7, 9, 4};
    int lenB = sizeof(B)/sizeof(B[0]);
    printArray(B, lenB);
    mergeSort(B, 0, 9);
    printArray(B, lenB);
    */
}
