#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_
#include <cstring>
#include <string>
#include <evhttp.h>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
//#include "apue.h"
class HTTPServer {
    public:
        HTTPServer(FILE* log);
        virtual ~HTTPServer() {}
        int serv(int port, int nthreads);
    protected:
        static void* dispatch(void *arg);
        static void genericHandler(struct evhttp_request *req, void *arg);
        virtual void processRequest(struct evhttp_request *request) = 0;
        int bindSocket(int port);
        FILE* m_pLog;
};

#endif //HTTP_SERVER_H_
