<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($submitted=="create")
{
  if ($theelpownername!=""&&$adminemail!=""&&$price!=""&&$monthlyprice!=""&&$commission!=""&&$monthlycommission!=""&&$fname!=""&&$lname!="")
  {
    $db = new MySQL_Access("elp");

    $fname = trim($fname);
    $lname = trim($lname);
    $adminemail = trim($adminemail);
    $theelpownername = trim($theelpownername);

    if (has_weird($theelpownername)) $notValid = "ERROR: ELP Owner name can only have a-z, A-Z, 0-9 or _ in it.";
    else if ($notValid = EmailFormat($adminemail)) {}
    else if (strlen($theelpownername)>20) $notValid = "ERROR: ELP Owner name is too long. 20 maximum characters.";
    else if (strlen($theelpownername)<4) $notValid = "ERROR: ELP Owner name is too short. 4 minimum characters.";
    else if ($db->Query("SELECT email FROM elpowners WHERE email='$adminemail'")) $notValid = "ERROR:  Email already in use.";
    else if (! is_numeric($price = trim($price))) $notValid = "ERROR: Price not a number.";
    else if (! is_numeric($monthlyprice = trim($monthlyprice))) $notValid = "ERROR: Monthly price not a number.";
    else if (! is_numeric($commission = trim($commission))) $notValid = "ERROR: Commission not a number.";
    else if (! is_numeric($monthlycommission = trim($monthlycommission))) $notValid = "ERROR: Monthly commission not a number.";
    else
    {
      $db->Query("SELECT elpownername FROM elpowners WHERE elpownername='$theelpownername'");

      if ($db->rows) $notValid = "ERROR: ELP Owner name <i>$theelpownername</i> is already taken.";
      else
      {
        $midnight = mktime(0, 0, -1, date("m"), date("d"), date("y"));
        $midnight = timestamp_to_mysql_timestamp($midnight);
        $password = "96e79218965eb72c92a549dd5a330112";
        $signuppaylinkhtml = "not used";
        $monthlypaylinkhtml = "not used";
        $message = "Type your subject here.n!t!w_s!4!0Type your message here.";

        $db->Query("INSERT INTO elpowners VALUES('$theelpownername','$fname','$lname','$password','$adminemail','$price','$monthlyprice','$commission','$monthlycommission','DEFAULT','$message','$signuppaylinkhtml','$monthlypaylinkhtml','0','0','0','0','0','','','','',NOW(),'0','0','0','0','0','0','0')");
        $db->Query("INSERT INTO system VALUES('$theelpownername','$midnight')");

        $_SESSION['aaelpownername'] = $theelpownername;

        header("Location: elpownercreated.php");
        exit;
      }
    }
  }
  else
    $notValid = "Error: Missing required fields.";
}
?>