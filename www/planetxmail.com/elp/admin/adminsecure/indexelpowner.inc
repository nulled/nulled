<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

if ($submitted=="login")
{
  if ($username AND $password)
  {
    $db = new MySQL_Access("elp");

  	$username = trim($username);
  	$password = trim($password);

    $passwordenc = md5($password);

    $db->Query("SELECT elpownername FROM elpowners WHERE elpownername='$username' AND password='$passwordenc'");

    if ($db->rows)
    {
    	// check if ELP owner has paid all billing periods.
    	$oneday = 86400;
    	$db->Query("SELECT id, paid FROM billingperiods WHERE elpownername='$username' AND paid='0' AND (UNIX_TIMESTAMP(NOW()) - (5 * $oneday)) > UNIX_TIMESTAMP(dateowed) ORDER BY dateowed DESC LIMIT 1");
			if ($db->rows)
			{
				list($id, $paid) = $db->FetchRow();
				echo "<html><head><title>ELP Billing Period 5 days Over Due</title></head><body><table align=center width=600><tr><td align=center>\n";
				echo "<img src=\"../images/elplogo.jpg\"><hr>\n";
				echo "<h4>A Billing Period is 5 days Over Due for your account.  The link to pay this Billing Period is below.  Once paid you will be able to Login.</h4>\n";
				echo "<a href=\"http://www.planetxmail.com/elp/elpownerpaylinks.php?id=$id&o=$username\">Pay Your ELP Billing Period.</a>";
				echo "</td></tr></table></body></html>";
				exit;
			}

      session_start();

      require_once('/home/nulled/www/planetxmail.com/elp/admin/adminsecure/session/elpownerpsk.inc');

      $_SESSION['aaownerpsk']  = $elpownerpsk;
      $_SESSION['aaownername'] = $username;

      if ($password=="111111")
      {
        header("Location: changepassword.php");
        exit;
      }

      header("Location: main.php");
      exit;
    }
    else
      $notValid = "ERROR: ELP Owner Name or Password incorrect.";
  }
  else
   $notValid = "ERROR: Missing required fields.";
}

?>
