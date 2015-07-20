<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

// contact and list address banned
$_BANNED_DOMAINS = array(
'comcast.com',
'comcast.net',
'cs.com',
'netscape.com',
'moomia.com',
'mac.com',
'etb.net.co',
'msn.com',
'muskurahat.com',
'infoseek.jp',
'inbox.com',
'netcabo.pt',
'netzero.com',
'mts.net',
'sympatico.ca',
'crawler.com'
);

$_GREYLISTED_DOMAINS = array(
'aim.com',
'aol.com'
);

$_LISTEMAIL_BANNED_DOMAINS = array(
'aim.com',
'aol.com',
'hotmail.com',
'hotmail.ca',
'hotmail.co.uk',
'hotmail.es',
'hotmail.it',
'live.ie',
'live.com',
'live.ca',
'live.com.au',
'live.co.uk',
'live.fr',
'live.dk',
'msn.com',
'outlook.fr',
'outlook.com',
'outlook.org',
'windowslive.com'
);

function EmailFormat($email, $check = 1)
{
  global $_BANNED_DOMAINS, $_GREYLISTED_DOMAINS, $greylist_bypass; // greylist_bypass signup.php/changesignupemail.php as a pass from greylist_domains[]

  $email = strtolower($email);

  list($name, $domain) = explode('@', $email);

  $h = substr(sha1('jsdfDIFJfjd86DFwj' . $_SESSION['aauserID'].$_SESSION['aalistname'].$_SESSION['aalistownerID']), 0, 5); // used at changelistemail
  $sh = substr(sha1('dfjJfd76f'), 0, 5); //signuphash (sh)  used at signup.php?l=xxxxx

  $l = trim($_POST['l']);
  $submitted = $_POST['submitted'];

  if ($check)
  {
    if (in_array($domain, $_GREYLISTED_DOMAINS))
    {
      if (! ($greylist_bypass AND $greylist_bypass == $h) AND $submitted != 'signup')
        return "INFO: <b>@{$domain}</b> Addresses are Grey Listed. <a href=\"/mle/main.php?option=greylist\">Click Here</a> to prepare them for use.";

      if (! ($greylist_bypass AND $greylist_bypass == $sh) AND $submitted == 'signup')
        return "INFO: <b>@{$domain}</b> Addresses are Grey Listed. <a href=\"/greylist.php?l=$l\">Click Here</a> to prepare them for use.";
    }

    if (in_array($domain, $_BANNED_DOMAINS))
      return "ERROR: <b>@{$domain}</b> Addresses are Banned.";
  }

  $regex = '/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4})$/';

  if (! preg_match($regex, $email))
  {
    //mail('elitescripts2000@yahoo.com', 'EmailFormat()', "bademail:{$email}", 'From: PXM <do_not_reply@planetxmail.com>');
    return 'ERROR: Email Address not Formatted Properly.';
  }
  else
    return '';
}

function sanstr($str, $mode = 'basic')
{
  // NoteL preg reserved characters listed below
  // . \ + * ? [ ^ ] $ ( ) { } = ! < > | : -

  if ($mode === 'basic') // removes quotes ; control-chars multi-whitespace and backslashes
  {
    $str = trim($str);
    $str = preg_replace('/[[:cntrl:]]/', '', $str);
    $str = preg_replace('/[`\'"]/', '', $str);
    $str = preg_replace('/[;]/', '', $str);
    $str = stripslashes($str);
    $str = preg_replace('/\s+/', ' ', $str);
    $str = trim($str);
  }

  return $str;
}

// used for tickets pxm.tickets database
function get_ticket_host($site)
{
  if (is_string($site) AND strstr($site, ' '))
    $site = explode(' ', $site);
  else if (is_string($site) AND ! strstr($site, ' '))
    $site = array($site);
  else if (! @is_array($site))
    exit('FATAL ERROR: get_ticket_host() not string with space or array input.');

  foreach ($site as $search)
  {
    if ($search == 'freeadplanet')
      return 'Free AD Planet - Support';
    else if ($search == 'planetxmail')
      return 'Planet X Mail - Support';
    else if ($search == 'targetedadplanet')
      return 'Targeted AD Planet - Support';
  }

  return 'Support';
}

