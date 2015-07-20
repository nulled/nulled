<table width="590" cellpadding="5" cellspacing="0">
  <tr>
    <td>
      <table align="center">
        <tr>
          <td>
            <center><font size="+2"><b>Your Affiliate Stats</b></font>
            <br />
            The List Owner is offering the following Commissions Rates:
            <br /><br />
              <li><b><?=$commission_pro?> %</b> commissions for Pro Referrals, which means <b>$ <?=number_format($owed_pro, 2, '.', '')?></b> Per Referral</li>
              <li><b><?=$commission_exe?> %</b> commissions for Exe Referrals, which means <b>$ <?=number_format($owed_exe, 2, '.', '')?></b> Per Referral</li>
            <br />
            <font size="3">Affiliate URL for this SafeList:</font>
            <br /><br />
            <input type="text" size="60" value="http://planetxmail.com/mle/affsignup.php?affid=<?=$affid?>" readonly />
            <?php if ($notValid) echo '<br /><b class="red">' . $notValid . '</b>'; ?>
            <br /><br />
            Your Paypal address:
            <form name="affmop" action="/mle/main.php" method="POST">
              <input type="text" size="35" name="affiliatemop" value="<?=$affiliatemop?>" />
              <input type="hidden" name="option" value="memberaffview" />
              <input type="hidden" name="submitted" value="affmop" />
              <input type="submit" value="Change Address" />
            </form>
            <br />
            <?php

              if (! $affiliatemop)
                echo '<font size="2">You will be paid your commissions through Paypal. If you do not have a Paypal account, please goto
                      <a href="https://www.paypal.com/refer/pal=accounts%40planetxmail.com" target="_BLANK"><b>www.paypal.com</b></a>
                      and Sign Up!  It is <i>FREE</i> and is the most widely used and trusted online merchant account available.</font>
                      <br /><br />
                      ';

            ?>
            <font size="3">People you have referred:</font></center>
            <table align="center" cellspacing="2" cellpadding="1">
              <tr>
                <td bgcolor="lightblue"><b>User Name</b></td>
                <td bgcolor="lightblue"><b>Date Signed Up</b></td>
                <td bgcolor="lightblue"><b>List Owner Paid You</b></td>
              </tr>
              <?php
                $i = 0;
                while (list($username, $datesignedup, $paid, $status) = mysqli_fetch_row($affiliates))
                {
                  list($datesignedup) = explode(" ", $datesignedup);
                  if ($i%2==0)
                    $bgcolor = "F4F4F7";
                  else
                    $bgcolor = "E9E9E9";

                  if ($paid) $paid = "Yes"; else $paid = "No";
                  if ($status=="mem") $paid = "Signed up as Free";
                  echo "<tr><td bgcolor=\"$bgcolor\">$username</td><td bgcolor=\"$bgcolor\">$datesignedup</td><td bgcolor=\"$bgcolor\" align=\"center\">$paid</td></tr>\n";
                  $i++;
                }
              ?>
            </table>
          </td>
        </tr>
        <tr>
          <td>
            <br><br>
            Members must sign up or upgrade to a Pro or Exe account in order for you to earn credit.  Also, note that if the values above change, this is
            due to the List Owner changing their Prices and or Commission percentages.  Even if you where paid already you may see the stats shift.  Depending
            on the demand for this system and how it works out we plan to add A LOT more features... stay tuned.
            <br><br>
            If you are getting sign ups but the List Owner is not paying your commissions, please email: accounts@planetxmail.com ... or for any other questions
            regarding MLE SafeLists.
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>