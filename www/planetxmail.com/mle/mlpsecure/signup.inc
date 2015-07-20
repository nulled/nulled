<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/phpsecure/turingkey.class.inc');

$db        = new MySQL_Access('mle');
$turingkey = new TuringKey(300);

// sh comes from greylist.php and is signup hash (sh) for greylisted_domains[]
if ($sh)
  $greylist_bypass = $sh;

// see if sponsored
if ($_COOKIE[$l])
{
  list($uid, $lh) = explode('|', $_COOKIE[$l]);
  $uid = strrev($uid);

  if (! ctype_alnum($uid) OR strlen($uid) != 10)
    $sponsor = '';
  else if ($db->Query("SELECT fname, lname FROM users WHERE userID='$uid' LIMIT 1"))
  {
    list($sponsor_fname, $sponsor_lname) = $db->FetchRow();
    $sponsor = "$sponsor_fname $sponsor_lname";
  }
  else
    $sponsor = '';
}
else
  $sponsor = '';

$newsletter = ($db->Query("SELECT listtype FROM listmanager WHERE listtype='Newsletter [closedlist]' AND {$_listID}")) ? 1 : 0;

if ($submitted == 'signup')
{
  if ($newsletter)
  {
    $pass1 = $pass2 = 111111;
    list($e) = explode('@', $email1);
    $username = substr(str_replace('-', '', $e), 0, 12) . generateID(4);
    $agree = 'yes';
  }

  if ($fname AND $lname AND $pass1 AND $pass2 AND $email1 AND $email2 AND $username)
  {
    $fname    = trim($fname);
    $lname    = trim($lname);
    $pass1    = trim($pass1);
    $pass2    = trim($pass2);
    $email1   = strtolower(trim($email1));
    $email2   = strtolower(trim($email2));
    $username = trim($username);

    if (has_weird($username))           $notValid = 'ERROR: Username may only contain Letters, Numbers and _ (underscores).';
    else if (! ctype_graph($pass1))     $notValid = 'ERROR: Password may not contain Spaces.';
    else if (strstr($pass1, '"'))       $notValid = 'ERROR: Password may not contain Quotation Marks.';
    else if (strstr($pass1, "'"))       $notValid = 'ERROR: Password may not contain Quotation Marks.';
    else if (! ctype_alpha($fname))     $notValid = 'ERROR: First Name may only contain Letters.';
    else if (! ctype_alpha($lname))     $notValid = 'ERROR: Last Name may only contain Letters.';
    else if (strcmp($email1, $email2))  $notValid = 'ERROR: Emails do not match.';
    else if (strcmp($pass1, $pass2))    $notValid = 'ERROR: Passwords do not match.';
    else if (strcasecmp($agree, 'yes')) $notValid = 'ERROR: Please, Click the Sign Up Agreement Check Box.';
    else if (! $turingkey->validate())  $notValid = "ERROR: Invalid Turing Key. You have {$turingkey->time_limit} secs before the Key Expires.";
    else if ($notValid = LengthPassword($pass1)) {}
    else if ($notValid = LengthUsername($username)) {}
    else if ($notValid = EmailFormat($email1)) {}
    else if ($db->Query("SELECT username FROM users WHERE username='$username' AND verified='yes' AND {$_listID} LIMIT 1"))
      $notValid = 'ERROR: Username is already Registered.';
    else if ($db->Query("SELECT email FROM users WHERE email='$email1' AND verified='yes' AND {$_listID} LIMIT 1"))
      $notValid = 'ERROR: Email Address is already Registered.';
    else
    {
      if ($db->Query("SELECT userID, email FROM users WHERE (email='$email1' OR username='$username') AND verified='no' AND {$_listID} LIMIT 1"))
      {
        list($userID, $email) = $db->FetchRow();

        // email1 submitted EQUALS email in DB we know match was based on email
        // if emails UNMATCH we know the username was matched and to use email from the DB
        $email = (strcmp($email, $email1) == 0) ? $email1 : $email;

        $validator = substr(sha1($userID.$email), 0, 5);
        $encode    = urlencode($email);

        $notValid = 'Your account has <i>not</i> been Verified.<br /><a href="rvm.php?u=' . $userID . '&e=' . $encode . '&v=' . $validator . '"><b>Click here</b></a> to Resend the Activation Email.';
      }
      else
      {
        if ($db->Query("SELECT bademail FROM bounced WHERE bademail='$email1' AND count > 0 LIMIT 1"))
          $notValid = "ERROR: <b>{$email1}</b> is found to be bouncing.";
        else
        {
          $resending = false;
          require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sendvalidationmail.php');
        }
      }
    }
  }
  else
    $notValid = 'ERROR: Missing required fields.';
}

?>
