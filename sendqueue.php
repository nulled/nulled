#!/usr/bin/php -q
<?php
set_time_limit(0);

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');

class SendQueue
{
  public $db;
  public $postfix_queue;
  public $queue_max;
  public $lifecycle;
  public $lifecycle_counter;
  public $totalmailed;
  public $fnames;
  public $prevmailed;

  function __construct($db, $argv, $postfix_queue)
  {
    $this->postfix_queue     = $postfix_queue;
    $this->queue_max         = 2000;
    $this->lifecycle         = 50;
    $this->lifecycle_counter = 0;
    $this->totalmailed       = 0;
    $this->prevmailed        = array();
    $this->fnames            = array('[fname]','[first-name]','[first_name]','[firstname]','%firstname%',
                                      '{firstname}','{first_name}','{!firstname}','(firstname)','(first_name)',
                                      'first-name','first_name','firstname','fname');

    if (is_file('/root/kill_sendqueue'))
      exit("not running per kill_sendqueue request ... exiting\n");

    if ($argv[1] != 'cron')
      exit("ERROR: Must be run as a cronjob!\n");

    if ($is_running = start_program('sendqueue.php cron'))
      exit("$is_running:sendqueue.php is already operating ... exiting\n");

    if (date('G') == 0 AND date('i') < 5)
      exit("It is midnight. Give time for all cronjobs to finish ... exiting\n");

    $this->db = $db;;
  }

  private function GetMicroSeconds()
  {
    // (86400 secs / totalmail) * 1000000 = usleep()
    $c_hour = date('G');
    $c_min  = date('i');
    $c_sec  = date('s');
    $hours  = (60 * 60 * $c_hour);
    $mins   = (60 * $c_min);
    $secs   = 0 + $c_sec;
    $secsFromMidnight = ($hours + $mins + $secs);
    $seconds = 86400 - $secsFromMidnight;

    $this->db->Query("SELECT totalcount FROM mailcount WHERE id='1'");
    list($totalcount) = $this->db->FetchRow();

    if (is_numeric($totalcount) AND $totalcount > 0 AND ! ($c_hour == 23 AND $c_min > 45))
    {
      if ($seconds < 1)
        $seconds = 86400;

      $u_seconds = floor(($seconds / $totalcount) * 1000000);
    }
    else
      $u_seconds = 250000;

    return $u_seconds;
  }

