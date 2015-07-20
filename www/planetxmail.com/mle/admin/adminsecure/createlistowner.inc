<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

if ($submitted=="create" AND $thelistownername AND $adminemail AND $numLists)
{
  $adminemail = strtolower(trim($adminemail));

  if (has_weird($thelistownername))         $notValid = 'ERROR: List Owner Name may only contain Latters, Numbers and Underscores (_).';
  else if (has_space($thelistownername))    $notValid = 'ERROR: List Owner Name may not contain any Spaces.';
  else if (strlen($thelistownername) > 20)  $notValid = 'ERROR: List Owner name may only contain 20 Characters.';
  else if (strlen($thelistownername) < 3)   $notValid = 'ERROR: List Owner name may contain a minimum of 3 Characters.';
  else if (! @is_numeric($numLists))        $notValid = 'ERROR: Number of Lists is not a number.';
  else if ($numLists > 5)                   $notValid = 'ERROR: Number of Lists too high. 5 Max.';
  else if ($notValid = EmailFormat($adminemail)) {}
  else
  {
    $db = new MySQL_Access('mle');

    if ($db->Query("SELECT username FROM listowner WHERE username='$thelistownername' LIMIT 1"))
      $notValid = "ERROR: List owner name <i>$thelistownername</i> is already taken.";
    else
    {
      $i = 0;
      while (true)
      {
        if ($i > 1000)
          mail_debug_backtrace_exit();

        $i++;

        $listownerID = generateID();

        if ($db->Query("SELECT listownerID FROM listowner WHERE listownerID='$listownerID' LIMIT 1"))
          continue;
        else
          break;
      }

      $listnameID = 'new' . generateID(12);
      $password   = '96e79218965eb72c92a549dd5a330112';

      $db->Query("INSERT INTO listowner VALUES('$listownerID','$thelistownername','$password','$adminemail','0',NOW())");

      for ($i = 0; $i < $numLists; $i++)
      {
        $listnameID = 'new' . generateID(12);
        $db->Query("INSERT INTO listmanager VALUES('$listownerID','$listnameID','','','','','','','','','','','','','','0','0','')");
      }

      $_SESSION['aalistownerID'] = $listownerID;

      header("Location: listownercreated.php?aalistownerID={$_SESSION['aalistownerID']}");
      exit;
    }
  }
}
else if ($submitted == 'create')
  $notValid = "Error: Missing required fields.";

?>