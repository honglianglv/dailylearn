#!/bin/bash
dataPath="/user/lvhongliang/discussion/all"
#dataPath="/user/lvhongliang/ask/2"
hadoop fs  -cat $dataPath/recordsbulk-000/part-00000 | awk -F":" '{print $1, $2;}' > idMap.txt
hadoop fs -rm -r $dataPath/ridpairs-originId
hadoop jar /opt/cloudera/parcels/CDH-4.3.1-1.cdh4.3.1.p0.110/lib/hadoop-0.20-mapreduce/contrib/streaming/hadoop-streaming-2.0.0-mr1-cdh4.3.1.jar \
	-D mapred.map.tasks=72 \
    -D mapred.reduce.tasks=20 \
    -D stream.num.map.output.key.fields=2 \
    -D num.key.fields.for.partition=1 \
    -D mapred.job.name='restoreDocId' \
	-input $dataPath/ridpairs-000 \
	-output $dataPath/ridpairs-originId \
	-mapper '/bin/bash restoreMap.sh' \
	-reducer '/bin/bash restoreReduce.sh' \
	-file "restoreMap.sh" \
    -file "idMap.txt"  \
	-file "restoreReduce.sh"



#    -D mapred.output.key.comparator.class=org.apache.hadoop.mapred.lib.KeyFieldBasedComparator \
#    -D mapred.text.key.comparator.options=-n \
 
