<table width="695" cellpadding="3" cellspacing="0" align="center" border="0">
  <tr>
    <td colspan="2" align="center">
      <font size="+2" color="#005F8C"><b>Regular Mailer</b></font>
      <hr>
    </td>
  </tr>

  <tr>
    <td colspan="2">

      <?php

        if ($nextmaildate AND substr($lastvacation, 0, 1) == "0" AND ! $vacation)
        {
          echo '<form style="width: 400px" name="clock">
                  <input type="text" size="12" name="face" READONLY /> <b>' . $nextmaildate . '</b><br />Counting down until the next time you can mail. <i>Eastern Time</i>
                </form><hr />' . "\n";
        }
        else
        {
          if ($vacation)
            echo '<center><font size="+1"><b>You can\'t mail, your vacation switch is on!</b></font><br></center>' . "\n";
          else if (substr($lastvacation, 0, 1) != '0')
            echo '<center><font size="+1"><b>Your vacation switch is off, but you need to wait a Day for it to reset!</b></font></center>' . "\n";
          else
            echo '<center><font size="+1"><b>You can mail today!</b></font></center>' . "\n";
        }

      ?>

    </td>
  </tr>

  <tr>
    <td align="center" colspan="2">
      <div style="font-size: 11px; text-align: center;">Works in the <b>Subject</b> and <b>Message</b>.
      <br />
      <b>[first_name]</b> - Replaced with each member's First Name.
      </div>
      <hr>
    </td>
  </tr>

  <tr>
    <td align="right">
      <form name="sendmail" action="/mle/main.php" method="POST" onSubmit="submitonce(this)">
      <b>Subject:</b>
    </td>
    <td>
      <input type="text" name="subject" size="60" value="<?=$subject?>" maxlength="70" />
    </td>
  </tr>

  <tr>
    <td align="right" valign="top">
      <script>
        var fwidth=100;
        var fheight=200;
        var delay=5000;
        var fcontent=new Array();
        begintag='<font size="2">';
        <?php
          $i=0;
          while (list($ad) = mysqli_fetch_row($directads))
          {
            $ad = str_replace("\r\n", "\\n", stripslashes($ad));
            echo "fcontent[$i]='$ad';\n";
            $i++;
          }

          // no direct ad, so we use a place holder
          if (! $i)
          {
            $ad = '<img src="http://planetxmail.com/images/elogo.jpg" /><hr />
<font size="-2">Here is an <b>example</b> AD.</font>
<br /><br /><i>AMAZING!</i>
<br /><br />You can even add graphics!';
            $ad = str_replace(array("\r\n","\n"), '', stripslashes($ad));
            echo "fcontent[$i]='$ad';\n";
          }
        ?>
        closetag='</font>';
      </script>
      <img src="images/null.gif" border="0" height="1" width="50"><b>Message:</b><br /><br />
      <script text="text/javascript" src="da.js"></script>
      <ilayer id="fscrollerns" width=&{fwidth}; height=&{fheight};><layer id="fscrollerns_sub" width=&{fwidth}; height=&{fheight}; left=0 top=0></layer></ilayer>
      <a href="http://planetxmail.com/directads.php?list=<?=$_SESSION['aalistname']?>" target="_blank"><font size="-2"><b>Your Ad Cound Be Here!</b></font></a>
    </td>
    <td valign="top">
      <textarea id="themessage" wrap="physical" rows="25" cols="60" name="message" onFocus="focused=true" onBlur="focused=false"><?=$message?></textarea><br>
      <?php echo '<input type="text" name="countmessage" size="4" readonly />&nbsp;&nbsp;Characters Remaining.' . "\n"; ?>
    </td>
  </tr>

  <tr>
    <td align="center" valign="top" colspan="2">
      <input type="hidden" name="submitted" value="mail" />
      <input type="hidden" name="option" value="sendmail" />
      <?php

      if (! $html)
        echo '<input type="checkbox" onclick="location.href=\'/mle/main.php?option=sendmail&html=1\'" style="border-width:0px;" />Check to send as HTML format!<br /><br />';
      else
        echo '<input type="hidden" name="sendashtml" value="1" />' . "\n";

      echo 'Credit URL: <input type="text" name="crediturl" value="' . $crediturl . '" size="50" maxlength="255" />&nbsp;<a href="../creditmailerhowto.php" target="_blank">What is this?</a><br><i>Example: http://yoursite.com</i><br><br>';

      ?>

      <input type="button" onclick="doSubmit(this)" class="greenbutton" value="Send Mail"><br>
    </td>
  </tr>
  </form>
</table>