  public function SendSoloAD($website)
  {
    if ($website == 'fap')
    {
      $GLOBALS['domain_name'] = $domain_name  = 'freeadplanet';
      $database     = 'fap';
      $abbr         = 'FAP';
      $mail_from    = 'Free AD Planet';
      $master_affid = '11187448';
    }
    else if ($website == 'tap')
    {
      $GLOBALS['domain_name'] = $domain_name  = 'targetedadplanet';
      $database     = 'tap';
      $abbr         = 'TAP';
      $mail_from    = 'Targeted AD Planet';
      $master_affid = '99999';
    }
    else
      exit("FATAL ERROR: website:{$website} in sendqueue.php unknown\n");

    $db = $this->db;
    $bad_emails = array();
    $good = $bad = $i = 0;
    $u_seconds = 2500000;

    $db->SelectDB('mle');

    // get bounced emails
    $db->Query("SELECT bademail FROM bounced WHERE count < 5 OR mailboxfull > 0 ORDER BY bademail");
    while (list($e) = $db->FetchRow())
      $bad_emails[] = strtolower($e);

    $db->SelectDB($database);

    echo "Begin mailing {$abbr} {$domain_name} ... \n";

    if ($db->Query("SELECT id, affid, subject, message, crediturl, usecredits, soload FROM mailqueue WHERE 1 ORDER BY id LIMIT 1"))
    {
      list($id, $affid, $subject, $message, $crediturl, $usecredits, $soload) = $db->FetchRow();

      $db->Query("DELETE FROM mailqueue WHERE id='$id' LIMIT 1");

      if ($db->Query("SELECT fname, username FROM users WHERE affid='$affid' LIMIT 1"))
        list($fname, $username) = $db->FetchRow();
      else
        return;

      if ($soload)
      {
        $isHTML    = ($soload == '2') ? 1 : 0; // $soload 0=downline, 1=textsoload, 2=HTMLsoload
        $headerID  = 'S';
        $type      = 9;
        $typename  = 'Solo Ad';
        $from_name = $abbr . ' SOLO AD';
        $mailcount = $db->Query("SELECT fname, username, email, affid FROM users WHERE email != '' AND verified='1' AND vacation='0' ORDER BY email");
      }
      else
      {
        $isHTML    = 0;
        $headerID  = 'D';
        $type      = 0;
        $typename  = 'DownLine';
        $from_name = $mail_from;
        $mailcount = $db->Query("SELECT fname, username, email, affid FROM users WHERE sponsor='$affid' AND email != '' AND verified='1' AND vacation='0' ORDER BY email LIMIT $usecredits");
      }
      $res = $db->result;

      $footer = "

** Click URL below to Earn Credits:
[credit_url]

______________________________________________________________
This message is not spam! You received this because you joined
the very successful {$domain_name}.com sent by {$typename} Submit
and agreed to receive periodic mail from other members, in return
for You being able to post Your own offers.

[remove_url]
32811 7th Ave SW, Federal Way, WA, 98023
";

      while ($e = mysqli_fetch_assoc($res))
      {
        $e['email'] = strtolower($e['email']);

        // skip bounced emails
        if (in_array($e['email'], $bad_emails))
        {
          echo "Skipping {$e['email']} ...\n";
          continue;
        }

        if (in_array($e['email'], $this->prevmailed))
        {
          echo 'Skipping previous mailed: ' . $e['email'] . "\n";
          continue;
        }

        $this->prevmailed[] = $e['email'];

        $head = "From: {$from_name} <do_not_reply@{$domain_name}.com>\n";

        $hash = substr(sha1('jd93JdmAz3hF1' . $e['affid']), 0, 5);
        $head .= "X-{$abbr}-UID: {$headerID}{$e['affid']} {$hash} Report: http://{$domain_name}.com/openticket.php";

        $hash = substr(sha1($e['affid'] . 'sjdhf3938483jhdsjh'), 0, 5); // do not change tied to fap/tap
        $remove_url = "http://{$domain_name}.com/?c=remove&a={$e['affid']}&h={$hash}";

        if ($e['affid'] != $affid OR $affid == $master_affid)
          $cred_url = convert_url($e['affid'], $crediturl, $affid, $db, $type); // do not change tied to fap/tap
        else
          $cred_url = 'Confirmation of your mailing. Earn links are valid only from other members.';

        if ($isHTML)
        {
          if (! stristr($cred_url, 'confirmation'))
            $cred_url = '<a href="' . $cred_url . '">** Click Here</a> to Earn 5 times the Credits from this Solo AD.';

          $remove_url = '<a href="' . $remove_url . '">Click Here to Unsubscribe</a>';

          $head .= "MIME-Version: 1.0\nContent-type: text/html; charset=iso-8859-1\n";

          $mess = $message . str_replace("\n", '<br />', $footer);
        }
        else
          $mess = $message . $footer;

        $subj = str_ireplace(array('[fname]', '[firstname]', '[first_name]'),
                            array($e['fname'] ,$e['fname'], $e['fname']),
                            $subject);

        $mess = str_ireplace(array('[fname]', '[firstname]', '[first_name]', '[credit_url]', '[remove_url]'),
                            array($e['fname'], $e['fname'], $e['fname'],     $cred_url,      $remove_url),
                            $mess);

        if (mail($e['email'], $subj, $mess, $head))
        {
          $good++;
          echo("{$lifecycle_counter}/{$this->lifecycle}   " . ($i + 1) . "/{$mailcount}   total:{$this->totalmailed}   usecs:{$u_seconds}   {$abbr}:{$typename}   {$e['email']}\n");
        }
        else
        {
          $bad++;
          echo("--> {$bad} BAD {$e['email']}\n");
        }

        $i++;

        usleep($u_seconds);
      }

      mail('tap4@planetxmail.com', $subj, $mess, $head);
      //mail('elitescripts2000@gmail.com', $subj, $mess, $head);
      //mail('elitescripts2000@yahoo.com', $subj, $mess, $head);

      $db->SelectDB('mle');

      // logdate, logins, signup, mails, adminmail
      $today = date('F j, Y');
      $db->Query("INSERT INTO hitcounter (logdate, mails) VALUES('$today', '{$good}') ON DUPLICATE KEY UPDATE mails = mails + {$good}");

      echo "Done mailing {$mail_from} {$typename}\n\n";

      $this->totalmailed += $good;

      if (is_file('/root/kill_sendqueue'))
        exit("stopping current operation per kill_sendqueue request ... exiting\n");
    }
    else
      echo("{$abbr} nothing to mail...\n");
  }

