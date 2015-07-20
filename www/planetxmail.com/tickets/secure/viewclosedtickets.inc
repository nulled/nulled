<?php

$db = new MySQL_Access("pxm");

$db->Query("SELECT id, email, subject, message, number, datereceived FROM tickets WHERE open='0' AND email!='admin-reply' ORDER BY number,id DESC");
while(list($id, $email, $subject, $message, $number, $date) = $db->FetchRow())
{
  $ids[]      = $id;
  $emails[]   = $email;
  $subjects[] = $subject;
  $dates[]    = mysql_datetime_to_humandate($date);
  $numbers[]  = $number;
}

?>
