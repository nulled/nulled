#!/usr/bin/php -q
<?php
set_time_limit(0);

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/config.inc');

class ProcBounce extends MySQL_Access
{
  private $p;
  private $headers;
  private $mail_log;
  private $pinged;

  // on the fly, config vars from: /home/nulled/procbounce.conf.inc.php
  private $D_time_max;
  private $D_ping_mod;
  private $D_u_seconds;
  private $D_save_mail_log;
  private $D_echo_query;
  private $D_OK_250_TXT;
  private $D_CYCLE_TXT;
  private $D_size_log;

  function __construct($argv)
  {
    parent::__construct('mle');

    $this->mail_log = $argv[2];
    $this->headers  = 'From: procbounce <do_not_reply@planetxmail.com>';
    $this->pinged   = 0;

    if (is_file('/root/kill_procbounce'))
      exit("NOTICE: Exiting per kill_procbounce request at start up ... exiting\n");

    if ($argv[1] != 'cron')
      exit("ERROR: Must be run as a cronjob ... exiting\n");

    if (! is_file($this->mail_log))
      exit("ERROR: mail_log:{$this->mail_log} not found ... exiting\n");

    // start_program() is helper function from config.inc
    if ($is_running = start_program('procbounce.php cron'))
      exit("NOTICE: {$is_running}:procbounce.php already operating ... exiting\n");

    $this->GetDynamicVars();

    $this->RestartRsyslog();

    if (! $this->p = popen('/usr/bin/tail -F ' . $this->mail_log, 'r'))
      exit("ERROR: procbounce.php: Unable to popen() ... exiting\n");

    $this->Query("DELETE FROM bounced WHERE datelogged < DATE_SUB(NOW(), INTERVAL 14 DAY)");

    echo("INFO: Started procbounce.php Daemon for a runtime of {$this->D_time_max} seconds ...\n");
  }

  private function LineExtract($line)
  {
    $mail_log = $this->mail_log;

    $email = $error = $status = '';

    $line = preg_replace('/\s+/', ' ', trim($line));

    if (strpos($line, 'status=expired') === false)
    {
      list(, $line) = explode('to=<', $line);
      list($email, $line) = explode('>, ', $line);
    }

    if (strpos($line, 'status=bounced') !== false)
    {
      $status = 'bounced';
      list(, $error) = explode('status=bounced ', $line);
    }
    else if (strpos($line, 'status=expired') !== false) // expired, so look back through mail.log for deferred entries
    {
      $status = 'expired';
      $email  = '';

      //Oct 11 17:19:45 planetxmail postfix/qmgr[30576]: 6C04F40FC3: from=<root@planetxmail.com>, status=expired, returned to sender
      list(, $mailID) = explode(': ', $line);

      if (ctype_alnum($mailID))
      {
        $line = '';

        // cat /tmpfs/mail.log | grep 327264120A | grep status=deferred
        // get just one deferred line for this queue transaction to get mail and error
        if ($p = popen("/bin/cat {$mail_log} | /bin/grep {$mailID} | /bin/grep status=deferred", 'r')) {
          $line = trim(fgets($p, 1024));
          pclose($p);
        }

        if ($line)
        {
          // Oct 11 16:27:25 planetxmail postfix/smtp[7453]: 327264120A: to=<dehrling@direcpc.com>, relay=none, delay=92,
          // delays=0.05/31/61/0, dsn=4.4.1, status=deferred (connect to a34-mta03.direcpc.com[66.82.4.104]:25: Connection timed out)
          list(, $line) = explode('to=<', $line);
          list($email, $line) = explode('>, ', $line);

          list(, $error) = explode('status=deferred ', $line);
        }
        else
          echo("ERROR: mailcode:{$mailcode} but no data to correspond with ...\n");
      }
      else
        echo("ERROR: mailcode:{$mailcode} not alpha numeric ...\n");
    }
    else if (strpos($line, 'status=sent') !== false)
    {
      $status = 'sent';
      $error  = '250 OK';
    }
    else
      exit("FATAL ERROR: in LineExtract(), should never reach this point ... exiting\n");

    if (strpos($error, 'said: ') !== false)
      list(, $error) = explode('said: ', $error);

    if ($error) $error = trim($error);
    if ($email) $email = strtolower(trim($email));

    return (! $email OR ! $error OR ! $status) ? false : array($email, $error, $status);
  }

  private function LineFilter($line)
  {
    return (
            ((strpos($line, 'status=bounced') !== false OR strpos($line, 'status=sent') !== false) AND strpos($line, 'postfix/smtp[') !== false)
              OR
             (strpos($line, 'status=expired') !== false AND strpos($line, 'postfix/qmgr[') !== false)
           ) ? 'sent' : false;
  }

  private function LineProcess($line)
  {
    if (($out = $this->LineFilter($line)) === false)
      return false;

    $direction = $out;

    if (($out = $this->LineExtract($line)) === false)
      return false;

    list($email, $error, $status) = $out;

    return array($email, $error, $status, $direction);
  }

