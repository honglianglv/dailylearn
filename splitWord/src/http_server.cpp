#include "http_server.h"
HTTPServer::HTTPServer(FILE* log) : m_pLog(log) {
}

int HTTPServer::bindSocket(int port) {
    int r;
    int nfd;
    nfd = socket(AF_INET, SOCK_STREAM, 0);
    if (nfd < 0) return -1;

    int one = 1;
    r = setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    r = bind(nfd, (struct sockaddr*)&addr, sizeof(addr));
    if (r < 0) return -1;
    r = listen(nfd, 10240);
    if (r < 0) return -1;

    int flags;
    if ((flags = fcntl(nfd, F_GETFL, 0)) < 0
            || fcntl(nfd, F_SETFL, flags | O_NONBLOCK) < 0)
        return -1;

    return nfd;
}

int HTTPServer::serv(int port, int nthreads) {
    int r;
    int nfd = bindSocket(port);
    if (nfd < 0) return -1;
    pthread_t ths[nthreads];
    //int evthread_use_pthreads(void);  
    for (int i = 0; i < nthreads; i++) {
        struct event_base *base = event_init();
        if (base == NULL) {
            return -1;
        }
        struct evhttp *httpd = evhttp_new(base);
        if (httpd == NULL) {
            return -1;
        }
        r = evhttp_accept_socket(httpd, nfd);
        if (r != 0) {
            return -1;
        }
        evhttp_set_gencb(httpd, HTTPServer::genericHandler, this);
        r = pthread_create(&ths[i], NULL, HTTPServer::dispatch, base);
        if (r != 0) {
            return -1;
        }
    }
    for (int i = 0; i < nthreads; i++) {
        int err = pthread_join(ths[i], NULL);
        if (err != 0) {
            printf("cant't join with thread i : %s\n", strerror(err));
            exit(1);
        }
    }
    return 0;
}

void* HTTPServer::dispatch(void *arg) {
    event_base_dispatch((struct event_base*)arg);
    return NULL;
}

void HTTPServer::genericHandler(struct evhttp_request *req, void *arg) {
    ((HTTPServer*)arg)->processRequest(req);
}
