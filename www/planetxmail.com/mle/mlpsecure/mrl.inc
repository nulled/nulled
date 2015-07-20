<?php
// master remove link
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

if (! $u OR ! $p)
{
	header("Location: notfound.php");
  exit;
}

if ($submitted == 'removeall')
{
  $db = new MySQL_Access('mle');

  $usr = strrev($u);
  $passcheck = substr($p, 0, 5);

  // check if link is legal
  $db->Query("SELECT email, listemail FROM users WHERE userID='$usr' AND LEFT(password, 5)='$passcheck'");
  if (! $db->rows)
  	$notValid = "ERROR:  Link not valid.  Make sure the FULL URL is pasted correctly.";
  else
  {
  	list($email, $listemail) = $db->FetchRow();

  	$email 		 = trim($email);
  	$listemail = trim($listemail);

  	if ($listemail) $condition = "email='$email' OR listemail='$listemail'";
  	else
  		$condition = "email='$email'";

	  $db->Query("SELECT userID, email, fname, lname, listname, listownerID FROM users WHERE $condition");
	  $users = $db->result;

	  while (list($userID, $email, $fname, $lname, $list, $id) = mysqli_fetch_row($users))
	  {
	    $userfullname = "$fname $lname";

	    $db->Query("SELECT fromname, fromemail, bounceemail, adminemail, unsubsuccess FROM listmanager WHERE listname='$list' AND listownerID='$id'");
	    list($fromname, $fromemail, $bounceemail, $adminemail, $message) = $db->FetchRow();

	    $message = str_replace("[admin_email_address]", $adminemail, $message);
	    $message = str_replace("[list_name]", $list, $message);
	    $message = str_replace("[user_name]", $userfullname, $message);

	    $subject = "$list - REMOVAL from list successful.";
	    $headers = "From: $fromname <$bounceemail>";

	    if(@mail($email, $subject, $message, $headers))
	    {
	      $db->Query("DELETE FROM urldata WHERE userID='$userID'");
	      $db->Query("DELETE FROM urlmanager WHERE userID='$userID'");
	      $db->Query("DELETE FROM users WHERE userID='$userID' LIMIT 1");

	      $notValid = "<h3>You have been ENTIRELY removed.</h3>";

	      // logdate, logins, signup, mails, adminmail
	      $today = date('F j, Y');
        $db->Query("INSERT INTO hitcounter (logdate, signup) VALUES('$today', '-1') ON DUPLICATE KEY UPDATE signup = signup - 1");
	    }
	    else
	    {
	      $notValid = "ERROR: Mail server down. Try again later.";
	      break;
	    }
	  }

	  if (! $notValid)
	  {
	  	header("Location: notfound.php");
	  	exit;
	  }

	  //session_set_cookie_params(0, '/mle', '.planetxmail.com');
	  session_start();
    session_destroy();
	}
}

?>
