<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/mailfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

if ($submitted == 'addlistaddress')
{
  if ($clear == 'yes')
  {
    $db->Query("UPDATE users SET listemail='' WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");

    $notValid = urlencode('List Address Successfully Cleared.');

    header("Location: main.php?option=memberprofile&notValid={$notValid}");
    exit;
  }

  if ($email1 AND $email2)
  {
    $email1 = strtolower(trim($email1));
    $email2 = strtolower(trim($email2));

    list(, $domain) = explode('@', $email1);

    if ($notValid = EmailFormat($email1)) {}
    else if (strcmp($email1, $email2))
      $notValid = 'ERROR: Email Addresses Entered Do Not Match.';
    else if ($db->Query("SELECT bademail FROM bounced WHERE bademail='{$email1}' AND count > 0 LIMIT 1"))
      $notValid = 'ERROR: Email Address is not allowed due to bouncing problems.';
    else if (@in_array($domain, $_LISTEMAIL_BANNED_DOMAINS))
      $notValid = 'ERROR: Email DOMAIN can not be used as List Address, due to Heavy Mail Loads.';
    else if ($db->Query("SELECT email FROM users WHERE email='{$email1}' AND userID='{$_SESSION['aauserID']}' LIMIT 1"))
      $notValid = 'ERROR: Your List Address must be Different from your Contact Address.';
    else if ($db->Query("SELECT listemail FROM users WHERE listemail='{$email1}' AND {$_listID} LIMIT 1"))
      $notValid = 'ERROR: List Address is already Registered with this List.';
    else
      $notValid = send_listemail_confirm_mail($email1, $_SESSION['aauserID'], $_SESSION['aalistname'], $_SESSION['aalistownerID']);
  }
  else
    $notValid = 'ERROR: Missing required fields.';
}

$db->Query("SELECT listemail FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($listaddress) = $db->FetchRow();

if (substr($listaddress, strlen($listaddress)-11, 11) == 'unconfirmed')
{
  $listaddress = substr($listaddress, 0, strlen($listaddress)-11);
  $listaddress .= ' - Unconfirmed';
}

?>