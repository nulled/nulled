<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("../mlpsecure/config/config.inc");
include("adminsecure/sendmailhtml.inc");
?>
<html>
<head>
<title><?=$program_name?> - Admin Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
document.onkeyup=updateCount;
var focused = false;
var focusedhtml = false;
function updateCount()
{
  if (focused) document.sendmail.countmessage.value = document.sendmail.nlmessage.value.length;
  if (focusedhtml) document.sendmail.countmessagehtml.value = document.sendmail.nlhtmlmessage.value.length;
}

function checkBoxes(formname, savetodb)
{
  var saved = <?=$saved?>;

  if (savetodb==0)
  {
    if (saved==false)
    {
      alert('You need to save message to database before you send your message.\nNote: The subject is not saved.');
      return;
    }
  }

  // check HTML values
  if (document.sendmail.nlhtmlsubject.value.length == 0)
  {
    alert('HTML subject field is empty.');
    return;
  }

  if (document.sendmail.nlhtmlmessage.value.length == 0)
  {
    alert('HTML message body is empty.');
    return;
  }

  if (document.sendmail.nlhtmlsubject.value.length > 80)
  {
    alert('HTML subject length can not exceed 80 characters.');
    return;
  }

  if (document.sendmail.nlhtmlmessage.value.length > 20000)
  {
    alert('HTML message body can not exceed 20000 characters.');
    return;
  }

  // check plain text values
  if (document.sendmail.nlsubject.value.length == 0)
  {
    alert('Plain text subject field is empty.');
    return;
  }

  if (document.sendmail.nlmessage.value.length == 0)
  {
    alert('Plain text message body is empty.');
    return;
  }

  if (document.sendmail.nlsubject.value.length > 80)
  {
    alert('Plain text subject length can not exceed 80 characters.');
    return;
  }

  if (document.sendmail.nlmessage.value.length > 20000)
  {
    alert('Plain text message body Plain Text can not exceed 20000 characters.');
    return;
  }

  var data = 'maillisthtml.php';
  var whattype = '';

  if (document.sendmail.format[0].checked)
  {
    whattype = 'HTML';
    data += '?isHTML=1';
  }
  else
  {
    whattype = 'PLAIN TEXT';
    data += '?isHTML=0';
  }

  if (savetodb)
  {
    document.sendmail.nlhtmlsubject.disabled=0;
    document.sendmail.nlhtmlmessage.disabled=0;
    document.sendmail.nlsubject.disabled=0;
    document.sendmail.nlmessage.disabled=0;
    formname.submit();
  }
  else
  {
    if (confirm('Remember you must save the messages after ALL changes are make.\nOtherwise you may not be sending the message you intended to.\nHit OK to send.'))
      if (confirm('Sending as: '+whattype+'.\nClick OK to mail.'))
        location.href = data;
  }
}
//-->
</script>
</head>
<body onLoad="<?php if ($format=="html" || ! $format) echo "document.sendmail.nlhtmlsubject.disabled=0; document.sendmail.nlhtmlmessage.disabled=0; document.sendmail.nlsubject.disabled=1; document.sendmail.nlmessage.disabled=1"; else echo "document.sendmail.nlhtmlsubject.disabled=1; document.sendmail.nlhtmlmessage.disabled=1; document.sendmail.nlsubject.disabled=0; document.sendmail.nlmessage.disabled=0"; ?>">
<table cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table width="590" cellpadding="3" cellspacing="0" align="center" border="0">
        <tr>
          <td colspan="2" align="center">
            <form name="sendmail" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
            <font color="#005F8C" size="+1"><b>Send Mail - NewsLetter - HTML or Plain Text.</b></font>
            <br><br>
            Tags below will be replaced with each members details:
            <ul>
              <li><b>[first_name]</b> - Replaced with the member's <b>First Name</b></li>
              <li><b>[last_name]</b> - Replaced with the member's <b>Last Name</b></li>
            </ul>
          </td>
        </tr>
        <tr>
          <td bgcolor="lightgrey" align="center" colspan="2">
            <font size="3">Select <b>format type</b> to send NewsLetter as.</font><br>
            <input type="radio" onClick="document.sendmail.nlhtmlsubject.disabled=0; document.sendmail.nlhtmlmessage.disabled=0; document.sendmail.nlsubject.disabled=1; document.sendmail.nlmessage.disabled=1;" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="format" value="html"<?php if ($format=="html"||$format=="") echo " CHECKED"; ?>>HTML&nbsp;&nbsp;&nbsp;&nbsp;
            <input type="radio" onClick="document.sendmail.nlhtmlsubject.disabled=1; document.sendmail.nlhtmlmessage.disabled=1; document.sendmail.nlsubject.disabled=0; document.sendmail.nlmessage.disabled=0;" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="format" value="plain"<?php if ($format=="plain") echo " CHECKED"; ?>>Plain Text
          </td>
        </tr>
        <tr>
          <td bgcolor="beige" colspan="2" align="center">
            <br>
          	<font color="red" size="3"><b><?php if ($notValid) echo "$notValid<br><br>"; ?></b></font>
            <h3>HTML NewsLetter</h3>
            All images must have a full URL.<br><i>Example:</i> &#60;img src="http://www.whatever.com/myimage.jpg"&#62;.
          </td>
        </tr>
