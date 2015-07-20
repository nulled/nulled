<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/main.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
function confirmClear(formname)
{
  if (confirm('Sure you want to CLEAR this ELP Owner?'))
    if (confirm('You will lose all members and their data!\nAre you sure?'))
      formname.submit();
}
function confirmDelete(formname)
{
  if (confirm('Sure you want to DELETE this ELP Owner?'))
    if (confirm('You will lose all members and their data!\nAre you sure?'))
      if (confirm('All trace will be gone!\nAre you sure?'))
        formname.submit();
}
//-->
</script>
</head>
<body>
<table align="center" cellpadding="3" cellspacing="0" border="1" width="500">
  <tr>
    <td align="center"><img src="../images/elplogo.jpg"></td>
  </tr>
  <tr>
    <td bgcolor="beige" align="center">
      <font size="+2">ELP Owner: <font color="red"><b><i><?=$_SESSION[aaelp]ownername?></i></b></font></font><br><br>
      <font size="+1"><b><i>NEW VERSION!!!</i></b> Ezy-List Pro / LITE Version: <b>2.1 FINAL</b></font>
      <br>Contact: <b>accounts@planetxmail.com</b> for Tech Questions.<br>
      <a href="http://www.planetxmail.com/downloads/" target="_blank">Download Ezy-List Versions</a>
      <h4>Total Members: <?=$totalMem?></h4>
      <?php
      if ($liteNum>0)
      {
        echo "<form action=\"$_SERVER[PHP_SELF]\" method=\"POST\"><font size=\"+1\"><b>Paid LITE:</b></font><select name=\"member\">\n";
        while (list($username) = mysqli_fetch_row($liteData))
          echo "<option value=\"$username\">$username</option>\n";
        echo "</select>\n";
        echo "<input type=\"submit\" class=\"greenbutton\" value=\"Get Profile\">&nbsp;&nbsp;$liteNum\n";
        echo "<input type=\"hidden\" name=\"submitted\" value=\"getprofile\"></form>\n";
      }
      else
        echo "<b><font size=\"+1\">Paid LITE Members:</font></b><i>None</i><br>\n";

      if ($unvliteNum>0)
      {
        echo "<form action=\"$_SERVER[PHP_SELF]\" method=\"POST\"><font size=\"+1\" color=\"red\"><b>Unpaid LITE:</b></font><select name=\"member\">\n";
        while (list($username) = mysqli_fetch_row($unvliteData))
          echo "<option value=\"$username\">$username</option>\n";
        echo "</select>\n";
        echo "<input type=\"submit\" class=\"bluebutton\" value=\"Get Profile\">&nbsp;&nbsp;$unvliteNum\n";
        echo "<input type=\"hidden\" name=\"submitted\" value=\"getprofile\"></form>\n";
      }
      else
        echo "<b><font size=\"+1\">Unpaid LITE Members:</font></b><i>None</i><br>\n";

      if ($memNum>0)
      {
        echo "<form action=\"$_SERVER[PHP_SELF]\" method=\"POST\"><font size=\"+1\"><b>Paid PRO:</b></font><select name=\"member\">\n";
        while (list($username) = mysqli_fetch_row($memData))
          echo "<option value=\"$username\">$username</option>\n";
        echo "</select>\n";
        echo "<input type=\"submit\" class=\"greenbutton\" value=\"Get Profile\">&nbsp;&nbsp;$memNum\n";
        echo "<input type=\"hidden\" name=\"submitted\" value=\"getprofile\"></form>\n";
      }
      else
        echo "<b><font size=\"+1\">PRO Members:</font></b><i>None</i><br>\n";

      if ($unvNum>0)
      {
        echo "<form action=\"$_SERVER[PHP_SELF]\" method=\"POST\"><font size=\"+1\" color=\"red\"><b>Unpaid PRO:</b></font><select name=\"member\" onChange=\"this.manual.onClick = location.href='manualverify.php?elpmember=' + this.options[this.selectedIndex].value\">\n";
        while (list($username) = mysqli_fetch_row($unvData))
          echo "<option value=\"$username\">$username</option>\n";
        echo "</select>\n";
        echo "<input type=\"submit\" class=\"bluebutton\" value=\"Get Profile\">&nbsp;&nbsp;$unvNum\n";
        echo "<input type=\"hidden\" name=\"submitted\" value=\"getprofile\"></form>\n";
      }
      else
        echo "<font size=\"+1\"><b>Unpaid PRO Members:</b></font><i>None</i>\n";
      ?>
      <p>
        Unpaid members will be AUTOMATICALLY re-mailed the confirmation link everyday until the 7th day in which time the Unpaid will be deleted automatically.<br>
      </p>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="lightblue">
      <form name="search" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <font color="red"><b><?="$notValid<br>"?></b></font>
      <b>Get Member Profile By:</b><br><br>
      <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="searchby" value="username"<?php if ($searchby=="username") echo " CHECKED"; else if ($searchby=="") echo " CHECKED"; ?>>User Name&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="searchby" value="email"<?php if ($searchby=="email") echo " CHECKED"; ?>>Email<br>
      <input type="text" name="usertosearch" value="<?=$usertosearch?>" size="35">
      <br><br>
      <input type="submit" class="beigebutton" value="Search">
      <input type="hidden" name="submitted" value="search">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center">
    	<h3>Main Options:</h3>
      <select size="<?php if ($_SESSION['aaadminpsk']) echo "4"; else echo "3"; ?>" onChange="window.location.href=this.options[this.selectedIndex].value">
      	<option value="sendmail.php">Send Mail</option>
      	<option value="editconfig.php">Edit Configuration</option>
      	<option value="transactions.php">Transactions</option>
      	<?php if ($_SESSION['aaadminpsk']) echo "<option value=\"getsyssummary.php\">Get System Summary</option>\n"; ?>
      </select>
      <br>
      <br>
      <a href="#" onClick="window.open('gettingstarted.php',0,'height=500,width=550,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')"><b>Getting Started</b></a>
      <br>
    </td>
  </tr>
  <tr>
  	<td bgcolor="pink" align="center">
  		<br>
  		<b>Pro Member Signup URL</b><br>
  		<input type="text" name="signupurl" value="http://www.planetxmail.com/elp/signup.php?o=<?=$_SESSION[aaelp]ownername?>" size="80">
  		<br>
  		<b>LITE Member Signup URL</b><br>
  		<input type="text" name="signupurl" value="http://www.planetxmail.com/elp/signuplite.php?o=<?=$_SESSION[aaelp]ownername?>" size="80">
  		<br>
  	</td>
  </tr>
  <tr>
    <td align="center" bgcolor="lightgrey">
    	<br>
    	<?php if (! $_SESSION['aaadminpsk']) echo "<font color=\"black\">Will reset your <b>PASSWORD</b> to 111111.  You should then re-login to CHANGE the password to a new one ASAP.<br>\n"; ?>
      <?php if ($_SESSION['aaadminpsk']) echo "<font color=\"black\">Will reset the ELP Owner <b>PASSWORD</b> to 111111.  When they login they will be asked to CHANGE the password to a new one.<br>\n"; ?>
      <?php if ($_SESSION['aaadminpsk']) echo "<h4>Current ELP Owner: $_SESSION[aaelp]ownername</h4>\n"; ?>
      <form name="resetpassword" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <input type="button" value="Reset Password" class="bluebutton" onClick="javascript: if (confirm('Reset ELP Owner password to 111111?\nAre you sure?')) this.form.submit();">
      <input type="hidden" name="submitted" value="resetpassword">
      </form>
    </td>
  </tr>
  <?php
	  if ($_SESSION['aaadminpsk'])
	  {
		  echo "<tr>\n";
		  echo "  <td align=\"center\" bgcolor=\"maroon\">\n";
		  echo "    <br>\n";
		  echo "    <font color=\"white\"><b>Will DELETE this ELP Owner and ALL members and entirly wipe this ELP Owner!</font><br><br>\n";
		  echo "    <font color=\"yellow\">Current ELP Owner: <b>$_SESSION[aaelp]ownername</b></font><br><br>\n";
		  echo "    <form name=\"deleteelpowner\" action=\"$_SERVER[PHP_SELF]\" method=\"POST\">\n";
		  echo "    <input type=\"hidden\" name=\"submitted\" value=\"deleteelpowner\">\n";
		  echo "    <input type=\"button\" value=\"DELETE ELP Owner\" class=\"redbutton\" onClick=\"javascript:confirmDelete(this.form)\">\n";
		  echo "    </form>\n";
		  echo "  </td>\n";
		  echo "</tr>\n";

			echo "<tr>\n";
			echo "	<td align=\"center\">\n";
			echo "		<h3>Change ELP Owner:</h3>\n";
	    echo "  	<select onChange=\"window.location.href=this.options[this.selectedIndex].value\">\n";
	    echo "  	<option>Choose One:</option>\n";
	    while (list($o) = mysqli_fetch_row($elpowners))
	    	echo "  	<option value=\"changeelpowner.php?o=$o\">$o</option>\n";
	    echo "  	</select>\n";
			echo "	</td>\n";
			echo "</tr>\n";
		}
	?>
  <tr>
    <td align="center">
      <br><input type="button" value="Log Off" class="beigebutton" onClick="javascript:location.href='logout.php'"><br><br>
    </td>
  </tr>
</table>
</body>
</html>

