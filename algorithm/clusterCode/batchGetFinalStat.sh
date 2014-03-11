#!/bin/bash
if [ $# -ne 2 ];then
    echo "Usage: batchGetFinalStat.sh clusterRet.txt filterQids.txt"
    exit 1
fi
clusterRet=$1
filterQids=$2
filterRetFile=$1".filter"
finalStatFile=$1".stat"
./filterClusterRet.sh $clusterRet $filterQids >  $filterRetFile
awk '{print $2}' $filterRetFile | sort | uniq -c | awk '{print $1}' | sort | uniq -c | awk '{print $2,$1}' | sort -k1nr > $finalStatFile
