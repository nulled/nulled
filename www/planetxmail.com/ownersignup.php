<td align="left">
  <font size="+1">Already a List Owner <b>ADDITIONAL LIST</b> Sign-up.</font>
  <?php echo "<br><br><center><font color=\"red\" size=\"3\"><b>$notValid</b></font></center>"; ?>
  <form name="signup" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
  <table border="0" cellspacing="0" cellpadding="3">
    <tr>
      <td bgcolor="ligtblue" colspan="2"><font size="+1" color="#000000">Your Information</font></td>
    </tr>
    <tr>
      <td width="50%" align="right">Your Name</td>
      <td><input type="text" name="name" value="<?=$name?>" size="35" READONLY></td>
    <tr>
      <td width="50%" align="right">Organization</td>
      <td><input type="text" name="organization" value="<?=$organization?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td width="50%" align="right">Address</td>
      <td><input type="text" name="address" value="<?=$address?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td width="50%" align="right">City</td>
      <td><input type="text" name="city" value="<?=$city?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td width="50%" align="right">State</td>
      <td><input type="text" name="state" value="<?=$state?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td width="50%" align="right">Zip Code</td>
      <td><input type="text" name="zipcode" value="<?=$zipcode?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td width="50%" align="right">Country</td>
      <td><input type="text" name="country" value="<?=$country?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td width="50%" align="right">Phone</td>
      <td><input type="text" name="phone" value="<?=$phone?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td width="50%" align="right">E-Mail Address</td>
      <td><input type="text" name="email" value="<?=$email?>" size="35" READONLY></td>
    </tr>
    <tr>
      <td bgcolor="ligtblue" colspan="2"><font size="+1" color="#000000">Mailing List Information</font></td>
    </tr>
    <tr>
      <td width="50%" align="right"><b>Importing</b> of an existing list needed?</td>
      <td>
        <select name="importlist" size="1">
          <option value="no"<?php if ($importlist=="no") echo " SELECTED"; ?>>No</option>
          <option value="yes"<?php if ($importlist=="yes") echo " SELECTED"; ?>>Yes</option>
        </select>
      </td>
    </tr>
    <tr>
      <td width="50%" align="right"><b>List Owner Name</b>.  One word:</td>
      <td><input type="text" name="listownername" value="<?=$listownername?>" size="35" READONLY></td>
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
          <option value="EzyListPro"<?php if ($howheard=="EzyListPro") echo " SELECTED"; ?>>EzyListPro</option>
          <option value="friend"<?php if ($howheard=="friend") echo " SELECTED"; ?>>Friend</option>
          <option value="other"<?php if ($howheard=="other") echo " SELECTED"; ?>>Other</option>
        </select>
      </td>
    </tr>
    <tr>
      <td colspan="2">
      <hr>
      <center><font size="+1">Pick a List Type and Size</font><br>With the Radio buttons on the left.</center><br>
      <table style="border-collapse: collapse" bordercolor="#000000" border="1" cellspacing="0" cellpadding="0" align="center">
        <tr>
          <td colspan="3" align="center" bgcolor="lightgrey"><b><font class="medsize">Safe Lists</font></b></td>
        </tr>
        <tr>
          <td bgcolor="beige"></td>
          <td bgcolor="beige" width="150" align="center">Safe List Members</td>
          <td bgcolor="beige" width="150" align="center">* Price Per Month</td>
        </tr>
        <tr>
          <td id="sl1-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl1');"<?php if ($whichlist=="sl1") echo " CHECKED"; ?>></td>
          <td id="sl1-2" width="150" align="center">0 - 1,000</td>
          <td id="sl1-3" width="150" align="center">$30</td>
        </tr>
        <tr>
          <td id="sl2-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl2');"<?php if ($whichlist=="sl2") echo " CHECKED"; ?>></td>
          <td id="sl2-2" width="150" align="center">1,001 - 2,000</td>
          <td id="sl2-3" width="150" align="center">$35</td>
        </tr>
        <tr>
          <td id="sl3-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl3');"<?php if ($whichlist=="sl3") echo " CHECKED"; ?>></td>
          <td id="sl3-2" width="150" align="center">2,001 - 3,000</td>
          <td id="sl3-3" width="150" align="center">$40</td>
        </tr>
        <tr>
          <td id="sl4-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl4');"<?php if ($whichlist=="sl4") echo " CHECKED"; ?>></td>
          <td id="sl4-2" width="150" align="center">3,001 - 4,000</td>
          <td id="sl4-3" width="150" align="center">$45</td>
        </tr>
        <tr>
          <td id="sl5-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl5');"<?php if ($whichlist=="sl5") echo " CHECKED"; ?>></td>
          <td id="sl5-2" width="150" align="center">4,001 - 8,000</td>
          <td id="sl5-3" width="150" align="center">$50</td>
        </tr>
        <tr>
          <td id="sl6-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl6');"<?php if ($whichlist=="sl6") echo " CHECKED"; ?>></td>
          <td id="sl6-2" width="150" align="center">8,001 - 10,000</td>
          <td id="sl6-3" width="150" align="center">$55</td>
        </tr>
        <tr>
          <td id="sl7-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl7');"<?php if ($whichlist=="sl7") echo " CHECKED"; ?>></td>
          <td id="sl7-2" width="150" align="center">10,001 - 15,000</td>
          <td id="sl7-3" width="150" align="center">$60</td>
        </tr>
        <tr>
          <td id="sl8-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('sl8');"<?php if ($whichlist=="sl8") echo " CHECKED"; ?>></td>
          <td id="sl8-2" width="150" align="center">15,001 - 20,000</td>
          <td id="sl8-3" width="150" align="center">$65</td>
        </tr>
      </table>
      <br>
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
          <td id="nl1-2" width="150" align="center">0 - 5,000</td>
          <td id="nl1-3" width="150" align="center">$20</td>
        </tr>
        <tr>
          <td id="nl2-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl2');"<?php if ($whichlist=="nl2") echo " CHECKED"; ?>></td>
          <td id="nl2-2" width="150" align="center">5,001 - 10,000</td>
          <td id="nl2-3" width="150" align="center">$25</td>
        </tr>
        <tr>
          <td id="nl3-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl3');"<?php if ($whichlist=="nl3") echo " CHECKED"; ?>></td>
          <td id="nl3-2" width="150" align="center">10,001 - 15,000</td>
          <td id="nl3-3" width="150" align="center">$30</td>
        </tr>
        <tr>
          <td id="nl4-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl4');"<?php if ($whichlist=="nl4") echo " CHECKED"; ?>></td>
          <td id="nl4-2" width="150" align="center">15,001 - 20,000</td>
          <td id="nl4-3" width="150" align="center">$35</td>
        </tr>
        <tr>
          <td id="nl5-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl5');"<?php if ($whichlist=="nl5") echo " CHECKED"; ?>></td>
          <td id="nl5-2" width="150" align="center">20,001 - 40,000</td>
          <td id="nl5-3" width="150" align="center">$40</td>
        </tr>
        <tr>
          <td id="nl6-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl6');"<?php if ($whichlist=="nl6") echo " CHECKED"; ?>></td>
          <td id="nl6-2" width="150" align="center">40,001 - 60,000</td>
          <td id="nl6-3" width="150" align="center">$45</td>
        </tr>
        <tr>
          <td id="nl7-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl7');"<?php if ($whichlist=="nl7") echo " CHECKED"; ?>></td>
          <td id="nl7-2" width="150" align="center">60,001 - 80,000</td>
          <td id="nl7-3" width="150" align="center">$50</td>
        </tr>
        <tr>
          <td id="nl8-1"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="list" onClick="javascript:changeColor('nl8');"<?php if ($whichlist=="nl8") echo " CHECKED"; ?>></td>
          <td id="nl8-2" width="150" align="center">80,001 - 100,000</td>
          <td id="nl8-3" width="150" align="center">$55</td>
        </tr>
      </table>
        <p>
          All list <b>configurations</b> such as, Sign-up messages, footers, headers, from email, bounce email and all other configurations are
          customizable by you once you have your <b>List Owner</b> account created.  We suggest you review the <b>Instruction Manual</b> while
          your order is being processed.
        </p>
        <p>
          <font size="+1"><b>Choose your method of payment.</b></font><br><br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="paypal"<?php if ($mop=="paypal") echo " CHECKED"; ?>><b>PayPal</b> - If you don't have an account you can signup then pay.<br><br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="clickbank"<?php if ($mop=="clickbank") echo " CHECKED"; ?>><b>Click Bank</b> - All major credit cards accepted.<br><br>
          <!-- <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="egold"<?php if ($mop=="egold") echo " CHECKED"; ?>><b>E-Gold</b> - Alternative to PayPal. //-->
        </p>
        <p align="center">
          <font color="red"><b><?="$notValid<br><br>"?></b></font>
          <input type="button" class="beigebutton" value="Buy your List" onClick="if (document.signup.mop[0].checked==false&&document.signup.mop[1].checked==false&&document.signup.mop[2].checked==false) alert('Pick a method of payment, please.'); else this.form.submit();">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <input type="reset" class="beigebutton" value="Reset">
          <input type="hidden" name="whichlist" value="<?=$whichlist?>">
          <input type="hidden" name="option" value="ownersignup">
          <input type="hidden" name="submitted" value="signup">
        </p>
        </form>
      </td>
    </tr>
  </table>
</td>