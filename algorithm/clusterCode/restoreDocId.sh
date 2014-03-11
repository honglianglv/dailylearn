#!/bin/bash

# this file transfer the mapped documentId to originalId

if [ $# -ne 3 ];
then
    echo "usage: transferId.sh src_file dst_file docMapDict";
    exit
fi

srcFile=$1
dstFile=$2

documentIdMapFile=$3
#"../data/lsa_full/document_id.map"
awk '
FILENAME==ARGV[1]{
    { #second use the dict file to get the select user dict
        selectDocument[$2] = $1;
    }
}
FILENAME==ARGV[2]{
    #select and map the ratings
    idLength=split($1, tmpArray, ":");
    documentId = selectDocument[tmpArray[1]];
    printf("%s:%d ", documentId, tmpArray[2]);
    for (fieldNum=2; fieldNum<=NF; ++fieldNum) {
        printf("%s", $fieldNum);
        if (fieldNum != NF) {
            printf(" ");
        }
    }
    printf("\n");
}' $documentIdMapFile $srcFile > $dstFile
