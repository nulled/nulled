<?php
include("mlpsecure/config/config.inc");
include("mlpsecure/config/classes.inc");

if ($uID AND $currentstatus AND $newstatus)
{
  if ($newstatus=="pro" OR $newstatus=="exe")
  {
    $db = new MySQL_Access();

    if ($cbreceipt) $receipt = $cbreceipt;
    else
      $receipt = $item;

    $db->Query("INSERT INTO upgrade VALUES ('','$uID','$currentstatus','$newstatus',NOW(),'$_SESSION[aalistname]','$_SESSION[aalistownerID]','$receipt')");
    $db->Query("UPDATE users SET status='$newstatus' WHERE userID='$uID'");
    /*
    $subject = "$list - New member sign up notice";
    $message = file_get_contents("/home/nulled/www/planetxmail.com/mle/mlpsecure/messages/newmemberupgradenotice.txt");
    $message = wordwrap($message, $email_wordwrap_length);

    $message = str_replace("[user_name]", $username, $message);
    $message = str_replace("[referer]", $referer, $message);
    $message = str_replace("[ipaddress]", $ipaddress, $message);
    $message = str_replace("[first_name]", $fname, $message);
    $message = str_replace("[last_name]", $lname, $message);
    $message = str_replace("[list_name]", $list, $message);
    $message = str_replace("[status]", $status, $message);
    $message = str_replace("[date]", mysql_timestamp_to_humandatetime(timestamp_to_mysql_timestamp(time())), $message);

    mail($adminemail, $subject, $message, "From: $fromname <$bounceemail>");
    */
  }
}

?>
