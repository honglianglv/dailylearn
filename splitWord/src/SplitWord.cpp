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

int main()
{
	//testNewWord(GBK_CODE);
	//testNewWord(UTF8_CODE);
    //初始化分词组件
    if(!ICTCLAS_Init("..",UTF8_CODE))//数据在当前路径下，设置为UTF8编码的分词
    {
        printf("ICTCLAS INIT FAILED!\n");
        return NULL;
    }

	const char *sInput = "@领袖未来俱乐部 ： @ICTCLAS张华平博士 是计算机领域的专家学者，专注于中文自然语言处理、信息检索、信息安全的学术交流与产业应用。吴裕待@简凡如是 来北京学习深造，在学习过程中多请教。也请@吴永夷 关注。 ";
    const char* sResult = SplitUTF8(sInput);
	printf("%s\n", sResult);
	
  	ICTCLAS_Exit();
    return 0;
}

