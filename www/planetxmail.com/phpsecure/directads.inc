<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($submitted == 'send')
{
  if ($message AND $name AND $email)
  {
    if ($notValid = EmailFormat($email)) {}
    else
    {
      if (! $page) $page = 'sendmail';

      if ($page == 'sendmail')   $ad_length = 750;
      else if ($page == 'links') $ad_length = 1000;

      $message = substr(str_replace("\'", '', $message), 0, $ad_length);

      $db = new MySQL_Access('mle');

      $db->Query("INSERT INTO directads VALUES('','$name','$message','$email',1,15,'$page','$list','','',NOW(),'0')");
      $id = mysqli_insert_id($db->link);

      header("Location: directadpaylinks.php?id=$id&numDays=1&page=$page");
      exit;
    }
  }
  else
    $notValid = "ERROR: Missing required fields.";
}

?>