<div style="width:600px;text-align:left">
      <div style="text-align:center;font-size:18px;font-weight:bold;margin:0;">This Contact Address is Bouncing</div>

      <div style="text-align:center;font-size:16px;font-weight:normal;margin:0;"><?=$email?></div>

      <div style="text-align:center;font-size:14px;margin:15px 0;">What To Do About It</div>

      <span style="color:red;font-weight:bold">Step 1:</span> Add <b>do_not_reply@planetxmail.com</b> as a Contact
      in your Address Book, to let your Mail Service know you wish to receive Email from Planet X Mail.
      <br /><br />
      <span style="color:red;font-weight:bold">Step 2:</span> ANY emails that end up in your Spam/Junk folder that are from Planet X Mail,
      click <b>Is Not Spam</b> Button.
      <br /><br />
      <span style="color:red;font-weight:bold">Step 3:</span> If you have tried adding <i>do_not_reply@planetxmail.com</i> to your Address
      Book and UnSpammed all messages in your Spam folder from Planet X Mail does not work, we have no choice but to change your Email Address.

      <div style="text-align:center;font-size:14px;margin:15px 0;">Resend Contact Address Confirmation Email</div>
      If you receive the confirmation email, it will clear the bounce.  If you do not receive the confirmation email, it means
      you need to pick a new email provider.

      <div style="text-align:center;padding:5px;border:1px solid red;background-color:pink;border-radius:5px;">

      <?php
        if ($notValid) : echo $notValid;
        ELSE: ?>

        <form name="resend" action="main.php" method="post">
          <input type="button" value="Resend Contact Address Confirmation" onclick="this.value='Loading...';this.disabled=true;this.form.submit();" />
          <input type="hidden" name="submitted" value="resend" />
          <input type="hidden" name="option" value="bannedmessagecontact" />
        </form>
      <?php ENDIF; ?>

      </div>

      Goto Your <a href="main.php?option=memberprofile">Profile</a> and see which Email Addresses you are using. Resubmit a New
      Email Address, possibly from a completely New Domain.
      <br /><br />
      <b>Contact</b> Address Bouncing: <b><?=$email?></b> and the Reason returned below.
      <hr />
<pre style="border:1px solid black; padding:5px; background-color: beige; border-radius: 10px;">
<?=$reason?>
</pre>
      <h3>Reason They Think We Are Spamming</h3>
      <ol>
        <li>Mail looks like spam, even though we have Unsub URLS and obey all Spam Laws.</li>
        <li>Many People mail the same message over and over and this appears to be Spam.</li>
      </ol>
</div>