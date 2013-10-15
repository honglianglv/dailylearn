<?php
$inputArray = array(1, 2, 3, 4, 5, 6);
$result = getPermutation($argv[1], $inputArray);
printTwoArray($result);

function getPermutation($n, $inputArray) {
    if ($n == 1) return array(array($inputArray[0]));
    $tmp = getPermutation($n-1, $inputArray);
    $ret = array();
    foreach ($tmp as $key=>$item) {
        $tmpLength = count($item);
        for ($i=0; $i<= $tmpLength; ++$i) {
            $ret[] = getInsertArray($inputArray[$n-1], $item, $i);
        }
    }
    return $ret;
}

function getInsertArray($insertValue, $array, $pos) {
    $tmpLen = count($array);
    for ($i=$tmpLen; $i>$pos; --$i) {
        $array[$i] = $array[$i-1];
    }
    $array[$pos] = $insertValue;
    return $array;
}

function printTwoArray($array) {
    foreach ($array as $item) {
        foreach ($item as $tmp) {
            echo "$tmp\t";
        }
        echo "\n";
    }
}
