<?php

function minimail_select_domain($d)
{
  global $mail_root;

  $domains = array();

  $select_domain = '<select onchange="window.location.href=this.options[this.selectedIndex].value">';
  $select_domain .= '<option value="/">-- Select a Domain --</option>';

  foreach (glob($mail_root.'/*', GLOB_ONLYDIR) as $domain)
  {
    $domains[] = $domain = basename($domain);

    $is_selected = ($d === $domain) ? ' SELECTED' : '';

    $select_domain .= '<option value="?d='.$domain.'"'.$is_selected.'>'.$domain.'</option>'."\n";
  }
  $select_domain .= '</select>';

  return array($select_domain, $domains);
}

function minimail_select_mailbox($d, $m)
{
  global $mail_root;

  $mailboxes = array();

  $select_mailbox = '<select onchange="window.location.href=this.options[this.selectedIndex].value">';
  $select_mailbox .= '<option value="?d='.$d.'">-- Select a Mailbox --</option>';

  foreach (glob($mail_root.'/'.$d.'/*', GLOB_ONLYDIR) as $mailbox)
  {
    $mailboxes[] = $mailbox = basename($mailbox);

    $is_selected = ($m === $mailbox) ? ' SELECTED' : '';

    $select_mailbox .= '<option value="?d='.$d.'&m='.$mailbox.'"'.$is_selected.'>'.$mailbox.'</option>'."\n";
  }
  $select_mailbox .= '</select>';

  return array($select_mailbox, $mailboxes);
}

function minimail_select_folder($d, $m, $fo)
{
  global $mail_root;

  $folders = array();

  $select_folder  = '<select onchange="window.location.href=this.options[this.selectedIndex].value">';
  $select_folder .= '<option value="?d='.$d.'&m='.$m.'">INBOX</option>';

  foreach (glob($mail_root.'/'.$d.'/'.$m.'/Maildir/.*', GLOB_ONLYDIR) as $folder)
  {
    $folder = basename($folder);

    if (in_array($folder, array('.','..'))) continue;

    $folders[] = $folder;

    $is_selected = ($fo === $folder) ? ' SELECTED' : '';

    $select_folder .= '<option value="?d='.$d.'&m='.$m.'&fo='.$folder.'"'.$is_selected.'>'.$folder.'</option>'."\n";
  }
  $select_folder .= '</select>';

  return array($select_folder, $folders);
}

function minimail_process_new($d, $m)
{
  global $mail_root;

  foreach (glob($mail_root.'/'.$d.'/'.$m.'/Maildir/new/*') as $mail)
  {
    copy($mail, $mail_root.'/'.$d.'/'.$m.'/Maildir/cur/'.basename($mail));
    chmod($mail_root.'/'.$d.'/'.$m.'/Maildir/cur/'.basename($mail), 0600);
    @unlink($mail);
  }
}

