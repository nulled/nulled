<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/signup.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title><?=$program_name?> - Sign up</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
<script language="javascript" src="submitsupressor.js"></script>
</head>
<?php flush(); ?>
<body">
<table width="600" border="1" cellspacing="0" cellpadding="5" align="center">
  <tr>
    <td>
      <table bgcolor="#FFFFFF" border="0" width="580" cellspacing="1" cellpadding="1" align="center">
        <tr>
          <td colspan="2" align="center">
            <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>">
          </td>
        </tr>
        <?php if ($bannerIMG) echo "<tr><td align=\"center\" colspan=\"2\"><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></td></tr>\n"; ?>
        <tr>
          <td bgcolor="#F9ECC5" align="center" colspan="2"><font size="+1">Sign Up<br><font size="+2"><b><?=$list?></b></font></font></td>
        </tr>
<!--
        <tr>
         <td colspan="2">
            <font color="red"><b>Friendly Warning:</b></font> There are now websites that claim to be <b>"Viral Mailers"</b>
            that once you get on their list, will Spam you to no end. ANY Website that ONLY accepts a Gmail account should
            put you on <font color="red">High Alert</font> that they will Spam you, even if you Unsubscribe.
         </td>
      </tr>
-->
        <tr>
          <td colspan="2" align="center">
            <font color="red" size="3"><b><?=$notValid?></b>
            <form name="signup" action="/mle/signup.php" method="POST" onSubmit="submitonce(this)" onClick="highlight(event)">
          </td>
        </tr>
        <?php
          if (! $newsletter)
          {
            echo '<tr>
                    <td align="right" bgcolor="#F4F4F4">User Name:</td>
                    <td align="left"  bgcolor="#F4F4F4"><input type="text" name="username" value="' . $username . '" size="20"></td>
                  </tr>
                  <tr>
                    <td align="right" bgcolor="#EFEEEA">Password:</td>
                    <td align="left"  bgcolor="#EFEEEA"><input type="password" name="pass1" value="' . $pass1 . '" size=15></td>
                  </tr>
                  <tr>
                    <td align="right" bgcolor="#F4F4F4">Confirm Password:</b></td>
                    <td align="left"  bgcolor="#F4F4F4"><input type="password" name="pass2" value="' . $pass2 . '" size=15></b></td>
                  </tr>
              ';
          }
        ?>
        <tr>
          <td align="right" bgcolor="#EFEEEA">
            <?php if (! $newsletter) echo '<b>Contact</b> Email:'; else echo '<b>Email Address</b>:'; ?>
          </td>
          <td align="left" bgcolor="#EFEEEA">
            <input type="text" name="email1" value="<?=$email1?>" size="40" maxlength="100" />
          </td>
        </tr>

        <tr>
          <td align="right" bgcolor="#F4F4F4">
            <?php if (! $newsletter) echo 'Confirm Email:'; else echo '<b>Confirm Email</b>:'; ?>
          <td align="left" bgcolor="#F4F4F4">
            <input type="text" name="email2" value="<?=$email2?>" size="40" maxlength="100" />
          </td>
        </tr>

        <tr>
          <td align="right" bgcolor="#EFEEEA">
            First Name:
          </td>
          <td align="left" bgcolor="#EFEEEA">
            <input type="text" name="fname" value="<?=$fname?>" size="15" maxlength="20" />
          </td>
        </tr>

        <tr>
          <td align="right" bgcolor="#F4F4F4">
            Last Name:
          </td>
          <td align="left" bgcolor="#F4F4F4">
            <input type="text" name="lname" value="<?=$lname?>" size="15" maxlength="20" />
          </td>
        <tr>

        </tr>
         <?php
          if (! $newsletter)
          {
            echo "<tr>\n";
            echo "  <td align=center valign=top colspan=2 bgcolor=#EFEEEA>\n";
            echo "    <input type=checkbox style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=agree value=yes ";
            if ($agree) echo "CHECKED";
            echo "> Yes, I have read the Sign Up Agreement below.</td>\n";
            echo "</tr>\n";
          }
        ?>
        <tr>
          <td align="center" colspan="2" valign="top">
            <br>
            <font size="2"><i>Enter Turing Key Below:</i></font><br />
            <img src="/mle/keyimages/<?=$turingkey->keyfilename?>" border="0" />
            <input type="text" name="key" size="4" maxlength="4" autocomplete="off" />
          </td>
        </tr>

        <tr>
          <td align="left" valign="top">
            <input type="submit" class="greenbutton" value="Sign Up" />
          </td>
          <td align="right">
            <input type="hidden" name="submitted" value="signup" />
            <input type="hidden" name="validate" value="<?=$turingkey->validate?>" />
            <input type="hidden" name="greylist_bypass" value="<?=$greylist_bypass?>" />
            <input type="hidden" name="status" value="<?=$status?>" />
            <input type="hidden" name="list" value="<?=$list?>" />
            <input type="hidden" name="id" value="<?=$id?>" />
            <input type="hidden" name="l" value="<?=$l?>" />
            </form>
          </td>
        </tr>

        <tr>
          <td colspan="2" align="center">
             <?php if ($sponsor) echo '<font color="red"><b>Sponsored by: </font>' . $sponsor . '</b>'; ?>
          </td>
        </tr>

        <?php
          if (! $newsletter)
          {
            echo "<tr>\n";
            echo "  <td align=left colspan=2>\n";
            echo "    <p>\n";
            echo "     <br><b>Sign Up Agreement:</b><br>\n";
            echo "      <ul>\n";
            echo "        <li>You agree to sign up only once per list.</li>\n";
            echo "        <li>You agree to receive all emails from members of the list.</li>\n";
            echo "        <li>You agree to receive periodic notices from the List Owner to your contact address.</li>\n";
            echo "        <li>You agree to read as many of the emails other members of the list are sending.</li>\n";
            echo "        <li>You agree to periodic Solo Ads to your contact address.</li>\n";
            echo "        <li>You agree to not use the URL Trackers in SPAM email.</li>\n";
            echo "        <li>You agree to not submit Adult Sites, Offensive or Scam material to the list.</li>\n";
            echo "      </ul>\n";
            echo "    </p>\n";
            echo "  </td>\n";
            echo "</tr>\n";
          }
       ?>
      </table>
    </td>
  </tr>
</table>
<script>
  document.forms[0].username.focus();
</script>
<!-- Start Quantcast tag -->
<script type="text/javascript" src="http://edge.quantserve.com/quant.js"></script>
<script type="text/javascript">
_qacct="p-a26V9rP8NfTY2";quantserve();</script>
<noscript>
<img src="http://pixel.quantserve.com/pixel/p-a26V9rP8NfTY2.gif" style="display: none" height="1" width="1" alt="Quantcast"/>
</noscript>
<!-- End Quantcast tag -->
<script src="http://www.google-analytics.com/urchin.js" type="text/javascript">
</script>
<script type="text/javascript">
_uacct = "UA-2323813-1";
urchinTracker();
</script>
</body>
</html>