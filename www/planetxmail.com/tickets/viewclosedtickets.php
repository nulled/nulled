<table width="600">

  <?php

    if (count($emails))
    {
      echo "<tr><td colspan=\"4\" align=\"center\"><h2>Closed Tickets</h2></td></tr>\n";
      echo "<tr><td bgcolor=\"lightgrey\"><b>Client Email:</b></td><td bgcolor=\"lightgrey\"><b>Email Subject:</b></td><td bgcolor=\"lightgrey\"><b>Date Received:</b></td><td bgcolor=\"lightgrey\"><b>Ticket Number:</b></td></tr>\n";

      $nums = array();
      for($i=0; $i<count($emails); $i++)
      {
        if (! in_array($numbers[$i], $nums))
        {
        	list($month, $day, $year) = explode(" ", $dates[$i]);
          $date = substr($month, 0, 3)." $day $year";

          list($site, $product, $listname, $username, $receipt) = explode("@%&", $subjects[$i]);
          $subjects[$i] = $site." ".$product." ".$listname." ".$username." ".$receipt;

          if (strlen($subjects[$i])>25) $subject = substr($subjects[$i], 0, 25)."...";
          echo "<tr><td bgcolor=\"beige\">$emails[$i]</td>\n";
          echo "<td bgcolor=\"beige\"><a href=\"main.php?c=readclosedticket&n=$numbers[$i]\">$subjects[$i]</a></td>\n";
          echo "<td bgcolor=\"beige\">$date</td>\n";
          echo "<td bgcolor=\"beige\"><a href=\"main.php?c=readclosedticket&n=$numbers[$i]\">$numbers[$i]</a></td></tr>\n";
          $nums[] = $numbers[$i];
        }
      }
    }
    else
      echo "<tr><td align=\"center\"><h2>No Closed Tickets</h2></td></tr>";

  ?>

</table>