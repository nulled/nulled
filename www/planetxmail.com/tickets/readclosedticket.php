<table width="600" cellpadding="2" cellspacing="1">
  <tr>
    <td>
      <h2>Ticket Number: <?=$number?></h2>
      The top of this page will show the most recently received message.  All previous messages
      are displayed below the Ticket Options.
      <br><br>
      <?php if ($notValid) echo "<font color=red><b>$notValid</b></font><br><br>"; ?>
    </td>
  </tr>

  <?php

    for($i=0; $i<count($emails); $i++)
    {
    	$messages[$i] = wordwrap($messages[$i], 100);

    	list($site, $product, $listname, $username, $receipt) = explode("@%&", $subjects[$i]);
      $subjects[$i] = $site." ".$product." ".$listname." ".$username." ".$receipt;

      echo "<tr><td bgcolor=\"lightgrey\"><b>From: {$emails[$i]}</b><br></td></tr>\n";
      echo "<tr><td bgcolor=\"lightgrey\"><b>Date:</b> {$dates[$i]}</td></tr>\n";
      echo "<tr><td bgcolor=\"beige\"><b>Subject:</b> {$subjects[$i]}</td>\n";
      echo "<tr><td bgcolor=\"lightblue\"><pre>{$messages[$i]}</pre></td></tr>\n";
      echo "<tr><td><br></td></tr>\n";

      if ($i==0)
      {
        echo "<form name=\"closedticket\" action=\"$_SERVER[PHP_SELF]\" onSubmit=\"javascript:submitonce(this)\" method=\"POST\">\n";
        echo "<tr><td><b>Options for this Ticket:</b><br><br></td></tr>\n";
        echo "<tr><td><input type=\"radio\" name=\"status\" value=\"0\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\"> Delete Ticket from Database</td></tr>\n";
        echo "<tr><td><input type=\"radio\" name=\"status\" value=\"1\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\"> Open Ticket Back up so you can reply to it again</td></tr>\n";
        echo "<tr><td><br><input type=\"button\" value=\"Submit Option\" onClick=\"javascript:checkoption()\"></td></tr>\n";
        echo "<input type=\"hidden\" name=\"number\" value=\"{$number}\">\n";
        echo "<input type=\"hidden\" name=\"c\" value=\"readclosedticket\">\n";
        echo "<input type=\"hidden\" name=\"submitted\" value=\"openbackup\">\n";
        echo "</form>\n";
        echo "<tr><td><hr></td></tr>\n";
        echo "<tr><td align=\"center\">Previous Replies listed newest to oldest: (<i>if any</i>):<br><br></td></tr>\n";
      }
    }

  ?>

</table>