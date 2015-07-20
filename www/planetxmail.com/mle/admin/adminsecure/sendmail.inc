<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

$db = new MySQL_Access('mle');

$ms = urlencode($mailstatus);

// Check if NewsLetter, goto the HTML mailer.
if ($db->Query("SELECT listtype FROM listmanager WHERE {$_listID} AND listtype='Newsletter [closedlist]' LIMIT 1"))
{
  header('Location: sendmailhtml.php');
  exit;
}

if ($submitted == 'save')
{
  $subject       = trim($subject);
  $message       = trim($message);
  $nlsubject     = 'Your newsletter PLAIN TEXT subject here';
  $nlmessage     = 'Your newsletter PLAIN TEXT message here';
  $nlhtmlsubject = 'Your newsletter HTML subject here';
  $nlhtmlmessage = 'Your newsletter HTML message here';

  $message = $subject .
             'n!t!w_s!4!0' .
             $message .
             'n!t!w_s!4!0' .
             $nlsubject .
             'n!t!w_s!4!0' .
             $nlmessage .
             'n!t!w_s!4!0' .
             $nlhtmlsubject .
             'n!t!w_s!4!0' .
             $nlhtmlmessage;

  $db->Query("UPDATE listmanager SET message='$message' WHERE {$_listID}");

  $saved    = true;
  $notValid = 'Message saved.';
}
else
{
  $saved    = 'false';
  $notValid = 'Not saved yet.';
}

$db->Query("SELECT message FROM listmanager WHERE {$_listID} LIMIT 1");
list($data) = $db->FetchRow();
list($subject, $message) = explode('n!t!w_s!4!0', $data);

?>