<table width="610" cellpadding="3" cellspacing="1" align="center">
  <tr>
    <td align="center" colspan="2">
      <font size="+2">Profile for: </font> <font color="red" size="+2"><b><?=$_SESSION['aausername']?></b></font>
      <?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div><hr />'; ?>
    </td>
  </tr>

  <?php

    if ($referer)
    {
      echo '
        <tr>
          <td colspan="2" bgcolor="beige">
            <p align="center">SafeList: <b>' . $_SESSION['aalistname'] . '</b> Referral URL: <font size="1"></font>&nbsp;<br />
            <input type="text" size="60" value="http://planetxmail.com/mle/affsignup.php?affid=' . $affid . '" READONLY />
          </td>
        </tr>
      ';
    }

  ?>

  <form name="userdata" action="/mle/main.php" method="POST" onSubmit="submitonce(this)">

  <tr>
    <td align="right" bgcolor="#EFEEEA">
      First Name:&nbsp;</td>
    <td bgcolor="#EFEEEA">
      <input type="text" size="30" name="fname" value="<?=$memberdata['fname']?>"></td>
  </tr>

  <tr>
    <td align="right" bgcolor="#F4F4F4">
      Last Name:&nbsp;</td>
    <td bgcolor="#F4F4F4">
      <input type="text" size="30" name="lname" value="<?=$memberdata['lname']?>"></td>
  </tr>

  <tr>
    <td align="right">
      Your Sponsor:&nbsp;</td>
    <td>
      <b><?=$sponsor?></b></td>
  </tr>

  <tr>
    <td align="right">
      Credits:&nbsp;</td>
    <td>
      <b><?=$memberdata['credits']?></b></td>
  </tr>

  <tr>
    <td align="right" bgcolor="#EFEEEA">
      <b>Contact</b> Email:&nbsp;</td>
    <td bgcolor="#EFEEEA">
      <input type="text" size="30" name="email" onclick="alert('Change/Edit by Clicking Edit Contact Email Button.')" value="<?=$memberdata['email']?>" readonly />&nbsp;&nbsp;<input type="button" value="Edit Contact Email" onclick="location.href='main.php?option=changesignupemail'" />&nbsp;<?php if ($ebanned) echo '<span class="banned">' . $ebanned . '</span>'; ?>
    </td>
  </tr>

  <tr>
    <td align="right" bgcolor="#F4F4F4">
      <b>List</b> Email:&nbsp;</td>
    <td bgcolor="#F4F4F4">
      <input type="text" size="30" name="listemail" onclick="alert('Change/Edit by Clicking Edit List Email Button.')" value="<?=$memberdata['listemail']?>" readonly />&nbsp;&nbsp;<input type="button" value="Edit List Email" onclick="location.href='main.php?option=enterlistemail'" />&nbsp;<?php if ($lbanned) echo '<span class="banned">' . $lbanned . '</span>'; ?>
    </td>
  </tr>

  <tr>
    <td align="right" bgcolor="#EFEEEA">
      Your Status:&nbsp;</td>
    <td bgcolor="#EFEEEA">
      <b>

      <?php

      if ($memberdata['status'] == "mem") echo "Free";
      else if ($memberdata['status'] == "pro") echo "Professional";
      else if ($memberdata['status'] == "exe") echo "Executive";

      if ($memberdata['status'] != "exe" && $allowupgrades)
        echo '&nbsp;&nbsp;&nbsp;&nbsp;<input type="button" class="bluebutton" value="Upgrade Your Status" onClick="location.href=\'http://planetxmail.com/mle/main.php?option=upgrade\'">';

      ?>

      </b>
    </td>
  </tr>

  <tr>
    <td align="right" bgcolor="#EFEEEA">
      <?=$memberdata['mailweek']?> of <?=$mailweekly?>
    </td>
    <td bgcolor="#EFEEEA">
      Regular Blaster weekly mailings used.
    </td>
  </tr>

  <tr>
    <td align="right" bgcolor="#EFEEEA">
      <?=$memberdata['mailcreditsweek']?> of <?=$mailcreditsweekly?>
    </td>
    <td bgcolor="#EFEEEA">
      Credit Blaster weekly mailings used.
    </td>
  </tr>

  <tr>
    <td align="right" bgcolor="#F4F4F4">
      List Name:&nbsp;</td>
    <td bgcolor="#F4F4F4">
      <b><?=$_SESSION['aalistname']?></b>
    </td>
  </tr>

  <tr>
    <td align="right" bgcolor="#EFEEEA" nowrap>
      List Admin Contact:&nbsp;</td>
    <td bgcolor="#EFEEEA">
      <?=$adminemail?>
    </td>
  </tr>

  <tr>
    <td align="right" bgcolor="#F4F4F4">
      Vacation:&nbsp;</td>
    <td bgcolor="#F4F4F4" nowrap>
      <input type="checkbox" style="border-width:0px;" name="vacation" value="1" <?php
      if ($memberdata['vacation'] == '1')
        echo ' CHECKED'; ?> onclick="if (document.userdata.vacation.checked==true) alert('Turning this ON will prevent you from sending AND receiving mail!\nIf you are just turning it OFF you will have to WAIT until the\nday AFTER the next mailing day for it to reset!');">&nbsp;If checked you <b>will not</b> receive mail to your List Address or be able to mail out.
    </td>
  </tr>

  <tr>
    <td colspan="2" bgcolor="#EFEEEA">
      <center><input type="submit" class="greenbutton" value="Apply Changes"></center>
    </td>
  </tr>

  <tr>
    <td colspan="2" align="center"><hr><a href="requestlogins.php" target="_BLANK">Request ALL Log-In URLs based on an Email Address.</a></td>
  </tr>

  <tr>
    <td colspan="2" align="center"><hr><a href="requestremovelinks.php" target="_BLANK">Request ALL REMOVAL Links based on an Email Address.</a><hr></td>
  </tr>

  <tr>
    <td colspan="2" align="center" bgcolor="#EFEEEA">
      <table border="0" cellspacing="0" cellpadding="0" align="center" width="500">
        <tr>
          <td colspan="3" align="center"><b><font size="3">Change Your Password</font></b><br><br></td>
        </tr>
        <tr>
          <td align="center">Old Password<br>1. <input type="password" name="passwordold"></td>
          <td align="center">New Password<br>2. <input type="password" name="passwordnew"></td>
          <td align="center">New Password Confirm<br>3. <input type="password" name="passwordnewconfirm"></td>
        </tr>
        <tr>
          <td align="center" colspan="3">
            <br>
            <input type="button" value="Change Password" onClick="this.form.submit()">
          </td>
        </tr>
      </table>
    </td>
  </tr>

  <tr>
    <td colspan="2"><hr></td>
  </tr>

  <tr>
    <td colspan="2" align="center" bgcolor="#F4F4F4">
      <b><font size="3">Terminate Your Account</font></b><br>
      Password: <input type="password" name="password">
      <input type="button" class="redbutton" value="Delete Me" onClick="if (confirm('Are you sure?\nYour account will be deleted!')){ document.userdata.submitted.value='delete'; this.form.submit(); }">
      <input type="hidden" name="submitted" value="1">
      <input type="hidden" name="option" value="memberprofile">
      </form>
    </td>
  </tr>
</table>