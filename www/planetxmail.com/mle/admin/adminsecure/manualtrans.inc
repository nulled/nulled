<?php
include("../mlpsecure/datefunctions.inc");
include("../mlpsecure/validationfunctions.php");
include("../mlpsecure/config/classes.inc");

if ($submitted=="generate")
{
	if ($mop && $receipt && $amount && $transtype)
	{
		$receipt = trim(substr($receipt, 0, 20));
		if (! is_numeric($amount=trim($amount))) $notValid = "ERROR: Amount value not a number.";
		else
		{
			$db = new MySQL_Access();

			$amount = number_format($amount, '2', '.', '');
			$db->Query("INSERT INTO transactions VALUES('','$_SESSION[aalisthash]','$u','$transtype','$amount','$commissionowed','0','$mop','$receipt',NOW())");

			if ($s=="pro" || $s=="exe")
				$db->Query("UPDATE users SET status='$s' WHERE userID='$u' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");

			$notValid = urlencode("Member Transaction Successfully Added.");
			header("Location: showmember.php?user=$u&notValid=$notValid");
			exit;
		}
	}
	else
		$notValid = "ERROR: Missing Required Params.";
}

?>