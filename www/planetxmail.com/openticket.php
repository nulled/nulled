<?php

if ($_GET['html'])
{
  $hash = substr(sha1($_GET['time'] . 'ks754gSkn86dgSbd7d'), 0, 5);

  if ($hash == $_GET['hash'] AND (time()-$_GET['time']) < 5) {
    exit(rawurldecode($_GET['html']));
  } else {
    header('Location: openticket.php');
    exit;
  }
}

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/phpsecure/turingkey.class.inc');

$db        = new MySQL_Access('pxm');
$turingkey = new TuringKey(300);

$max_chars    = 5000;
$banned_words = array('cialis', 'viagra', 'levitra', 'Secret of Making Money', 'handbag', 'ringtones');

$email    = strtolower(trim($_POST['email']));
$site     = strip_tags(trim($_POST['site']));
$username = strip_tags(trim($_POST['username']));
$summary  = strip_tags(trim($_POST['summary']));
$message  = strip_tags(trim($_POST['message']));

if ($_POST['submitted'] == 'addticket')
{
  // build subject
  $username = sanstr($username);
  $summary  = sanstr($summary);

  // check for spam
  $banned = '';
  foreach ($banned_words as $word)
  {
    if (stripos($message.$subject, $word) !== false)
      $banned = 'ERROR: Illegal words in Subject and/or Message.';
  }

  if ($message == '')                     $notValid = 'ERROR: Missing Message.';
  else if ($site == '')                   $notValid = 'ERROR: Choose a Department.';
  else if (strlen($message) > $max_chars) $notValid = "ERROR: Message exceeds $max_chars Characters.";
  else if (! $turingkey->validate())      $notValid = 'ERROR: You have ' . $turingkey->time_limit . ' seconds before Turing Key Expires.';
  else if ($banned)                       $notValid = $banned;
  else if ($notValid = EmailFormat($email)) {}
  else
  {
    if (strlen($summary) > 40)
      $summary = substr($summary, 0, 40);

    $subject = "$site $username $summary";

    $subject = $db->EscStr($subject);
    $message = $db->EscStr($message);

    $number = substr(sha1(microtime(1) . $email), 0, 8);

    $db->Query("INSERT INTO tickets VALUES('','$number','$email','$subject','$message','1',NOW())");

    $date = date('F j, Y, g:i a');

    $host = get_ticket_host($site);

    $headers = "From: $host <do_not_reply@planetxmail.com>";

    $subject = "$host Ticket Request Received.";

    $message  = "We received your request for support on: $date\n\n";
    $message .= "Your Ticket history: http://planetxmail.com/clientreply.php?n=$number\n\n";
    $message .= "We will respond to your question as soon as we can.\n\n";
    $message .= "Thank you,\n";
    $message .= "$host Team";

    $ticketlink = "http://planetxmail.com/clientreply.php?n=$number";

    @mail($email, $subject, $message, $headers);
    @mail('elitescripts2000@yahoo.com', $subject, $message, $headers);

    $html = rawurlencode('<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Open a Ticket</title>
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
Your question was submitted.  Please, wait for a response at: <b>' . $email . '</b>.
<br /><br />
Or, <a href="clientreply.php?n=' . $number . '">Click Here.</a>
</div>
</body>
</html>');

    $time = time();
    $hash = substr(sha1($time . 'ks754gSkn86dgSbd7d'), 0, 5);

    header("Location: openticket.php?time={$time}&hash={$hash}&html={$html}");
    exit;
  }
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Open a Ticket</title>
<link rel="stylesheet" type="text/css" href="x.css" />
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
</style>
<script language="javascript">
var focused = false;
function updateCount()
{
  if (focused) {
    document.openticket.countmessage.value = <?=$max_chars?> - document.openticket.message.value.length;
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
<body onload="document.openticket.countmessage.value = <?=$max_chars?> - document.openticket.message.value.length">
<div align="center" class="main_content">
<table align="center" border="0" width="640">

  <tr>
    <td colspan="2">
      <h3>Open a Ticket/Email for Support</h3>
      <?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div>'; ?>
    </td>
  </tr>

  <form name="openticket" action="openticket.php" method="POST">

  <tr>
    <td align="right">Reply <b>Email:</b></td>
    <td><input type="text" name="email" value="<?=$email?>" size="40" maxlength="100" /> Must be <i>valid</i> so we can reply to you!</td>
  </tr>

  <tr>
    <td colspan="2"><hr></td>
  </tr>

  <tr>
    <td align="right"><b>Department</b>:</td>
    <td>
      <select name="site">
        <option<?php if (! $site)                     echo ' selected="selected"'; ?> value="">-- Choose a Department --</option>
        <option<?php if ($site == 'planetxmail')      echo ' selected="selected"'; ?> value="planetxmail">planetxmail.com</option>
        <option<?php if ($site == 'targetedadplanet') echo ' selected="selected"'; ?> value="targetedadplanet">targetedadplanet.com</option>
        <option<?php if ($site == 'freeadplanet')     echo ' selected="selected"'; ?> value="freeadplanet">freeadplanet.com</option>
      </select>
    </td>
  </tr>

  <tr>
    <td align="right"><b>Username</b>:</td>
    <td><input type="text" name="username" value="<?=$username?>" size="10" maxlength="20" /></td>
  </tr>

  <tr>
    <td align="right"><b>Summary</b>&nbsp;:</td>
    <td><input type="text" name="summary" value="<?=$summary?>" size="30" maxlength="40" ></td>
  </tr>

 <tr>
    <td colspan="2"><hr></td>
  </tr>

  <tr>
    <td valign="top" align="right"><b>Message:</b></td>
    <td>
      <textarea cols="80" rows="20" wrap="PHYSICAL" onFocus="focused=true" onBlur="focused=false" name="message"><?=$message?></textarea>
      <br />
      <input type="text" name="countmessage" size="2" readonly="readonly" />&nbsp;&nbsp;Characters Remaining
    </td>
  </tr>

  <tr>
    <td align="center" colspan="2">
      Entering Turing Key: <img src="/mle/keyimages/<?=$turingkey->keyfilename?>" border="0" />
      <input type="text" name="key" size="4" maxlength="4" />
      <br /><br /> <!-- this.disabled=true;checkCount(this.form) -->
      <input type="submit" value="Submit Ticket" onclick="this.value='Loading...';this.disabled=true;checkCount(this.form)" />
    </td>
  </tr>

  <input type="hidden" name="c" value="openticket" />
  <input type="hidden" name="submitted" value="addticket" />
  <input type="hidden" name="validate" value="<?=$turingkey->validate?>" />
  </form>

</table>
</div>
</body>
</html>