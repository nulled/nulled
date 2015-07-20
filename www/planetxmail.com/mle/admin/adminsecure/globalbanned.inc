<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

$db = new MySQL_Access('mle');

if ($deleteemail == '1')
{
  //$db->Query("DELETE FROM bounced WHERE bademail='$email' LIMIT 1");

  //$notValid = 'Email has been removed from the list.';
  $notValid = 'This feature is disabled.';
}
else if ($addemail == '1' AND $email)
{
  $email = trim($email);

  if (substr($email, 0, 1) == '@')
    $notValid = 'ERROR: Domain name can not start with an @, leave that out to include whole domains.';
  else
  {
    $date = mysql_timestamp_to_humandatetime_qbounce(timestamp_to_mysql_timestamp(time()));

    //$db->Query("REPLACE INTO bounced VALUES('$email','1','0','Global Ban Entry from MLE',NOW()) LIMIT 1");
    $notValid = 'This feature is disabled.';
  }
}

$db->Query("SELECT bademail FROM bounced WHERE count > 0 ORDER BY bademail");

$bannedlist = $db->result;

?>
