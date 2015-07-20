<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/sendmail.inc');
?>
<html>
<head>
<title><?=$program_name?> - Admin Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<style>
.thecheckbox {
  border-top-width: 0px;
  border-bottom-width: 0px;
  border-right-width: 0px;
  border-left-width: 0px;
}
</style>
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
  var statusGroup = false;
  var saved = <?=$saved?>;

  if (savetodb==0)
  {
    if (saved==false)
    {
      alert('You need to save message to database before you send your message.');
      return;
    }

    if (document.sendmail.mailtomem.checked) statusGroup = true;
    if (document.sendmail.mailtopro.checked) statusGroup = true;
    if (document.sendmail.mailtoexe.checked) statusGroup = true;

    <?php if ($_SESSION['aaadminpsk']) echo 'if (document.sendmail.mailtolistowners.checked) statusGroup = true;'."\n"; ?>

    if (statusGroup==false)
    {
      alert('You need to pick at least one status group.');
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

  if (document.sendmail.subject.value.length > <?=$email_subject_length?>)
  {
    alert('Subject length can not exceed <?=$email_subject_length?> characters.');
    return;
  }

  if (document.sendmail.message.value.length > <?=$admin_email_length?>)
  {
    alert('Message body can not exceed <?=$admin_email_length?> characters.');
    return;
  }

  if (savetodb) formname.submit();
  else
  {
    if (confirm('Remember you must save the message after ALL changes are made.\nOtherwise you may not be sending the message you intended to.\nHit OK to send.'))
    {
      var data = 'maillist.php?';

      if (document.sendmail.mailtomem.checked) data += '&mailtomem=1';
      if (document.sendmail.mailtopro.checked) data += '&mailtopro=1';
      if (document.sendmail.mailtoexe.checked) data += '&mailtoexe=1';
      if (document.sendmail.mailtoall.checked) data += '&mailtoall=1';
      <?php if ($_SESSION['aaadminpsk']) echo "if (document.sendmail.mailtolistowners.checked) data += '&mailtolistowners=1';\n"; ?>

      if (document.sendmail.whichaddress[1].checked) data += '&whichaddress=listemail';
      else if (document.sendmail.whichaddress[0].checked) data += '&whichaddress=email';

      location.href=''+data+'';
    }
  }
}

function theCheckBox()
{
  if (document.sendmail.mailtolistowners.checked)
    alert('This will mail to All Your List Owners.\nAll other settings are Ignored.');
}
//-->
</script>
</head>
<table cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table width="500" cellpadding="3" cellspacing="1" align="center" border="0">
        <tr>
          <td colspan="2" align="center">
            <form name="sendmail" action="/mle/admin/sendmail.php" method="POST">
            <font size="4" color="#005F8C"><b>Send Mail</b></font><br>
            Mailing system to your members.
            <hr>
            <b class="red"><?=$mailstatus?></b>
          </td>
        </tr>
        <tr>
          <td bgcolor="lightgrey" align="right">
            <input type="checkbox" class="theCheckBox" name="mailtomem" value="1"<?php if ($mailtomem) echo " CHECKED"; ?>>
          </td>
          <td bgcolor="lightgrey">Mail to <b>Free Members</b></td>
        </tr>
        <tr>
          <td bgcolor="lightgrey" align="right">
            <input type="checkbox" class="theCheckBox" name="mailtopro" value="1"<?php if ($mailtopro) echo " CHECKED"; ?>>
          </td>
          <td bgcolor="lightgrey">Mail to <b>Professionals</b></td>
        </tr>
        <tr>
          <td bgcolor="lightgrey" align="right">
            <input type="checkbox" class="theCheckBox" name="mailtoexe" value="1"<?php if ($mailtoexe) echo " CHECKED"; ?>>
          </td>
          <td bgcolor="lightgrey">Mail to <b>Executives</b></td>
        </tr>
<!-- List Owners -->
        <?php
          if ($_SESSION['aaadminpsk'])
          {
            echo "<tr>\n";
            echo "  <td align=\"right\" bgcolor=\"beige\">\n";
            echo "    <input type=\"checkbox\" class=\"thecheckbox\" name=\"mailtolistowners\" value=\"1\" onClick=\"theCheckBox();\"";
            echo ($mailtolistowners) ? ' CHECKED' : " />\n";
            echo "  </td>\n";
            echo "  <td bgcolor=\"beige\"><font color=\"black\">Mail to <b>ALL List Owners</b> only</a></td>\n";
            echo "</tr>\n";
          }
        ?>
        <tr>
          <td align="right" bgcolor="maroon">
            <input type="checkbox" class="theCheckBox" name="mailtoall" value="1" onClick="javascript:if (document.sendmail.mailtoall.checked) alert('This will mail to ALL SafeLists that are currently created.\nNo newsletters will be mailed to.\nUse this with caution!!!');"<?php if ($mailtoall=="1") echo " CHECKED"; ?>>
          </td>
          <td bgcolor="maroon"><font color="white">Mail to <b>ALL Safe-Lists</b></a></td>
        </tr>
<!-- list or regular -->
        <tr>
          <td align="right" bgcolor="tan">
            <input type="radio" class="theCheckBox" name="whichaddress" value="email"<?php if ($whichaddress=="email") echo " CHECKED"; else if ($whichaddress=="") echo " CHECKED"; ?>>
          </td>
          <td bgcolor="tan"><b>Mail to users Sign-Up address.</b></td>
        </tr>
        <tr>
          <td align="right" bgcolor="tan">
            <input type="radio" class="theCheckBox" name="whichaddress" value="listemail"<?php if ($whichaddress=="listemail") echo " CHECKED"; ?>>
          </td>
          <td bgcolor="tan"><b>Mail to users List address.</b></td>
        </tr>
<!-- // -->
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
            <textarea wrap="physical" rows="20" cols="80" name="message" onFocus="focused=true;" onBlur="focused=false;"><?=$message?></textarea>
          </td>
        </tr>
        <tr>
          <td align="right">Characters:</td>
          <td align="left">
            <input type="text" name="countmessage" size="4" readonly>&nbsp;&nbsp;Maximum of <?=$admin_email_length?> characters allowed.<br><br>
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
            <input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='<?php if ($_SESSION['aaadminpsk']) echo "main.php"; else echo "mainlistowner.php"; ?>'">
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>