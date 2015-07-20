<?php
if (!isset($mail_functions_set))
{
  $mail_functions_set = 1;

  function send_signup_mail($list, $id, $resending, $pass1, $email, $username, $uID, $fname, $lname, $email1, $status="", $where="not set", $refer="")
  {
    global $db, $email_wordwrap_length, $defaultstatus;

    $db->Query("SELECT fromname, adminemail, paylinkparams FROM listmanager WHERE listname='$list' AND listownerID='$id'");
    list($fromname, $adminemail, $paylinkparams) = $db->FetchRow();

    // extract check billing
    $parts = explode('|', $paylinkparams);
    $checkbilling = $parts[10];

    $db->Query("SELECT listhash FROM listurls WHERE listname='$list' AND listownerID='$id' LIMIT 1");
    list($listhash) = $db->FetchRow();

    $emailenc  = urlencode($email);
    $validator = substr(sha1($uID.$email), 0, 5);

    $subscribelink = "http://planetxmail.com/mle/au.php?u={$uID}&e={$emailenc}&v={$validator}";

    $subject = (! $resending) ? "$list - New user Confirmation Notice" : "$list - Resending New user Confirmation Notice";

    $db->Query("SELECT subconfirm FROM listmanager WHERE listname='$list' AND listownerID='$id' LIMIT 1");
    list($message) = $db->FetchRow();

    $message = wordwrap($message, $email_wordwrap_length);

    $validator = strrev(substr(md5($uID), 0, 5));
    $usr       = strrev($uID);

    $unsublink = "http://planetxmail.com/mle/rl.php?u={$usr}&v={$validator}";

    if (! $status) $status = $defaultstatus;

    if ($status == 'pro')	     $readablestatus = 'a Professional';
    else if ($status == 'exe') $readablestatus = 'an Executive';

    $validator_paylinks = strrev(substr(sha1(md5($uID)), 0, 5));

    // if check billing and member is pro or exec then replace subscribe link with a paylink
    if ($checkbilling AND $status != 'mem')
    	$subscribelink = "Use the Link below to pay the subscribe fee since this is a $readablestatus account. This will also verify your email address:\nhttp://planetxmail.com/mle/signuppaylinks.php?u=$usr&v=$validator_paylinks";

    $message = str_replace(array('[subscribe_link]','[unsubscribe_link]','[list_name]','[program_name]','[admin_email_address]','[user_name]','[first_name]','[last_name]','[password]'),
                           array($subscribelink,      $unsublink,         $list,        $program_name,    $adminemail,           $username,    $fname,        $lname,       $pass1),
                           $message);

    $message = stripslashes($message);

    //mail('elitescripts2000@yahoo.com', $subject.$email, $message);

    @mail($email, $subject, $message, "From: $fromname <do_not_reply@planetxmail.com>");

    if (! $resending)
    {
      // get when list was last cleaned and apply to new user
      $db->Query("SELECT lastcleaned FROM system WHERE listname='$list' AND listownerID='$id' LIMIT 1");
      list($lastcleaned) = $db->FetchRow();
      $lastcleaned = timestamp_to_mysql_timestamp(mysql_datetime_to_timestamp($lastcleaned));

      $db->Query("SELECT freestartcredits, prostartcredits, exestartcredits, freeearnedcredits, proearnedcredits, exeearnedcredits FROM listconfig WHERE listname='$list' AND listownerID='$id' LIMIT 1");
      list($freestartcredits, $prostartcredits, $exestartcredits, $freeearnedcredits, $proearnedcredits, $exeearnedcredits) = $db->FetchRow();

      /*
      // award creds to referal if any
      $parts  = explode("|", $refer);
    	$ref_userID = strrev(trim($parts[0]));
    	$ref_listhash = trim($parts[1]);
    	exit("ref_userID=$ref_userID ref_listhash=$ref_listhash refer=$refer");
    	if ($db->Query("SELECT status FROM users WHERE userID='$ref_userID'"))
    	{
    	  list($ref_status) = $db->FetchRow();
    	  if ($ref_status == 'mem')      $earned_credits = $freeearnedcredits;
        else if ($ref_status == 'pro') $earned_credits = $proearnedcredits;
        else if ($ref_status == 'exe') $earned_credits = $exeearnedcredits;

        if (is_numeric($earned_credits) && $earned_credits > 0)
          $db->Query("UPDATE users SET credits=credits+$earned_credits WHERE userID='$ref_userID'");
    	}
      */

      // get starting credits
      if ($status == 'mem')      $startcredits = $freestartcredits;
      else if ($status == 'pro') $startcredits = $prostartcredits;
      else if ($status == 'exe') $startcredits = $exestartcredits;

      if (! is_numeric($startcredits) OR $startcredits < 1) $startcredits = 0;

      $db->Query("INSERT INTO users
             (userID, fname,  lname,    email,    status,   username,  password,    datesignedup,listname,lastloggedin,lastmailweek,listownerID,referer,datelastbilled,credits)
      VALUES ('$uID','$fname','$lname','$email1','$status','$username',MD5('$pass1'),NOW(),     '$list',  NOW(),      $lastcleaned,'$id',      '$refer',NOW(),'$startcredits')");
    }

    header ("Location: emailsentmessage.php?email={$email}&list={$list}&id={$id}");
    exit;
  }

  function send_listemail_confirm_mail($email, $uID, $list, $id)
  {
    $classloaded_MySQL_Access = 1;
    include ("mlpsecure/config/config.inc");

    $db = new MySQL_Access();

    $db->Query("SELECT fromname, adminemail FROM listmanager WHERE listname='$list' AND listownerID='$id'");
    list($fromname, $adminemail) = $db->FetchRow();

		$validator = strrev(substr(md5($uID.$email.'unconfirmed'), 0, 5));
		$usr = strrev($uID);

    $confirmlink = "http://planetxmail.com/mle/cla.php?u=$usr&v=$validator";

    $db->Query("SELECT username, fname, lname FROM users WHERE userID='$uID'");
    list($usernamelink, $fname, $lname) = $db->FetchRow();

    $db->Query("SELECT subconfirm FROM listmanager WHERE listname='$list' AND listownerID='$id'");
    list($message) = $db->FetchRow();

    $subject = "$list - List address ACTIVATION confirmation.";
    $message = file_get_contents("messages/confirmlistaddress.txt");
    $message = wordwrap($message, $email_wordwrap_length);

    $message = str_replace("[subscribe_link]", "$confirmlink\n", $message);
    $message = str_replace("[list_name]", $list, $message);
    $message = str_replace("[program_name]", $program_name, $message);
    $message = str_replace("[admin_email_address]", $adminemail, $message);
    $message = str_replace("[user_name]", $usernamelink, $message);
    $message = str_replace("[first_name]", $fname, $message);
    $message = str_replace("[last_name]", $lname, $message);
    $message = str_replace("[password]", "", $message);

    $message = stripslashes($message);

    $unconfirmedemail = $email."unconfirmed";

    if(@mail($email, $subject, $message, "From: $fromname <do_not_reply@planetxmail.com>"))
    {
      $db->Query("UPDATE users SET listemail='$unconfirmedemail' WHERE userID='$uID'");

      header("Location: main.php?option=listemailmessagesent&email=$email");
      exit;
    }
    else
      return "ERROR: Mail server down. Try again later";
  }

  function send_activated_listemail_mail($id, $list, $listemail, $uID)
  {
    $classloaded_MySQL_Access = 1;
    include("mlpsecure/config/config.inc");
    include("mlpsecure/validationfunctions.php");

    $db = new MySQL_Access();

    $db->Query("SELECT username, fname, lname FROM users WHERE userID='$uID'");
    list($usernamelink, $fname, $lname) = $db->FetchRow();

    $db->Query("SELECT fromname, fromemail, adminemail FROM listmanager WHERE listname='$list' AND listownerID='$id'");
    list($fromname, $fromemail, $adminemail) = $db->FetchRow();

    $db->Query("SELECT subsuccess FROM listmanager WHERE listname='$list' AND listownerID='$id'");
    list($message) = $db->FetchRow();

    $db->Query("SELECT listhash FROM listurls WHERE listownerID='$id' AND listname='$list'");
    list($listhash) = $db->FetchRow();

    $subject = "$list - List Address ACTIVATION successful.";
    $message = wordwrap($message, $email_wordwrap_length);

    $validator = strrev(substr(md5($uID), 0, 5));
		$usr = strrev($uID);

    $unsublink = "http://planetxmail.com/mle/rl.php?u=$usr&v=$validator";
    $loginlink = "http://planetxmail.com/mle/login.php?l=$listhash";

    $message = str_replace("[unsubscribe_link]", "$unsublink\n", $message);
    $message = str_replace("[list_name]", $list, $message);
    $message = str_replace("[program_name]", $program_name, $message);
    $message = str_replace("[admin_email_address]", $adminemail, $message);
    $message = str_replace("[login_link]", $loginlink, $message);
    $message = str_replace("[user_name]", $usernamelink, $message);
    $message = str_replace("[first_name]", $fname, $message);
    $message = str_replace("[last_name]", $lname, $message);

    $db->Query("UPDATE users SET listemail='$listemail' WHERE userID='$uID'");
    @mail($listemail, $subject, $message, "From: $fromname <do_not_reply@planetxmail.com>");

    return true;
  }
}
?>
