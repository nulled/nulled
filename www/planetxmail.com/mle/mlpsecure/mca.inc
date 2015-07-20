<?php
// modify contact address
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if (! $u OR ! $email OR ! $v)
  $notValid = 'Missing required fields.';
else
{
  $usr = strrev(trim($u));
  $email = urldecode(trim($email));
  $validator = strrev(substr(md5($usr.$email), 0, 5));

  $db = new MySQL_Access('mle');

  // $r means resend, to clear a bounced email, initialted from bannedmessagecontact/listemail

  if ($v != $validator)
    $notValid = 'ERROR: This URL is Invalid please resubmit a Contact Address Change Request.';
  else if (! $r AND $db->Query("SELECT email FROM users WHERE email='$email' AND userID='$usr' LIMIT 1"))
    $notValid = 'Your Contact Address is already to ' . $email;
  else
  {
    $db->Query("UPDATE users SET email='$email' WHERE userID='$usr' LIMIT 1");
    $db->Query("DELETE FROM bounced WHERE bademail='$email'");

    if ($r)
      $notValid = 'Your Contact Address has been cleared from Bounced List.';
    else
      $notValid = 'Your Contact Address has been changed.';
  }
}

?>