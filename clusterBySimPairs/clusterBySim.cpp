#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <unordered_map>

#include "util.h"
/*
 * 
 *  usage:  cat ../data/recordPairs/onlineFormat.txt | ./clusterBySim > clusterRet.txt
 *
 *  inputfile onlineFormat.txt :
 *
 * 0000031000005@0.9821826,
 * 10000051000003@0.9821826,
 * 100000759999568@0.8217054,
 * 10000111000000@1.0,
 * 1000013999974@1.0,
 * 1000026010000264@1.0,
 * 10000341013001@0.71428573,844473@0.7692308,828057@0.7692308,839343@0.7692308,
 * 100003559999992@1.0,
 * 1000056510000569@1.0,
 * 100006277651122@0.7,
 *
 *
 **/

using namespace std;

int getMaxClusterId(std::map<int, int> &countMap) {
    std::map<int, int>::const_iterator iter = countMap.begin();
    int maxCount = 0;
    int curClusterId = 0;
    for (; iter != countMap.end(); ++iter) {
        if (iter->second > maxCount) {
            maxCount = iter->second;
            curClusterId = iter->first;
        }
    }
    return curClusterId;
}

int main(int argc, char** argv) {
    unordered_map<int, int> cluster;
    int clusterNum = 1;
    for (std::string line; std::getline(std::cin, line);) {
        //std::cout << line.size() << endl;
        if (line.length() < 1) { 
            continue;
        }
        vector<string> lineInfo; 
        explode(line, "\t", lineInfo);
        if (lineInfo.size() < 2) {
            continue;
        }
        int docId1 = atoi(lineInfo[0].c_str());
        int doc1CId = 0;
        std::unordered_map<int, int>::const_iterator iterDoc1 = cluster.find(docId1);
        if (iterDoc1 != cluster.end()) {
            doc1CId = iterDoc1->second;
        }
        
        vector<string> sims;
        explode(lineInfo[1], ',', sims);
        map<int, int> simClusterCount;
        for (int i = 0; i < sims.size(); ++i) {
            if (sims[i].size() < 1) {
                continue;
            }
            vector<float> sim;
            explode(sims[i], '@', sim);
            int docId2 = (int)sim[0];
            float similarity = sim[1];
            if (similarity < 0.75) {
                continue; 
            }
            std::unordered_map<int, int>::const_iterator iterDoc2 = cluster.find(docId2);
            if (iterDoc2 != cluster.end()) {
                int tmpCId = iterDoc2->second;
                if (simClusterCount.find(tmpCId) == simClusterCount.end()) {
                    simClusterCount[tmpCId] = 1;
                } else {
                    ++simClusterCount[tmpCId];
                }
            } else {
                if (similarity > 0.94 && doc1CId != 0) {
                    //iterDoc2->second = doc1CId;
                    cluster[docId2] = doc1CId;
                }
            }
        }

        if (0 == doc1CId) {
            if (simClusterCount.size() != 0) {
                doc1CId = getMaxClusterId(simClusterCount);
            } else {
                doc1CId = clusterNum;
                ++clusterNum;
            }
        }
        cluster[docId1] = doc1CId;
        cout << docId1 << " " << doc1CId << endl;
    }
    return 0;
}
