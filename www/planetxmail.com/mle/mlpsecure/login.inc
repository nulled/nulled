<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/phpsecure/turingkey.class.inc');

$db = new MySQL_Access('mle');

$turingkey = new TuringKey();

$today = date('F j, Y');

$onehour    = 3600;
$oneday     = 86400;
$time_limit = 120; // turing key expire time

$email    = strtolower(trim($email));
$username = trim($username);
$password = trim($password);

if ($submitted)
{
  if ($submitted == 'login' AND ! has_weird($username) AND ! strstr($password, '"') AND ! strstr($password, "'"))
  {
    // check if elp is being used if so by pass turing key
    $ezylistgood = 0;

    if ($evalidate)
    {
      $checkkey = strrev(substr($validate, 2, 1).substr($validate, 10, 1).substr($validate, 4, 1).substr($validate, 15, 1).substr($validate, 12, 1).substr($validate, 9, 1));

      if ($checkkey == $evalidate)
      {
        $ezylistgood = '420';
        $key = 1;
      }
    }

    if ($turingkey->validate() OR $ezylistgood == '420')
    {
      if (! $db->Query("SELECT email, listemail, verified, memberpaid, userID, username, status, listname FROM users WHERE username='$username' AND password=MD5('$password') AND {$_listID}"))
        $notValid = 'ERROR: User Name or Password not found.';
      else
      {
        list($email, $listemail, $verified, $memberpaid, $userID, $username, $status, $listname) = $db->FetchRow();

        if (strtolower($listname) == strtolower($list))
        {
          if (! $newsletter)
          {
            if ($verified == 'yes')
            {
              $db->Query("SELECT paylinkparams FROM listmanager WHERE {$_listID}");
              list($paylinkparams) = $db->FetchRow();

              list($checkbilling, $renewaltype) = explode('|', $paylinkparams);

              //if (! $memberpaid AND $checkbilling AND $status != 'mem' AND $renewaltype != 4)
              if (1 == 2) // disable billing til it is fixed ...
                $notValid = 'Bill is due! <a href="renew.php?u=' . strrev($userID) . '" target="_blank">Click Here</a> to pay so you can log in.';
              else
              {
                session_set_cookie_params(0, '/mle', '.planetxmail.com', 0, 1);
                session_start();
                session_destroy();
                session_set_cookie_params(0, '/mle', '.planetxmail.com', 0, 1);
                session_start();

                $ipaddress = $_SERVER['REMOTE_ADDR'];

                $_SESSION['aausername']    = $username;
                $_SESSION['aauserID']      = $userID;
                $_SESSION['aastatus']      = $status;
                $_SESSION['aapsk']         = 'jjDK83hFsj93bvi8shHbwj';
                $_SESSION['aalistname']    = $listname;
                $_SESSION['aalistownerID'] = $id;
                $_SESSION['aaelp']         = ($ezylistgood == '420') ? '1' : '0';
                $_SESSION['aaipaddress']   = $ipaddress;
                $_SESSION['LAST_ACTIVITY'] = time();

                $db->Query("INSERT IGNORE INTO ips VALUES('{$ipaddress}')");

                // logdate, logins, signup, mails, adminmail
                $db->Query("INSERT INTO hitcounter (logdate, logins) VALUES('$today', '1') ON DUPLICATE KEY UPDATE logins=logins+1");

                $db->Query("UPDATE users SET lastloggedin=NOW(), ipaddress='{$ipaddress}' WHERE userID='{$userID}' LIMIT 1");

                // make sure listemail does not equal contact email
                $db->Query("UPDATE users SET listemail='' WHERE listemail=email AND userID='{$userID}' LIMIT 1");

                header('Location: main.php');
                exit;
              }
            }
            else
            {
              $validator = substr(sha1($userID.$email), 0, 5);
              $encode    = urlencode($email);

              $notValid = 'Your account has <i>not</i> been verified!<br /><a href="rvm.php?u=' . $userID . '&e=' . $encode . '&v=' . $validator . '"><b>Click here</b></a> to re-send the activation email.';
            }
          }
          else
            $notValid = 'ERROR: Can not log into a NewsLetter type list.';
        }
        else
          $notValid = 'ERROR: You are not signed up to the list: ' . $list;
      }
    }
    else
      $notValid = "ERROR: Invalid Turing Key. You have {$turingkey->time_limit} secs before the Key Expires.";
  }
  else if ($submitted == 'lostpassword' AND $email)
  {
    if ($notValid = EmailFormat($email, 1)) {}
    else if (! $db->Query("SELECT email, userID, username FROM users WHERE email='$email' AND {$_listID} LIMIT 1"))
      $notValid = "ERROR: <i>$email</i> not found for this List: {$list}";
    else
    {
      list($email, $userID, $username) = $db->FetchRow();

      $db->Query("SELECT fromname FROM listmanager WHERE {$_listID} LIMIT 1");
      list($fromname) = $db->FetchRow();

      $v = substr(sha1($userID . 'skdH76Sdh76Ma' . $email), 0, 5);
      $enc = urlencode($email);

      $newpasslink = "http://planetxmail.com/mle/enp.php?u={$userID}&v={$v}&e={$enc}&l={$listhash}";

      $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/lostpassmessage.txt');

      $message = str_replace(array('[link]',    '[username]'),
                             array($newpasslink, $username),
                             $message);

      $subject = "{$list} - Login Retrieval";
      $header = "From: {$fromname} <do_not_reply@planetxmail.com>";

      @mail($email, $subject, $message, $header);

      header("Location: http://planetxmail.com/mle/passwordsentmessage.php?email={$email}&list={$list}&id={$id}");
      exit;
    }
  }
  else
    $notValid = 'ERROR: Missing required fields.';
}

?>