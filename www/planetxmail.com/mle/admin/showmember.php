<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/showmember.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var currentstatus = '<?=$userData['status']?>';
function confirmDelete(formname)
{
  if (confirm('Are you sure you want to erase member?  Including all URL data for this member?'))
    formname.submit();
}
function checkStatus(formname, statuspicked)
{
  if ((statuspicked=='pro' && currentstatus=='mem') || (statuspicked=='exe' && (currentstatus=='mem' || currentstatus=='pro')))
  {
    if (confirm('You are UPGRADING this members Status and your Check Billing System is ON.\n\nDo you wish to generate a transaction because this member has paid you to upgrade?\n\nChoosing OK we will direct you to a form to add the transaction amount.\nChoosing Cancel it will simply Upgrade the Member.'))
    {
      formname.todo.value = 'generatetransaction';
      formname.s.value = statuspicked;
      formname.submit();
    }
  }
  else if (statuspicked==currentstatus)
    return;

  formname.submit();
}
//-->
</script>
</head>
<body>
<table style="border-left: solid 1px #000000;border-bottom: solid 1px #000000;border-top: solid 1px #000000;border-right: solid 1px #000000;" align="center" cellpadding="3" cellspacing="1" border="0" width="500">
  <tr>
    <td align="center" colspan="2">
      <?php if ($notValid) echo "<font color=\"red\" size=\"3\"><b>$notValid<br></b></font>\n"; ?>
      <font size="+1">Profile for User: </font> <font color="red" size="+2"><b><?=$userData['username']?></b></font>
      <br><hr>
    </td>
  </tr>

  <form name="userdata" action="/mle/admin/showmember.php" method="POST">

  <tr>
    <td align="right" bgcolor="#EFEEEA">
      First Name:</td>
    <td bgcolor="#EFEEEA" align="left">
      <b><input type="text" size="30" name="fname" value="<?=$userData['fname']?>"></b></td>
  </tr>

  <tr>
    <td bgcolor="#F4F4F4" align="right">Last Name:</td>
    <td bgcolor="#F4F4F4" align="left">
      <b><input type="text" size="30" name="lname" value="<?=$userData['lname']?>"></b></td>
  </tr>

  <tr>
    <td bgcolor="#EFEEEA" align="right">
      Contact Address:
      <?php

          if ($emailbounce=="bounce") echo " <a href=\"#\" onClick=\"window.open('bouncereason.php?email=$email',0,'height=360,width=600,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\"><font color=red><b>Bounced</b></font></a> ";
          else if ($emailbounce=="mailboxfull") echo " <a href=\"#\" onClick=\"window.open('bouncereason.php?email=$email',0,'height=360,width=600,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\"><font color=red><b>Mailbox Full</b></font></a> ";
      ?>

    </td>
    <td bgcolor="#EFEEEA" align="left">
      <b><input type="text" size="30" name="email" value="<?=$userData['email']?>" READONLY></b>
    </td>
  </tr>

  <?php

    if ($listtype=="Safelist [openlist]")
    {
      echo "<tr>\n";
      echo "  <td bgcolor=\"#F4F4F4\">\n";
      echo "    <p align=\"right\">List Address:";
      if ($listemailbounce=="bounce") echo " <a href=\"#\" onClick=\"window.open('bouncereason.php?email=$listemail',0,'height=360,width=600,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\"><font color=red><b>Bounced</b></font></a> ";
      else if ($listemailbounce=="mailboxfull") echo " <a href=\"#\" onClick=\"window.open('bouncereason.php?email=$listemail',0,'height=360,width=600,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\"><font color=red><b>Mailbox Full</b></font></a> ";
      echo "</td>\n";
      echo "  <td bgcolor=\"#F4F4F4\" align=\"left\">\n";
      echo "<b><input type=\"text\" size=\"30\" name=\"listemail\" value=\"".$userData['listemail']."\" READONLY></b></td>\n";
      echo "</tr>\n";

      echo "<tr>\n";
      echo "  <td bgcolor=\"#EFEEEA\">\n";
      echo "    <p align=\"right\">Credits:</td>\n";
      echo "  <td bgcolor=\"#EFEEEA\" align=\"left\">\n";
      echo "    <b><input type=\"text\" size=\"5\" name=\"credits\" value=\"".$userData['credits']."\"></b>\n";
      echo "  </td>\n";
      echo "</tr>\n";

      echo "<tr>\n";
      echo "  <td bgcolor=\"#EFEEEA\" align=\"right\">\n";
      echo "    Vacation Switch:";
      echo "  </td>\n";
      echo "  <td bgcolor=\"#EFEEEA\">\n";
      echo "    <b>$vacation</b>";
      echo "  </td>\n";
      echo "</tr>\n";

      echo " <tr>\n";
      echo "  <td bgcolor=\"#F4F4F4\">\n";
      echo "    <p align=\"right\">Member Status:&nbsp;</td>\n";
      echo "  <td bgcolor=\"#F4F4F4\">\n";
      echo "    <p align=\"left\"><b>"; if ($userData['status']=="mem") echo "Free Member"; if ($userData['status']=="pro") echo "Professional"; if ($userData['status']=="exe") echo "Executive"; echo "</b>\n";
      echo " </td>\n";
      echo "</tr>\n";

      echo "<tr>\n";
      echo "  <td bgcolor=\"#EFEEEA\">\n";
      echo "    <p align=\"right\">URL Trackers Created:&nbsp;</td>\n";
      echo "  <td bgcolor=\"#EFEEEA\">\n";
      echo "    <p align=\"left\"><b>$numURLs</b>\n";
      echo "  </td>\n";
      echo "</tr>\n";

      echo "<tr>\n";
      echo "  <td bgcolor=\"#F4F4F4\" align=\"right\">\n";
      echo "    Change User's Password To:\n";
      echo "  </td>\n";
      echo "  <td bgcolor=\"#F4F4F4\">\n";
      echo "    <input type=\"text\" name=\"password\">\n";
      echo "  </td>\n";
      echo "</tr>\n";

      echo "<tr>\n";
      echo "  <td bgcolor=\"#EFEEEA\">\n";
      echo "    <p align=\"right\">Num Days Inactive:</td>\n";
      echo "  <td bgcolor=\"#EFEEEA\">\n";
      echo "    <p align=\"left\"><b>$numDays</b> <i>Days since last log in.</i>\n";
      echo "  </td>\n";
      echo "</tr>\n";

    }

  ?>

  <tr>
    <td bgcolor="#F4F4F4" align="right">Date Signed Up:</td>
    <td bgcolor="#F4F4F4" align="left">
      <input type="text" size="30" name="datesignedup" value="<?=$userData['datesignedup']?>" READONLY />
    </td>
  </tr>

  <tr>
    <td bgcolor="#EFEEEA" align="right">Date Last Billed:</td>
    <td bgcolor="#EFEEEA" align="left">
      <input type="text" size="30" name="lastbilled" value="<?=$userData['datelastbilled']?>" READONLY />
    </td>
  </tr>

  <tr>
    <td colspan="2">
      <input type="hidden" name="todo" value="changememberdata">
      <input type="hidden" name="user" value="<?=$user?>">
      <br>
      <center><input type="submit" class="greenbutton" value="Apply Changes"></center>
    </td>
  </tr>

  </form>

