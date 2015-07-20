<?php
// remove link
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

if (! $u OR ! $v)
{
  header("Location: notfound.php?error=missing_params");
  exit;
}

// validate user
$userID = strrev(trim($u));
$validator = strrev(substr(md5($userID), 0, 5));
if ($validator != trim($v))
{
  header('Location: notfound.php?error=validator_incorrect');
  exit;
}

$db = new MySQL_Access('mle');

// verify userID exists then extract list and id
if ($db->Query("SELECT email, username, fname, lname, listname, listownerID, listemail FROM users WHERE userID='$userID' LIMIT 1"))
  list($email, $username, $fname, $lname, $list, $id, $listemail) = $db->FetchRow();
else
{
  header("Location: notfound.php?error=user_not_found");
  exit;
}

$fullname = $fname . ' ' . $lname;

$db->Query("SELECT listhash FROM listurls WHERE listname='$list' AND listownerID='$id' LIMIT 1");
list($listhash) = $db->FetchRow();

$db->Query("SELECT programname, adminemailaddress FROM listconfig WHERE listname='$list' AND listownerID='$id' LIMIT 1");
list($program_name, $adminemailaddress) = $db->FetchRow();

$db->Query("SELECT fromname, adminemail, unsubsuccess FROM listmanager WHERE listname='$list' AND listownerID='$id' LIMIT 1");
list($fromname, $listowneremail, $message) = $db->FetchRow();

if (! $listowneremail AND $adminemailaddress) $listowneremail = $adminemailaddress;
if (! $listowneremail)                        $listowneremail = 'admin.email@planetxmail.com';

$headers = "From: {$fromname} <do_not_reply@planetxmail.com>";

if ($submitted == 'removeall')
{
  $message = str_replace(array('[admin_email_address]', '[list_name]', '[program_name]', '[user_name]'),
                         array($listowneremail,          $list,          $program_name,  $fullname),
                         $message);

  $subject = "{$list} - Complete Unsubscribe Notification";

  //if ($userID != '1391131213') {
    $db->Query("DELETE FROM urldata WHERE userID='$userID'");
    $db->Query("DELETE FROM urlmanager WHERE userID='$userID'");
    $db->Query("DELETE FROM users WHERE userID='$userID' LIMIT 1");
  //}

  $notValid = '<h4>Your Membership has been Completely Removed from:<br /><b style="color:black;font-size:16px">' . $list . '</b></h4>';

  // logdate, logins, signup, mails, adminmail
  $today = date('F j, Y');

  //if ($userID != '1391131213')
  $db->Query("INSERT INTO hitcounter (logdate, signup) VALUES('$today', '-1') ON DUPLICATE KEY UPDATE signup = signup - 1");

  @mail($email, $subject, $message, $headers);
  //@mail('admin.email@planetxmail.com', $subject, $message, $headers);
}
else if ($submitted == 'removelistaddressonly')
{
  $message = str_replace(array('[admin_email_address]', '[list_name]', '[program_name]', '[user_name]'),
                         array($listowneremail,          $list,         $program_name,    $fullname),
                         $message);

  $subject = "{$list} - Partial Unsubscribe Notification";

  //if ($userID != '1391131213')
  $db->Query("UPDATE users SET listemail='' WHERE userID='$userID' LIMIT 1");

  $notValid = '<h4>Your <u>List Address</u> has been blanked out from:<br /><b style="color:black;font-size:16px">' . $list . '</b>, <i>but your Account Remains!</i></h4>
  <a href="/mle/login.php?l=' . $listhash . '&username=' . $username . '" target="_blank">Click to Login</a>';

  @mail($email, $subject, $message, $headers);
  //@mail('admin.email@planetxmail.com', $subject, $message, $headers);
}

?>