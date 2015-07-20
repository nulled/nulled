<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/mailfunctions.php');

if (! @mysqli_ping($db->link))
  $db = new MySQL_Access('mle');
else
  $db->SelectDB('mle');

if (! $resending)
{
  $i = 0;
  while (true)
  {
    $i++;

    if ($i > 3000)
      mail_debug_backtrace_exit();

    $uID = generateID(10);

    if ($db->Query("SELECT userID FROM users WHERE userID='$uID' LIMIT 1"))
      continue;
    else
      break;
  }

  $email = $email1 = strtolower(trim($email1));
}

$referercookie = ($referer) ? $_COOKIE["$listhash"] : 0;

$notValid = send_signup_mail($list, $id, $resending, $pass1, $email, $username,
                             $uID, $fname, $lname, $email1, $status, 'sendvalidationmail.php', $referercookie);

?>