<?php
exit;
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc');

$db = new MySQL_Access('fap');

if ($db->Query("SELECT affid FROM users WHERE 1"))
{
  $result = $db->result;
  while(list($affid) = mysqli_fetch_row($result)) delete_user($affid, $db);
}

$db->Query("DELETE FROM commissions");
$db->Query("DELETE FROM commissions_paid");
$db->Query("DELETE FROM earnedurls");
$db->Query("DELETE FROM pastaffs");
$db->Query("DELETE FROM receipts");
$db->Query("DELETE FROM urls");

$db->Query("DELETE FROM ad_purchased");
$db->Query("INSERT INTO ad_purchased (id) VALUES('')");

echo "done...\n";

?>
