<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/elp/admin/adminsecure/session/adminpsk.inc');
require_once('/home/nulled/www/planetxmail.com/elp/adminsecure/session/elpownerpsk.inc');

$db = new MySQL_Access("elp");

if ($submitted == 'login')
{
  if ($username AND $password AND ($elpowner OR $createelpowner=="1"))
  {
    $pass = md5($password);

    if ($db->Query("SELECT * FROM admin WHERE name='$username' AND password='$pass'"))
    {
      $db->Query("SELECT elpownername FROM elpowners WHERE elpownername='$elpowner'");
      list($elpownername) = $db->FetchRow();

      session_start();
      @session_destroy();
      session_start();

			$_SESSION['aaadminpsk']      = $adminpsk;
      $_SESSION['aaelpownerpsk']   = $elpownerpsk;
      $_SESSION['aaelpownername']  = $elpownername;

      // first time admin logging in so ask to change password
      if ($password=="111111")
      {
        if ($createelpowner=="1")
        {
          header("Location: changepassword.php?createelpowner=1");
          exit;
        }
        else
        {
          header("Location: changepassword.php");
          exit;
        }
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
    else
      $notValid = "ERROR: Username or Password incorrect.";
  }
  else
   $notValid = "ERROR: Missing required fields.";
}

$db->Query("SELECT elpownername FROM elpowners ORDER BY elpownername");
$elpowners = $db->result;
$numOwners = $db->rows;

$db->Query("SELECT password FROM admin LIMIT 1");
list($pass) = $db->FetchRow();

if ($pass=="96e79218965eb72c92a549dd5a330112" OR $numOwners==0)
  $newadmin = true;
else
  $newadmin = false;

?>