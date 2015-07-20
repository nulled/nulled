<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access();

if (! $db->Query("SELECT username, userID FROM users WHERE userID='$user'"))
{
	header("Location: deadurltracker.php");
	exit;
}

$userdata = $db->FetchArray();
$username = $userdata['username'];
$userID = $userdata['userID'];

if (! $db->Query("SELECT url, name FROM urlmanager WHERE userID='$userID' AND urlID='$urlID'"))
{
  header("Location: deadurltracker.php");
	exit;
}

$urldata = $db->FetchArray();
$URL = $urldata['url'];
$urldbname = $urldata['name'];
$ipaddress = $_SERVER["REMOTE_ADDR"];

$db->Query("INSERT INTO urldata VALUES ('','$userID','$urldbname','$ipaddress',NOW())");
?>
<html>
<head>
<title>Planet X Mail - URL Trackers</title>
<meta http-equiv="refresh" content="5; URL=<?=$URL?>">
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body>
<table align="center" border="0" cellpadding="0" cellspacing="0" width="640">
	<tr>
		<td>
			<center><h2>Was this URL Tracker found in SPAM?</h2></center>
			Report the SPAM <b>with URL Tracker</b> by <a href="../openticket.php" target="_blank">Opening a Ticket</a>.
			<br /><br />
			Otherwise, the page will re-direct you to the destination site in 5 secs.
			<br /><br />
			Or <a href="<?=$URL?>">Click Here</a> to goto the destination URL manually.
			<br /><br />
			If, it is spam, it DID NOT originate from <i>OUR</i> servers.
			The URL you are clicking is a URL Tracker which is freely available to all our members.
			You will need to forward the HEADERS of the email ( NOT our domain ) to	spam authorities.
			<br /><br />
			<u>WE DO NOT TOLERATE spammers using our URL Trackers in their spam with our domain name in it.</u>
			<br /><br />
			Regards,
			<br />
			<img src="../images/signature.jpg" border="0" />
			<br />
			CEO / Founder of planetxmail.com
		</td>
	</tr>
</table>
</body>
</html>