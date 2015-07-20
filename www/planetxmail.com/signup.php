<?php
// used because some confuse list sign up with safelist signup
if ($l)
{
	header ("Location: http://planetxmail.com/mle/signup.php?l=$l");
	exit;
}

$ip = $_SERVER['REMOTE_ADDR'];

// if ($ip != '67.160.68.19') exit('<font color="red"><center><h2>We are in the process of revamping our Safelist List owner ADMIN. Stay tuned...</h2>As a result we are not accepting any new List Owner sign ups. Come back and we will have something even better!</center></font>');

?>
<td align="left">
  <font size="+1">Sign-up Online</font>
  <p>
    Yes!  Sign me up now!
    <br><br>
    We accept all major <b>credit cards</b>.
    <br><br>
    If you are a List Owner else where and wish to move your SafeList to our servers please contact: <a href="http://planetxmail.com/openticket.php">Click Here</a>
  </p>
  <p>
    <hr>
    <center><font size="+1" color="#000000">Already a List Owner?</font></center><br>
    If you are <b>already signed-up</b> and wish to request an <b>addition</b> list to <i>avoid</i> the $<?=$setupFee?> set-up fee.
    Enter your List Owner login information below.<br>
    <form name="alreadymember" action="/index.php" method="POST" onSubmit="submitonce(this)" onClick="highlight(event)">
    List Owner Name:<input type="text" name="listowner" value="<?=$listowner?>"><br>
    List Owner Pass:&nbsp;<input type="password" name="password">&nbsp;&nbsp;
    <input type="hidden" name="submitted" value="login">
    <input type="hidden" name="option" value="signup">
    <input type="submit" class="beigebutton" value="Log In">
    </form>
    <hr>
    <center><font size="+1" color="#000000">New to Planet X Mail?</font></center>
  </p>
  <?php if ($notValid) echo '<div style="padding:10px;text-align:center;border:1px solid black;color:black;background-color:pink;border-radius:3px;margin:5px auto;width:300px;font-size:16px"><b>' . $notValid . '</b></div>'; ?>
  <form name="signup" action="/index.php" method="POST" onClick="highlight(event)">
  <table border="0" cellspacing="0" cellpadding="3">
    <tr>
      <td bgcolor="lightblue" colspan="2"><font size="+1" color="#000000">Your Information</font></td>
    </tr>
    <tr>
      <td width="50%" align="right">Your First and Last Name</td>
      <td><input type="text" name="name" value="<?=$name?>" size="35"></td>
    </tr>

    <tr>
      <td width="50%" align="right">E-Mail Address</td>
      <td><input type="text" name="email" value="<?=$email?>" size="35"></td>
    </tr>
    <tr>
      <td bgcolor="lightblue" colspan="2"><font size="+1" color="#000000">Mailing List Information</font></td>
    </tr>
    <tr>
      <td width="50%" align="right"><b>Importing</b> of an existing list needed?</td>
      <td nowrap>
        <select name="importlist" size="1">
          <option value="no"<?php if ($importlist=="no") echo " SELECTED"; ?>>No</option>
          <option value="yes"<?php if ($importlist=="yes") echo " SELECTED"; ?>>Yes</option>
        </select> <u>We do not import Harvested/Spam Lists.</u>
      </td>
    </tr>
    <tr>
      <td width="50%" align="right"><b>List Owner Name</b>.  One word:</td>
      <td><input type="text" name="listownername" value="<?=$listownername?>" size="35"></td>
    </tr>
    <tr>
      <td width="50%" align="right"><b>List Name</b>.  One word:</td>
      <td><input type="text" name="listname" value="<?=$listname?>" size="35"></td>
    </tr>
    <tr>
      <td width="50%" align="right">List Owner <b>E-Mail</b>:</td>
      <td><input type="text" name="listowneremail" value="<?=$listowneremail?>" size="35"></td>
    </tr>
    <tr>
      <td width="50%" align="right">How do you hear about us?</td>
      <td>
        <select name="howheard" size="1">
          <option value="searchengine"<?php if ($howheard=="searchengine") echo " SELECTED"; ?>>Search Engine</option>
          <option value="friend"<?php if ($howheard=="friend") echo " SELECTED"; ?>>Friend</option>
          <option value="other"<?php if ($howheard=="other") echo " SELECTED"; ?>>Other</option>
        </select>
      </td>
    </tr>

    <tr>
      <td colspan="2">
      <hr>
      <center><font size="+1">Pick a List Type</font><br>With the Radio buttons on the left.</center><br>
      <table style="border-collapse: collapse" bordercolor="#000000" border="1" cellspacing="0" cellpadding="0" align="center">
        <tr>
          <td colspan="3" align="center" bgcolor="lightgrey"><b><font class="medsize">SafeLists</font></b></td>
        </tr>
        <tr>
          <td bgcolor="beige"></td>
          <td bgcolor="beige" width="150" align="center">Safe List Members</td>
          <td bgcolor="beige" width="150" align="center">* Price Per Month</td>
        </tr>
        <tr>
          <td id="sl1-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl1');"></td>
          <td id="sl1-2" width="150" align="center">Any Size</td>
          <td id="sl1-3" width="150" align="center">$30</td>
        </tr>
      </table>

      <br>
<!--
      <table style="border-collapse: collapse" bordercolor="#000000" border="1" cellspacing="0" cellpadding="0" align="center">
        <tr>
          <td colspan="3" align="center" bgcolor="lightgrey"><b><font class="medsize">NewsLetters</font></b></td>
        </tr>
        <tr>
          <td bgcolor="beige"></td>
          <td bgcolor="beige" width="150" align="center">NewsLetter Members</td>
          <td bgcolor="beige" width="150" align="center">* Price Per Month</td>
        </tr>
        <tr>
          <td id="nl1-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl1');"<?php if ($whichlist=="nl1") echo " CHECKED"; ?>></td>
          <td id="nl1-2" width="150" align="center">Any Size</td>
          <td id="nl1-3" width="150" align="center">$20</td>
        </tr>
      </table>
      -->
        <br /><br />
        <font color="red"><b>Remember, these lists are empty. It is up to the List Owner ( You ) to get membership sign-ups.</b></font>
        <br /><br />
        <b>*</b> There is a one time $25 setup fee per SafeList/NewsLetter. <b>We will reimburse you this $25 setup fee
        once your List reaches only 100 unique members!</b>
        <p>
          <hr>
          <font size="+1"><b>Choose a method of payment.</b></font>
          <br><br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="clickbank"><b>Click Bank</b> - Credit Cards and Paypal accepted.<br>
        </p>

        <input type="button" class="beigebutton" value="Buy your List" onClick="if (document.signup.mop.checked==false) alert('Choose a method of payment.'); else { submitonce(this.form); this.form.submit(); }">&nbsp;&nbsp;&nbsp;&nbsp;<font color="red"><b><?=$notValid?></b></font>
        <br>

        <p>
        	<b><font color="red">Important note:</font></b> Make sure to COMPLETELY finish the pay process all the way through in order for your list to be created.
        	You will know you have completed the pay process FULLY when you get to the Thank you page and asks if you wish to close the window.
        </p>

        <input type="hidden" name="whichlist" value="<?=$whichlist?>">
        <input type="hidden" name="option" value="signup">
        <input type="hidden" name="submitted" value="signup">
        <input type="hidden" name="country" value="earth" size="35">

        </form>
      </td>
    </tr>
  </table>
</td>