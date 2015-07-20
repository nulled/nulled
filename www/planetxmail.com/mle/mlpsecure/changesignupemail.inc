<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($submitted == 'changeemail')
{
  if ($email1 AND $email2)
  {
    $email1 = strtolower(trim($email1));
    $email2 = strtolower(trim($email2));

    $db = new MySQL_Access('mle');

    $e = urlencode($email1);
    $h = substr(sha1('sddsf876DFJDhf8' . $email1), 0, 5);

    if ($notValid = EmailFormat($email1)) {}
    else if (strcmp($email1, $email2))
      $notValid = 'ERROR: Emails do not match.';
    else if ($db->Query("SELECT bademail FROM bounced WHERE bademail='{$email1}' AND count > 0 LIMIT 1"))
      $notValid = 'ERROR: Email Address is Bouncing. <a href="/mle/main.php?option=bannedmessagecontact&e='.$e.'&h='.$h.'">Click Here</a> for Details.';
    else if ($db->Query("SELECT listemail FROM users WHERE listemail LIKE '{$email1}%' AND userID='{$_SESSION['aauserID']}' LIMIT 1"))
      $notValid = 'ERROR: Contact Address may not be the same as your List Address.';
    else if ($db->Query("SELECT email FROM users WHERE email='{$email1}' AND {$_listID} LIMIT 1"))
      $notValid = 'ERROR: Email is already Registered on this List.';
    else
    {
      $db->Query("SELECT fromname FROM listmanager WHERE {$_listID} LIMIT 1");
      list($fromname) = $db->FetchRow();

      $headers = "From: {$fromname} <do_not_reply@planetxmail.com>";

      $emailenc  = urlencode($email1);
      $usr       = strrev($_SESSION['aauserID']);
      $validator = strrev(substr(md5($_SESSION['aauserID'] . $email1), 0, 5));

      $link = "http://planetxmail.com/mle/mca.php?u={$usr}&email={$emailenc}&v={$validator}";

      $subject = $_SESSION['aalistname'] . ' - Change Contact Email Confirmation';

      $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/changesignupemail.txt');

      $message = str_replace(array('[list_name]',          '[user_name]',           '[email]', '[link]'),
                             array($_SESSION['aalistname'], $_SESSION['aausername'], $email1,   $link),
                             $message);

      mail($email1, $subject, $message, $headers);

      $notValid = "Confirmation email was sent to: {$email1}";
      $sentemail = 1;
    }
  }
  else
    $notValid = 'ERROR: Missing required fields.';
}

?>