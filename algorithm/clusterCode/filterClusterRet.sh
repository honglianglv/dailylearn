#!/bin/bash

#将导入的问题过滤掉

if [ $# -ne 2 ];then
    echo "Usage: filterClusterRet.sh clusterRet.txt filterQids.txt"
    exit 1
fi
clusterRet=$1
filterQids=$2

awk 'BEGIN{
}
FILENAME==ARGV[1] {
    filterQids[$1] = 1;
}
FILENAME==ARGV[2] {
    if (!filterQids[$1]) {
        print $0;
    }
}'  $filterQids $clusterRet
