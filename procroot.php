#!/usr/bin/php -q
<?php
require_once('/home/nulled/config.inc');

$dbug = 0;

$db = new MySQL_Access('mle');

function get_reason($filename)
{
  $collect_reason = false;
  $reason = '';
  $empty_lines = 0;

  if (! $contents = file_get_contents($filename))
    return false;

  foreach (explode("\n", $contents) as $line)
  {
    $line = trim($line);

    if ($collect_reason)
    {
      if (! $line)
        $empty_lines++;
      else
        $empty_lines = 0;

      // if line begins with '--' or a double space (2 empty lines) detected, we know we reached the end
      if (substr($line, 0, 2) == '--' OR $empty_lines > 1)
        return trim($reason);
      else
      {
        if (! stristr($line, 'X-Postfix'))
          $reason .= $line . "\n";
      }
    }
    else if ($line AND strtolower(substr($line, 0, 30)) == strtolower('Content-Type: message/delivery'))
      $collect_reason = true;

    /* Example: Reason for failure, universal to most all known MTA
    Content-Type: message/delivery-status

    Reporting-MTA: dns; mta12.charter.net
    Arrival-Date: Thu, 31 Oct 2013 11:34:03 -0400
    Received-From-MTA: dns; imp05 (10.20.200.5)

    Final-Recipient: RFC822; <rgebke@charter.net>
    Action: failed
    Status: 4.2.2

    --====blahblah=========boundary======
    */
  }

  // did not find 'Content-Type: message/delivery', most likely an auto-reply
  return false;
}

echo "procroot: Started\n";

foreach (glob("/home/vmail/planetxmail.com/root/{new,cur}/*", GLOB_BRACE) as $filename)
{
  // uncomment line below to test get_reason()
  // $reason = ($reason = get_reason($filename)) ? "$filename\n$reason\n\n" : "$filename\n\n"; echo $reason; continue;

  if (! $contents = file_get_contents($filename))
    continue;

  foreach (explode("\n", $contents) as $line)
  {
    // trim and skip empty lines
    if (! $line = trim($line))
      continue;

    // look for UID lines to extract userID and email
    if (strstr($line, 'X-PXM-UID') OR strstr($line, 'X-FAP-UID'))
    {
      // get userID and hash
      // X-PXM-UID: L7ba41177e7 49121 Report: http://planetxmail.com/openticket.php
      list(, $userID, $hash) = explode(' ', $line);

      if ($dbug) echo "userID -> $userID\n";

      // if not numbers and letters, abort and continue
      if (! ctype_alnum($userID) OR strlen($userID) < 5)
        break;

      // first letter in userID C=pxm_solo_ad, L=pxm_listmail, D=fap_downline, S=fap_soload, X=fap system msg
      $_col = substr($userID, 0, 1);

      // get userID, strip first letter
      $userID = substr($userID, 1);

      $header_hash = substr(sha1('jd93JdmAz3hF1' . $userID), 0, 5);

      if ($header_hash != $hash)
        break;

      if ($dbug) echo "_col -> $_col :: userID -> $userID\n";

      // get db->Query column name to use
      if      ($_col == 'C') $col = 'email';      // mle - sendsoload.php
      else if ($_col == 'L') $col = 'listemail';  // mle - sendqueue.php
      else if ($_col == 'S') $col = 'email';      // fap - sendqueue.php
      else if ($_col == 'D') $col = 'email';      // fap - sendqueue.php
      else if ($_col == 'X') $col = 'email';      // fap - fap_billing.php
      else
        break;

      if ($dbug) echo "col -> $col\n";

      // determine column and DB based on first letter in userID
      if ($_col == 'C' OR $_col == 'L')
      {
        $user_col = 'userID';
        $db->SelectDB('mle');
      }
      else
      {
        $user_col = 'affid';
        $db->SelectDB('fap');
      }

      // extract email from mle or fap if exists, if not exist abort, move on to next file
      if ($db->Query("SELECT $col FROM users WHERE $user_col = '$userID' AND $col != '' LIMIT 1"))
        list($email) = $db->FetchRow();
      else
        break;

      if ($dbug) echo "email -> $email :: DB -> {$db->GetDBName()}\n";

      $reason = get_reason($filename);

      // determine if this is a quota bounce or not, and set db column to update in mle.bounced table
      if (stristr($contents, 'full') OR stristr($contents, 'quota'))
      {
        $bounced_col = 'mailboxfull';
        $reason = ($reason) ? "Mailbox is Over Quota!\n" . $reason : 'Mailbox is Over Quota.';
      }
      else
      {
        $bounced_col = 'count';
        $reason = ($reason) ? "Mailbox is Bouncing!\n" . $reason : 'Mailbox is Bouncing!';
      }

      $db->SelectDB('mle');

      // insert into mle.bounced table
      $reason = $db->EscapeString($reason);

      // get other bounced column
      $col_other = ($bounced_col == 'count') ? 'mailboxfull' : 'count';

      $sql = "INSERT INTO bounced (bademail, $bounced_col, reason, datelogged) VALUES ('$email', '1', '$reason', NOW())
              ON DUPLICATE KEY UPDATE {$bounced_col}={$bounced_col}+1, {$col_other}=0, reason='{$reason}', datelogged=NOW()";

      if (! $dbug)
      {
        $db->Query($sql);
        @unlink($filename);
        echo "procroot: $bounced_col -> $email :: DELETED -> $filename\n";
      }
      else
        echo "{$filename}\n{$sql}\n\n";

      break;
    }
  }
}

echo "procroot: QUIT\n";

?>