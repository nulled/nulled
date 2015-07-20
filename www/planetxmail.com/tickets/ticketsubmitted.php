<table>
  <tr>
    <td>

      <?php

        if ($m == 'deleted')
        {
          echo '
          Your reply was sent to <b>'.$e.'</b> and this ticket was also <b>CLOSED</b>.
          <br /><br />
          <a href="main.php?c=readclosedticket&number='.$n.'">Delete Closed Ticket</a>
          <br /><br />
          <a href="main.php?c=viewopentickets">Keep Closed Ticket and Goto Open Tickets</a>
          <br /><br />
          <div id="layer1" style="border: 1 solid black"></div>
          ';
        }
        else
        {
          echo '
          Your reply was sent to <b>'.$e.'</b> and ticket is still <b>OPEN</b>.
          <br /><br />
          <a href="main.php?c=viewopentickets">Goto Open Tickets</a>
          <br /><br />
          <div id="layer1" style="border: 1 solid black"></div>
          ';
        }

      ?>

    </td>
  </tr>
</table>