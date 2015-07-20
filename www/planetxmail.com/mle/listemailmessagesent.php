<table width="590" cellpadding="3" cellspacing="0" align="center" border="0">
  <tr>
    <td colspan="2" align="center">
      A confirmation email to <b><?=$email?></b> was sent.  Please follow the instructions when it is delivered.
      <br>
      <?php
        if ($bannerIMG)
          echo "<p><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></p>\n";
      ?>
      <?php echo str_replace('[location]','listemailmessagesent', $ads_ads_ads); ?>
    </td>
  </tr>
</table>