<?php

class MySQL_Access
{
  public  $link, $result, $rows;
  private $user, $pass, $host, $dbname;

  function __construct($dbname = 'mle')
  {
    $this->user   = 'root';
    $this->pass   = '';
    $this->host   = 'localhost';
    $this->dbname = $dbname;

    $this->link = @mysqli_connect($this->host, $this->user, $this->pass, $this->dbname) or $this->ErrorMsg(mysqli_connect_error());

    if (mysqli_character_set_name($this->link) != 'utf8')
      if (! mysqli_set_charset($this->link, 'utf8'))
        $this->ErrorMsg(mysqli_error($this->link));
  }

  public function Query($query)
  {
    $this->result = @mysqli_query($this->link, $query) or $this->ErrorMsg(mysqli_error($this->link));
    $this->rows   = @mysqli_num_rows($this->result);

    $query = strtolower(trim($query));

    if (substr($query, 0, 6) == 'select')
      return $this->rows;
  }

  public function FetchArray()
  {
    return $this->FetchAssoc();
  }

  public function FetchAssoc()
  {
    return @mysqli_fetch_assoc($this->result);
  }

  public function FetchRow()
  {
    return @mysqli_fetch_row($this->result);
  }

  public function Seek($row)
  {
    if (@is_numeric($row))
      @mysqli_data_seek($this->result, $row);
  }

  public function SelectDB($dbname)
  {
    if ($dbname === $this->dbname) return;

    @mysqli_select_db($this->link, $dbname) or $this->ErrorMsg(mysqli_error($this->link));

    $this->dbname = $dbname;
  }

  public function GetLastID()
  {
    return mysqli_insert_id($this->link);
  }

  public function EscapeString($str)
  {
    if ($str === '' OR ! is_string($str))
      return $str;

    // does not work well ... need to do more research
    // perhaps only nessassary in a multilingual database
    // with english only ... addslashes() does just fine.
    // Characters encoded are NUL (ASCII 0), \n, \r, \, ', ", and Control-Z.
    // return mysqli_real_escape_string($this->link, $str);

    // single quote ('), double quote ("), backslash (\) and NUL (the NULL byte).
    return addslashes($str);
  }

  public function EscStr($str)
  {
    return $this->EscapeString($str);
  }

  public function Ping()
  {
    return @mysqli_ping($this->link);
  }

  public function GetDBName()
  {
    return $this->dbname;
  }

  public function Close()
  {
    @mysqli_close($this->link);
  }

  public function OptimizeTables($verbose = 0)
  {
    $this->DoTables('OPTIMIZE', $verbose);
  }

  public function RepairTables($verbose = 0)
  {
    $this->DoTables('REPAIR', $verbose);
  }

  private function ErrorMsg($error)
  {
    ob_start();
    debug_print_backtrace();
    $trace = ob_get_contents();
    ob_end_clean();

    @mail('elitescripts2000@yahoo.com', 'config.inc', $trace);
    $this->Close();
    die('Error detected. Our technicians are on it!');
  }

  private function DoTables($operation, $verbose)
  {
    $operation = strtoupper($operation);

    if (! in_array($operation, array('OPTIMIZE','REPAIR')))
      exit("ERROR: invalid operation:{$operation} in MySQL_Access()->DoTables()");

    $result = mysqli_query($this->link, 'SHOW TABLES');
    if (mysqli_num_rows($result))
    {
      while(list($table) = mysqli_fetch_row($result))
      {
        if ($verbose) echo "$operation table: {$table} ... ";
        mysqli_query($this->link, "$operation TABLE {$table}");
        if ($verbose) echo "done\n";
      }
    }
    else if ($verbose) echo "No tables found to $operation.\n";
  }

  function __destruct()
  {
    $this->Close();
  }
};

function check_queue_size($postfix_queue)
{
  if (! $p = popen('/usr/bin/find ' . $postfix_queue . ' -type f -print | /usr/bin/wc -l', 'r'))
    exit("FATAL ERROR: check_queue_size({$postfix_queue}) popen() failed ... exiting\n");
  else
    $num = trim(fread($p, 32));

  @pclose($p);

  if (! @is_numeric($num = trim($num)))
    exit("FATAL ERROR: check_queue_size({$postfix_queue}) non numeric value ... exiting\n");

  return $num;
}

function start_program($program)
{
  if (! $p = popen('/bin/ps aux | /bin/grep "' . $program . '" | /bin/grep -v grep | /usr/bin/wc -l', 'r'))
    exit("FATAL ERROR: start_program({$program}) popen() failed ... exiting\n");
  else
    $num = fread($p, 32);
  @pclose($p);

  $num = trim($num);

  if (! @is_numeric($num))
    exit("FATAL ERROR: start_program({$program}) non numeric value ... exiting\n");

  return ($num > 1) ? $num : 0;
}

function calc_mail_mod($emailcount)
{
       if ($emailcount > 2400)  $mod = 16;
  else if ($emailcount > 2200)  $mod = 15;
  else if ($emailcount > 2000)  $mod = 14;
  else if ($emailcount > 1800)  $mod = 13;
  else if ($emailcount > 1600)  $mod = 12;
  else if ($emailcount > 1400)  $mod = 11;
  else if ($emailcount > 1200)  $mod = 10;// 120
  else if ($emailcount > 1000)  $mod = 9; // 111
  else if ($emailcount > 800)   $mod = 8; // 100
  else if ($emailcount > 600)   $mod = 7; // 85
  else if ($emailcount > 400)   $mod = 6; // 66
  else if ($emailcount > 200)   $mod = 5; // 40
  else if ($emailcount > 100)   $mod = 4; // 25
  else if ($emailcount > 50)    $mod = 3; // 16
  else if ($emailcount > 25)    $mod = 2; // 12
  else                          $mod = 1; //

  return $mod;
}

