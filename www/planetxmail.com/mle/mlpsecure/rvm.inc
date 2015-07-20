<?php
// resent validation mail
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/mailfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if (! ctype_alnum($u) OR ! ctype_alnum($v))
{
	header("Location: notfound.php?error=missing_params");
  exit;
}

$uID = trim($u);

$db = new Mysql_Access('mle');

if ($db->Query("SELECT username, fname, lname, status, email, listname, listownerID FROM users WHERE userID='$uID' LIMIT 1"))
{
	list($username, $fname, $lname, $status, $email, $list, $id) = $db->FetchRow();

	$validator = substr(sha1($uID.$email), 0, 5);

	if ($validator != $v)
	{
		header("Location: notfound.php?error=validator_incorrect");
	  exit;
	}

  // needed for wordwrap .. cleaning this crap up in the mean time this is it ... sorry :)
  require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

  $notValid = send_signup_mail($list, $id, 1, '', $email, $username, $uID, $fname, $lname, '', $status, 'rvm.php');
}
else
{
	header('Location: notfound.php?error=user_not_found');
  exit;
}

$notValid = urlencode($notValid);

$db->Query("SELECT listhash FROM listurls WHERE listname='$list' AND listownerID='$id'");
list($listhash) = $db->FetchRow();

header("Location: login.php?l=$listhash&notValid=$notValid");
exit;

?>