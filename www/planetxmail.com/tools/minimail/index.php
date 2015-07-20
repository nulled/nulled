<?php
set_time_limit(0);

require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');
require_once('/home/nulled/www/planetxmail.com/tools/minimail/secure/functions.inc');

$mail_root = '/home/nulled/mailstorage';

$d       = trim($_REQUEST['d']);    // domain
$m       = trim($_REQUEST['m']);    // mailbox
$f       = trim($_REQUEST['f']);    // file
$fo      = trim($_REQUEST['fo']);   // folder (blank= INBOX)
$mode    = trim($_REQUEST['mode']); // modes 'read', 'reply', 'send', 'deleteselected', 'deleteall', 'delete'

$to      = trim($_REQUEST['to']);
$subject = trim($_REQUEST['subject']);
$content = trim($_REQUEST['content']);
$headers = trim($_REQUEST['headers']);

// prevent url code injection
$val_in = $d.$m.$f.$fo;
if (strstr($val_in, '/') OR strstr($val_in, ';')) $d = $m = $f = $fo = '';

$general_message = "\n\n";

// prevent unauthorized mode inputs
$allowed_modes = array('read', 'reply', 'deleteall', 'send', 'deleteselected', 'delete', 'moveselected');
if (! in_array($mode, $allowed_modes)) $mode = '';

list($select_domain, $domains) = minimail_select_domain($d);

// check domain exists
if (in_array($d, $domains))
{
  list($select_mailbox, $mailboxes) = minimail_select_mailbox($d, $m);

  // check mailbox exists
  if (@in_array($m, $mailboxes))
  {
    list($select_folder, $folders) = minimail_select_folder($d, $m, $fo);

    $folder = (@in_array($fo, $folders)) ? "{$fo}/" : '';

    if ($mode == 'send') minimail_send($d, $m, $folder, $f, $to, $subject, $content, $headers);

    minimail_process_new($d, $m);

    $emails = minimail_process_cur($d, $m, $f, $folder, $fo, $mode, $deletemail);

    // if one of these modes used, set to '', so that mail listing will occur
    if ($mode == 'delete' OR $mode == 'deleteall' OR $mode == 'deleteselected' OR $mode == 'moveselected' OR $mode == 'send') $mode = '';
  }
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>MiniMail</title>
<link rel="icon" href="/favicon.ico" type="image/x-icon" />
<link rel="stylesheet" type="text/css" href="mm.css" />
<script language="javascript" src="mm.js"></script>
</head>
<body>
<table border="0" align="left" cellpadding="0" cellspacing="0" summary="Main Table">
  <tr>
    <td>
      <h2>Welcome to MiniMail</h2>

<?php

      if (trim($general_message))
        echo '<div class="general_message">' . htmlentities($general_message) . '</div>';

      minimail_create_header($select_folder, $select_mailbox, $select_domain, $mode, $fo, $folder, $m, $d);

?>

    </td>
  </tr>

  <tr>
    <td>
      <table border="0" align="center" cellpadding="0" cellspacing="1" summary="Main Content View">

<?php

      if ($mode == '')           minimail_list($d, $m, $fo);
      else if ($mode == 'read')  minimail_read($d, $m, $f, $fo);
      else if ($mode == 'reply') minimail_reply($d, $m, $f, $fo);

?>

      </table>
    </td>
  </tr>
</table>
</body>
</html>
