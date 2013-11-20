#/bin/bash

awk -F"\t" '
BEGIN {
    docId1="";
    docId2="";
}
{
    if (docId1 == "" || docId1 != $1 || docId2 != $2) {
        print $1, $2, $3;
        docId1 = $1;
        docId2 = $2;
    } else {
    }
}'
