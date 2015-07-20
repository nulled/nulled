<?php
include("phpsecure/classes.inc");

$db = new MySQL_Access("pxm");

$db->Query("SELECT link, linkname, testimonial, listdescription, listownerID, listname FROM clients WHERE verified=1 ORDER BY MD5(RAND())");
$clients = $db->result;

?>