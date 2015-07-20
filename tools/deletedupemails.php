<?php
include("/home/nulled/www/planetxmail.com/phpsecure/classes.inc");

set_time_limit(0);

$db = new MySQL_Access("mle");

$i = 1;

$listownerID 	= "";
$listname 		= "";
$whichemail 	= "listemail"; // should be email or listemail

if (! $db->Query("SELECT $whichemail FROM users WHERE $whichemail!='' AND listownerID='$listownerID' AND listname='$listname' ORDER BY $whichemail"))
{
	echo "List or Owner not found. Or number emails found is 0";
	exit;
}
$emails = $db->result;

echo "<pre>";
while(list($email) = mysqli_fetch_row($emails))
{
	$db->Query("SELECT COUNT(*) FROM users WHERE $whichemail='$email' AND $whichemail!='' AND $listownerID='$listownerID' AND listname='$listname'");
	list($count) = $db->FetchRow();

	if ($count>1)
	{
  	$db->Query("DELETE FROM users WHERE $whichemail='$email' AND $whichemail!='' AND listownerID='$listownerID' AND listname='$listname' LIMIT 1");

  	echo "\n$whichemail='$email' : LIMIT $i, -1\n";

  	$db->Query("SELECT $whichemail FROM users WHERE $whichemail!='' AND listownerID='$listownerID' AND listname='$listname' ORDER BY $whichemail LIMIT $i, -1");
		$emails = $db->result;

		$i -= 2;
		flush();
		continue;
	}
	else
		echo ".";

	$i++;
}
echo "</pre>";

?>