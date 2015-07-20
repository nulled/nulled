<?php
include("/home/nulled/www/planetxmail.com/phpsecure/classes.inc");

$db = new MySQL_Access("pxm");

$db->Query("SELECT product, amount, mop, receipt, dateofsale FROM transactions WHERE product!='cb_referral' AND mop='clickbank' AND dateofsale LIKE '2003-%' ORDER BY dateofsale");

echo "<pre>";

$totalamount=0;
while (list($product, $amount, $mop, $receipt, $dateofsale) = $db->FetchRow())
{
  $totalamount += $amount;
  echo "$product, $amount, $mop, $receipt, $dateofsale\n";
}

echo "\n\nTotal Amount: $totalamount</pre>";

?>