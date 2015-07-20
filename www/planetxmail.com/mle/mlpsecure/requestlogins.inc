<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($_COOKIE['reqlog'])
  $notValid = 'ERROR: Please, wait a few minutes to submit another request.';
else if ($email)
{
  $email = strtolower(trim($email));

  if ($notValid = EmailFormat($email)) {}
  else
  {
    $db = new MySQL_Access('mle');

    if ($db->Query("SELECT DISTINCT listname, listownerID, username FROM users WHERE email='$email' OR listemail='$email'"))
    {
      $data = $db->result;

      while (list($listname, $listownerID, $username) = mysqli_fetch_row($data))
      {
        $db->Query("SELECT listhash FROM listurls WHERE listname='$listname' AND listownerID='$listownerID' LIMIT 1");
        list($listhash) = $db->FetchRow();

        $urls .= "Listname: $listname\nUsername: $username\nhttp://planetxmail.com/mle/login.php?l=$listhash\n\n";
      }

      $message = "You requested all Logins for which the email: $email is applied to. Either as a Contact Address or a List Address.  If you are receiving this without your approval please discard and report abuse to: http://planetxmail.com/openticket.php\n\n----------------------------\n\n";
      $message .= $urls;

      @mail($email, 'Login URLs Request Results', $message, 'From: Planet X Mail <do_not_reply@planetxmail.com>');

      setcookie('reqlog', '1', time()+3600, '/mle', '.planetxmail.com', 0, 1); // expires in 1 hour

      $notValid = "Matches where found and the report was emailed to $email";
    }
    else
      $notValid = 'ERROR: Email not listed in any of our SafeLists.';
  }
}

?>