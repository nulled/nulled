<table width="590" cellpadding="5" cellspacing="0">
  <tr>
    <td>
      <table align="center">
        <tr>
          <td>
            <center><font size="+2"><b>Your URL trackers.</b></font></center>
            <br>
            <font size="-1"><b><font color="red">If it is found that you are using ANY URL Trackers to track SPAM mail your COMPLETE membership account will be DELETED without notice!</font></b>
            <br><br>
            We recently had to add an <b>inbetween page</b> which asks if the URL tracker was found in SPAMMED eMail.  We will then delete ANY account found guilty
            of using our URL Trackers in SPAMMED eMail, <b>without refund</b>.  So if you value your SafeList account it is best you not use our URL Trackers to track your SPAM!</font><br>
            <center>
            <font color="red"><?php if ($notValid) echo $notValid."<br><br>"; ?></font></center>
            <form name="urllist" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
            <input type="text" size="2" value="<?=$numurls?>" readonly>&nbsp;URLs being tracked out of <?php if ($_SESSION[aastatus]=="mem") echo $numurltrackersMem; else if ($status=="pro") echo $numurltrackersPro; else echo $numurltrackersExe; ?> allowed.<br><br>
            <select name="urlID" size="10">
              <option></option>
            <?php
              while ($row = mysqli_fetch_array($results))
                echo "<option value=\"".$row['name']."\">".$row['name']."</option>\n";
            ?>
            </select><br>
            <input type="hidden" name="submitteddelview" value="1">
            <input type="hidden" name="option" value="urltrackers">
            <input type="button" class="beigebutton" value="View Stats" onClick="urlTrackerChoice(1,urlID.value)">
            <img src="<?php if ($membername!="") echo "../images/null.gif"; else echo "images/null.gif";?>" width="50" height="1" border="0">
            <input type="button" class="redbutton" value="Delete URL Tracker" onClick="urlTrackerChoice(2,'none')"><br>
            </form>
            <form name="addurl" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
            Add a URL to track<br>
            <input type="text" name="newnametotrack">&nbsp;&nbsp;&nbsp;&nbsp;<b>Enter a Friendly Name for the tracker.</b><br>
            <input type="text" name="newurltotrack" value="http://" size="50">&nbsp;&nbsp;&nbsp;&nbsp;<b>Enter the URL to track.</b><br>
            <input type="hidden" name="option" value="urltrackers">
            <input type="hidden" name="submittedaddurltracker" value="1"><br>
            <input type="submit" class="greenbutton" value="Submit URL Tracker">
            </form>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>