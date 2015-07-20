<?php
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/config/config.inc");
include("../mlpsecure/validationfunctions.php");

$db = new MySQL_Access();

if ($submitted=="update")
{
  $usrs  = explode("|", $affs);
  $counter = count($usrs);

  for ($i=0; $i < $counter; $i++)
  {
    if ($usrs[$i]!="")
      $userlist .= "username='$usrs[$i]' OR ";
  }

  $userlist = substr($userlist, 0, strlen($userlist)-4);

  $db->Query("UPDATE users SET paid='1' WHERE $userlist AND listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
}

$db->Query("SELECT username, email, affiliatemop FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND userID='$u'");
list($uname, $email, $affiliatemop) = $db->FetchRow();

$db->Query("SELECT listhash FROM listurls WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
list($listhash) = $db->FetchRow();

$affid = strrev($u)."|$listhash";

$db->Query("SELECT username, datesignedup, paid, status FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND referer='$affid'");
$affiliates = $db->result;

if ($commission_pro) $owed_pro = $cost_of_pro * ($commission_pro / 100);
if ($commission_exe) $owed_exe = $cost_of_exe * ($commission_exe / 100);

if ($affiliatemop)
{
  $html  = "";

  $html .= "<tr>\n";
  $html .= "        <td bgcolor=\"lightblue\"><b>User Name</b></td>\n";
  $html .= "        <td bgcolor=\"lightblue\"><b>Date Signed Up</b></td>\n";
  $html .= "        <td bgcolor=\"lightblue\"><b>Amount Owed</b></td>\n";
  $html .= "        <td bgcolor=\"lightblue\"><b><i>$uname</i> was paid?</b></td>\n";
  $html .= "        <td bgcolor=\"lightblue\"><b>Check To Pay</b></td>\n";
  $html .= "      </tr>\n";

  $i = $totalowed = 0;
  while (list($username, $datesignedup, $paid, $status) = mysqli_fetch_row($affiliates))
  {
    list($datesignedup) = explode(" ", $datesignedup);

    if ($i%2==0)
      $bgcolor = "F4F4F7";
    else
      $bgcolor = "E9E9E9";

    if ($paid) $paid = "Yes"; else $paid = "No";

    if ($status=="mem") { $owed = "Free Member"; $paid = "N/A"; }
    else if ($status=="pro") { $owed = "\$ ".number_format($owed_pro, 2, '.', ''); if ($paid=="No") $totalowed += $owed_pro; $owned_plain = number_format($owed_pro, 2, '.', ''); }
    else if ($status=="exe") { $owed = "\$ ".number_format($owed_exe, 2, '.', ''); if ($paid=="No") $totalowed += $owed_exe; $owned_plain = number_format($owed_exe, 2, '.', ''); }
    else $owed = "Error in Status";

    $html .= "<tr><td bgcolor=\"$bgcolor\">$username</td><td bgcolor=\"$bgcolor\">$datesignedup</td><td bgcolor=\"$bgcolor\">$owed</td><td bgcolor=\"$bgcolor\" align=\"center\">$paid</td><td bgcolor=\"$bgcolor\" align=\"center\">";

    if ($paid=="No" && $status!="mem")
    	$html .= "<input style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" type=\"checkbox\" value=\"$username\" onClick='setAmountToPay($owned_plain, this.checked)'>";

    echo "</td></tr>\n";
    $i++;
  }

  $html .= "<tr><td align=\"right\" colspan=\"2\"><i>Total Owed:</i></td><td bgcolor=\"yellow\">\$ ".number_format($totalowed, 2, '.', '')."</td><td align=\"right\"><i>Amount you will pay:</i></td><td><input type=\"text\" name=\"amounttopay\" value=\"0.00\"size=\"10\" READONLY></td>\n";

  $html .= "<tr><td align=\"center\" colspan=\"5\"><br><br><input type=\"button\" value=\"Update Affiliate Records and Pay $uname\" onClick=\"if (checkSelect(this.form)) if (confirm('This will update your Affiliate Database\\\nthat you have PAID this member: $uname\\\nthe amount of: \$ ' + document.affiliates.amounttopay.value + '\\\nto their Paypal address: $affiliatemop\\\n\\\nHit OK to Update your Affiliate records.\\\nYou will then be directed to Paypal.')) preSubmit(this.form);\"></tr></td>\n";
  $html .= "      <input type=\"hidden\" name=\"submitted\" value=\"update\">\n";
  $html .= "      <input type=\"hidden\" name=\"affs\" value=\"\">\n";
  $html .= "      <input type=\"hidden\" name=\"u\" value=\"$u\">\n";
  $html .= "      </form>\n";
}
else
  $html = "<tr><td>This member does not have their Paypal address set.  You may contact them at: <b>$email</b> and let them know... they will also be notified in their Member Profile.";
?>