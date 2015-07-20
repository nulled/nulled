<table width="640" cellspacing="2" cellpadding="3">

  <?php

    if (count($emails))
    {
      echo '<tr><td colspan="4" align="center"><h2>Open Tickets</h2>
      The last message received is at the top of the list.<br />This page also refreshes ever 1 minute to reveal any updates to tickets.
      <br /><br /></td></tr>
      <tr><td bgcolor="lightgrey"><b>Last&nbsp;Person&nbsp;to&nbsp;Email:</b></td>
      <td bgcolor="lightgrey"><b>Subject:</b></td>
      <td bgcolor="lightgrey"><b>Date&nbsp;Received:</b></td></tr>
      ';

      $prev_nums = array();
     for ($i=0; $i < count($emails); $i++)
      {
        if (! in_array($numbers[$i], $prev_nums))
        {
          if ($emails[$i] != 'admin-reply')
          {
            $waiting = 'Yes';
            $bgcolor = 'pink';
          }
          else
          {
            $waiting = 'No';
            $bgcolor = 'beige';
          }

          list($month, $day, $year) = explode(" ", $dates[$i]);
          $date = substr($month, 0, 3)." $day $year";

          list($site, $product, $listname, $username, $receipt) = explode("@%&", $subjects[$i]);
          $subject = $site." ".$product." ".$listname." ".$username." ".$receipt;

          if (strlen($subject)>40) $subject = substr($subject, 0, 40)."...";
          echo "<tr><td bgcolor=\"".$bgcolor."\">".$emails[$i]."</td>\n";
          echo "<td bgcolor=\"".$bgcolor."\"><a href=\"main.php?c=readreplyticket&n=".$numbers[$i]."\">".$subject."</a></td>\n";
          echo "<td bgcolor=\"".$bgcolor."\">".$date."</td></tr>\n";
          $prev_nums[] = $numbers[$i];
        }
      }
    }
    else
      echo '<tr><td align="center"><h2>No Open Tickets</h2></td></tr>';

  ?>

</table>