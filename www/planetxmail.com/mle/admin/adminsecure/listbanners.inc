<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();
$db->Query("SELECT id, banner FROM banners WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]' AND bannerlink NOT LIKE 'PER%' AND bannerlink !='TITLE_GRAPHIC'");

$banners = $db->result;

?>