function minimail_process_cur($d, $m, $f, $folder, $fo, $mode, $deletemail)
{
  global $mail_root;

  $emails = $filenames = $mails = array();

  // read mail from selected folder
  // place into an array
  foreach (glob($mail_root.'/'.$d.'/'.$m.'/Maildir/'.$folder.'cur/*') as $mail)
  {
    $filenames[] = basename($mail);
    $mails[]     = $mail;
  }

  // reverse sort the array, so that the most recent entry is at the top of the listing
  $filenames = array_reverse($filenames);
  $mails     = array_reverse($mails);

  $total = count($filenames);

  if (! is_dir($mail_root.'/'.$d.'/'.$m.'/Maildir/.Trash/cur'))
  {
    mkdir($mail_root.'/'.$d.'/'.$m.'/Maildir/.Trash/cur', 0770, true);
    mkdir($mail_root.'/'.$d.'/'.$m.'/Maildir/.Trash/new', 0770, true);
    mkdir($mail_root.'/'.$d.'/'.$m.'/Maildir/.Trash/tmp', 0770, true);
  }

  for ($i=0; $i < $total; $i++)
  {
    $filename = $filenames[$i];
    $mail     = $mails[$i];

    // if deleteall and .Trash, keep going until all deleted, or delete?????
    if (($mode == 'deleteall' OR $mode == 'delete') AND $fo == '.Trash')
    {
      @unlink($mail);

      if ($mode == 'delete') $mode = '';

      continue;
    }
    else if ($mode == 'delete' AND $mail == $mail_root.'/'.$d.'/'.$m.'/Maildir/'.$folder.'cur/'.$f)
    {
      copy($mail, $mail_root.'/'.$d.'/'.$m.'/Maildir/.Trash/cur/'.$f);
      @unlink($mail);
      if ($mode == 'delete') $mode = '';
      continue;
    }
    else if ($mode == 'deleteselected' AND @is_array($deletemail))
    {
      if (in_array($filename, $deletemail))
      {
        if ($fo != '.Trash')
          copy($mail, $mail_root.'/'.$d.'/'.$m.'/Maildir/.Trash/cur/'.$filename);

        @unlink($mail);
        unset($deletemail[$filename]);
        continue;
      }
    }
    else if ($mode == 'moveselected' AND @is_array($deletemail))
    {
      if (in_array($filename, $deletemail))
      {
        if ($fo == '.Trash')
          copy($mail, $mail_root.'/'.$d.'/'.$m.'/Maildir/cur/'.$filename);

        @unlink($mail);
        unset($deletemail[$filename]);
        continue;
      }
    }

    list($emails[$filename]['timestamp']) = explode('.', $filename);

    $headers = '';
    $get_content_boundary = $collect_content = $collect_content_begin = 0;

    $emails[$filename]['raw_data'] = file_get_contents($mail);

    $lines = file($mail);

    foreach ($lines as $line)
    {
      $line = trim($line);

      // end of headers
      if ($line == '')
        break;

      $headers .= $line."\n";

      if ($get_content_boundary)
      {
        list(, $emails[$filename]['content-boundary']) = explode('"', $line);
        $get_content_boundary = 0;
        continue;
      }

      if (substr($line, 0, 4) == 'To: ')           list(, $emails[$filename]['to']) = explode(' ', $line, 2);
      else if (substr($line, 0, 9) == 'Subject: ') list(, $emails[$filename]['subject']) = explode(' ', $line, 2);
      else if (substr($line, 0, 6) == 'From: ')    list(, $emails[$filename]['from']) = explode(' ', $line, 2);
      else if (substr($line, 0, 6) == 'Date: ')    list(, $emails[$filename]['date']) = explode(' ', $line, 2);
      else if (substr($line, 0, 4) == 'To: ')      list(, $emails[$filename]['to']) = explode(' ', $line, 2);

      else if (substr($line, 0, 27) == 'Content-Transfer-Encoding: ')
        list(, $emails[$filename]['content-transfer-encoding']) = explode(' ', $line, 2);

      else if (substr($line, 0, 14) == 'Content-Type: ')
      {
        list(, $emails[$filename]['content-type']) = explode(' ', $line, 2);
        if ($emails[$filename]['content-type'] == 'multipart/alternative;')
          $get_content_boundary = 1;
      }
    }

    $emails[$filename]['headers'] = $headers;

    // get mail content
    if ($mode != '' AND $mode != 'deleteselected')
    {
      $data = file_get_contents($mail);
      list(, $body) = explode("\n\n", $data, 2);

      $k = 1;

      if ($emails[$filename]['content-boundary'])
      {
        $parts = explode($emails[$filename]['content-boundary'], $body);

        //echo print_r($parts, 1); sleep(2);

        foreach ($parts as $part)
        {
          $get_body = 0;
          $lines = explode("\n", $part);

          if (count($lines))
          {
            $j = 0;
            foreach ($lines as $line)
            {
              //sleep(1); echo $line."\n";

              if ($j == 0 AND $line == '') continue;
              if ($j == 0 AND substr($line, 0, 14) != 'Content-Type: ')
                break;

              if ($line == '' OR $get_body)
              {
                $emails[$filename]['content-'.$k] .= $line."\n";
                $get_body = 1;
              }
              else
              {
                if (substr($line, 0, 14) == 'Content-Type: ')
                  list(, $emails[$filename]['content-type-'.$k]) = explode(' ', $line, 2);
                if (substr($line, 0, 27) == 'Content-Transfer-Encoding: ')
                  list(, $emails[$filename]['content-transfer-encoding-'.$k]) = explode(' ', $line, 2);
              }

              $j++;
            }

            if ($emails[$filename]['content-type-'.$k]) $k++;
          }
        }
      }
      else
      {
        $emails[$filename]['content-'.$k] = $body;
      }
    }
  }

  //exit('<pre>'.print_r($emails, 1).'</pre>');

  return $emails;
}

