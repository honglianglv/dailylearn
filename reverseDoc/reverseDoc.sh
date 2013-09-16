#!/bin/bash

awk '{
    split($2, terms, ",");
    for (termId in terms) {
        if (termDict[terms[termId]]) {
            termDict[terms[termId]] = termDict[terms[termId]]","$1;
        }
        else {
            termDict[terms[termId]] = $1;
        }
    }
}
END {
    for (termId in termDict) {
        print termId" "termDict[termId];
    }
}' $1
