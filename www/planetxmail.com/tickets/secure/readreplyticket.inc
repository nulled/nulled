<?php

$db = new MySQL_Access('pxm');

if ($_POST['submitted'] == 'reply')
{
  $sub    = substr(trim($_POST['sub']), 0, 70);
  $mess   = trim($_POST['mess']);
  $status = trim($_POST['status']);
  $number = trim($_POST['n']);
  $email  = strtolower(urldecode(trim($_POST['e'])));

  // used if a previous message was moved to the top, so reply to it
  if ($_POST['id'])
    $id = trim($_POST['id']);

  if ($status == '2')
  {
    $db->Query("UPDATE tickets SET open='0' WHERE number='{$number}' LIMIT 1");

    exit('Ticket #: $number was closed. No reply was sent.<br /><br />
          <a href="main.php?c=readclosedticket&n=' . $number . '">Delete Closed Ticket</a><br /><br />
          <a href="main.php?c=viewopentickets">Keep Closed Ticket and Goto Open Tickets</a></td></tr></table></body></html>');
  }

  if ($sub == '' OR $mess == '')  $notValid = 'ERROR: Missing required fields.';
  else if (! ctype_alnum($number))$notValid = 'ERROR: Ticket number is not valid.';
  else if (strlen($sub) > 70)     $notValid = 'ERROR: Subject exceeds 70 characters.';
  else if (strlen($mess) > 500)   $notValid = 'ERROR: Message exceeds 500 characters.';
  else if ($notValid = EmailFormat($email)) {}
  else
  {
    if (@is_numeric($id))
      $db->Query("SELECT message FROM tickets WHERE number='{$number}' AND id='{$id}'");
    else
      $db->Query("SELECT message FROM tickets WHERE number='{$number}' ORDER BY id DESC");

    list($lastmessage) = $db->FetchRow();

    $db->Query("INSERT INTO tickets (number,     email,        subject, message,  open, datereceived)
                             VALUES ('{$number}','admin-reply','{$sub}','{$mess}','{$status}',NOW())");

    $headers = 'From: Support Staff <do_not_reply@planetxmail.com>';

    $replylink = 'http://planetxmail.com/clientreply.php?number=' . $number;

    $length = strlen($replylink);
    if ($length > 80) $length = 80;
    $divider = str_repeat('-', $length);

    $messheader = "DO NOT reply to this email. You have to click the link below or copy and paste it to your browser in order to reply!\n\n";

    $messheader .= "$divider\n";
    $messheader .= $replylink."\n";
    $messheader .= "$divider\n\n";
    $messheader .= "$divider\n";
    $messheader .= "Below is our response to your question:\n";
    $messheader .= "$divider";

    $messfooter = "$divider\n";
    $messfooter .= "The email you sent us is below:\n";
    $messfooter .= "$divider\n\n";
    $messfooter .= $lastmessage;

    $messagetosend = $messheader."\n\n".$mess."\n\n".$messfooter;

    @mail($email, $sub, $messagetosend, $headers);
    @mail('elitescripts2000@yahoo.com', $sub, $messagetosend, $headers);

    $hash = strrev(substr(md5(sha1(strrev($email))), 0, 5));

    if ($status == '0')
    {
      $db->Query("UPDATE tickets SET open='0' WHERE number='{$number}' LIMIT 1");

      header("Location: main.php?c=ticketsubmitted&e={$email}&h={$hash}&m=deleted&n={$number}");
      exit;
    }
    else if ($status == '1')
    {
      header("Location: main.php?c=ticketsubmitted&e={$email}&h={$hash}&n={$number}");
      exit;
    }
    else
      $notValid = 'FATAL ERROR: Status param invalid.';
  }
}

if ($_POST['submitted'] == 'close')
{
  $number = trim($_POST['number']);

  $db->Query("UPDATE tickets SET open='0' WHERE number='$number'");

  exit("Ticket: '$number' was <b>CLOSED</b>.<a href=main.php>Back to Main</a></td></tr></table></body></html>\n");
}

if ($_GET['number'])
  $number = trim($_GET['number']);
if (! $number)
  $number = trim($_GET['n']);

$msgid = $_GET['id'];

// fetch message if id is present in URL
if (is_numeric($msgid))
{
  if ($db->Query("SELECT id, email, subject, message, number, datereceived FROM tickets WHERE number='$number' AND id='$msgid'"))
  {
    list($id, $email, $subject, $message, $num, $date) = $db->FetchRow();

    $sub        = 'Re: ' . $subject;
    $ids[]      = $id;
    $emails[]   = $email;
    $dates[]    = mysql_datetime_to_humandate($date);
    $subjects[] = $subject;
    $messages[] = $message;
  }
  else
    unset($msgid);
}

$i = 0;

if (is_numeric($msgid))
  $db->Query("SELECT id, email, subject, message, number, datereceived FROM tickets WHERE number='$number' AND id != '$msgid' ORDER BY id DESC");
else
  $db->Query("SELECT id, email, subject, message, number, datereceived FROM tickets WHERE number='$number' ORDER BY id DESC");

while (list($id, $email, $subject, $message, $num, $date) = $db->FetchRow())
{
  $sub_prefix = '';
  if (! strstr($subject, 'Re: Re: '))
    $sub_prefix = 'Re: ';

  if ($i == 0 AND ! is_numeric($msgid))
    $sub = $sub_prefix . $subject;

  $ids[]      = $id;
  $emails[]   = $email;
  $dates[]    = mysql_datetime_to_humandate($date);
  $subjects[] = $subject;
  $messages[] = $message;
  $i++;
}

?>