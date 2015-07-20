<?php
exit;
include("../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access();

echo "<pre>";

if ($mode=="userID")
{
	// check form duplicate userIDs
	$db->Query("SELECT userID FROM users WHERE 1 ORDER BY userID");

	while (list($userID) = $db->FetchRow())
	{
		$uIDs[] = $userID;
		//echo $userID."\n";
	}

	for ($i=0; $i<count($uIDs); $i++)
	{
		if ($uIDs[$i]==$prev){ $dups[] = $uIDs[$i]; continue; }
		$prev = $uIDs[$i];
	}

	for ($i=0; $i<count($dups); $i++)
		echo $dups[$i]."\n";
}


// check form duplicate username, listownerID, listname
if ($mode=="userID|listownerID|listname")
{
	$db->Query("SELECT username, listownerID, listname FROM users WHERE 1 ORDER BY listownerID, listname, username");

	while (list($username, $listownerID, $listname) = $db->FetchRow())
	{
		$usernames[] = strtolower($username);
		$listownerIDs[] = $listownerID;
		$listnames[] = strtolower($listname);
	}

	for ($i=0; $i<count($usernames); $i++)
	{
		if ($usernames[$i]==$prevusername && $listownerIDs[$i]==$prevlistownerID && $listnames[$i]==$prevlistname)
		{
			$dupsusername[] = $usernames[$i];
			$dupslistownerID[] = $listownerIDs[$i];
			$dupslistname[] = $listnames[$i];
			continue;
	  }

		$prevusername = $usernames[$i];
		$prevlistownerID = $listownerIDs[$i];
		$prevlistname = $listnames[$i];
	}

	for ($i=0; $i<count($dupsusername); $i++)
		//$db->Query("DELETE FROM users WHERE username='$dupsusername[$i]' AND listownerID='$dupslistownerID[$i]' AND listname='$dupslistname[$i]' LIMIT 1");
		echo "$dupsusername[$i] - $dupslistownerID[$i] - $dupslistname[$i]\n";
}

echo "</pre>";

?>