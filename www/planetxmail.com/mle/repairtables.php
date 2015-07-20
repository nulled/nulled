<?php
include("mlpsecure/config/classes.inc");
$db = new Mysql_Access("mle");
$db->RepairTables();
$db->Close();
unset($db);

echo "mle repaired<br>\n";

$db = new Mysql_Access("pxm");
$db->RepairTables();
$db->Close();
unset($db);

echo "pxm repaired<br>\n";

$db = new Mysql_Access("pxmb");
$db->RepairTables();
$db->Close();
unset($db);

echo "pxmb repaired<br>\n";

$db = new Mysql_Access("elp");
$db->RepairTables();
$db->Close();
unset($db);

echo "elp repaired<br>\n";

?>