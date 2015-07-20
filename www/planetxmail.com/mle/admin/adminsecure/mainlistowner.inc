<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

if ($submitted == 'search')
{
  set_time_limit(0);

  $usertosearch = trim($usertosearch);

  if (strlen($usertosearch)>2)
  {
    if ($searchby=="username")       $db->Query("SELECT userID FROM users WHERE username LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
    else if ($searchby=="listemail") $db->Query("SELECT userID FROM users WHERE listemail LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
    else if ($searchby=="email")     $db->Query("SELECT userID FROM users WHERE email LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
    else if ($searchby=="firstname") $db->Query("SELECT userID FROM users WHERE fname LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
    else if ($searchby=="lastname")  $db->Query("SELECT userID FROM users WHERE lname LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
  }
  else
    $notValid = "Search must contain at least 3 characters.";

  if (! $notValid)
  {
    while (list($uIDs) = $db->FetchRow()) $totalIDs .= "$uIDs|";

    if ($totalIDs)
    {
      header("Location: searchresults.php?totalIDs=$totalIDs");
      exit;
    }
    else
      $notValid = "No user match found.";
  }
}
else if ($submitted=="resetpassword")
{
  if ($_SESSION['aalistownername'] != "demoit")
    $db->Query("UPDATE listowner SET password='96e79218965eb72c92a549dd5a330112' WHERE listownerID='$_SESSION[aalistownerID]'");
}
else if ($submitted=="changelist")
{
  if (substr($list, 0, 3)=="new")
  {
    header("Location: createlistlistowner.php");
    exit;
  }

  $_SESSION['aalistname'] = $list;
}
else if ($submitted=="changemailingrule")
  $db->Query("UPDATE listmanager SET mailingrule='$mailingrule' WHERE listname='$_SESSION[aalistname]'");

$db->Query("SELECT listname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND created='1' LIMIT 1");

if (! $db->rows) $noList = true;
else
  $noList = false;

if ($noList==false)
{
  $getData = 0;

  require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/getmembers.inc');

  $db->Query("SELECT listtype FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $listtype = $db->FetchRow();

  $db->Query("SELECT listname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' ORDER BY listname");
  $lists = $db->result;

  $db->Query("SELECT mailingrule FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $mailingrule = $db->FetchRow();

  $db->Query("SELECT listhash FROM listurls WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
  list($listhash) = $db->FetchRow();
}

require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/billing.inc');

// check if listowner needs to pay bill

if (($paid == 'no' OR $paid == '0') AND $paid != 'free2months')
{
  echo "<html><head><title>Bill Due Paylink</title></head>\n";
  echo "<link rel=\"stylesheet\" type=\"text/css\" href=\"../css_mlp.css\" /><body>\n";
  echo "<table align=\"center\" cellspacing=\"0\" cellpadding=\"2\" border=\"1\" width=\"600\"><tr><td>\n";
  echo "<center><img src=\"../images/title.gif\">\n";
  echo "<h3>Bill is Due.  ListName: $_SESSION[aalistname]</h3>\n";
  echo "You must pay your List Bill before you can Log-in!  Please use the paylink\n";
  echo "below to pay your List Bill<br><br>\n";
  echo "<a href=\"http://www.planetxmail.com/listpayment.php?id=$orderID&listtype=$type&p=$price&ex=$ex\">Click Me to Pay Bill for ListName: $_SESSION[aalistname]</a><br><br>\n";
  echo "<font color=red><b>Important Note!</b></font> You need to click all the way to Planet X Mail Thank you pages after you make your payment in order to register it with us!</center>\n";
  echo "<tr></td></table></body></html>";
  exit;
}


?>