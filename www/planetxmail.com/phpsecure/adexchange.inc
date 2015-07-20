<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$page = 'links';

if ($_POST['submitted'] == 'send')
{
  $name    = trim($_POST['name']);
  $message = trim($_POST['message']);
  $email   = trim($_POST['email']);

  if ($message && $name && $email)
  {
    if ($notValid = EmailFormat($email)) {}
    else
    {
      if (! $page) $page = 'links';

      if ($page == 'sendmail')   $ad_length = 750;
      else if ($page == 'links') $ad_length = 1000;

      $message = substr(str_replace("\'", '', trim($message)), 0, $ad_length);
      $name    = trim($name);

      $db = new MySQL_Access("mle");
      $db->Query("INSERT INTO directads VALUES('','$name','$message','$email','0','$reference',NOW())");
      $id = $db->GetLastID();

      // header("Location: adexchangepaylinks.php?id=$id");
      exit('Please follow these steps and email elitescripts2000@yahoo.com when you are done and we will approve your listing.');
    }
  }
  else
    $notValid = 'ERROR: Missing required parameters.';
}

?>