<?php

if ($_GET['html'])
{
  $hash = substr(sha1($_GET['time'] . $_GET['n'] . 'ks754gSkn86dgSbd7d'), 0, 5);

  if ($hash == $_GET['hash'] AND (time()-$_GET['time']) < 5) {
    exit(rawurldecode($_GET['html']));
  } else {
    header('Location: openticket.php?n=' . $_GET['n']);
    exit;
  }
}

$SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$max_chars = 5000;

$number = trim($_GET['n']);

if (! @ctype_alnum($number))
  exit('Ticket number/URL is not valid.  Be sure you correctly typed or pasted the URL to your browser.');

$db = new MySQL_Access('pxm');

if ($_POST['submitted'] == 'reply')
{
  $subject = trim($_POST['subject']);
  $message = trim($_POST['message']);
  $number  = trim($_POST['n']);
  $email   = urldecode(trim($_POST['e']));

  if ($message == '')                     $notValid = 'ERROR: Missing Required Fields.';
  else if (strlen($message) > $max_chars) $notValid = 'ERROR: Message Exceeds ' . $max_chars . ' Characters.';
  else if (! ctype_alnum($number))        $notValid = "ERROR: Ticket Number is Invalid.";
  else
  {
    $message = $db->EscStr($message);

    $db->Query("INSERT INTO tickets VALUES('','$number','$email','$subject','$message','1',NOW())");

    $date = date('F j, Y, g:i a');

    $host = get_ticket_host($subject);

    $headers = "From: $host <do_not_reply@planetxmail.com>";

    $subject = "$host request received.";

    $message  = "We received your request for support on: $date\n\n";
    $message .= "Your Ticket history: http://planetxmail.com/clientreply.php?n=$number\n\n";
    $message .= "We will respond to your question as soon as we can.\n\n";
    $message .= "Thank you,\n";
    $message .= "$host Team";

    @mail($email, $subject, $message, $headers);

    $html = rawurlencode('<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Client Reply to Ticket</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<style>
.message {
width: 500px;
font-size: 16px;
text-align: center;
margin: 10px auto;
padding: 10px;
border: 1px solid black;
}
</style>
</head>
<body>
<div class="message">
Your question was submitted. Please wait for a response at your Email: <b>' . $email . '</b>
</div>
</body>
</html>');

    $time = time();
    $hash = substr(sha1($time . $number . 'ks754gSkn86dgSbd7d'), 0, 5);

    header("Location: clientreply.php?time={$time}&hash={$hash}&html={$html}&n=$number");
    exit;
  }
}

if (! $db->Query("SELECT email, subject, message, open FROM tickets WHERE number='$number' ORDER BY id DESC"))
  exit('Ticket number was not found. Incorrectly entered number or was deleted from our database. <a href="openticket.php">Open a new Ticket</a>');

$emails = $subjects = $messages = array();

while(list($email, $subject, $message, $status) = $db->FetchRow())
{
  if (! $status)
    exit('This ticket is closed. If you wish to open a new ticket <a href="openticket.php">Click Here</a>.');

  $emails[]   = $email;
  $subjects[] = $subject;
  $messages[] = htmlentities($message);
}

$foundemail = false;
if (count($emails))
{
  foreach ($emails as $email)
  {
    if ($email != 'admin-reply')
    {
      $foundemail = true;
      break;
    }
  }
}

if (! $foundemail)
  exit('FATAL ERROR: Unable to find your reply email. <a href="openticket.php">Click here</a> to open a new ticket.');

$site_host = get_ticket_host($subjects[0]);

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Reply to Ticket</title>
<link rel="stylesheet" type="text/css" href="tickets/x.css" />
<style>
.main_content {
  margin: 10px auto;
  overflow: auto;
  width: 850px;
  border: 1px solid black;
}
.notValid {
  border: 1px solid red;
  background-color: pink;
  color: black;
  font-size: 14px;
  width: 400px;
  padding: 10px;
  margin: 5px auto;
  border-radius: 5px;
  text-align: center;
}
textarea {
  resize: none;
}
</style>
<script>
var focused = false;
function updateCount()
{
  if (focused) {
    document.replyticket.countmessage.value = <?=$max_chars?> - document.replyticket.message.value.length;
  }
}

function checkCount(formname)
{
  if (formname.message.value.length > <?=$max_chars?>) {
    alert('Message greater than <?=$max_chars?> Characters.');
  } else {
    formname.submit();
  }
}
document.onkeyup = updateCount;
</script>
</head>
<?php flush(); ?>
<body>
<table width="640">
  <tr>
    <td>
      <h2><?=$site_host?></h2>

      <h2>Ticket: <?php echo "$number<br />Email: $email"; ?></h2>
      Most recently received messages are at top.  Previous messages
      appear <i>below</i> the Ticket Reply Text Area.
      <br /><br />
      <?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div>'; ?>
    </td>
  </tr>

  <?php

    if (count($emails))
    {
      for($i = 0; $i < count($emails); $i++)
      {
        $messages[$i] = wordwrap($messages[$i], 70);

        $num_lines = count(explode("\n", $messages[$i]));

        echo "<tr><td bgcolor=\"lightblue\"><b>From: {$emails[$i]}</b><br /></td></tr>\n";
        echo "<tr><td bgcolor=\"beige\"><b>Subject:</b> {$subjects[$i]}</td>\n";
        echo "<tr><td bgcolor=\"#e3e3e3\"><pre>{$messages[$i]}</pre></td></tr>\n";
        echo "<tr><td><hr /></td></tr>\n";

        if ($i == 0)
        {
          $sub_prefix = '';
          if (! strstr($subject, 'Re: Re: '))
            $sub_prefix = 'Re: ';

          echo '
          <form name="replyticket" action="clientreply.php" method="POST">
            <tr><td><b>Subject:</b> <i>(already set)</i><br /><input type="text" name="subject" value="' . $sub_prefix . $subjects[$i] . '" size="70" readonly="readonly" /></td></tr>
            <tr><td><b>Message:</b> <i>(Please, do not use ALL CAPS!)</i><br />
            <textarea cols="80" rows="20" wrap="PHYSICAL" onfocus="focused=true" onblur="focused=false" name="message">' . $message[$i] . '</textarea></td></tr>
            <tr><td><input type="text" name="countmessage" size="4" readonly="readonly" />&nbsp;&nbsp;Characters Remaining</td></tr>
            <tr><td><input type="submit" value="Reply to Ticket" onclick="this.value=\'Loading...\';this.disabled=true;checkCount(this.form)" /></td></tr>
            <input type="hidden" name="n" value="' . $number . '" />
            <input type="hidden" name="e" value="' . urlencode($email) . '" />
            <input type="hidden" name="submitted" value="reply" />
          </form>
          <tr><td><hr /></td></tr>
          <tr><td align="center">Previous Replies listed Newest to Oldest: (<i>if any</i>):<br /><br /></td></tr>
          ';
        }
      }
    }

  ?>

</table>
</body>
</html>