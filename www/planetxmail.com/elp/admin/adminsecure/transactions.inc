<?php
include ("../../mle/mlpsecure/validationfunctions.php");
include ("../../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

if ($show=="billingperiods")
{
	$db->Query("SELECT id, amountowed, totalearned, paid, dateowed, datepaid, bypassed FROM billingperiods WHERE elpownername='$_SESSION[aaelp]ownername'");
	$billingperiods = $db->result;
}
else if ($show=="showbillingperiodtrans")
{
	$db->Query("SELECT transids, dateowed, bypassed, id FROM billingperiods WHERE id='$id' AND elpownername='$_SESSION[aaelp]ownername'");
	list($transids, $dateowed, $periodbypassed, $billingperiodid) = $db->FetchRow();

	$ids = array();
	$ids = explode(",", $transids);
	for ($i=0; $i<count($ids); $i++)
	{
		$db->Query("SELECT username, transtype, amount, receipt, mop, datepaid, paid, commissionowed FROM membertrans WHERE id='$ids[$i]' AND elpownername='$_SESSION[aaelp]ownername'");
		list($username[$i], $transtype[$i], $amount[$i], $receipt[$i], $mop[$i], $datepaid[$i], $paid[$i], $commissionowed[$i], $bypassed[$i]) = $db->FetchRow();
	}
}
else if ($show=="elpnotpaid")
{
	$db->Query("SELECT username, transtype, amount, receipt, datepaid, paid, commissionowed FROM membertrans WHERE paid='0' AND elpownername='$_SESSION[aaelp]ownername'");
	$membertrans = $db->result;
}
else if ($show=="elppaid")
{
	$db->Query("SELECT username, transtype, amount, receipt, datepaid, paid, commissionowed FROM membertrans WHERE paid='1' AND elpownername='$_SESSION[aaelp]ownername'");
	$membertrans = $db->result;
}
else if ($show=="memnotpaid")
{
	$db->Query("SELECT username, fname, lname, paid FROM users WHERE paid='0' AND verified='1' AND elpownername='$_SESSION[aaelp]ownername'");
	$membertrans = $db->result;
}
else if ($show=="mempaid")
{
	$db->Query("SELECT username, fname, lname, paid FROM users WHERE paid='1' AND verified='1' AND elpownername='$_SESSION[aaelp]ownername'");
	$membertrans = $db->result;
}
else if ($show=="showallmem")
{
	$db->Query("SELECT username, fname, lname, paid FROM users WHERE verified='1' AND elpownername='$_SESSION[aaelp]ownername'");
	$membertrans = $db->result;
}

?>