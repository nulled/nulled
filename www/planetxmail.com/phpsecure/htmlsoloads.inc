<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access("mle");

session_start();
if ($list) $l = $list;
else if ($_SESSION[aalistname]) $l = $_SESSION[aalistname];

if ($submitted=="send")
{
  if ($message)
  {
    $message = trim($message);

    $l .= " - HTMLSOLOAD";

    if (! $id)
    {
      $db->Query("INSERT INTO soloads VALUES('','','','$message','','49','','','$l','0','0','0',NOW(),'0','0')");
      $id = mysqli_insert_id($db->link);
      mail('elitescripts2000@yahoo.com', 'htmlsolo ad violation', 'id: '.$id.' - ip: '.$_SERVER['REMOTE_ADDR']);
    }
    else
      $db->Query("UPDATE soloads SET message='$message', datesubmitted=NOW() WHERE id='$id'");

    header("Location: htmlsoloadspreview.php?id=$id");
    exit;
  }
  else
    $notValid = "ERROR: Missing required fields.";
}
else if ($id)
{
  $db->Query("SELECT message FROM soloads WHERE id='$id'");
  list($message) = $db->FetchRow();
}

$db->Query("SELECT COUNT(*) FROM users WHERE 1");
list($totalmembers) = $db->FetchRow();

$db->Query("SELECT COUNT(*) FROM listowner WHERE 1");
list($totalowners) = $db->FetchRow();

$db->Query("SELECT COUNT(*) FROM listconfig WHERE 1");
list($totallists) = $db->FetchRow();

$totalmembers += 60000;
$totalowners += 145;
$totallists += 145;

?>