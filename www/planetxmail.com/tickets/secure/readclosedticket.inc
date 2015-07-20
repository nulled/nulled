<?php

$db = new MySQL_Access("pxm");

if (trim($_GET['number']))
{
	$_POST['submitted'] = "openbackup";
	$_POST['status'] = 0;
	$_POST['number'] = $_GET['number'];
	$redirect_to_opentickets = 1;
}

if ($_POST['submitted']=="openbackup")
{
  $status = trim($_POST['status']);
  $number = trim($_POST['number']);

  if (! $number)
    $notValid = "ERROR: Number: '$number' not there!";
  else
  {
    if ($status=="1")
    {
      $db->Query("UPDATE tickets SET open='1' WHERE number='$number'");
      echo "Ticket #: ".$number." was re-opened.<br><br><a href=\"main.php?c=viewopentickets\">Goto Open Tickets</a><br><br><a href=\"main.php?c=viewclosedtickets\">Goto Closed Tickets</a></td></tr></table></body></html>\n";
      exit;
    }
    else if ($status=="0")
    {
      $db->Query("DELETE FROM tickets WHERE number='$number'");

      if ($redirect_to_opentickets)
      {
      	echo "Ticket #: ".$number." was deleted.<br><br><a href=\"main.php?c=viewopentickets\">Goto Open Tickets</a><br><br><a href=\"main.php?c=viewclosedtickets\">Goto Closed Tickets</a></td></tr></table></body></html>\n";
      	exit;
      }
    }
  }
}

if($_GET['n']) $number = trim($_GET['n']);

$db->Query("SELECT id, email, subject, message, number, datereceived FROM tickets WHERE number='$number' ORDER BY id DESC");
while(list($id, $email, $subject, $message, $num, $date) = $db->FetchRow())
{
  $emails[]   = $email;
  $dates[]    = mysql_datetime_to_humandate($date);
  $subjects[] = stripslashes($subject);
  $messages[] = stripslashes(htmlentities($message));
}

if (! count($emails))
{
	echo "<a href=\"main.php?c=viewclosedtickets\">Goto Closed Tickets</a><br><br><a href=\"main.php?c=viewopentickets\">Goto Open Tickets</a></td></tr></table></body></html>\n";
  exit;
}

?>
