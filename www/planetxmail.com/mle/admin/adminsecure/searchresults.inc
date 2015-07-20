<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

$ID = explode("|", $totalIDs);

$numMatches = count($ID)-1;

for ($i=0; $i<$numMatches; $i++)
{
	$db->Query("SELECT username, fname, lname, userID FROM users WHERE userID='$ID[$i]' AND listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
	list($uname, $fname, $lname, $uID) = $db->FetchRow();

	$userMatches[$i][0] = $uname;
	$userMatches[$i][1] = $fname;
	$userMatches[$i][2] = $lname;
	$userMatches[$i][3] = $uID;
}

?>