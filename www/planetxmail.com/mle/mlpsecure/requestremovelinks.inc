<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($_COOKIE['getremoveurllogins'])
  $notValid = 'ERROR: You have to wait a few hours to submit another request.';
else if ($email)
{
  $email = strtolower(trim($email));

  if ($notValid = EmailFormat($email)) {}
  else
  {
    $db = new MySQL_Access('mle');

    if ($db->Query("SELECT userID, password, email, listemail, username, listname FROM users WHERE email='$email' OR listemail='$email'"))
    {
      while(list($userID, $password, $contactemail, $listemail, $username, $listname) = $db->FetchRow())
      {
        $emailstr = (strtolower($contactemail) == strtolower($email)) ? 'CONTACT Address Set' : 'LIST Address Set';

        $validator = strrev(substr(md5($userID), 0, 5));
        $u = strrev($userID);

        $urls .= "Listname: $listname\nUsername: $username\n$emailstr\nhttp://planetxmail.com/mle/rl.php?u=$u&v=$validator\n\n";

        $tmpuserID   = $u;
        $tmppassword = $password;
      }

      $mrl = "Below is the MASTER Remove URL.  If used ALL membership accounts with email: $email applied to it as a Contact OR List Address will be COMPLETELY removed from ALL Planet X Mail SafeLists!  This means losing all your URL Tracking Data and ability to log in!\nUse With Caution!\nCan not be used if you already used the LAST removelink provided in the above list.  You will have to request another one of these Removal Emails if you have.\n\nhttp://planetxmail.com/mle/mrl.php?u={$tmpuserID}&p=" . substr($tmppassword, 0, 5) . "\n";

      $message = "You requested all Remove URLs for which the email: $email is applied to. Either as a Contact Address or a List Address.  If you are receiving this without your approval please discard and report abuse to: http://planetxmail.com/openticket.php\n\n----------------------------\n\n";
      $message .= $urls;
      $message .= "-------------------------------\n\n";
      $message .= $mrl;

      @mail($email, 'Remove URL Request Results', $message, 'From: Planet X Mail <do_not_reply@planetxmail.com>');

      setcookie('getremoveurllogins', 'wasused', time()+1800, '/mle', '.planetxmail.com', 0, 1); // expires in 1 hr

      $notValid = 'Matches where found and the report was emailed to '. $email;
    }
    else
      $notValid = 'ERROR: Email not listed in any of our SafeLists.';
  }
}

?>