function get_param($p)
{
  if (isset($_POST[$p]) AND is_array($_POST[$p])) return $_POST[$p];
  if (isset($_GET[$p])  AND is_array($_GET[$p]))  return $_GET[$p];

  if (isset($_POST[$p])) return ex_stripslashes(trim($_POST[$p]));
  if (isset($_GET[$p]))  return ex_stripslashes(trim($_GET[$p]));

  return '';
}

function mail_debug_backtrace_exit($exit_msg = '', $redirect = '', $email = '')
{
  ob_start();
  debug_print_backtrace();
  $trace = ob_get_contents();
  ob_end_clean();

  if ($email === '' AND $email !== null)
    $email = 'elitescripts2000@yahoo.com';

  if (! $exit_msg)
    $exit_msg = 'ERROR: Technicians were notified. <a href="http://planetxmail.com/openticket.php">Open a Ticket</a>';

  if ($mail) {
    @mail($email, 'mail_debug_backtrace_exit()', "{$trace}\n\n" . print_r($GLOBALS, 1), 'From: Debug Backtrace <do_not_reply@planetxmail.com>');
  }

  if ($redirect) {
    header('Location: ' . $redirect . urlencode($exit_msg));
    exit;
  }

  exit($exit_msg);
}

function ex_stripslashes($text)
{
  global $_PARAMETERS_WERE_ESCAPED; // set in register_globals.inc

  return (get_magic_quotes_gpc() OR $_PARAMETERS_WERE_ESCAPED) ? stripslashes($text) : $text;
}

function ex_addslashes($text)
{
  global $_PARAMETERS_WERE_ESCAPED;

  return (get_magic_quotes_gpc() OR $_PARAMETERS_WERE_ESCAPED) ? $text : addslashes($text);
}

function LengthUsername($username)
{
  if (strlen($username) > 20)     return 'ERROR: Username longer than 20 Characters.';
  else if (strlen($username) < 4) return 'ERROR: Username shorter than 4 Characters.';

  return '';
}

function LengthRealname($username)
{
  if (strlen($username) > 20)     return 'ERROR: $username longer than 40 Characters.';
  else if (strlen($username) < 2) return 'ERROR: $username shorter than 2 Character.';

  return '';
}

function LengthPassword($pass)
{
  if (strlen($pass) > 50)     return 'ERROR: Password may not be longer than 50 Characters.';
  else if (strlen($pass) < 4) return 'ERROR: Password may not be shorter than 4 Characters.';

  return '';
}

function has_space($text)
{
  return preg_match('/\\s/', $text) ? true : false;
}

function has_weird($text)
{
  return (! preg_match('/^[a-z0-9_]+$/i', $text)) ? true : false;
}

function has_illegal($text)
{
  return preg_match('/[&@#$%^*]/', $text) ? true : false;
}

function has_urlunsafe($text)
{
  return preg_match("/[\\\,<>#(\\s){}|~'`\"^\[\]]/", $text) ? true : false;
}

function has_urlunsafe2($text)
{
  return preg_match("/[\\\,<>#(\\s){}|~'`\"^\[\]]/", $text) ? true : false;
}

function generateID($length = 10)
{
  if ($length > 40) $length = 40;
  return substr(sha1(bin2hex(openssl_random_pseudo_bytes(20))), 0, $length);
}

function timestamp_to_mysql_timestamp($ts)
{
  $d=getdate($ts);
  $yr=$d["year"]; $mo=$d["mon"]; $da=$d["mday"]; $hr=$d["hours"]; $mi=$d["minutes"]; $se=$d["seconds"];
  return sprintf("%04d%02d%02d%02d%02d%02d",$yr,$mo,$da,$hr,$mi,$se);
}