function minimail_list($d, $m, $fo)
{
  global $emails;

  $subject_max_display_length = 60;
  $td_width = 25;

  if (count($emails))
  {
    echo '
    <form name="listmail" action="?d='.$d.'&m='.$m.'&fo='.$fo.'" method="POST">

    <tr bgcolor="beige">
      <td nowrap align="center" width="'.$td_width.'"><input type="checkbox" name="checkdeleteall" onclick="checkAll()" /></td>
      <td width="40%">&nbsp;<b>From:</b></td>
      <td width="40%"><b>Subject:</b></td>
      <td><b>Date Received:</b></td>
    </tr>
    <tr>
      <td colspan="10"><hr /></td>
    </tr>
    ';

    $email_inc = 1;

    foreach ($emails as $filename => $arr)
    {
      $to = $from = $subject = $date = '';

      foreach ($arr as $header => $value)
      {
        $value = trim($value);

        if ($header == 'to')
          $to = $value;
        else if ($header == 'from')
        {
          unset($from, $from1, $from2);

          list($from1, $from2) = preg_split('/[<>]/', $value);

          if ($from2)
            $from = trim($from2);
          else
            $from = trim($from1);
        }
        else if ($header == 'subject')
        {
          if (strlen($value) > $subject_max_display_length)
            $subject = substr($value, 0, $subject_max_display_length).' ...' ;
          else
            $subject = $value;
        }
        else if ($header == 'date')
          $date = $value;
        else if ($header == 'timestamp')
          $timestamp = $value;
        else if ($header == 'spam-status')
          $spam_status = $value;
      }

      $filename = urlencode($filename);

      $ymd  = strftime("%x", $timestamp);
      $time = strftime("%X", $timestamp);
      $date = "$ymd $time";

      list($_1, $_2) = explode('@', $from);
      $from = $_1.'@<font color="red">'.$_2.'</font>';

      $align = 'left';

      // rotate row colors
      if ($email_inc % 2)
        $bgcolor = '#E9E9F1';
      else
        $bgcolor = '#FFFFFF';

      $mouseovr = 'onmouseover="changeColorMouseOver('.$email_inc.')"';
      $mouseout = 'onmouseout="changeColorMouseOut('.$email_inc.')"';

      // create mail row
      echo '
     <tr id="'.$email_inc.'" bgcolor="'.$bgcolor.'" '.$mouseovr.' '.$mouseout.'>
      <td nowrap align="'.$align.'" width="'.$td_width.'">
        <input type="checkbox" id="cb_'.$email_inc.'" name="deletemail[]" value="'.$filename.'" onclick="changeColor('.$email_inc.', this.checked)" />
      </td>
      <td nowrap>&nbsp;'.$from.'</td>
      <td nowrap>
        <a href="?d='.$d.'&m='.$m.'&f='.$filename.'&fo='.$fo.'&mode=read">'.htmlentities($subject).'</a>
      </td>
      <td nowrap>'.$date.'</td>
     </tr>
      ';

      $email_inc++;
    }

    echo '<tr><td align="left" colspan="20"><hr />
    <input type="button" value="Delete Selected" onclick="document.forms[\'listmail\'].mode.value=\'deleteselected\';document.forms[\'listmail\'].submit();" />
    ';

    if ($fo == '.Trash') echo ' OR <input type="button" value="Move Selected to INBOX" onclick="document.forms[\'listmail\'].mode.value=\'moveselected\';document.forms[\'listmail\'].submit();" />
    </td></tr>
    ';
  }
  else
  {
    echo '<h3>No Email in your Box.</h3>';
    $mode = '';
  }

  echo '<input type="hidden" name="mode" value="" />
        </form>';
}

function minimail_read($d, $m, $f, $fo)
{
  global $emails;

  $f = urldecode($f);

  $from    = $emails[$f]['from'];
  $subject = $emails[$f]['subject'];

  /*
  $emails[$f]['content-1']
  $emails[$f]['content-type-1']
  $emails[$f]['content-transfer-encoding-1']
  */

  //exit('<pre>'.print_r($emails[$f], 1).'</pre>');

  if ($emails[$f]['content-transfer-encoding-1'] == 'quoted-printable' OR
      $emails[$f]['content-transfer-encoding']   == 'quoted-printable')
    $content = quoted_printable_decode($emails[$f]['content-1']);
  else
    $content = $emails[$f]['content-1'];

  $reply_link  = "?d={$d}&m={$m}&f=" . urlencode($f) . "&fo={$fo}&mode=reply";
  $delete_link = "?d={$d}&m={$m}&f=" . urlencode($f) . "&fo={$fo}&mode=delete";

  echo '
  <tr>
    <td>
      <button onclick="javascript:location.href=\'' . $reply_link . '\'">Reply</button> Or
      <button onclick="javascript:location.href=\'' . $delete_link . '\'">Delete</button>
      <br /><br />
      From: <b>' . htmlentities($from) . '</b><br />
      Subject: <b>' . htmlentities($subject) . '</b><br />
      <br />
      <textarea name="email" rows="30" cols="120" wrap="on">' . $content . '</textarea>
      <br /><br />
      <button onclick="javascript:location.href=\'' . $reply_link . '\'">Reply</button> OR
      <button onclick="javascript:location.href=\'' . $delete_link . '\'">Delete</button>
      <br /><br />
    <td>
  </tr>
  ';

  echo "<tr><td><pre>" . print_r($emails[$f]['raw_data'], 1) . "</pre></td></tr>";
}