<!-- HTML BASED message -->
        <tr>
          <td bgcolor="beige" align="right">
            Subject <b>HTML</b>:
          </td>
          <td bgcolor="beige" >
            <input type="text" name="nlhtmlsubject" size="80" value="<?=$nlhtmlsubject?>">
          </td>
        </tr>
        <tr>
          <td bgcolor="beige" align="right" valign="top">
            Message <b>HTML</b>:
          </td>
          <td bgcolor="beige" >
            <textarea wrap="OFF" rows="20" cols="<?=$email_wordwrap_length?>" name="nlhtmlmessage" onFocus="focusedhtml=true;" onBlur="focusedhtml=false;"><?=$nlhtmlmessage?></textarea>
          </td>
        </tr>
        <tr>
          <td bgcolor="beige" align="right" valign="top">Characters <b>HTML</b>:</td>
          <td bgcolor="beige" align="left">
            <input type="text" name="countmessagehtml" size="4" readonly>&nbsp;&nbsp;Maximum of 20,000 characters allowed.<br><br>
          </td>
        </tr>
<!-- END HTML BASED message -->
        <tr>
          <td bgcolor="lightblue" colspan="2" align="center">
            <br>
            <h3>Plain Text NewsLetter</h3>
          </td>
        </tr>
<!-- NON HTML BASED message -->
        <tr>
          <td bgcolor="lightblue" align="right">
            Subject <b>plain text</b>:
          </td>
          <td bgcolor="lightblue">
            <input type="text" name="nlsubject" size="80" value="<?=$nlsubject?>">
          </td>
        </tr>
        <tr>
          <td bgcolor="lightblue" align="right" valign="top">
            Message <b>plain text</b>:
          </td>
          <td bgcolor="lightblue">
            <textarea wrap="PHYSICAL" rows="20" cols="<?=$email_wordwrap_length?>" name="nlmessage" onFocus="focused=true;" onBlur="focused=false;"><?=$nlmessage?></textarea>
          </td>
        </tr>
        <tr>
          <td bgcolor="lightblue" align="right" valign="top">Characters <b>plain text</b>:</td>
          <td bgcolor="lightblue" align="left">
            <input type="text" name="countmessage" size="4" readonly>&nbsp;&nbsp;Maximum of 20,000 characters allowed.<br><br>
          </td>
        </tr>
<!-- END NON HTML BASED message -->
        <tr>
          <td colspan="2"><hr></d>
        </tr>
        <tr>
          <td valign="top">
            <input type="button" class="bluebutton" value="Save Message" onClick="checkBoxes(this.form,1);"><br><img src="../images/null.gif" border="0" height="1" width="100">
            <?=$savedstatus?>
          </td>
          <td align="right" valign="top">
            <input type="button" class="greenbutton" value="Send Mail" onClick="checkBoxes(this.form,0);">
            <input type="hidden" name="submitted" value="save">
            </form>
          </td>
        </tr>
        <tr>
          <td align="center" colspan="2">
            <input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>
