<?php
include("../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("mle");

$db->Query("SELECT bademail, count, mailboxfull, reason FROM bounced WHERE 1 ORDER BY date DESC");

echo "<pre><font face=ariel>\n";

while (list($email, $count, $mbf, $reason) = $db->FetchRow())
{
	echo sprintf("%-35s%-2s%-2s\n%-s", $email, $count, $mbf, $reason);
	echo "<hr>\n";
}

echo "</font></pre>";

?>