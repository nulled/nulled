<?php
include ("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

if ($submitted=="signup")
{
	if ($fname!=""&&$lname!=""&&$message!=""&&$subject!=""&&email!="")
	{
		$fname = trim($fname);
		$lname = trim($lname);
		$email = trim($email);

		include ("../mle/mlpsecure/validationfunctions.php");

		if ($notValid = EmailFormat($email)) {}
		else if ($notValid = LengthRealname($fname)) {}
		else if ($notValid = LengthRealname($lname)) {}
		else
		{
			$db->Query("INSERT INTO petitions VALUES('','$fname','$lname','$email','$subject','$message',NOW())");

			header("Location: petitionthankyou.php");
			exit;
		}
	}
	else
		$notValid = "ERROR: Missing required parameters.";
}
?>