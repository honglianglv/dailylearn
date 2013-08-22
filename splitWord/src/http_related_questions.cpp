#include "header.h"
#define WORD_SIZE 256
using namespace std;


class RelatedQuestions : public HTTPServer {
    public:
        RelatedQuestions(FILE* log, QuestionVectorFactory* qvFactory, DBBase* db) : HTTPServer(log) {
            this->mQVFactory = qvFactory;
            this->mDb = db;
        }
        void processRequest(struct evhttp_request *req) {  
            //pthread_t tid = pthread_self();
            //fprintf(m_pLog, "in thread: %u (0x%x)\n", (unsigned int)tid, (unsigned int)tid);
            struct evbuffer *buf = evbuffer_new();
            //evbuffer_enable_locking(buf);
            //evbuffer_lock(buf);
            if (buf == NULL) {
                return;
            }
            string ret;
            const char* uri = evhttp_request_uri(req);
            char* decode_uri = evhttp_decode_uri(uri);
            struct evkeyvalq para;
            //printf("decode_uri: %s\n", decode_uri); 
            evhttp_parse_query(decode_uri, &para);
            const char *qId = evhttp_find_header(&para, "qId");
            const char *title = evhttp_find_header(&para, "title");
            const char *content = evhttp_find_header(&para, "content");
            const char *ageId = evhttp_find_header(&para, "ageId");
            processLog(qId, title, content);
            RealTimeRelatedQuestions* realTimeRelatedQ = NULL;
            if (qId == NULL) {
                /*
                 if (ageId == NULL) {
                    ret = "如果想得到相关问题，必须输入问题的ageId！";
                } else if (!ArrayUtil::inArray(tmpAgeId, QuestionVectorFactory::ageIds)) {
                    ret = "您输入的ageId取值必须是: 1, 2, 3, 4, 5, 477, 488其中之一";
                } else*/
                if (title != NULL && title[0] !='\0') {
                    if (ageId != NULL && ArrayUtil::inArray(atoi(ageId), QuestionVectorFactory::ageIds)) {
                        int tmpAgeId = atoi(ageId);
                        QuestionVectors* pQueVec = mQVFactory->getQuestionVector(tmpAgeId);
                        realTimeRelatedQ = new RealTimeRelatedQuestions(title, content, pQueVec);
                    } else if (ageId == NULL) {
                        ret = getRelatedQuestionByNoAgeId(title, content);
                    } else if (ArrayUtil::inArray(atoi(ageId), QuestionVectorFactory::ageIds)) {
                        ret = "您输入的ageId取值必须是: 1, 2, 3, 4, 5, 477, 488其中之一";
                    }
                } else {
                    ret = "必须输入问题的title，并且title不能为空！";
                }
            } else if (isdigit(qId[0])) {  //qId的第一个字符是数字
                int id = atoi(qId);
                QuestionBO  qBO(id, this->mDb);
                if (qBO.isQuestionExist()) {
                    int tmpAgeId = qBO.getAgeId();
                    const char* qTitle = qBO.getTitle().c_str();
                    const char* qContent = qBO.getContent().c_str();

                    if (ArrayUtil::inArray(tmpAgeId, QuestionVectorFactory::ageIds)) { 
                        QuestionVectors* pQueVec = mQVFactory->getQuestionVector(tmpAgeId);
                        realTimeRelatedQ = new RealTimeRelatedQuestions(qTitle, qContent, pQueVec);
                    } else {
                        //如果没有question没有ageId的话，那么从所有的问题中选择相关问题
                        //ret  = "您输入的问题没有ageId或者ageId不在1，2，3，4，5，477，488之中，无法计算相关问题！";
                        ret = getRelatedQuestionByNoAgeId(qTitle, qContent);
                    }
                } else {
                    ret = "您输入的问题不存在";
                }
            } else {
                ret = "输入问题Id的格式有问题，请重新输入"; 
            }
            if (NULL != realTimeRelatedQ) {
                ret = realTimeRelatedQ->getRelatedQuestions();
                //printf("get Return:%s\n", ret.c_str());
            } 
            //printf("Before Output: %s\n", ret.c_str());
            evbuffer_add_printf(buf, "%s\n", ret.c_str());
            //fprintf(m_pLog, "appendNum: %d\n", appendNum);
            evhttp_add_header(req->output_headers, "Server", "RelatedQuestions/1.0");
            evhttp_add_header(req->output_headers, "Content-Type", "text/plain; charset=UTF8");
            evhttp_send_reply(req, HTTP_OK, "OK", buf);
            evbuffer_free(buf);
            //evbuffer_unlock(buf);
            //delete buf;
            delete decode_uri;
            delete realTimeRelatedQ;
        }
        ~RelatedQuestions() {}
    protected:
        void processLog(const char* qId, const char* title, const char* content) {
            //cout << "cout: " << qId << '\t' << title << '\t' << content << endl;
            //FILE* fp;
            //fp = fopen("log.txt.1", "a+");
            //int rc = fprintf(fp, "file: %s\t%s\t%s\n", qId, title, content);
            //fprintf(m_pLog, "printf: %d\t%s\t%s\t%s\n", rc, qId, title, content);
            //fclose(fp);
        }
        
