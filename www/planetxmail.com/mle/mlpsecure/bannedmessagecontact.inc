<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

if ($e AND $h)
{
  $email = urldecode(trim($e));
  $vhash = substr(sha1('sddsf876DFJDhf8' . $email1), 0, 5);
}

if ($e AND trim($h) == $vhash) {}
else
{
  $db->Query("SELECT email FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
  list($email) = $db->FetchRow();
}

if ($submitted == 'resend')
{
  $db->Query("SELECT fromname FROM listmanager WHERE {$_listID} LIMIT 1");
  list($fromname) = $db->FetchRow();

  $headers = "From: {$fromname} <do_not_reply@planetxmail.com>";

  $emailenc  = urlencode($email);
  $usr       = strrev($_SESSION['aauserID']);
  $validator = strrev(substr(md5($_SESSION['aauserID'] . $email), 0, 5));

  // added $r mrans resent to clear bounced table ... as apposed to confirmation
  $link = "http://planetxmail.com/mle/mca.php?u={$usr}&email={$emailenc}&v={$validator}&r=1";

  $subject = $_SESSION['aalistname'] . ' - Contact Email Confirmation';

  $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/changesignupemail.txt');

  $message = str_replace(array('[list_name]',          '[user_name]',           '[email]', '[link]'),
                         array($_SESSION['aalistname'], $_SESSION['aausername'], $email,   $link),
                         $message);

  mail($email, $subject, $message, $headers);

  $notValid = "Confirmation email was sent to: {$email}";
}

$db->Query("SELECT reason FROM bounced WHERE bademail='$email' LIMIT 1");
list($reason) = $db->FetchRow();

$reason = wordwrap($reason, 85);

?>