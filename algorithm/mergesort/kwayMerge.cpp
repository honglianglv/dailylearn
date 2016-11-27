#include<iostream>
using namespace std;
#define ROWS 3
#define COLUMNS 3

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
void printTowDimensionArray(int** A, int rowLen, int colLen) {
    if (A == NULL) {
        return;
    }
    cout << "the row length of the array: " << rowLen << endl;
    cout << "the column length of the array: " << colLen << endl;
    for (int i=0; i<rowLen; ++i) {
        for (int j=0; j<colLen; ++j) {
            cout << A[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}


void kWayMerge(int* A, int p, int r, int k) {
	int indArr[k];
    for (int i = 0; i < k; ++i) {
        indArr[i] = 0;
    }
    cout << "the content of indArr:" << endl;
    printArray(indArr, k);
	int rowLen = (r-p+1) / k;
	int extra = 0;
	if ((r-p+1)%k != 0){
		//rowLen++;
		extra++;
	}
	/*if (extra) {
		int B[k][rowLen+1];		
	}
	else { */
    //		int B[3][3];
	//}
    int **dynamicArray = 0;
    dynamicArray = new int *[ROWS] ;
    
    //memory allocated for  elements of each column.
    for( int i = 0 ; i < ROWS ; i++ ) {
        dynamicArray[i] = new int[COLUMNS];
    }
    for (int i = 0; i < k; i++) {
		int tempInd = i * ROWS;
		for (int j = 0; j < COLUMNS; j++) {
			dynamicArray[i][j] = A[tempInd];
			tempInd++;
		}
	}
    
    printTowDimensionArray(dynamicArray, ROWS, COLUMNS);

	if (extra) {
//		B[k][rowLen] = A[r];
	}
	for (int i = p; i <= r; i++) {
		int mink = -1;
		int min = 999999999;
		for (int j = 0; j < k; j++) {
			if (dynamicArray[j][indArr[j]] < min) {
				min = dynamicArray[j][indArr[j]];
				mink = j;
			}
		}
		A[i] = min;
		indArr[mink]++;
	}

	printArray(A, r-p+1); 
}

int main(void) {
    int A[9] = {2, 4, 7, 3, 9, 10, 6, 7, 20};
    int length = sizeof(A)/sizeof(A[0]);
	printArray(A, length); 
	kWayMerge(A, 0, 8, 3);
    /*
    int B[10] = {3, 20, 7, 9, 10, 2, 6, 7, 9, 4};
    int lenB = sizeof(B)/sizeof(B[0]);
    printArray(B, lenB);
    mergeSort(B, 0, 9);
    printArray(B, lenB);
    */
}
