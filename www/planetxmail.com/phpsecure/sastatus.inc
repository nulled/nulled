<?php

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

$v = trim($_GET['v']);
$h = trim($_GET['h']);

$hash = substr(sha1($v . sha1('jfHdf8745JfhfdjdiLuaQ')), 0, 5);

if ($h == $hash)
{
  $db = new MySQL_Access('mle');

	if ($db->Query("SELECT name, subject, message, email, crediturl, listname, datesubmitted, mailed, datemailed FROM soloads WHERE receipt != '' AND id='$v' LIMIT 1"))
	{
		list($name, $subject, $message, $email, $crediturl, $type, $datesubmitted, $mailed, $datemailed) = $db->FetchRow();

		$db->Query("SELECT url FROM userlinks WHERE id='$crediturl' LIMIT 1");
		list($crediturl) = $db->FetchRow();

		if (! $mailed)
		  $notValid = 'In Queue, waiting to be delivered...';
		else if ($datemailed == '0000-00-00 00:00:00')
		  $notValid = 'Currently being mailed out...';
		else
		  $notValid = 'Mailing Complete.';
	}
	else
		$notValid = 'ERROR: Receipt not found. Please contact: <a href="openticket.php">Open a Ticket</a>';
}
else
	$notValid = 'ERROR: Make sure you copy and pasted the URL/Link correctly. Contact: <a href="openticket.php">Open a Ticket</a> for assistance.';

?>