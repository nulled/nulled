<?php
if ($submitted=="change")
{
  if ($password1!=""&&password2!="")
  {
    include("../../mle/mlpsecure/validationfunctions.php");

    if ($password1!=$password2) $notValid = "ERROR: Passwords do not match.";
    else if ($notValid = LengthPassword($password1)) {}
    else if ($password1=="111111") $notValid = "ERROR: Can not use 111111 as a password.";
    else if (has_space($password1)) $notValid = "ERROR: Can not have a space in password.";
    else
    {
      include("../../mle/mlpsecure/config/classes.inc");
      $db = new MySQL_Access("elp");

      $password1 = md5($password1);

			if ($_SESSION['aaadminpsk'])
      	$db->Query("UPDATE admin SET password='$password1' WHERE name='admin'");
      else
      {
      	$db->Query("UPDATE elpowners SET password='$password1' WHERE elpownername='$_SESSION[aaelp]ownername'");
      	$createelpowner = "";
      }

      if ($createelpowner=="1")
      {
        header("Location: createelpowner.php");
        exit;
      }
      else
      {
        header("Location: main.php");
        exit;
      }
    }
  }
  else
    $notValid = "ERROR: Missing required fields.";
}
?>
