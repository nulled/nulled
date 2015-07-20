<table width="590" cellpadding="3" cellspacing="0" align="center" border="0">
  <tr>
    <td colspan="2">
    	<center><h3>MailBox Full or Over Quota</h3></center>
      <b>Contact</b> Address: <b><?=$email?></b> is all clogged up, until you Clean It Out!
      Usually, clearing out the <i>'Sent'</i> and/or <i>'Trash'</i> Folders will do the trick.
      Or, if you have any <b>Large Attachments</b> in your Emails, try
      downloading them and moving them to another safe place, then deleting them from your Mailbox.
      <br /><br />
      Also, if you cleared out your Mail Box from a passed "fill up" you will still get this message until you
      confirm with us you cleared it out.
      <br /><br />
      Click the <b>Cleaned My Mailbox</b> button below <b>After</b> you have actually worked on clearing things out,
      otherwise you will trigger this message again and again.
      <form name="clearmailbox" action="/mle/main.php" method="POST">
      <input type="button" class="beigebutton" value="Yes, I promise I Cleaned Up My Full Mailbox" onclick="preSubmit(this)" />
      <input type="hidden" name="submitted" value="cleared" />
      <input type="hidden" name="option" value="mailboxfullcontact" />
      </form>
      <?php
        if ($bannerIMG)
          echo "<p><center><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></center></p>\n";
      ?>
    </td>
  </tr>
</table>