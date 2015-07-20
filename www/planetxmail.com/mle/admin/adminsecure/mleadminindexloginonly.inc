<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

if ($submitted == 'login')
{
  if ($username AND $password AND ($listowner OR $createlistowner == '1'))
  {
    if ($db->Query("SELECT name FROM admin WHERE name='$username' AND password=MD5('$password') LIMIT 1"))
    {
      $db->Query("SELECT username FROM listowner WHERE listownerID='$listowner' LIMIT 1");
      list($listusername) = $db->FetchRow();

      $db->Query("SELECT listname FROM listmanager WHERE listownerID='$listowner' AND created='1' LIMIT 1");
      list($createdlistname) = $db->FetchRow();

      $db->Query("SELECT listhash FROM listurls WHERE listname='$createdlistname' AND listownerID='$listowner' LIMIT 1");
      list($listhash) = $db->FetchRow();

      session_name('PHPADMINID'); // must use the same session_name for regular and super list owner
      session_set_cookie_params(0, '/mle/admin', '.planetxmail.com', 0, 1);
      session_start();
      @session_destroy();
      session_name('PHPADMINID');
      session_set_cookie_params(0, '/mle/admin', '.planetxmail.com', 0, 1);
      session_start();

      $_SESSION['aaadminpsk']      = 'hKsjO74GsbqcCos7264';
      $_SESSION['aalistownerpsk']  = 'hSk8dKdj3Hak815hFcb'; // must be set so we can access reg listowner pages as well
      $_SESSION['aalistownerID']   = $listowner;
      $_SESSION['aalistownername'] = $listusername;
      $_SESSION['aalistname']      = $createdlistname;
      $_SESSION['aalisthash']			 = $listhash;
      $_SESSION['LAST_ACTIVITY']   = time();

      // first time admin logging in so ask to change password
      if ($password == '111111')
      {
        if ($createlistowner == '1')
        {
          header('Location: changepassword.php?createlistowner=1');
          exit;
        }
        else
        {
          header('Location: changepassword.php');
          exit;
        }
      }

      if ($createlistowner == '1')
      {
        header('Location: createlistowner.php');
        exit;
      }
      else
      {
        header('Location: main.php?firstList=1');
        exit;
      }
    }
    else
      $notValid = 'ERROR: User Name or Password incorrect.';
  }
  else
   $notValid = 'ERROR: Missing required fields.';
}

$db->Query("SELECT username, listownerID FROM listowner ORDER BY username");
$listowners = $db->result;

$db->Query("SELECT password FROM admin LIMIT 1");
list($pass) = $db->FetchRow();

$db->Query("SELECT listownerID FROM listowner");
$noListOwners = $db->rows;

$newadmin = ($pass == '96e79218965eb72c92a549dd5a330112' OR $noListOwners == 0) ? true : false;

$db->Query("SELECT username FROM listowner");
$numOwners = $db->rows;

?>
