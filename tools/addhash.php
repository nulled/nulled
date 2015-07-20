<?php
include("../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("mle");

$db->Query("SELECT listownerID FROM listowner WHERE 1");
$listowners = $db->result;

echo "<pre>";

while (list($listownerID) = mysqli_fetch_row($listowners))
{
	$db->Query("SELECT listname FROM listmanager WHERE listownerID='$listownerID' AND created=1");
	$listnames = $db->result;

	while (list($listname) = mysqli_fetch_row($listnames))
	{
		$listhash = substr(md5($listownerID.$listname.microtime()), 0, 5);

		$db->Query("INSERT INTO listurls VALUES('$listownerID','$listname','$listhash')");

		echo "$listhash - $listownerID - $listname\n";
	}
}

echo "</pre>";
?>