function calc_total_mail($verbose = 1)
{
  global $db;

  $totalcount   = 0;
  $count_queues = 1;

  $db->Query("SELECT DATE_SUB(CURDATE(), INTERVAL 1 DAY)");
  list($whichday) = $db->FetchRow();

  if ($verbose) echo "===>>> Calculating mailcount for {$whichday}\n";

  $num_queues = $db->Query("SELECT id, userID, listownerID, listname, headers, subject, message, credits FROM queue WHERE datesubmitted LIKE '$whichday%' ORDER BY listname");

  $result = $db->result;
  while(list($id, $userID, $listownerID, $listname, $headers, $subject, $message, $credits) = mysqli_fetch_row($result))
  {
    $credits = $urlID = 0;

    list($credits, $urlID) = explode('|', $credits);

    $is_creditmailer = ($credits AND is_numeric($credits)) ? " LIMIT $credits" : '';

    $emailcount = $db->Query("SELECT listemail, userID, username, fname, lname FROM users
                              LEFT JOIN bounced ON users.listemail = bounced.bademail
                              WHERE users.listemail != ''
                              AND users.lastvacation='0000-00-00 00:00:00'
                              AND users.verified='yes'
                              AND users.vacation='0'
                              AND users.listname='{$listname}'
                              AND users.listownerID='{$listownerID}'
                              AND RIGHT(users.listemail, 11) != 'unconfirmed'
                              AND ((bounced.count < 1 AND bounced.mailboxfull < 1) OR bounced.bademail IS NULL)
                              ORDER BY MD5(RAND()){$is_creditmailer}");

    $mod = 'n/a';

    if ($is_creditmailer === '' AND $emailcount)
    {
      $mod = calc_mail_mod($emailcount);

      for ($i=0; $i < $emailcount; $i++)
        if ($i % $mod == 0)
          $totalcount++;
    }
    else
      $totalcount += $emailcount;

    $is_cred = ($is_creditmailer) ? 'yes' : 'no';

    if ($verbose) echo "===>>> {$count_queues}/{$num_queues} listname:{$listname} mod:{$mod} emailcount:{$emailcount} is_cred:{$is_cred} totalcount:{$totalcount}\n";

    $count_queues++;
  }

  $db->Query("SELECT COUNT(*) FROM bounced WHERE 1");
  list($bouncedcount) = $db->FetchRow();

  $db->Query("UPDATE mailcount SET totalcount=$totalcount, bouncedcount=$bouncedcount WHERE id='1'");

  if ($verbose) echo "===>>> {$whichday} bouncedcount=$bouncedcount\n";
  if ($verbose) echo "===>>> {$whichday} totalcount=$totalcount\n";
  if ($verbose) echo "===>>> {$whichday} DONE\n\n";
}

/*
function error_handler_custom($errno, $errstr, $errfile, $errline, $errcontext)
{
  if (! ($errno & error_reporting()) ) return;

  echo '<pre>' . print_r($errcontext, 1) . '</pre>';

  switch ($errno) {
    case E_USER_ERROR:
    case E_ERROR:
    case E_COMPILE_ERROR:
      echo "<b>My ERROR</b> [$errno] $errstr<br />\n";
      echo "  Fatal error on line $errline in file $errfile";
      echo ", PHP " . PHP_VERSION . " (" . PHP_OS . ")<br />\n";
      echo "Aborting...<br />\n";
      //emailErrorFunction($errno,$erstr,$errfile,$errline);
      exit(1);
      break;

  default:
      echo "Unknown error type: [$errno] $errstr<br />\n";
      break;
  }

  // Don't execute PHP internal error handler
  return true;
}
*/

if (! function_exists('array_qsort2'))
{
  function array_qsort2(&$array, $column=0, $order=SORT_ASC, $first=0, $last=-2)
  {
    if ($last == -2)
      $last = count($array) - 1;

    if ($last > $first)
    {
      $alpha = $first;
      $omega = $last;
      $guess = strtolower($array[$alpha][$column]);

      while ($omega >= $alpha)
      {
        if ($order == SORT_ASC)
        {
          while(strtolower($array[$alpha][$column]) < $guess) $alpha++;
          while(strtolower($array[$omega][$column]) > $guess) $omega--;
        }
        else
        {
          while(strtolower($array[$alpha][$column]) > $guess) $alpha++;
          while(strtolower($array[$omega][$column]) < $guess) $omega--;
        }

        if ($alpha > $omega) break;

        $temporary = $array[$alpha];
        $array[$alpha++] = $array[$omega];
        $array[$omega--] = $temporary;
      }

      array_qsort2($array, $column, $order, $first, $omega);
      array_qsort2($array, $column, $order, $alpha, $last);
    }
  }
}

$ads_ads_ads = '
<center>
  <hr /><br />
  <a href="http://planetxmail.com/soloads.php?list=[location]" target="_blank">Send a SOLO AD to 135,000+ members!</a>
  <br /><br  >

  <a href="http://targetedadplanet.com" target="_blank">
    <img src="http://targetedadplanet.com/images/tap_mini.jpg" border="0" />
    <br />
    <i>100% Free ADs - 50% Commission Payouts</i>
  </a>
</center>
';

?>
