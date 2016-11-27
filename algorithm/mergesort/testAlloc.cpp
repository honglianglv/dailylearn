// Example program
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int StringToNumber (string Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
    stringstream ss(Text);
    int result;
    return ss >> result ? result : 0;
}
int main()
{
    std::string tmpStr;
    int  rowLen, columnLen;
    std::cout << "What is the row length of the array:";
    getline (std::cin, tmpStr);
    rowLen = StringToNumber(tmpStr);
    std::cout << "What is the column length of the array:";
    getline (std::cin, tmpStr);
    columnLen = StringToNumber(tmpStr);
    cout << rowLen << std::endl;
    //int rowLen = 3;
    //int columnLen = 3;
    int array[rowLen][columnLen];
    for (int i=0; i<rowLen; ++i) {
        for (int j=0; j<columnLen; ++j) {
            array[i][j] = 1;
        }
    }

    for (int i=0; i<rowLen; ++i) {
        for (int j=0; j<columnLen; ++j) {
            cout << i << j << ":" << array[i][j] << endl;
        }
    }

    std::cout << "Hello, " << columnLen << "!\n";
}