  public function Loop()
  {
    $lifecycle_counter = 0;

    $db = $this->db;

    while (true)
    {
      $mle_no_mail = 0;

      $queue_size = check_queue_size($this->postfix_queue);

      if ($queue_size > $this->queue_max)
        exit("Postfix queue is too full:{$queue_size} ... exiting\n");

      if (! $db->Ping())
        exit("MySQL db connection dropped ... exiting\n");

      $db->Query("SELECT DATE_SUB(CURDATE(), INTERVAL 1 DAY)");
      list($date_prev) = $db->FetchRow();

      if ($db->Query("SELECT id, userID, listownerID, listname, headers, subject, message, credits FROM queue WHERE datesubmitted LIKE '{$date_prev}%' ORDER BY datesubmitted ASC LIMIT 1"))
      {
        list($id, $userID, $listownerID, $listname, $headers, $subject, $message, $credits) = $db->FetchRow();

        $db->Query("DELETE FROM queue WHERE id='{$id}' LIMIT 1");

        // userID not in mle.users, delete and move on
        if (! $db->Query("SELECT listemail, status FROM users WHERE userID='$userID' LIMIT 1"))
        {
          echo("Submitters userID not found: $userID\n");
          continue;
        }

        list($submitters_listemail, $status) = $db->FetchRow();

        //$subject = stripslashes(trim($subject));
        //$message = str_replace("\r\n", "\n", stripslashes(trim($message)));

        list($header, $message_type) = explode(',', $headers);

        $headers = $header . "\n";

        if ($message_type == 'HTML')
          $headers .= "MIME-Version: 1.0\nContent-type: text/html; charset=iso-8859-1\n";

        $headers .= "X-PXM-UID: LUSERID HASH Report: http://planetxmail.com/openticket.php\n";

        $urlID = 0;
        list($credits, $urlID) = explode('|', $credits);

        if (! is_numeric($urlID))
          $urlID = 0;

        $is_creditmailer = (is_numeric($credits) AND $credits) ? " LIMIT $credits" : '';

        $emailcount = $db->Query("SELECT listemail, userID, username, fname, lname
                                  FROM users
                                  LEFT JOIN bounced ON users.listemail = bounced.bademail
                                  WHERE users.listemail != ''
                                  AND users.lastvacation='0000-00-00 00:00:00'
                                  AND users.verified='yes'
                                  AND users.vacation='0'
                                  AND users.listname='{$listname}'
                                  AND users.listownerID='{$listownerID}'
                                  AND users.listemail NOT LIKE '%unconfirmed'
                                  AND ((bounced.count < 6 AND bounced.mailboxfull < 1) OR bounced.bademail IS NULL)
                                  ORDER BY MD5(RAND()){$is_creditmailer}");

        $emails = array();
        while ($row = $db->FetchArray())
          $emails[] = $row;

        $good = $bad = 0;

        $mod = calc_mail_mod($emailcount);

        $u_seconds = $this->GetMicroSeconds();

        echo("Begin Mailing to: {$listname}\n\n");

        $skipped = 0;

        foreach ($emails as $i => $e)
        {
          // send limited amount, based on size, larger the list, the more that is skipped
          if ($i % $mod AND $e['listemail'] != $submitters_listemail)
          {
            $skipped++;
            continue;
          }

          $usr = '?u=' . strrev($e['userID']) . '&v=' . strrev(substr(md5($e['userID']), 0, 5));
          $cl = create_credit_link($e['userID'], $urlID, 0);

          $unsublink = 'http://planetxmail.com/mle/rl.php' . $usr;

          if ($message_type == 'HTML')
          {
            $credlink  = '<a href="http://planetxmail.com/earn.php?' . $cl . '">** Click Here</a> to Earn Mailer Credits.<br /><br />'."\n";
            $unsublink = '<a href="' . $unsublink . '">Click Here</a> to unsubscribe from ' . $listname . '<br />'."\n";
            $newline   = '<br /><br />'."\n";
          }
          else
          {
            $credlink  = "** Earn Mailer Credits by clicking this link:\nhttp://planetxmail.com/earn.php?{$cl}\n\n";
            $unsublink = "Click the link below to unsubscribe.\n{$unsublink}\n";
            $newline   = "\n\n";
          }

          $credlink = ($cl) ? $newline.$credlink : $newline;

          // prevent triple or more blank lines
          $message = preg_replace('/(?:(?:\r\n|\r|\n)\s*){2}/s', "\n\n", $message);

          $subj = str_ireplace($this->fnames, $e['fname'], $subject);
          $mess = str_ireplace($this->fnames, $e['fname'], str_ireplace(array('[credit_mailer_link]', '[unsubscribe_link]'), array($credlink, $unsublink), $message));
          $head = str_ireplace(array('USERID','HASH'), array($e['userID'], substr(sha1('jd93JdmAz3hF1' . $e['userID']), 0, 5)), $headers);

          if (mail($e['listemail'], $subj, $mess, $head))
          {
            $good++;
            echo("{$this->lifecycle_counter}/{$this->lifecycle}   " . ($i + 1) . "/{$emailcount}   total:{$this->totalmailed}   usecs:$u_seconds   list:$listname   mod:$mod   skipped:{$skipped}   email:{$e['listemail']}\n");
          }
          else
          {
            $bad++;
            echo("--> $bad BAD {$e['listemail']}\n");
          }

          $skipped = 0;

          if ($u_seconds) usleep($u_seconds);
        }

        mail('tap4@planetxmail.com', $subj, $mess, $head);

        // logdate, logins, signup, mails, adminmail
        $today = date('F j, Y');
        $db->Query("INSERT INTO hitcounter (logdate, mails) VALUES('$today', '{$good}') ON DUPLICATE KEY UPDATE mails = mails + {$good}");

        echo "Done mailing mle list={$listname}\n\n";

        $this->totalmailed += $good;

        if (is_file('/root/kill_sendqueue'))
          exit("stopping current operation per kill_sendqueue request ... exiting\n");
      }
      else
      {
        $mle_no_mail = 1;
        echo "MLE Mail Queue:0, Postfix Queue:$queue_size ...\n";
      }

      $this->SendSoloAD('fap');

      $this->SendSoloAD('tap');

      if ($mle_no_mail)
      {
        echo "Nothing to mail in mle, fap, tap ... exiting\n";
        break;
      }

      $lifecycle_counter++;

      if ($lifecycle_counter > $this->lifecycle)
      {
        echo("lifecycle:{$this->lifecycle} reached totalmailed:{$this->totalmailed} ... exiting\n");
        break;
      }

      $db->SelectDB('mle');
    }
  }
};

$db = new MySQL_Access('mle');

$sendQueue = new SendQueue($db, $argv, '/var/spool/postfix/active');
$sendQueue->Loop();

?>