function minimail_reply($d, $m, $f, $fo)
{
  global $emails;

  $f = urldecode($f);

  $from    = $emails[$f]['from'];
  $subject = $emails[$f]['subject'];

  /*
  $emails[$f]['content-1']
  $emails[$f]['content-type-1']
  $emails[$f]['content-transfer-encoding-1']
  */

  if ($emails[$f]['content-transfer-encoding-1'] == 'quoted-printable' OR $emails[$f]['content-transfer-encoding'] == 'quoted-printable')
    $content = quoted_printable_decode($emails[$f]['content-1']);
  else
    $content = $emails[$f]['content-1'];

  $subject = 'Re: '.$subject;

  $oldcontent = '';
  $lines = explode("\n", $content);
  foreach ($lines as $line) $oldcontent .= '>'.rtrim($line)."\n";
  $content = "\n\n\n\n".$oldcontent;

  $headers = "From: Matt <$m@$d>\nX-Mailer: Sent using MiniMail 1.0 (PHP)";

  echo '
  <form name="sendmail" action="?d='.$d.'&m='.$m.'&fo='.$fo.'" method="POST">
  <tr>
    <td>
      <br />
      <b>To:</b> <input type="text" name="to" value="'.htmlentities($from).'" size="80" maxlength="255" /><br />
      <b>Subject:</b> <input type="text" name="subject" value="'.$subject.'" size="80" maxlength="80" /><br />
      <textarea name="content" rows="20" cols="80" wrap="on">'.$content.'</textarea>
      <br />
      <input type="submit" value="Send Mail" />
    <td>
  </tr>
  <input type="hidden" name="d" value="'.$d.'" />
  <input type="hidden" name="m" value="'.$m.'" />
  <input type="hidden" name="fo" value="'.$fo.'" />
  <input type="hidden" name="f" value="'.$f.'" />
  <input type="hidden" name="headers" value="'.$headers.'" />
  <input type="hidden" name="mode" value="send" />
  </form>
  ';
}

function minimail_send($d, $m, $folder, $f, $to, $subject, $content, $headers)
{
  global $general_message, $mail_root;

  $to      = stripslashes($to);
  $subject = stripslashes($subject);
  $content = stripslashes($content);
  $headers = urldecode($headers);

  //exit('<pre>'.htmlentities("to=$to subject=$subject content=$content headers=$headers").'</pre>');

  $mail      = "$mail_root/$d/$m/Maildir/{$folder}cur/{$f}";
  $sent_mail = "$mail_root/$d/$m/Maildir/.sent-mail/cur/{$f}";

  if (! is_dir("$mail_root/$d/$m/Maildir/.sent-mail/cur"))
  {
    mkdir("$mail_root/$d/$m/Maildir/.sent-mail/cur", 0770, true);
    mkdir("$mail_root/$d/$m/Maildir/.sent-mail/new", 0770, true);
    mkdir("$mail_root/$d/$m/Maildir/.sent-mail/tmp", 0770, true);
  }

  if (@is_file($mail))
  {
    copy($mail, $sent_mail);
    chmod($sent_mail, 0600);
    $general_message .= "Saved a copy in sent-mail folder.\n";
  }
  else
    $general_message .= "ERROR: Unable to save mail to sent-mail folder, mail file not found.\n";

  @mail($to, $subject, $content, $headers);

  $general_message .= "Delivered to: <b>$to</b>\n";
}

function minimail_create_header($select_folder, $select_mailbox, $select_domain, $mode, $fo, $folder, $m, $d)
{
  global $emails;

  echo '<br />Current Mailbox:&nbsp;' . $select_mailbox . '<font size="+1"><b>@</b></font>' . $select_domain;

  $return_to_folder = "?d=$d&m=$m&fo=$fo";

  if ($mode == '')
  {
    echo '&nbsp;Current Folder: ' . $select_folder. '&nbsp;<button onclick="javascript:location.href=\'' . $return_to_folder . '\'">Reload Folder</button>';

    if ($fo == '.Trash' AND count($emails))
      echo '&nbsp;<button onclick="javascript:if (confirm(\'Are you sure?\')) location.href=\'' . $return_to_folder . "&mode=deleteall'\">Empty Folder</button>";
  }
  else
  {
    if ($fo == '')
      $_folder = 'INBOX';
    else
      $_folder = $fo;

    echo '&nbsp;&nbsp;<button onclick="javascript:location.href=\'' . $return_to_folder . '\'">Return to <b>'.$_folder.'</b> Folder</button>';
  }

  echo '<br /><br />';
}

?>
