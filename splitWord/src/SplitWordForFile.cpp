// win_cDemo.cpp : 定义控制台应用程序的入口点。
//

#include "../include/NLPIR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef OS_LINUX
#pragma comment(lib, "../bin/NLPIR.lib")
#endif

//Linux
#ifdef OS_LINUX
	#define _stricmp(X,Y) strcasecmp((X),(Y))
	#define _strnicmp(X,Y,Z) strncasecmp((X),(Y),(Z))
	#define strnicmp(X,Y,Z)	strncasecmp((X),(Y),(Z))
	#define _fstat(X,Y)     fstat((X),(Y))
	#define _fileno(X)     fileno((X))
	#define _stat           stat
	#define _getcwd         getcwd
	#define _off_t          off_t
	#define PATH_DELEMETER  "/"
#else
	#pragma warning(disable:4786)
	#define PATH_DELEMETER  "\\"
#endif

const char* SplitUTF8(const char* sInput)
{
    const char * sResult;
    sResult=ICTCLAS_ParagraphProcess(sInput, 0);
    return sResult;
}

int main(int argc, char** argv)
{
	//testNewWord(GBK_CODE);
	//testNewWord(UTF8_CODE);
    //初始化分词组件
    char* inputFile = argv[1];
    char* outputFile = argv[2];
    printf("%s\n", inputFile);
    printf("%s\n", outputFile);

    if(!ICTCLAS_Init("..",UTF8_CODE))//数据在当前路径下，设置为UTF8编码的分词
    {
        printf("ICTCLAS INIT FAILED!\n");
        return NULL;
    }
   	ICTCLAS_FileProcess(inputFile, outputFile, 0);
  	ICTCLAS_Exit();
    return 0;
}

