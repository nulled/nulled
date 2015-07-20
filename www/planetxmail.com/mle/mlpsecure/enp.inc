<?php
// enter new password
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($u AND $v AND $e AND $l)
{
  $email   = urldecode($e);
  $v_check = substr(sha1($u . 'skdH76Sdh76Ma' . $email), 0, 5);

  $db = new MySQL_Access('mle');

  if ($v_check != $v)
    $notValid = 'ERROR: URL not valid. Make sure you copy and pasted it correctly.';
  else if ($db->Query("SELECT listname, listownerID FROM users WHERE userID='$u' LIMIT 1"))
  {
  	list($list, $id) = $db->FetchRow();

    if ($submitted == 'changepassword')
    {
      if (strcmp($password1, $password2) != 0)  $notValid = 'ERROR: Passwords do not match.';
      else if (has_space($password1))           $notValid = 'ERROR: Passwords may not contain Spaces.';
      else if (strstr($password1, "'"))         $notValid = 'ERROR: Passwords may not contain Quotes.';
      else if (strstr($password1, '"'))         $notValid = 'ERROR: Passwords may not contain Quotes.';
      else if ($notValid = LengthPassword($password1)) {}
			else
			{
        $db->Query("UPDATE users SET password=MD5('$password1') WHERE userID='$u' LIMIT 1");

        header("Location: emailchanged.php?list={$list}&id={$id}");
        exit;
      }
    }
  }
  else
  	$notValid = 'ERROR: User no longer exists.';
}
else
  $notValid = 'ERROR: Make sure you cut and pasted the correct url.';

?>
