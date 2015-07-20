<?php
require_once('/home/nulled/www/planetxmail.com//mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access("elp");

if (! $o) $o = "EliteScripts";

$db->Query("SELECT elpownername FROM elpowners WHERE elpownername='$o'");
if (! $db->rows)
{
  echo "Missing ELP OWNER param or Owner does not exist.";
  exit;
}

if ($submitted=="signup")
{
  if ($fname && $lname && $username && $password1 && $password2 && $email)
  {
    $fname    = trim($fname);
    $lname    = trim($lname);
    $email    = trim($email);
    $username = trim($username);
    $r        = trim($r);

    if ($lite)
      $memsignuppaylinks = "memsignuplitepaylinks";
    else
      $memsignuppaylinks = "memsignuppaylinks";

    if ($notValid = EmailFormat($email)) {}
    else if (strtolower($username)=="demo") { $notValid = "ERROR: You can not use <i>demo</i> as a username."; }
    else if ($notValid = LengthUsername($username)) {}
    else if ($notValid = LengthRealname($fname)) {}
    else if ($notValid = LengthRealname($lname)) {}
    else if ($password1 != $password2) $notValid = "ERROR: Passwords do not match.";
    else if ($notValid = LengthPassword($password1)) {}
    else if (has_space($password1)) $notValid = "Password can not contain a space.";
    else if (has_weird($username)) $notValid = "ERROR: Username can only contain A-Z, a-z, 0-9 and _";
    else if ($db->Query("SELECT username FROM users WHERE elpownername='$o' AND username='$username'")) $notValid = "ERROR: Username already registered.  If you need to pay your signup fee please: <a href=\"$memsignuppaylinks.php?o=$o&u=$username\">CLICK HERE.</a>";
    else if ($db->Query("SELECT email FROM users WHERE elpownername='$o' AND email='$email'")) $notValid = "ERROR: Email already registered.";
    else
    {
      $passwordenc = md5($password1);

      if ($lite)
        $db->Query("INSERT INTO users VALUES('$username','$o','$email','$passwordenc','$fname','$lname',NOW(),'0',NOW(),'0','0','lite')");
      else
        $db->Query("INSERT INTO users VALUES('$username','$o','$email','$passwordenc','$fname','$lname',NOW(),'0',NOW(),'0','0','pro')");

      // make sure the day of the week is 28 or less
      $db->Query("SELECT datesignedup FROM users WHERE username='$username' AND elpownername='$o'");
      list($datesignedup) = $db->FetchRow();

      $parts = preg_split("/[- ]/", $datesignedup);
      if ($parts[2]>28)
      {
        $parts[2] = "28";
        $datesignedup = "$parts[0]-$parts[1]-$parts[2] $parts[3]";
        $db->Query("UPDATE users SET datesignedup='$datesignedup' WHERE username='$username' AND elpownername='$o'");
      }

      if ($lite)
        header("Location: memsignuplite.php?u=$username&o=$o");
      else
        header("Location: memsignuppaylinks.php?u=$username&o=$o");

      exit;
    }
  }
  else
    $notValid = "ERROR: Missing required parameters.";
}
?>