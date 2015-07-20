<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/mainlistowner.inc');

if ($noList)
{
  header('Location: createlistlistowner.php?firstList=1');
  exit;
}
?>
<html>
<head>
<title><?=$program_name?> - List Owner - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
function confirmDelete(formname)
{
  if (confirm('Sure you want to delete this list?'))
    if (confirm('You will lose all members and their data!\nAre you sure?'))
      formname.submit();
}
//-->
</script>
</head>
<body>
<table style="border: 1px solid #000000" align="center" cellpadding="3" cellspacing="0" border="0" width="500">
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
        echo $_SESSION['aalistownername'] . '</i></b><br />
        List Name: <b class="red"><i>' . $_SESSION['aalistname'] . '</i></b><br />
        List Type: <b class="red">' . $listtype[0] . '</b></h4>
        <font size="3">Total members for all status:</font> <font size="4"><b>' .$totalAll . '</b></font><br /><br />
        <input type="button" class="beigebutton" value="View Profiles" onClick="location.href=\'viewprofiles.php\'"><br /><br />
        <font size="4"><b>' . $memNum . '</b></font> <font size="3">Free Members(s)</font><br />
        <font size="4"><b>' . $proNum . '</b></font> <font size="3">Professional(s)</font><br />
        <font size="4"><b>' . $exeNum . '</b></font> <font size="3">Executive(s)</font><br /><br />
        <font size="4"><b>' . $unvNum . '</b></font> <font size="3">Unverified</font>
        '
      ?>
      </div>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="lightblue">
      <form name="search" action="/mle/admin/mainlistowner.php" method="POST">
      <b class="red"><?="$notValid<br />"?></b>
      <b>Search for User profile by:</b><br>
      <input type="radio" style="border-width:0px" name="searchby" value="username"<?php if ($searchby == 'username') echo ' CHECKED '; else if (! $searchby) echo ' CHECKED '; ?>>&nbsp;User Name &nbsp;&nbsp;
      <input type="radio" style="border-width:0px" name="searchby" value="email"<?php if ($searchby == 'email') echo ' CHECKED '; ?>>&nbsp;Contact Address &nbsp;&nbsp;
      <input type="radio" style="border-width:0px" name="searchby" value="listemail"<?php if ($searchby == 'listemail') echo ' CHECKED '; ?>>&nbsp;List Address<br />
      <input type="radio" style="border-width:0px" name="searchby" value="firstname"<?php if ($searchby == 'firstname') echo ' CHECKED '; ?>>&nbsp;First Name &nbsp;&nbsp;
      <input type="radio" style="border-width:0px" name="searchby" value="lastname"<?php if ($searchby == 'lastname') echo ' CHECKED '; ?>>&nbsp;Last name<br />
      <input type="text" name="usertosearch" value="<?=$usertosearch?>" size="35">
      <br><br>
      <input type="submit" class="beigebutton" value="Search">
      <input type="hidden" name="submitted" value="search">
      </form>
    </td>
   </tr>
   <tr>
    <td align="center">
    	<font size=+1><b>Main Options:</b></font><br />
    	<i>Click on an option:</i><br />
      <select size="<?php if ($listtype[0] != 'Newsletter [closedlist]') echo '13'; else echo '9'; ?>" onChange="window.location.href=this.options[this.selectedIndex].value">
      	<option value="sendmail.php">Admin Mailer</option>
      	<?php if ($listtype[0] != 'Newsletter [closedlist]' AND $referer) echo '<option value="affiliatemanager.php">Affiliate Manager</option>'."\n"; ?>
      	<option value="editbannedlist.php">Banned Domain List</option>
      	<option value="editmessages.php">Footers/Headers</option>
      	<?php if ($listtype[0] != 'Newsletter [closedlist]') echo '<option value="edithomepage.php">Home Pages</option>'."\n"; ?>
      	<option value="wizard.php">List Wizard</option>
      	<option value="changelistname.php">List Name</option>
      	<option value="clientprofile.php">List Profile</option>
      	<option value="changelistownername.php">List Owner User Name</option>
      	<?php if ($listtype[0] != 'Newsletter [closedlist]') echo '<option value="editpaymenthtml.php">Manually Edit PayLinks</option>'."\n"; ?>
      	<option value="addchangetitle.php">Title Graphic</option>
      	<?php if ($listtype[0] != 'Newsletter [closedlist]') echo '<option value="editupgradeinfo.php">Upgrade Info Pages</option>'."\n"; ?>
	      <?php if ($listtype[0] != 'Newsletter [closedlist]') echo '<option value="viewtransactions.php">View Transactions</option>'."\n"; ?>
      </select>
      <br><br>
      <a href="http://planetxmail.com/mle/manuals/" target="_BLANK">List Owner's Guide</a>
      <br>
    </td>
   </tr>
    <tr>
    <td align="center" bgcolor="lightblue">
    	<br>
      <input type="button" value="Members Currently Logged In" class="beigebutton" onClick="location.href='mms.php'">
      <br />
    </td>
  </tr>
    <tr>
      <td bgcolor="#99CCCC" align="center">
        <br />
        <p>This section is used to set up the Banners and AD space you want to sell to List Members.  You can use them for your own use as well.</p>
        <?php
          if ($listtype[0] != 'Newsletter [closedlist]')
          {
            echo '
            <font size="+1"><b>Seen After Sending an AD:</b><br >
            <select onChange="window.location.href=this.options[this.selectedIndex].value">
            <option>Choose One:</option>
            <option value="adbanners.php">Add a Banner</option>
            <option value="listbanners.php">Edit Banners</option>
            <option value="postad.php">Add a BillBoard</option>
            <option value="listads.php">Edit BillBoards</option>
            </select><br /><br />
            ';
          }
       ?>
        <font size="+1"><b>Banner Rotation:</b><br>
        <select onChange="window.location.href=this.options[this.selectedIndex].value">
        	<option>Choose One:</option>
        	<option value="addpersonalbanner.php">Add a Rotating Banner</option>
  			  <option value="listbannerads.php">Edit/View Rotating Banners</option>
        </select>
        <br /><br />
      </td>
    </tr>
    <tr>
      <td bgcolor="beige" align="center">
	      <b>Sign-Up Link</b>:<br /><input type="text" value="<?='http://planetxmail.com/mle/signup.php?l=' . $listhash?>" size="40" readonly="readonly" /><br /><br />
      	<?php if ($listtype[0] != 'Newsletter [closedlist]') echo '<b>Log-In Link</b>:<br /><input type="text" value="http://planetxmail.com/mle/login.php?l=' . $listhash . '" size="40" readonly="readonly" /><br /><br />'."\n"; ?>
	    </td>
    </tr>
    <?php
      if ($listtype[0] != 'Newsletter [closedlist]')
      {
        echo '
        <tr>
        <td bgcolor="lightgrey" align="center">
        <br />
        <b>Mailing Rules</b>
        <form name="changemailingrule" action="/mle/admin/mainlistowner.php" method="POST">
        <input onClick="this.form.submit()" type="radio" style="border-width:0px" name="mailingrule" value="0"'; if ($mailingrule[0] == '0') echo ' CHECKED '; echo '>&nbsp;OFF';
        echo '&nbsp;&nbsp;<input onClick="this.form.submit()" type="radio" style="border-width:0px" name="mailingrule" value="1"'; if ($mailingrule[0] == '1') echo ' CHECKED '; echo '>&nbsp;Rule 1';
        echo '&nbsp;&nbsp;<input onClick="this.form.submit()" type="radio" style="border-width:0px" name="mailingrule" value="2"'; if ($mailingrule[0] == '2') echo ' CHECKED '; echo '>Rule 2<br /><br />';
        echo '
        <p align="left">
        <b>Rule OFF:</b> No rule applies and all receive from all.<br />
        <b>Rule 1:</b> Exec receive mail from Exec and Pro. Pro receive from Pro and Exec. Free receive all.<br />
       	<b>Rule 2:</b> Exec receive mail from Exec ONLY, Pro receive from Pro and Exec. Free receive all.<br />
        </p>
        <input type="hidden" name="submitted" value="changemailingrule" />
        </form>
        </td>
        </tr>
        ';
      }
    ?>
  <tr>
    <td bgcolor="lightblue" align="center">
      <form name="changelist" action="/mle/admin/mainlistowner.php" method="POST">
      <h4>Change / Create List:</h4>
      Currently Selected List: <b><?=$_SESSION['aalistname']?></b><br>
      <select name="list" onChange="this.form.submit()">
      <option>Choose One:</option>
      <?php
        $i = 1;
        while (list($aList) = mysqli_fetch_row($lists))
        {
          if (substr($aList, 0, 3) == 'new')
          {
            echo '<option value="' . $aList . '">EmptyList' . $i . '</option>'."\n";
            $i++;
          }
          else
            echo '<option value="' . $aList . '">' . $aList . '</option>'."\n";
        }
      ?>
      </select>
      <input type="hidden" name="submitted" value="changelist" />
      </form>
    </td>
  </tr>

  <tr>
    <td align="center" bgcolor="lightgrey">
      <br>
      <font color="black">Will reset the listowner <b>PASSWORD</b> to 111111.  When you next Log In you will be asked to CHANGE the password to a new one.<br>
      <h5>Current List Owner: <b class="red"><?=$_SESSION['aalistownername']?></b></h5></font>
      <form name="resetpassword" action="/mle/admin/mainlistowner.php" method="POST">
      <input type="button" value="Reset Password" class="bluebutton" onClick="if (confirm('Reset List Owner password to 111111?\nAre you sure?'))this.form.submit();">
      <input type="hidden" name="submitted" value="resetpassword">
      </form>
    </td>
  </tr>

  <tr>
    <td align="center">
      <br><input type="button" value="Log Off" class="redbutton" onClick="location.href='logout.php'"><br><br>
    </td>
  </tr>
</table>
</body>
</html>

