<?php
include("mlpsecure/config/classes.inc");
include("mlpsecure/mailfunctions.php");

if ($u AND $v)
{
  $db = new MySQL_Access();

  $usr = strrev($u);

  if (! $db->Query("SELECT listemail FROM users WHERE listemail!='' AND userID='$usr'"))
  {
    header("Location: listemailactivateerror.php?u=$u");
    exit;
  }

  list($listemail) = $db->FetchRow();

  // is already confirmed?
  if (substr($listemail, strlen($listemail)-11, strlen($listemail))!="unconfirmed")
  {
     header("Location: listemailactiveated.php?u=$u");
     exit;
  }

  // validate this user for this new email
  $validator = strrev(substr(md5($usr.$listemail), 0, 5));
	if ($validator != $v)
	{
		header("Location: listemailactivateerror.php?u=$u&error=validator_incorrect");
	  exit;
	}

  $listemail = substr($listemail, 0, (strlen($listemail)-11));

  $db->Query("SELECT listname, listownerID FROM users WHERE userID='$usr'");
	list($list, $id) = $db->FetchRow();

  send_activated_listemail_mail($id, $list, $listemail, $usr);

  header("Location: listemailactiveated.php?u=$u");
  exit;

}
else
{
  header("Location: listemailactivateerror.php?u=$u");
  exit;
}

?>