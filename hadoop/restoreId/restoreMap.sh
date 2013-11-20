#/bin/bash

awk '
BEGIN{
    OFS="\t";
}
FILENAME==ARGV[1] {
    docIdMap[$1] = $2;
}
FILENAME==ARGV[2] {
    docId1 = docIdMap[$1];
    docId2 = docIdMap[$2];
    print docId1,docId2, $3;
    print docId2,docId1, $3;
}' idMap.txt -
