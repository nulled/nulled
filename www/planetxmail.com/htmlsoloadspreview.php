<?php
require_once("/home/nulled/www/planetxmail.com/phpsecure/htmlsoloadspreview.inc");
?>
<html>
<head>
<title>Planet X Mail HTML SOLO ADs</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<script language="javascript" src="submitsupressor.js"></script>
<body>
<table cellSpacing="0" cellPadding="5" width="590" align=center border="1">
  <tr>
    <td>
      <center><img src="images/htmlsolo_ad_title.jpg"></center>
      <hr>
      <font face=verdana size=2>
      <center><font size="+3"><b>Step 2</b></font><br><font size="-2">HTML Solo AD submittion process</font></center><br>
      <font color="red"><b><?php if ($notValid) echo "$notValid<br>"?></b></font>

      <form name="soload" action="<?=$_SERVER[PHP_SELF]?>" method="POST" onClick="highlight(event)" onSubmit="submitonce(formname)">

      <b>Your name:</b><br>
      <input type="text" name="name" value="<?=$name?>" size="20">
      <br><br>

      <b>Your contact email:</b> Used for your receipt only.<br>
      <input type="text" name="email" value="<?=$email?>" size="40">

      <br /><br />
      <b>Credit URL:</b> People earn credits for reading your Solo AD and visiting your website.<br />
      <input type="text" name="crediturl" value="<?=$crediturl?>" size="80" maxlength="255"><br />
      <i>Example: http://yoursite.com/here.html</i>

      <br><br>

      <b>AD Subject:</b> 80 Characters Max.
      <br>
      <input type="text" name="subject" value="<?=$subject?>" size="80" MAXLENGTH="80">
      <input type="hidden" name="submitted" value="send">
      <input type="hidden" name="id" value="<?=$id?>">
      <br><br>
      <input type="submit" class="greenbutton" value="Submit Solo AD"> <a href="http://planetxmail.com/loadhtmlpreview.php?id=<?=$id?>" target="_blank"><font size="3"><b>Preview Your AD</b></font></a>
      </form>
      <p>
        <b>Read This!</b> - If your Subject line reads deceptive titles like, "Notification Of Payment Received", "Confirm your list address" or the like, your
        SOLO AD will NOT be sent.  Reason being, since I have 100+ safelists it makes members and List Owners mad and is not right to deceive people like that.
      </p>
      <p>
        <textarea name="Message" rows="4" cols="80">DISCLAIMER

        Although many clients get good results from Solo Ad mailings, we cannot guarantee results from using our service, as this largely depends on market demand for your product or service and your ability to write ads that create a desire for the product or service in the readers mind, and as such, we do Not offer refunds with Planet X Mail Solo Ads service.  We do however guarantee that your ad will reach the number of people ordered.</textarea>
      </p>
      <a href="http://planetxmail.com/htmlform.php?id=<?=$id?>"><font size="3"><b>Go Back and Edit Your Ad</b></font></a>
      </font>
    </td>
    <tr>
    <td align="center" valign="top">
      <br><font size="-1">All Rights Reserved &copy;2001-<?php echo date('Y'); ?><br>Planet X Mail<br>
      Contact: <a href="openticket.php">Support Team</a></font>
    </td>
  </tr>
  </tr>
</table>
</body>
</html>