</table>

<table style="border-left: solid 1px #000000;border-bottom: solid 1px #000000;border-top: solid 1px #000000;border-right: solid 1px #000000;" align="center" cellpadding="3" cellspacing="0" border="0" width="500">
  <?php
    if ($listtype=="Safelist [openlist]")
    {
      echo "<tr><td align=\"center\" colspan=\"2\"><h4>Change Member's Status Level</h4></td></tr>\n";
      echo "<tr>\n";
      echo "  <td align=\"right\" width=\"35%\">\n";
      echo "    <form name=\"status\" action=\"$_SERVER[PHP_SELF]\" method=\"POST\">\n";
      echo "    <input type=\"radio\" onClick=\""; if ($checkbilling) echo "checkStatus(this.form,'mem')"; else echo "this.form.submit()"; echo "\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"newstatus\" value=\"mem\"";
      if ($userData['status']=="mem") echo " CHECKED"; echo "></td><td align=\"left\">Free Member</td></tr>\n";
      echo "    <tr><td align=\"right\" width=\"35%\"><input type=\"radio\" onClick=\""; if ($checkbilling) echo "checkStatus(this.form,'pro')"; else echo "this.form.submit()"; echo "\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"newstatus\" value=\"pro\"";
      if ($userData['status']=="pro") echo " CHECKED"; echo "></td><td align=\"left\">Professional</td></tr>\n";
      echo "    <tr><td align=\"right\" width=\"35%\"><input type=\"radio\" onClick=\""; if ($checkbilling) echo "checkStatus(this.form,'exe')"; else echo "this.form.submit()"; echo "\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"newstatus\" value=\"exe\"";
      if ($userData['status']=="exe") echo " CHECKED"; echo "></td><td align=\"left\">Executive</td></tr>\n";
      echo "    <tr><td colspan=\"2\" valign=\"bottom\" align=\"center\"><input type=\"hidden\" name=\"todo\" value=\"changestatus\">\n";
      echo "    <input type=\"hidden\" name=\"s\" value=\"\">\n";
      echo "    <input type=\"hidden\" name=\"user\" value=\"$user\"></form><hr>\n";
      echo "</td></tr>\n";

      // change members paid status
      echo "<tr><td align=\"center\" colspan=\"2\"><h4>Change Member's Paid Status.</h4>\n";

      if ($userData['status']=="mem" OR $userData['memberpaid']==2)
      {
        if ($userData['status']=="mem")
          echo "Free Members are always concidered paid since they are FREE accounts.\n";
        else
          echo "This member is set as Immune and so does not have to pay.\n";

        echo "<br><br><hr></td></tr>\n";
      }
      else
      {
        echo "<form name=\"paid\" action=\"/mle/admin/showmember.php\" method=\"POST\">\n";
        echo "  Member Has <b>NOT</b> Paid <input onClick=\"this.form.submit();\" type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=paid value=0 "; if ($userData['memberpaid']==0) echo " CHECKED"; echo ">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n";
        echo "  Member Has Paid <input onClick=\"this.form.submit();\" type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=paid value=1 "; if ($userData['memberpaid']==1) echo " CHECKED"; echo ">\n";
        echo "      <input type=hidden name=todo value=setpaid>\n";
        echo "    <input type=\"hidden\" name=\"user\" value=\"$user\">\n";
        echo "</form><hr>\n";
      }

      // immunity check billing
      echo "<tr><td align=\"center\" colspan=\"2\"><h4>Immunity From the Check Billing?</h4>\n";

      if ($userData['status']=="mem")
        echo "Free Members are always Immune from the Billing Check System and will never be billed.\n";
      else
      {
        echo "<form name=\"immune\" action=\"/mle/admin/showmember.php\" method=\"POST\">\n";
        echo "  No <input onClick=\"this.form.submit();\" type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=immune value=1 "; if ($userData['memberpaid']!=2) echo " CHECKED"; echo ">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n";
        echo "  Yes <input onClick=\"this.form.submit();\" type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=immune value=2 "; if ($userData['memberpaid']==2) echo " CHECKED"; echo ">\n";
        echo "      <input type=hidden name=todo value=setimmune>\n";
        echo "    <input type=\"hidden\" name=\"user\" value=\"$user\">\n";
        echo "</form>\n";
        echo "No, means the member will be billed <b>$subtype</b>.\n<br>Yes, means they will not and never will as long as <i>immune</i>.\n";
      }
      echo "<br><br><hr></td></tr>\n";
    }

  ?>

  <tr>
    <td colspan="2">
      <p>Deleting a member will remove all records <b>including</b> all URLs and URL data they have accumulated.</p>
    </td>
  </tr>

  <tr>
    <td colspan="2" align="center">
      <form name="delete" action="/mle/admin/showmember.php" method="POST">
      <input type="hidden" name="user" value="<?=$user?>">
      <input type="hidden" name="todo" value="deletemember"><br>
      <input type="button" value="Delete Member" class="redbutton" onClick="confirmDelete(this.form)">
      </form>
    </td>
  </tr>

  <tr>
    <td align="center" colspan="2">
      <hr />
      <input type="button" value="Back to Main" class="beigebutton"
             onClick="location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php'; else echo 'mainlistowner.php'; ?>'"> |

      <input type="button" value="Back to Profiles" class="beigebutton"
             onClick="location.href='viewprofiles.php'" />
    </td>
  </tr>

</body>
</html>