<?php
session_start();

$parts = array();
$parts = parse_url($_SERVER['HTTP_REFERER']);

if ($_SESSION['elpID']=="!elp123!" && $parts['host']=="www.planetxmail.com" && $parts['path']=="/elp/login.php")
{
	$key = "54gf_jf!hd_hd";
}
else if ($_SESSION['elpID']=="!elpDEMO!" && $parts['host']=="www.planetxmail.com" && $parts['path']=="/elp/logind.php")
{
	$key = "22gfdemo!hd!xes";
}
else
{
	session_unregister("elpID");
	echo "ERROR: Do not try to compromise the system.";
	exit;
}
session_unregister("elpID");
?>
<html>
<head>
<title></title>
</head>
<body>
<input type="hidden" name="key" value="<?=$key?>">
</body>
</html>