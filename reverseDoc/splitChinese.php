<?php
class CASSplitWord {
    //private $host = "192.168.1.90:9999";
    private $tokens=array();
    private $base_url="";

    public function CASSplitWord() {
        //$p_config = PlatformConfigInI::getInstance();
        //$host = $p_config->get("RelatedQuestionServer", "WebService");
        $host = "172.16.9.36:9998";
        $this->base_url="http://".$host."/index.html";
    } 

    public function splitWord($str, $method="GET"){
        if ($method == "GET") {
            return $this->getRet($this->base_url, $str);
        } else {
            return $this->postRet($this->base_url, $str);
        }
    }
    
    private function getRet($url, $str) {
        $header=array("Content-Type:text/xml;charset=UTF-8");
        $ch = curl_init();
        $url = $url."?str=".urlencode($str);
        curl_setopt($ch, CURLOPT_URL, $url); // set url to post to
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_TIMEOUT, 10);
        curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
        curl_setopt($ch, CURLOPT_ENCODING,"");
        curl_setopt($ch, CURLOPT_HTTPHEADER, $header);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT,10);
        curl_setopt($ch, CURLOPT_DNS_USE_GLOBAL_CACHE, 0);
        $data = curl_exec($ch);
        curl_close($ch);
        return $data;
    }


    private function postRet($url, $str) {
        $header=array("Content-Type:text/xml;charset=UTF-8");
        $ch = curl_init();
        $post_data = array(
                    "str"=>urlencode($str),
                );
        curl_setopt($ch, CURLOPT_URL, $url); // set url to post to
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_TIMEOUT, 10);
        curl_setopt($ch, CURLOPT_ENCODING,"");
        curl_setopt($ch, CURLOPT_HTTPHEADER, $header);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT,10);
//        curl_setopt($ch, CURLOPT_VERBOSE, true); 
        curl_setopt($ch, CURLOPT_DNS_USE_GLOBAL_CACHE, 0);
        curl_setopt($ch, CURLOPT_POST, 1);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $post_data);
        $data = curl_exec($ch);
        curl_close($ch);
        return $data;
    }
}
$obj = new CASSplitWord();
$str = file_get_contents("inChinese.txt");
$docs = explode("\n", $str);
foreach ($docs as $doc) {
    if (empty($doc)) continue;
    $docInfo = explode("@", $doc);
    $tmpSplitContent = $obj->splitWord($docInfo[1], "GET");
    $tmpSplitContent = preg_replace("/[ ]+/", " ", $tmpSplitContent);
    $tmpSplitContent = trim(str_replace(" ", ",", $tmpSplitContent));
    $contentArray = explode(",", $tmpSplitContent);
    $contentArray = array_unique($contentArray);
    //var_dump($contentArray);
    $tmpSplitContent = implode(",", $contentArray);
    echo $docInfo[0]." ".$tmpSplitContent."\n";
}
