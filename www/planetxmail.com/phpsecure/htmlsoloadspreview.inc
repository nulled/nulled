<?php
include("/home/nulled/www/planetxmail.com/phpsecure/classes.inc");
include("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

if (! is_numeric($id)) exit('Invalid ID');

$db = new MySQL_Access("mle");

if ($submitted=="send")
{
  $name      = trim($name);
  $crediturl = trim($crediturl);
  $subject   = trim($subject);
  $email     = trim($email);

  if ($email && $subject && $name)
  {
    if ($crediturl && (strtolower(substr($crediturl, 0, 7)) != 'http://' && strtolower(substr($crediturl, 0, 8)) != 'https://'))
      $notValid = "ERROR: Credit URL must begin with http:// or https://";
    else if ($notValid = EmailFormat($email)) {}
    else
    {
      $urlID = create_creditID($crediturl, 'SOLOAD');

      $db->Query("UPDATE soloads SET name='$name', subject='$subject', email='$email', crediturl='$urlID', datesubmitted=NOW() WHERE id='$id'");

      $hash = substr(sha1($id.'sahfme845jdkdhf87hff'), 0, 5);

      header("Location: soloadpaylinks.php?id=$id&h=$hash&type=html");
      exit;
    }
  }
  else
    $notValid = "ERROR: Missing required params.";
}

$db->Query("SELECT message FROM soloads WHERE id='$id'");
list($message) = $db->FetchRow();

?>