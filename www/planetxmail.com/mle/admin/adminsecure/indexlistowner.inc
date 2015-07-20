<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($submitted == 'login')
{
  $db = new MySQL_Access('mle');

  if ($username AND $password)
  {
    $temppass = $password;

    if ($db->Query("SELECT password, listownerID FROM listowner WHERE username='$username' AND password=MD5('$password') LIMIT 1"))
    {
      list($password, $listownerID) = $db->FetchRow();

      $db->Query("SELECT listname FROM listmanager WHERE listownerID='{$listownerID}' AND created='1' LIMIT 1");
      list($listname) = $db->FetchRow();

      $db->Query("SELECT listhash FROM listurls WHERE listname='{$listname}' AND listownerID='{$listownerID}' LIMIT 1");
      list($listhash) = $db->FetchRow();

      $db->Query("UPDATE listowner SET lastlogin=NOW() WHERE listownerID='{$listownerID}'");

      session_name("PHPADMINID");
      session_set_cookie_params(0, '/mle/admin', '.planetxmail.com', 0, 1);
      session_start();
      @session_destroy();
      session_name("PHPADMINID");
      session_set_cookie_params(0, '/mle/admin', '.planetxmail.com', 0, 1);
      session_start();

      $_SESSION['aalistownerpsk']  = 'hSk8dKdj3Hak815hFcb';
      $_SESSION['aalistownerID']   = $listownerID;
      $_SESSION['aalistownername'] = $username;
      $_SESSION['aalistname']      = $listname;
      $_SESSION['aalisthash']      = $listhash;
      $_SESSION['LAST_ACTIVITY']   = time();

      if ($temppass == '111111')
      {
        header('Location: changepasswordlistowner.php');
        exit;
      }

      header('Location: news.php');
      exit;
    }
    else
      $notValid = 'ERROR: User Name or Password incorrect.';
  }
  else
   $notValid = 'ERROR: Missing required fields.';
}

?>