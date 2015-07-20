<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/clientprofile.inc");
?>
<html>
<head>
<title><?=$program_name?> - List Profile</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript" src="../submitsupressor.js"></script>
<script language="javascript">
<!--
var focusedtest = false;
var focuseddesc = false;

function updateCount()
{
  if (focusedtest) document.client.counttestimonial.value = document.client.testimonial.value.length;
  else if (focuseddesc) document.client.countlistdescription.value = document.client.listdescription.value.length;

  if (document.client.testimonial.value.length > 500 || document.client.listdescription.value.length > 500)
  {
  	 document.client.testimonial.value = contenttestimonial;
	   document.client.listdescription.value = contentlistdescription;

	   document.client.counttestimonial.value = document.client.testimonial.value.length;
	   document.client.countlistdescription.value = document.client.listdescription.value.length;

  	alert('500 chars max!');
  }
	else
	{
	  contenttestimonial = document.client.testimonial.value;
	  contentlistdescription = document.client.listdescription.value;
	}
}

function presubmit(formname)
{
	if (confirm('Submitting this will set it to UNVERIFIED!\nWe will review the info you sent before\nit will be posted on our site.'))
		formname.submit();
}

document.onkeyup=updateCount;
//-->
</script>
</head>
<body onLoad="updateCount()">
<table width="600" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center">
    	<h2>List Profile for: <?=$_SESSION[aalistname]?></h2>
    	Profile is: <b><?php if ($verified) echo "Verified"; else echo "Unverified"; ?></b>
    	<p align="left">
    	Enter in the information below and we will place the List: <b><?=$_SESSION[aalistname]?></b> in our <a href="http://www.planetxmail.com/index.php?option=clients" target="_BLANK">Clients section</a>
    	on our VERY HIGH traffic sales site.  We will review your entry and make it <b>Verified</b> before you will see it appear on the <a href="http://www.planetxmail.com/index.php?option=clients" target="_BLANK">Clients section</a>.
    	We check for obsenity, etc.
    	<br><br><b>Note:</b> If you did not uploaded your own List Title Graphic then no image will appear.<br>Goto: Main Options->Title Graphic
    	<br><hr>
    	</p>
    	<p align="left">
    	<?php
    		if ($notValid) echo "<font color=\"red\"><b>$notValid</b></font><br><br>\n";
    		if ($titleIMG) echo "List Title Graphic:<br><img src=\"$titleIMG\" border=\"0\"><br>\n";
    	?>
    	<form name="client" action="<?=$_SERVER[PHP_SELF]?>" method="POST" onSubmit="submitonce(this)" onClick="highlight(event)">
	    	URL/Link to your List Sales page: <i>Your domain typically.</i><br>
	    	<b>http://</b> <input type="text" name="link" value="<?=$link?>" size="40"> DO NOT include the <b>http://</b> prefix.
	    	<br><br>
	    	Short description of your List: <i>500 characters max</i><br>
	    	<textarea cols="60" rows="10" name="listdescription" onFocus="focuseddesc=true;" onBlur="focuseddesc=false;"><?php echo stripslashes($listdescription); ?></textarea><br>
	    	<input type="text" name="countlistdescription" value="0" size="5" READONLY>
	    	<br><br>
	    	Short Testimonial about Planet X Mail: <i>500 characters max</i><br>
	    	<textarea cols="60" rows="10" name="testimonial" onFocus="focusedtest=true;" onBlur="focusedtest=false;"><?php echo stripslashes($testimonial); ?></textarea><br>
	    	<input type="text" name="counttestimonial" value="0" size="5" READONLY>
	    	<br>
	    	</p>
	    	<input type="button" onClick="presubmit(this.form)" class="greenbutton" value="Submit Form">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="button" value="Back to Main" class="beigebutton" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
	    	<input type="hidden" name="submitted" value="yes">
    	</form>
	  </td>
	</tr>
</table>
</body>
</html>
    	