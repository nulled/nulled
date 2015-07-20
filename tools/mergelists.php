<?php
include("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("mle");

$listownerID = "1019244831";
$listname  = "THEMUSTARDSEED"; # list to merge to
$listname_to_move = "SharedProfitClub"; # list to move and merger

exit;

$db->Query("SELECT userID, username FROM users WHERE listownerID='$listownerID' ORDER BY username");

$i=0;
while (list($uID, $u) = $db->FetchRow())
{
	$users[$i][0]  = $uID;
	$users[$i][1] = strtolower($u);
	$i++;
}

// collect duplicate userIDs
for ($i=0; $i<count($users); $i++)
{
	if ($prevuser==$users[$i][1])
	{
		$dupuserIDs[] = $users[$i][0];
		continue;
	}

	$prevuser = $users[$i][1];
}

echo "<pre>";

echo "Will delete these userIDs\n";
for ($i=0; $i<count($dupuserIDs); $i++)
	echo "$dupuserIDs[$i]\n";
echo "\nTotal: ".count($dupuserIDs)."\n\n";

// delete dup usernames
for ($i=0; $i<count($dupuserIDs); $i++)
{
	$userID = $dupuserIDs[$i];
	$db->Query("DELETE FROM urldata WHERE userID='$userID'");
	$db->Query("DELETE FROM urlmanager WHERE userID='$userID'");
	$db->Query("DELETE FROM users WHERE userID='$userID'");
}

// merge lists
$db->Query("UPDATE users SET listname='$listname' WHERE listname='$listname_to_move' AND listownerID='$listownerID'");

echo "Completed all tasks";

echo "</pre>";
?>