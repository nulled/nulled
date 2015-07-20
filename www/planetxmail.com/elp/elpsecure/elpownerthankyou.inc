<?php
if (! $id || ! $o)
{
	echo "Missing required params. Contact: <b>accounts@planetxmail.com</b>";
	exit;
}

include("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

sleep(5);  // used to offset the time it takes for paypay and egold to post transactions
$db->Query("SELECT amountowed, paid FROM billingperiods WHERE id='$id' AND elpownername='$o'");
if ($db->rows)
{
  list($amountpaid, $paid) = $db->FetchRow();

  if ($paid)
  {
  	$db->Query("SELECT fname, lname FROM elpowners WHERE elpownername='$o'");
  	list($fname, $lname) = $db->FetchRow();

    $good = 1;
  }
  else
    echo "Please <b>wait 10 seconds</b> for the system to <i>process your transaction</i>... then <b>REFRESH the browser window</b>. ( Hit F5 key )<br><br>\nIf over 60 seconds your transaction was not processed contact: <b>accounts@planetxmail.com</b>";
}
else
	echo "There was an <b>problem processing</b> your Billing Period Payment. Contact: <b>accounts@planetxmail.com</b>";

?>