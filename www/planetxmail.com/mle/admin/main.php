<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecureadmin.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/main.inc');

if ($noList)
{
  header("Location: createlist.php?firstList=$firstList");
  exit;
}
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
function confirmClear(formname)
{
  if (confirm('Sure you want to CLEAR this list?'))
    if (confirm('You will lose all members and their data!\nAre you sure?'))
      formname.submit();
}
function confirmDelete(formname)
{
  if (confirm('Sure you want to DELETE this list?'))
    if (confirm('You will lose all members and their data!\nAre you sure?'))
      if (confirm('As well as from being able to recreate it!\nAre you sure?'))
        formname.submit();
}
//-->
</script>
</head>
<body>
<table style="border-left: solid 1px #000000;border-bottom: solid 1px #000000;border-top: solid 1px #000000;border-right: solid 1px #000000;" align="center" cellpadding="3" cellspacing="0" border="0" width="500">
  <tr>
    <td align="center">
      <img src="../images/title.gif"><br>
      <?php
        if (($paid=="yes" || $paid=="1"))
          echo "<font size=\"4\"><b><font size=\"4\"><b>$timestr_next_bill</b> until next billing.</font>\n";
        else if (($paid=="no" || $paid=="0"))
          echo "<font size=\"4\"><font size=\"5\"><b>Bill is due for this list.</b></font><br>Billing started on: $date_bill_start<br>$timestr_late_bill since first bill was sent.</font><br>A bill was sent to: <b>$email</b> as well.<h3><a href=\"http://www.planetxmail.com/listpayment.php?id=$orderID&listtype=$type&p=$price&ex=$ex\" target=\"_BLANK\">Click Here To Pay</a></h3>After 15 days your List account will be disabled.";
        else if ($paid=="free2months")
          echo "<font size=\"4\">This List is Free for 1 month.</font><br><b>$days_free_left</b> day(s) left.";
        else if ($paid=="cancelled")
          echo "<font size=\"4\">This List is cancelled, but active.";
        else if ($paid=="notlisted")
          {}
      ?>
      <hr>
    </td>
  </tr>
  <tr>
    <td background="../images/main_bg_twirl.jpg" align="left">
      <div style="margin-left: 25%">
      <h4>List Owner: <b class="red"><i>
      <?php
        echo "$_SESSION[aalistownername]</i></b><br>\n";
        echo "List Name: <b class=\"red\"><i>$_SESSION[aalistname]</i></b><br>\n";
        echo "List Type: <b class=\"red\">$listtype[0]</b></h4>\n";
        echo "<font size=\"3\">Total members for all status:</font> <font size=\"4\"><b>$totalAll</b></font><br><br>\n";
        echo "<input type=\"button\" class=\"beigebutton\" value=\"View Profiles\" onClick=\"location.href='viewprofiles.php'\"><br><br>\n";
        echo "<font size=\"4\"><b>$memNum</b></font> <font size=\"3\">Free Member(s)</font><br>\n";
        echo "<font size=\"4\"><b>$proNum</b></font> <font size=\"3\">Professional(s)</font><br>\n";
        echo "<font size=\"4\"><b>$exeNum</b></font> <font size=\"3\">Executive(s)</font><br><br>\n";
        echo "<font size=\"4\"><b>$unvNum</b></font> <font size=\"3\">Unverified</font>\n";
      ?>
      </div>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="lightblue">
      <form name="search" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <b class="red"><?="$notValid<br>"?></b>
      <b>Search for User profile by:</b><br>
      <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="searchby" value="username"<?php if ($searchby=="username") echo " CHECKED"; else if ($searchby=="") echo " CHECKED"; ?>>&nbsp;User Name &nbsp;&nbsp;
      <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="searchby" value="email"<?php if ($searchby=="email") echo " CHECKED"; ?>>&nbsp;Contact Address &nbsp;&nbsp;
      <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="searchby" value="listemail"<?php if ($searchby=="listemail") echo " CHECKED"; ?>>&nbsp;List Address<br>
      <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="searchby" value="firstname"<?php if ($searchby=="firstname") echo " CHECKED"; ?>>&nbsp;First Name &nbsp;&nbsp;
      <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="searchby" value="lastname"<?php if ($searchby=="lastname") echo " CHECKED"; ?>>&nbsp;Last name<br>
      <input type="text" name="usertosearch" value="<?=$usertosearch?>" size="35">
      <br><br>
      <input type="submit" class="beigebutton" value="Search">
      <input type="hidden" name="submitted" value="search">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center">
    	<font size=+1><b>Main Options:</b></font><br><i>Click on an option:</i><br>
      <select size="<?php if ($listtype[0]!="Newsletter [closedlist]") echo "13"; else echo "9"; ?>" onChange="window.location.href=this.options[this.selectedIndex].value">
      	<option value="sendmail.php">Admin Mailer</option>
      	<?php if ($listtype[0]!="Newsletter [closedlist]" && $referer) echo "<option value=\"affiliatemanager.php\">Affiliate Manager</option>\n"; ?>
      	<option value="editbannedlist.php">Banned Domain List</option>
      	<option value="editmessages.php">Footers/Headers</option>
      	<?php if ($listtype[0]!="Newsletter [closedlist]") echo "<option value=\"edithomepage.php\">Home Pages</option>\n"; ?>
      	<option value="wizard.php">List Wizard</option>
      	<option value="changelistname.php">List Name</option>
      	<option value="clientprofile.php">List Profile</option>
      	<option value="changelistownername.php">List Owner User Name</option>
      	<?php if ($listtype[0]!="Newsletter [closedlist]") echo "<option value=\"editpaymenthtml.php\">Manually Edit PayLinks</option>\n"; ?>
      	<option value="addchangetitle.php">Title Graphic</option>
      	<?php if ($listtype[0]!="Newsletter [closedlist]") echo "<option value=\"editupgradeinfo.php\">Upgrade Info Pages</option>\n"; ?>
	      <?php if ($listtype[0]!="Newsletter [closedlist]") echo "<option value=\"viewtransactions.php\">View Transactions</option>\n"; ?>
      </select>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="lightblue">
    	<br>
      <input type="button" value="List Stats" class="beigebutton" onClick="location.href='liststats.php?time=<?=$time?>'">
      <input type="button" value="List Graphs" class="beigebutton" onClick="location.href='listgraphs.php?time2=<?=$time2?>'">
      <input type="button" value="Current Members" class="beigebutton" onClick="location.href='mms.php'"><br>
      <br>
    </td>
  </tr>
  <tr>
    <td bgcolor="#99CCCC" align="center">
      <br>
      <p>This section is used to set up the Banners and AD space you want to sell to List Members.  You can use them for your own use as well.</p>
      <?php
          if ($listtype[0]!="Newsletter [closedlist]")
          {
            echo "<font size=\"+1\"><b>Seen After Sending an AD:</b><br>\n";
            echo "<select onChange=\"window.location.href=this.options[this.selectedIndex].value\">\n";
            echo "	<option>Choose One:</option>\n";
            echo "	<option value=\"adbanners.php\">Add a Banner</option>\n";
            echo "	<option value=\"listbanners.php\">Edit Banners</option>\n";
            echo "	<option value=\"postad.php\">Add a BillBoard</option>\n";
            echo "	<option value=\"listads.php\">Edit BillBoards</option>\n";
            echo "</select><br><br>\n";
          }
       ?>
      <font size="+1"><b>Banner Rotation:</b><br>
      <select onChange="window.location.href=this.options[this.selectedIndex].value">
      	<option>Choose One:</option>
      	<option value="addpersonalbanner.php">Add a Rotating Banner</option>
			  <option value="listbannerads.php">Edit/View Rotating Banners</option>
      </select>
      <br><br>
    </td>
  </tr>

  <tr>
    <td bgcolor="beige" align="center">
      <br>
      <b>Sign-Up Link</b>:<br><input type="text" value="<?="http://www.planetxmail.com/mle/signup.php?l=$listhash"?>" size="50" READONLY><br><br>
      <?php if ($listtype[0]!="Newsletter [closedlist]") echo "<b>Log-In Link</b>:<br><input type=\"text\" value=\"http://www.planetxmail.com/mle/login.php?l=$listhash\" size=\"50\" READONLY><br><br>\n"; ?>
    </td>
  </tr>

  <tr>
    <td bgcolor="white" align="center">
      <h3>Convert Process Order Tag</h3>
    <?php

    if ($converted) echo "$converted";

    echo '
      <form name="convert" action="'.$_SERVER[PHP_SELF].'" method="POST">
        <input type=text" name="convert" size="25" />
        <br />
        <input type="submit" value="Convert" />
        <input type="hidden" name="submitted" value="convert" />
      </form>
    ';

    ?>

    </td>
  </tr>

  <?php
      if ($listtype[0]!="Newsletter [closedlist]")
      {
        echo "<tr>\n";
        echo "  <td bgcolor=\"lightgrey\" align=\"center\">\n";
        echo "    <br>\n";
        echo "    <b>Mailing Rules</b>\n";
        echo "    <form name=\"changemailingrule\" action=\"$_SERVER[PHP_SELF]\" method=\"POST\">\n";
        echo "    <input onClick=\"this.form.submit();\" type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"mailingrule\" value=\"0\""; if ($mailingrule[0]=="0") echo "CHECKED"; echo ">&nbsp;OFF\n";
        echo "    &nbsp;&nbsp;<input onClick=\"this.form.submit();\" type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"mailingrule\" value=\"1\""; if ($mailingrule[0]=="1") echo "CHECKED"; echo ">&nbsp;Rule 1\n";
        echo "    &nbsp;&nbsp;<input onClick=\"this.form.submit();\" type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"mailingrule\" value=\"2\""; if ($mailingrule[0]=="2") echo "CHECKED"; echo ">Rule 2<br><br>\n";
        echo "    <p align=left>\n";
        echo "    <b>Rule OFF:</b> No rule applies and all receive from all.<br>\n";
        echo "    <b>Rule 1:</b> Exec receive mail from Exec and Pro. Pro receive from Pro and Exec. Free receive all.<br>\n";
       	echo "    <b>Rule 2:</b> Exec receive mail from Exec ONLY, Pro receive from Pro and Exec. Free receive all.<br>\n";
        echo "    </p>\n";
        echo "    <input type=\"hidden\" name=\"submitted\" value=\"changemailingrule\">\n";
        echo "    </form>\n";
        echo "  </td>\n";
        echo "</tr>\n";
      }
    ?>
  <tr>
    <td bgcolor="lightblue" align="center">
      <form name="createlist" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <br>
      <b>Add an Empty List for this List Owner: <b class="red"><?=$_SESSION[aalistownername]?></b></b><br><br>
      <input type="button" class="bluebutton" value="Add Empty List" onClick="if (confirm('The new list will appear in the CHANGE LIST section.\nAnd named EmptyList.\nHit OK to create the empty list.')) this.form.submit();">
      <input type="hidden" name="submitted" value="createlist">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center">
      <br>
      Will clear <b>all</b> members, their URL trackers and URL data.<br>
      <h5>Current list: <b class="red"><?=$_SESSION[aalistname]?></b></h5>
      <form name="clearlist" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <input type="button" value="Clear List" class="redbutton" onClick="confirmClear(this.form)">
      <input type="hidden" name="submitted" value="clearlist">
      </form>
    </td>
  </tr>
  <tr>
    <td bgcolor="beige" align="center">
      <br>
      <form name="changelist" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <h4>Change / Create List:</h4>
      Currently Selected List: <b><?=$_SESSION[aalistname]?></b><br>
      <select name="list" onChange="this.form.submit()">
      <option>Choose One:</option>
      <?php
        $i = 1;
        while (list($aList) = mysqli_fetch_row($lists))
        {
          if (substr($aList, 0, 3)=="new")
          {
            echo "<option value=\"$aList\">EmptyList$i</option>\n";
            $i++;
          }
          else
            echo "<option value=\"$aList\">$aList</option>\n";
        }
      ?>
      </select>
      <input type="hidden" name="submitted" value="changelist">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="lightgrey">
      <br>
      <font color="black">Will reset the listowner <b>PASSWORD</b> to 111111.  When they login they will be asked to CHANGE the password to a new one.<br>
      <h5>Current List Owner: <b class="red"><?=$_SESSION[aalistownername]?></b></h5></font>
      <form name="resetpassword" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <input type="button" value="Reset Password" class="bluebutton" onClick="javascript: if (confirm('Reset List Owner password to 111111?\nAre you sure?')) this.form.submit();">
      <input type="hidden" name="submitted" value="resetpassword">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="maroon">
      <br>
      <font color="white"><b>Will DELETE all members, their URL trackers and URL data as well as the List itself.</b><br>
      <h5>Current list: <b class="red"><?=$_SESSION[aalistname]?></b></h5></font>
      <form name="deletelist" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <input type="button" value="DELETE List" class="redbutton" onClick="confirmDelete(this.form)">
      <input type="hidden" name="submitted" value="deletelist">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="pink">
      <br>
      <b>Will DELETE this Listowner and all members, their URL trackers and URL data as well as <b>ALL</b> Lists that belong to this List Owner.<br>
      <h5>Current List Owner: <?=$_SESSION[aalistownername]?></h5></b>
      <input type="button" value="DELETE List Owner" class="redbutton" onClick="javascript:if (confirm('This will DELETE the List Owner!\nAre you sure?')) if (confirm('All of the List Owners members will be gone too!\nAre you sure?')) location='deletelistowner.php';">
      <br><br>
    </td>
  </tr>
  <tr>
		<td align="center">
			<font size="4"><b>Change List Owner:</b></font><br>
	    <select onChange="window.location.href=this.options[this.selectedIndex].value">
	    	<option>Choose One:</option>
	    	<?php while (list($oID, $oname) = mysqli_fetch_row($listowners)) echo "  	<option value=\"changelistowner.php?id=$oID&list=$oname\">$oname</option>\n";   ?>
	    </select>
	  </td>
	</tr>
  <tr>
    <td align="center">
      <hr><br><input type="button" value="Log Off" class="redbutton" onClick="javascript:location.href='logout.php?a=aq1sw2de3'"><br><br>
    </td>
  </tr>
</table>
</body>
</html>
