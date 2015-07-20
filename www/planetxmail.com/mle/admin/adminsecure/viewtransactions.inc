<?php
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/config/config.inc");

function mysql_timestamp_to_humandatetime($dt)
{
  $yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2));
  $hr=strval(substr($dt,8,2)); $mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2));
  return date("M j, Y H:i", mktime ($hr,$mi,$se,$mo,$da,$yr));
}

$db = new MySQL_Access();

$db->Query("SELECT userID, product, amount, commissionamount, commissionpaid, mop, receipt, dateofsale FROM transactions WHERE listhash='$listhash' ORDER BY dateofsale DESC");
$transactions = $db->result;

?>