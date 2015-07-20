<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/sendmail.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Admin Control</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
<script language="javascript">
<!--
document.onkeypress=updateCount;
var focused = false;
function updateCount()
{
  if (focused) document.sendmail.countmessage.value = document.sendmail.message.value.length;
}

function checkBoxes(formname, savetodb)
{
  var saved = <?=$saved?>;

  if (savetodb==0)
  {
    if (saved==false)
    {
      alert('You need to save message to database before you send your message.');
      return;
    }
  }

  if (document.sendmail.subject.value.length == 0)
  {
    alert('Subject field is empty.');
    return;
  }

  if (document.sendmail.message.value.length == 0)
  {
    alert('Message body is empty.');
    return;
  }

  if (document.sendmail.subject.value.length > 80)
  {
    alert('Subject length can not exceed 80 characters.');
    return;
  }

  if (document.sendmail.message.value.length > 5000)
  {
    alert('Message body can not exceed 5000 characters.');
    return;
  }

  if (savetodb)
    formname.submit();
  else
  {
    if (confirm('Remember you must save the message after ALL changes are make.\nOtherwise you may not be sending the message you intended to.\nHit OK to send.'))
    {
      var data = 'maillist.php?';
      <?php if ($_SESSION['aaadminpsk']) echo "if (document.sendmail.mailtoelpowners.checked) data += '&mailtoelpowners=1';\n"; ?>
      location.href=''+data+'';
    }
  }
}
//-->
</script>
</head>
<table width="400" cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table cellpadding="3" cellspacing="0" align="center" border="0">
        <tr>
          <td colspan="2" align="center">
            <form name="sendmail" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
            <font color="#005F8C"><b>Send emails</b></font><br>
            Mailing system to your members.<br><br>
            <b>NOTE:</b> This is NOT to be used like you would a Safe-List.  This is
            <i>STRICTLY</i> intended for sending members your notices on policy or price changes ONLY.
            <hr>
          </td>
        </tr>
<!-- List Owners-->
        <?php
          if ($_SESSION['aaadminpsk'])
          {
            echo "<tr>\n";
            echo "  <td align=\"right\" bgcolor=\"beige\">\n";
            echo "    <input type=\"checkbox\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"mailtoelpowners\" value=\"1\" onClick=\"javascript:if (document.sendmail.mailtoelpowners.checked) alert('This will ONLY mail to ALL ELP Owners.\\nYou members are NOT mailed.');\""; if ($mailtoelpowners=="1") echo " CHECKED"; echo ">\n";
            echo "  </td>\n";
            echo "  <td bgcolor=\"beige\"><font color=\"black\">Mail to <b>ALL ELP Owners</b> only</a></td>\n";
            echo "</tr>\n";
          }
        ?>
        <tr>
          <td align="right">
            Subject:
          </td>
          <td>
            <input type="text" name="subject" size="45" value="<?=$subject?>">
          </td>
        </tr>
        <tr>
          <td align="right" valign="top">
            Message:
          </td>
          <td>
            <textarea wrap="physical" rows="30" cols="60" name="message" onFocus="focused=true;" onBlur="focused=false;"><?=$message?></textarea>
          </td>
        </tr>
        <tr>
          <td align="right">Characters:</td>
          <td align="left">
            <input type="text" name="countmessage" size="4" READONLY>&nbsp;&nbsp;Maximum of 5000 characters allowed.<br><br>
          </td>
        </tr>
        <tr>
          <td colspan="2"><hr></d>
        </tr>
        <tr>
          <td>
            <input type="button" class="bluebutton" value="Save Message" onClick="javascript:checkBoxes(this.form,1);"><br>
            <?=$notValid?>
          </td>
          <td align="right">
            <input type="button" class="greenbutton" value="Send Mail" onClick="javascript:checkBoxes(this.form,0);">
            <input type="hidden" name="submitted" value="save">
            </form>
          </td>
        </tr>
        <tr>
          <td align="center" colspan="2">
            <input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='main.php'">
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>