  private function FgetsNonBlocking($fp)
  {
    $p = array($fp);

    if (false === ($changed = stream_select($p, $write = NULL, $except = NULL, 0, $this->D_u_seconds)))
      exit("FATAL ERROR: Socket Error: in FgetsNonBlocking() at stream_select()\n");
    else if ($changed > 0)
      return fgets($fp, 4096);

    return '';
  }

  private function EmailClear($email, $list_email_only = 0)
  {
    // disabled ... we do not delete emails anymore, and reply on mle.bounce.reason to inform users
    // leave this code, just in case it might be used in the future.
    // return;
    // $headers = $this->headers;

    if ($list_email_only)
      $this->Query("UPDATE users SET listemail='' WHERE listemail='$email'");
    else
    {
      $this->Query("UPDATE users SET listemail='' WHERE listemail='$email'");
      $this->Query("UPDATE users SET email='' WHERE email='$email'");
      $this->Query("UPDATE listmanager SET adminemail='' WHERE adminemail='$email'");
      $this->Query("UPDATE listowner SET email='' WHERE email='$email'");
      $this->Query("UPDATE listconfig SET adminemailaddress='' WHERE adminemailaddress='$email'");

      $this->SelectDB('pxm');
      $this->Query("UPDATE orders SET email='' WHERE email='$email'");
      $this->SelectDB('fap');
      $this->Query("UPDATE users SET email='' WHERE email='$email' LIMIT 1");
      $this->SelectDB('tap');
      $this->Query("UPDATE users SET email='' WHERE email='$email' LIMIT 1");

      $this->SelectDB('mle');
    }
  }

  private function RestartRsyslog()
  {
    $mail_log      = $this->mail_log;
    $size_log      = $this->D_size_log;
    $save_mail_log = $this->D_save_mail_log;

    if (! $p = popen('/bin/ps aux | /bin/grep rsyslog | /bin/grep -v grep', 'r'))
      exit("FATAL ERROR: unable to popen(1) in restart_rsyslog() ... exiting\n");
    $sys = fgets($p, 1024);
    pclose($p);

    $sys = preg_replace('/\s+/', ' ', trim($sys));

    list($rsyslog_user, $rsyslog_pid) = explode(' ', $sys);

    $rsyslog_pid  = trim($rsyslog_pid);
    $rsyslog_user = trim($rsyslog_user);

    if (! is_numeric($rsyslog_pid))      exit("FATAL ERROR: rsyslog_pid:{$rsyslog_pid} is not numeric ... exiting\n");
    if (strcmp($rsyslog_user, 'syslog')) exit("FATAL ERROR: rsyslog_user:{$rsyslog_user} is not user 'syslog' ... exiting\n");

    $cat_log = ($save_mail_log) ? "/bin/cat {$mail_log} >> /root/MAIL_LOG_SAVED;" : '';

    $c = array();
    $c[0] = "/bin/rm -vf {$mail_log};";
    $c[1] = "/bin/touch {$mail_log};";
    $c[2] = "/bin/chown -v syslog:adm {$mail_log};";
    $c[3] = "/bin/chmod -v 644 {$mail_log};";
    $c[4] = "/bin/kill -1 {$rsyslog_pid};";

    $logsize = filesize($mail_log);

    if (is_numeric($logsize))
      $logsize = $logsize / 1024000;

    if (is_numeric($logsize) AND $logsize > $size_log)
    {
      $cmd = "{$cat_log}{$c[0]} {$c[1]} {$c[2]} {$c[3]} {$c[4]}";

      if (! $p = popen($cmd, 'r'))
        exit("FATAL ERROR: unable to popen(2) in restart_rsyslog() ... exiting\n");
      $line = trim(fread($p, 4096));
      pclose($p);

      echo "{$line}\n";
    }
  }

  public function GetDynamicVars()
  {
    include('/home/nulled/procbounce.conf.inc.php');

    $this->D_time_max       = $time_max;
    $this->D_ping_mod       = $ping_mod;
    $this->D_u_seconds      = $u_seconds;
    $this->D_save_mail_log  = $save_mail_log;
    $this->D_echo_query     = $echo_query;
    $this->D_OK_250_TXT     = $OK_250_TXT;
    $this->D_CYCLE_TXT      = $CYCLE_TXT;
    $this->D_size_log       = $size_log;
  }

  private function IsMailBoxFull($error)
  {
    $error = strtolower($error);

    return (strpos($error, 'full') !== false OR
            strpos($error, 'quota') !== false OR
            strpos($error, 'contains too much') !== false OR
            strpos($error, 'exceeded storage') !== false
           ) ? true : false;
  }

