<?php

$db = new MySQL_Access('pxm');

$db->Query("SELECT email, subject, number, datereceived FROM tickets WHERE open='1' ORDER BY datereceived DESC");
while(list($email, $subject, $number, $date) = $db->FetchRow())
{
  $emails[]    = $email;
  $subjects[]  = $subject;
  $numbers[]   = $number;
  $dates[]     = mysql_datetime_to_humandate($date);
}

?>