function mysql_datetime_to_humandate($datetime)
{
  $yr=strval(substr($datetime,0,4)); $mo=strval(substr($datetime,5,2)); $da=strval(substr($datetime,8,2));
  return date("M j, Y", mktime (0,0,0,$mo,$da,$yr));
}

function mysql_datetime_to_timestamp($dt)
{
  $yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,5,2));  $da=strval(substr($dt,8,2));
  $hr=strval(substr($dt,11,2)); $mi=strval(substr($dt,14,2)); $se=strval(substr($dt,17,2));
  return (! $hr AND ! $mi AND ! $se) ? mktime(0,0,0,$mo,$da,$yr) : mktime($hr,$mi,$se,$mo,$da,$yr);
}

function timestamp_to_mysql_date($ts)
{
  $d=getdate($ts);
  $yr=$d["year"]; $mo=$d["mon"]; $da=$d["mday"];
  return sprintf("%04d-%02d-%02d",$yr,$mo,$da);
}

function mysql_timestamp_to_humandatetime($dt)
{
  $yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2));
  $hr=strval(substr($dt,8,2)); $mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2));
  return date("F j, Y H:i:s", mktime ($hr,$mi,$se,$mo,$da,$yr));
}

function mysql_timestamp_to_humandate($dt)
{
  $yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2));
  $hr=strval(substr($dt,8,2)); $mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2));
  return date("F j, Y", mktime ($hr,$mi,$se,$mo,$da,$yr));
}

function mysql_timestamp_to_humandatetime_qbounce($dt)
{
  $yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2)); $hr=strval(substr($dt,8,2));
  $mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2));
  return date("j M Y H:i:s -0000", mktime ($hr,$mi,$se,$mo,$da,$yr));
}

function login_failed_redirect($url)
{
  @header("Location: $url");
  exit;
}

function mixup($str)
{
  if (strlen($str) < 20) return 0;
  $str = strrev($str);
  $str1 = substr($str, 0, 5);
  $str2 = substr($str, 5, 10);
  $str3 = substr($str, 15, 4);
  $str4 = substr($str, 19);
  return $str1.strrev($str2).$str3.$str4;
}

function unmixup($str)
{
  if (strlen($str) < 20) return 0;
  $str1 = substr($str, 0, 5);
  $str2 = substr($str, 5, 10);
  $str3 = substr($str, 15, 4);
  $str4 = substr($str, 19);
  return strrev($str1.strrev($str2).$str3.$str4);
}

function makehash($str)
{
  return substr(md5(sha1(strrev($str))), 0, 5);
}

function randomkeys($length)
{
  $pattern = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for ($i=0; $i < $length; $i++)
  {
   if (isset($key))
     $key .= $pattern{rand(0,35)};
   else
     $key = $pattern{rand(0,35)};
  }
  return $key;
}

function create_creditID($crediturl, $userID)
{
  global $db;

  $urlID = '0';

  $crediturl = trim($crediturl);

  if ($crediturl)
  {
    if (! $db->Query("SELECT id FROM userlinks WHERE userID='$userID' AND url='$crediturl' LIMIT 1"))
    {
      $db->Query("INSERT INTO userlinks (userID, url) VALUES('$userID','$crediturl')");
      $urlID = $db->GetLastID();
    }
    else
      list($urlID) = $db->FetchRow();
  }

  return $urlID;
}

function create_credit_link($userID, $urlID, $type=0)
{
  global $db;

  if ($urlID == '' OR ! is_numeric($urlID) OR $urlID < 1)
    return 0;
  if (! $db->Query("SELECT id FROM userlinks WHERE id='$urlID' LIMIT 1"))
    return 0;

  $i = 0;
  while(true)
  {
    $i++;
    if ($i > 1000)
      return 0;

    $seed  = randomkeys(10);
    $link  = $seed.$userID.$urlID.$type;
    $mixup = mixup($link);
    $hash  = makehash($link);

    if (! $db->Query("SELECT link FROM earnedlinks WHERE link='$mixup' LIMIT 1"))
      return "c={$mixup}&h={$hash}";
  }
}

?>
