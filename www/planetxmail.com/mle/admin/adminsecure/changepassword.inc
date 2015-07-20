<?php

if ($submitted=="1")
{
  if ($password1!=""&&$password2!="")
  {
    include("../mlpsecure/validationfunctions.php");

    if ($password1!=$password2) $notValid = "ERROR: Passwords do not match.";
    else if ($notValid = LengthPassword($password1)) {}
    else if ($password1=="111111") $notValid = "ERROR: Can not use 111111 as a password.";
    else if (has_space($password1)) $notValid = "ERROR: Can not have a space in password.";
    else
    {
      include("../mlpsecure/config/classes.inc");

      $password1 = md5($password1);

      $db = new MySQL_Access();
      $db->Query("UPDATE admin SET password='$password1' WHERE name='admin'");

      if ($createlistowner=="1")
      {
        header("Location: createlistowner.php");
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
