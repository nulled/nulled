<table width="500">
  <tr>
    <td>
      <h2>Ticket Number: <?=$number?></h2>
      The top of this page will show the most recently received message.  All previous messages
      are displayed at the bottom. If you are waiting for the client to respond your <i>admin-reply</i>
      will be at the top instead.  You can choose to respond to any message the client  sends by clicking
      on it's <b>subject line</b>.
      <br /><br />
      <?php if ($notValid) echo '<font color="red"><b>' . $notValid . '</b></font><br /><br />'; ?>
    </td>
  </tr>
  <?php

    if (count($emails))
    {
      for($i = 0; $i < count($emails); $i++)
      {
        if ($i == 0 AND $emails[$i] == 'admin-reply')
        {
          echo '<tr><td>You can not reply to your own message, which was the last message sent so far for this ticket.
          If you wish to respond to a customer request, click on the <b>subject line</b> of the corresponding
          message.</b><br /><br /></td></tr>
          <form name="replyticket" action="/tickets/main.php" onSubmit="submitonce(this)" method="POST">
          <tr><td><b>Close this Ticket?</b><br /><br /></td></tr>
          <tr><td><input type="button" name="submitButton" value="Submit" onClick="checkreply(1)" /></td></tr>
          <tr><td><input type="radio" name="status" value="0" style="border-width:0px" /> Close Ticket</td></tr>
          <input type="hidden" name="n" value="' . $number . '" />
          <input type="hidden" name="c" value="readreplyticket" />
          <input type="hidden" name="submitted" value="close" />
          </form>
          <tr><td><hr></td></tr>
          <tr><td align="center">Previous Replies listed newest to oldest: (<i>if any</i>):<br /><br /></td></tr>';
        }

        echo '<tr><td bgcolor="lightgrey"><b>From: ' . $emails[$i] . '</b><br /></td></tr>
              <tr><td bgcolor="lightgrey"><b>Date:</b> ' . $dates[$i] . '</td></tr>';

        if ($i > 0 AND $emails[$i] != 'admin-reply')
          echo '<tr><td bgcolor="beige"><b>Subject:</b> <a href="main.php?c=readreplyticket&n=' . $number . '&id=' . $ids[$i] . '">' . $subjects[$i] . '</a></td>';
        else
          echo '<tr><td bgcolor="beige"><b>Subject:</b> ' . $subjects[$i] . '</td>';

        $messages[$i] = wordwrap($messages[$i], 70);

        echo '<tr><td bgcolor="lightblue"><pre>' . $messages[$i] . '</pre></td></tr>
              <tr><td><br /></td></tr>';

       if ($i == 0 AND $emails[$i] != 'admin-reply')
       {
          echo '<form name="replyticket" action="/tickets/main.php" onSubmit="submitonce(this)" method="POST">
          <tr><td><b>Reply to this Ticket</b><br /><br /></td></tr>
          <tr><td><b>Subject:</b><br /><input type="text" name="sub" value="' . $sub . '" size="70" readonly /></td></tr>
          <tr><td><b>Message:</b><br /><textarea cols="80" rows="15" wrap="PHYSICAL" onFocus="focused=true" onBlur="focused=false" name="mess">' . $mess . '</textarea></td></tr>
          <tr><td><input type="button" value="Submit Ticket" onClick="checkreply(0)"></td></tr>
          <tr><td><input type="radio" name="status" value="1" style="border-width:0px"> Keep Ticket Open</td></tr>
          <tr><td><input type="radio" name="status" value="0" style="border-width:0px"> Close Ticket and send your reply</td></tr>
          <tr><td><input type="radio" name="status" value="2" style="border-width:0px"> Close Ticket and DO NOT send a reply</td></tr>
          <input type="hidden" name="n" value="' . $number . '">
          <input type="hidden" name="e" value="' . urlencode($emails[0]) . '">
          <input type="hidden" name="c" value="readreplyticket">';

          if (isset($msgid)) echo '<input type="hidden" name="id" value="' . $msgid . '">';

          echo '<input type="hidden" name="submitted" value="reply">
          </form>
          <tr><td><hr></td></tr>
          <tr><td align="center">Previous Replies listed Newest to Oldest: (<i>if any</i>):<br /><br /></td></tr>';
        }
      }
    }

  ?>

</table>