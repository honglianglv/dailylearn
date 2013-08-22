#ifndef HEADER_H_
#define HEADER_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <sys/queue.h>
#include <event.h>
#include <cstdio>

#include "http_server.h"
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

/*
#include "../util/ConfigFile.h"
#include "../util/ArrayUtil.h"
#include "../util/StringUtil.h"
#include "QuestionVectorFactory.h"
#include "DBBase.h"
#include "RealTimeRelatedQuestions.h"
#include "QuestionBO.h"
typedef std::pair<int,float> mypair;
bool comparator( const mypair& l, const mypair& r) {
    return l.second > r.second;
}
*/
#endif //HEADER_H_

