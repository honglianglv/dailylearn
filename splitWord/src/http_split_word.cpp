#include "header.h"
#define WORD_SIZE 256
using namespace std;


class SplitWord : public HTTPServer {
    public:
        SplitWord(FILE* log) : HTTPServer(log) {
            if(!ICTCLAS_Init("..",UTF8_CODE))//数据在当前路径下，设置为UTF8编码的分词
            {
                printf("ICTCLAS INIT FAILED!\n");
            }
        }
        
        void processRequest(struct evhttp_request *req) {  
            printf("get request!\n");
            //pthread_t tid = pthread_self();
            //fprintf(m_pLog, "in thread: %u (0x%x)\n", (unsigned int)tid, (unsigned int)tid);
            struct evbuffer *buf = evbuffer_new();
            //evbuffer_enable_locking(buf);
            //evbuffer_lock(buf);
            if (buf == NULL) {
                return;
            }
            const char* contline ;
            const char* ret; 
            char* decode_uri;
            if (req->type == EVHTTP_REQ_GET) {
                const char* uri = evhttp_request_uri(req);
                decode_uri = evhttp_decode_uri(uri);
                struct evkeyvalq para;
                evhttp_parse_query(decode_uri, &para);
                contline = evhttp_find_header(&para, "str");
                ret = ICTCLAS_ParagraphProcess(contline, 0);
            } else if (req->type == EVHTTP_REQ_POST) {
                //const char *contyp = evhttp_find_header (req->input_headers, "Content-Type");
                const char *contlenstr = evhttp_find_header(req->input_headers, "Content-Length");
                int contlen = 0;
                contlen = contlenstr ? atoi (contlenstr) : 0;
                char *data = (char*)malloc(contlen);
                evbuffer_remove(req->input_buffer, data, contlen);
                decode_uri =  evhttp_decode_uri(data);
                string tmpStr(decode_uri);
                free(data);
                int startPos = tmpStr.find("\r\n\r\n");
                int endPos = tmpStr.find("\n--");
                string tmpRet = tmpStr.substr(startPos+4, endPos-startPos-4);
                printf("%s\n", tmpRet.c_str());
                ret = ICTCLAS_ParagraphProcess(tmpRet.c_str(), 0);
                /* should have a reusable routine to transform the form
                                      encoded data into a dictionnary */
                //warning unimplemented login post, should make a dictionnary of the form data!
            }
            printf("%s\n", ret);
            //printf("Before Output: %s\n", ret.c_str());
            evbuffer_add_printf(buf, "%s\n", ret);
            //fprintf(m_pLog, "appendNum: %d\n", appendNum);
            evhttp_add_header(req->output_headers, "Server", "RelatedQuestions/1.0");
            evhttp_add_header(req->output_headers, "Content-Type", "text/plain; charset=UTF8");
            evhttp_send_reply(req, HTTP_OK, "OK", buf);
            evbuffer_free(buf);
            delete decode_uri;
            //evbuffer_unlock(buf);
            //delete buf;
        }
        ~SplitWord() {
            ICTCLAS_Exit();
        }
};

int main() {
    /*
    int fd0, fd1, fd2;
    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (pid != 0) {
        exit(0);
    }
    setsid();
    if (chdir("/") < 0) {
        exit(1);
    }
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    */
    FILE * g_pFile;
    g_pFile = fopen("/home/lvhl/log.txt", "a+");
        SplitWord ser(g_pFile);
    ser.serv(9998, 1);
    return 0;
}
