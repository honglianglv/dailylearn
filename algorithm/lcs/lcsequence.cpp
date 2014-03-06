/** 
    找出两个字符串的最长公共子序列
    @author : lvhongliang 
    @date   : 2014-03-05
*/ 
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <vector>
#include <iostream>
using namespace std;
void printLongestSquence(vector< vector<int> >& c, int i, int j, const char* str1, const char* str2) {
    if (i == 0 || j == 0) {
        return;
    }
    if (str1[i-1] == str2[j-1]) {
        printLongestSquence(c, i-1, j-1, str1, str2);
        cout << str1[i-1];
    } else {
        if (c[i-1][j] >= c[i][j-1]) {
            printLongestSquence(c, i-1, j, str1, str2);
        } else {
            printLongestSquence(c, i, j-1, str1, str2);
        }
    }
}

int longest_common_sequence(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int maxLen = -1;
    
    //构造一个对象存储子问题的结果
    vector< vector<int> > c(len1+1, vector<int>(len2+1));
    //int c[len1+1][len2+1];

    //初始化
    for (int i=0; i< len2+1; ++i) {
        c[0][i] = 0;
    }

    for (int i=0; i<len1+1; ++i) {
        c[i][0] = 0;
    }
    
    for (int i=1; i < len1+1; ++i) {
        for (int j=1; j < len2+1; ++j) {
            if (str1[i-1] == str2[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
            } else if (c[i-1][j] > c[i][j-1]) {
                c[i][j] = c[i-1][j];
            } else {
                c[i][j] = c[i][j-1];
            }
        }
    }
    maxLen = c[len1][len2];
    
    //print longest squence 
    printLongestSquence(c, len1, len2, str1, str2);
    cout << endl;
    return maxLen;
}

int main(void)
{
    char str1[1000],str2[1000];
    printf("请输入第一个字符串：");
    gets(str1);
    printf("请输入第二个字符串：");
    gets(str2);
    int len = longest_common_sequence(str1, str2);
    printf("最长公共子序列的长度为：%d\n",len);
    return 0;
}
