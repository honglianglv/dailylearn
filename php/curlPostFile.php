<?php
$url = "http://172.16.9.36/test.php";
$ch = curl_init();
$base64str = base64_encode("babytree:babytree_sogou");
$headers = array(
            "Authorization: Basic $base64str",
        );
$post_field = "site=".urlencode("宝宝树")."&type=compressed";
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
curl_setopt($ch, CURLOPT_HEADER, 0);
curl_setopt($ch, CURLOPT_VERBOSE, 0);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible;)");
curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_POST, true);
curl_setopt($ch, CURLOPT_VERBOSE, true);
// same as <input type="file" name="file_box">
$post = array(
        "data"=>"@/Users/lvhl/Downloads/sample.xml",
        "site"=>urlencode("宝宝树"),
        "type"=>"compressed",
        );
var_dump($post);
curl_setopt($ch, CURLOPT_POSTFIELDS, $post); 
$response = curl_exec($ch);
var_dump($response);die;
/*
function call_me(){
    $file_path = "/home/myfile.mov";
    $url = "http://myurl.com";
    $this->post_file($url, $file_path);
}
function post_file($url, $file_path){
    $data['Filedata'] = "@".$file_path;
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $data); 
    $response = curl_exec($ch);
    return $response;
}
*/
?>
