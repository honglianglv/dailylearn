#!/bin/bash
#这个文件的作用就是
if [ $# -ne 2 ];then
    echo "Usage: batchCluster.sh all_pair_similarity.txt.ori retFileSuffix(fg. stage3)"
    exit 1
fi
allPairSimilarityFile=$1
retFileSuffix=$2
nohup ./clusterBySimQuick $allPairSimilarityFile 0.6 > "clusterRet"$retFileSuffix".0.6.txt" 2> "2_"$retFileSuffix"_0.6.txt" &
nohup ./clusterBySimQuick $allPairSimilarityFile 0.65 > "clusterRet"$retFileSuffix".0.65.txt" 2> "2_"$retFileSuffix"_0.65.txt" &
nohup ./clusterBySimQuick $allPairSimilarityFile 0.7 > "clusterRet"$retFileSuffix".0.7.txt" 2> "2_"$retFileSuffix"_0.7.txt" &
nohup ./clusterBySimQuick $allPairSimilarityFile 0.8 > "clusterRet"$retFileSuffix".0.8.txt" 2> "2_"$retFileSuffix"_0.8.txt" &