        string getRelatedQuestionByNoAgeId(const char* title, const char* content) {
            //printf("in getRelatedQuestionByNoAgeId\n");
            int length = QuestionVectorFactory::ageIds.size();
            vector<mypair> allRelates;
            for (int i = 0; i < length; ++i) {
                int ageId = QuestionVectorFactory::ageIds[i];
                QuestionVectors* pQueVec = mQVFactory->getQuestionVector(ageId);
                RealTimeRelatedQuestions* tmpRealTimeRelatedQ;
                tmpRealTimeRelatedQ = new RealTimeRelatedQuestions(title, content, pQueVec);
                string relatesQ  = tmpRealTimeRelatedQ->getRelatedQuestions();
                //printf("%d: %s\n", ageId, relatesQ.c_str());
                vector<string> tmpRel; 
                StringUtil::explode(relatesQ, ',', tmpRel);
                //printf("ageId %dsize: %d\n", ageId, tmpRel.size());
                for (std::vector<string>::iterator it = tmpRel.begin(); it != tmpRel.end(); ++it) {
                    if (it->length() < 2) continue;
                    vector<string> tmpInfo;
                    StringUtil::explode(*it, '@', tmpInfo);
                    mypair tmpPair = make_pair(atoi(tmpInfo[0].c_str()), atof(tmpInfo[1].c_str()));
                    allRelates.push_back(tmpPair);
                }
                delete tmpRealTimeRelatedQ;
            }
            sort(allRelates.begin(), allRelates.end(), comparator);
            std::ostringstream ret;
            int totalNum = 0;
            //printf("ret size %d\n", allRelates.size());
            for (std::vector<mypair>::iterator it = allRelates.begin(); it != allRelates.end(); ++it) {
                ret << it->first << "@" << it->second << ",";
                //printf("ret: %s\n", ret.str().c_str());
                ++totalNum;
                if (totalNum >= 30) break;
            }
            return ret.str();
        }

    private:
        QuestionVectorFactory* mQVFactory;
        DBBase* mDb;
};

int main() {
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
    FILE * g_pFile;
    g_pFile = fopen("/home/lvhongliang/autoAnswer/AutoAnswer/log.txt", "a+");
    const char* configLoc = "/home/lvhongliang/autoAnswer/AutoAnswer/configLoc.txt";
    ConfigFile config; 
    config.load(configLoc);
    QuestionVectorFactory qvFactory(&config);
    DBBase db;
    int conRet = db.openConnection(config.Value("database", "server").c_str(),
            config.Value("database", "dbname").c_str(),
            config.Value("database", "user").c_str(),
            config.Value("database", "password").c_str());
    if (200 != conRet) {
        cout << dberror(conRet);
        exit(1);
    }

    //fprintf(g_pFile, "%s\n", "all data is loaded successfully! start the web server...");
    RelatedQuestions ser(g_pFile, &qvFactory, &db);
    ser.serv(9999, 10);
    return 0;
}
