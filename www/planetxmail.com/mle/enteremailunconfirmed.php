<table width="590" cellpadding="3" cellspacing="0" align="center" border="0">
  <tr>
    <td colspan="2" align="center">
      <p>You entered a <b>Contact Email Address</b> already and we sent a confirmation mail to that address.
      However, we haven't received a response yet.  If you feel you entered the
      Contact Address in error please <a href="<?=$_SERVER[PHP_SELF]."?option=changesignupemail"?>"><b>Click Here</b></a> to <i>reenter</i> the address.</p>
      <p>Or, reply to the confirmation mail we sent you to activate this List Address account.</p>
      <?php
        if ($bannerIMG)
          echo "<p><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></p>\n";
      ?>
    </td>
  </tr>
</table>