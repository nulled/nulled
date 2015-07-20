<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/addchangetitle.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Add\Change Title Graphics</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table width="500" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center" colspan="2">
      <p><h4>Your Title Graphic</h4><br>
      This graphic <b>jpeg</b> or <b>gif</b> will appear as the title graphic for your ELP.  On the signup\login.<br>
      If left blank will default to the one provided by the system.</p>
      <font color="red"><b><? if ($notValid) echo $notValid."<br>"; ?></b></font>
    </td>
  </tr>
  <tr>
    <td align="center" colspan="2"><img src="<?=$titleIMG?>" border="0"></td>
  </tr>
  <tr>
    <td align="right"><form name="edittitle" action="<?=$_SERVER[PHP_SELF]?>" ENCTYPE="multipart/form-data" method="POST"></td>
    <td><input type="file" name="title">&nbsp;&nbsp;&nbsp;<input type="checkbox" name="useDefault" value="yes">Use Default Title Image</td>
  </tr>
  <tr>
    <td><input type="submit" class="greenbutton" value="Submit"></td>
    <td align="right">
    	<input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='main.php'">
    	<input type="hidden" name="submitted" value="change">
    	</form>
    </td>
  </tr>
</table>
</body>
</html>