  private function IsBounce($error)
  {
    $error = strtolower($error);

    return (
            strpos($error, 'administrative prohibition') !== false OR
            strpos($error, "can't connect") !== false OR
            strpos($error, 'content denied') !== false OR
            strpos($error, 'deactivated mailbox') !== false OR
            strpos($error, 'disabled') !== false OR
            strpos($error, 'discontinued') !== false OR
            strpos($error, 'does not exist') !== false OR
            strpos($error, 'expired') !== false OR
            strpos($error, 'illegal alias') !== false OR
            strpos($error, 'inactiv') !== false OR
            strpos($error, 'invalid') !== false OR
            strpos($error, 'local error') !== false OR
            strpos($error, 'lost connection') !== false OR
            strpos($error, 'name server loop') !== false OR
            strpos($error, 'no longer active') !== false OR
            strpos($error, 'no mailbox') !== false OR
            strpos($error, 'no route') !== false OR
            strpos($error, 'no such') !== false OR
            strpos($error, 'not a known user') !== false OR
            strpos($error, 'not a valid mailbox') !== false OR
            strpos($error, 'not found') !== false OR
            strpos($error, 'not known') !== false OR
            strpos($error, 'refused') !== false OR
            strpos($error, 'rejected') !== false OR
            strpos($error, 'relay ') !== false OR
            strpos($error, 'relaying ') !== false OR
            strpos($error, 'service denied') !== false OR
            strpos($error, 'suspended') !== false OR
            strpos($error, 'unavailable') !== false OR
            strpos($error, 'unknown') !== false OR
            strpos($error, 'unrouteable') !== false OR
           (strpos($error, 'have a ') !== false AND strpos($error, ' account') !== false) //OR
           //(strpos($error, 'spam') !== false AND strpos($error, 'block') !== false)
          ) ? true : false;
  }

  private function IsEmailSent($out)
  {
    list($email, $error, $status, $direction) = $out;

    if ($error != '250 OK')
      return false;

    if ($this->Query("SELECT bademail FROM bounced WHERE bademail='$email' LIMIT 1"))
    {
      $this->Query("DELETE FROM bounced WHERE bademail='$email' LIMIT 1");
      echo("$email - status:$status - SENT+DELETE - $error\n");
    }
    else
    {
      $str = ($this->D_OK_250_TXT) ? $this->D_OK_250_TXT : "{$email} - status:{$status} - SENT - $error\n";
      echo($str);
    }

    $this->Query("INSERT INTO emails_sent (email, count, datelastsent) VALUES ('{$email}','1',NOW())
                      ON DUPLICATE KEY UPDATE count = count + 1, datelastsent = NOW()");

    return true;
  }

  private function InsertBounce($msg, $column, $out)
  {
    list($email, $error, $status, $direction) = $out;

    echo("\n({$column}) - {$msg} - direction:{$direction} - status:{$status} - email:{$email} - {$error}\n");

    $error = $this->EscapeString($error);

    //if ($msg == 'COUNTED')
      //$this->EmailClear($email);

    $col_other = ($column == 'count') ? 'mailboxfull' : 'count';

    $sql = "INSERT INTO bounced (bademail,{$column},reason,datelogged) VALUES ('$email','1','{$error}',NOW())
              ON DUPLICATE KEY UPDATE {$column}={$column}+1, {$col_other}=0, reason='{$error}', datelogged=NOW()";

    if ($this->D_echo_query)
      echo("\n{$sql}\n\n");

    $this->Query($sql);
  }

  private function LoopInterrupt($time_start)
  {
    $sec = date('s');

    if ($this->D_CYCLE_TXT)
      echo($this->D_CYCLE_TXT);

    $time_TTL = time() - $time_start;

    if ($this->D_time_max < $time_TTL) {
      echo("INFO: time_max:{$this->D_time_max} reached ... exiting\n");
      return true;
    }

    if ($sec % $this->D_ping_mod == 0 AND ! $this->pinged)
    {
      if (is_file('/root/kill_procbounce')) {
        echo("NOTICE: Stopping Loop per kill_procbounce request ... exiting\n");
        return true;
      }

      if (! $this->Ping()) {
        echo("ERROR: MySQL Database connection dropped ... exiting\n");
        return true;
      }

      $this->GetDynamicVars();

      // safety limit
      if ($this->D_ping_mod < 2)
        $this->D_ping_mod = 2;

      echo("\n{$this->D_ping_mod} - {$time_TTL}/{$this->D_time_max}");

      $this->pinged = 1;
    }
    else if ($sec % $this->D_ping_mod AND $this->pinged)
      $this->pinged = 0;

    return false;
  }

  public function Loop()
  {
    $time_start = time();

    $this->GetDynamicVars();

    while (true)
    {
      if ($this->LoopInterrupt($time_start)) {
        break;
      }

      if (($output = $this->FgetsNonBlocking($this->p)) === false) {
        exit("ERROR: FgetsNonBlocking() returned FALSE in procbounce.php ... exiting\n");
      }

      if ($output === '') {
        continue;
      }

      foreach (explode("\n", $output) as $line)
      {
        $column = $msg = '';

        if (($out = $this->LineProcess($line)) === false)
          continue;

        list(, $error) = $out;

        if ($this->IsEmailSent($out)) {
          continue;
        }
        else if ($this->IsMailBoxFull($error))
        {
          $msg    = 'FULLBOX';
          $column = 'mailboxfull';
        }
        else if ($this->IsBounce($error))
        {
          $msg    = 'COUNTED';
          $column = 'count';
        }
        else
        {
          $msg    = 'CATCHALL';
          $column = 'count';
        }

        $this->InsertBounce($msg, $column, $out);
      }
    }
  }
};

$pBounce = new ProcBounce($argv);
$pBounce->Loop();

?>