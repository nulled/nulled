<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

session_start();

$html = trim($_GET['html']);
$list = trim($_GET['list']);
$l    = trim($_GET['l']);

$l = $list ? $list : ($l ? $l : $_SESSION['aalistname']);

// detect SQL injector
if (strstr($l, ';') OR strstr($l, "'") OR ! $l)
  $l = 'unknown';

$db = new MySQL_Access('mle');

if (trim($_POST['submitted']) == 'send')
{
  $subject   = trim($_POST['subject']);
  $message   = trim($_POST['message']);
  $name      = trim($_POST['name']);
  $email     = trim($_POST['email']);
  $crediturl = trim($_POST['crediturl']);

  $html = ($_POST['html']) ? '1' : '';

  if ($subject AND $message AND $name AND $email AND $crediturl)
  {
    $email = strtolower($email);

    if (strtolower(substr($crediturl, 0, 7) != 'http://' AND strtolower(substr($crediturl, 0, 8)) != 'https://'))
      $notValid = 'ERROR: Credit URL must begin with http:// or https://';

    else if (stristr($crediturl, 'yoursite.com'))
      $notValid = 'ERROR: The Credit URL must be Your OWN website! Not the example!';

    else if ($notValid = EmailFormat($email)) {}

    else if (stristr($subject, 'notification of payment') OR
             stristr($subject, 'payment recieved') OR
             stristr($subject, 'payment received') OR
             stristr($subject, 'transaction') )
               $notValid = 'ERROR: Subject Line contains deceptive text. Please Correct and Try Again.';

    else if (stristr($subject.$message, ' xxx ') OR
             stristr($subject.$message, 'pussy') OR
             stristr($subject.$message, ' cock ') OR
             stristr($subject.$message, 'teen sex') OR
             stristr($subject.$message, 'clit ') OR
             stristr($subject.$message, 'horney ') OR
             stristr($subject.$message, 'masterbate ') OR
             stristr($subject.$message, ' cum ') OR
             stristr($subject.$message, ' prick ') OR
             stristr($subject.$message, ' fuck ') OR
             stristr($subject.$message, ' fucker ') OR
             stristr($subject.$message, ' fucking ') OR
             stristr($subject.$message, ' nipples ') OR
             stristr($subject.$message, 'hotsex') OR
             stristr($subject.$message, 'flirting') OR
             stristr($subject.$message, ' porn ') OR
             stristr($subject.$message, 'adult store') OR
             stristr($subject.$message, ' penis') OR
             stristr($subject.$message, ' erection') OR
             stristr($subject.$message, ' male enhance') OR
             stristr($subject.$message, ' viagra ') OR
             stristr($subject.$message, 'nigeria')
    )
               $notValid = "ERROR: Illegal Content Detected. Please Correct and Try Again.";
    else
    {
      $urlID = create_creditID($crediturl, 'SOLOAD');

      $html_header = ($html) ? ' - HTMLSOLOAD' : '';

      $l .= ' - ' . $_SERVER['REMOTE_ADDR'] . $html_header;

      // remove terminating SMTP code from messages or messages will be cut short
      $message = str_replace("\n.\n", "\n", $message);

      $db->Query("INSERT INTO soloads VALUES('','$name','$subject','$message','$email','','','$l','$urlID','0','0',NOW(),'0','0')");

      $id = $db->GetLastID();

      $h = substr(sha1($id . 'sahfme845jdkdhf87hff'), 0, 5);

      $db->Query("DELETE FROM soloads WHERE mop = '' AND datesubmitted < DATE_SUB(NOW(), INTERVAL 5 DAY)");

      header("Location: soloadpaylinks.php?id={$id}&h={$h}");
      exit;
    }
  }
  else
    $notValid = 'ERROR: Missing required fields.';
}

$totalmembers = $db->Query("SELECT username FROM users WHERE 1");
$totalowners  = $db->Query("SELECT username FROM listowner WHERE 1");
$totallists   = $db->Query("SELECT listname FROM listconfig WHERE 1");

$totalmembers += 240000;
$totalowners  += 195;
$totallists   += 235

?>
