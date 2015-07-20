<?php
include("mlpsecure/config/classes.inc");
include("mlpsecure/config/config.inc");

$newnametotrack = trim($newnametotrack);
$newurltotrack = trim($newurltotrack);

$db = new MySQL_Access();
$db->Query("SELECT * FROM urlmanager WHERE userID='$_SESSION[aauserID]' ORDER BY urlID");

for ($i=0; $i<$db->rows; $i++)
{
  $urlnames = $db->FetchArray();

  if ($urlnames['name'] == $newnametotrack)
  {
    $notValid = "ERROR: URL name already used.";
    $notValid = urlencode($notValid);

    header("Location: main.php?option=urltrackers&notValid=$notValid");
    exit;
  }
}

if ($_SESSION['aastatus'] == "pro") $urlsallowed = $numurltrackersPro;
else if ($_SESSION['aastatus'] == "exe") $urlsallowed = $numurltrackersExe;
else if ($_SESSION['aastatus'] == "mem") $urlsallowed = $numurltrackersMem;

if ($db->rows > $urlsallowed-1)
{
  $notValid = urlencode("ERROR:  You are allowed only $urlsallowed url trackers.");
  header("Location: main.php?option=urltrackers&notValid=$notValid");
  exit;
}

if ($db->rows) $db->Seek(0);

// Find first open url id position
if ($db->rows)
{
  $num = $urlsallowed + 1;

  for ($i=1; $i < $num; $i++)
  {
    $urlIDs = $db->FetchRow();

    if (strcmp($urlIDs[2], $i))
    {
      $urlID = $i;
      break;
    }
  }

  if ($i < $urlsallowed) $urlID = $i;
}
else
  $urlID = 1;

$db->Query("INSERT INTO urlmanager VALUES ('$_SESSION[aauserID]','$newnametotrack','$urlID','$newurltotrack',NOW())");

$tracker = urlencode("http://www.planetxmail.com/mle/uht.php?urlID=$urlID&user=$_SESSION[aauserID]");

header("Location: main.php?option=urltrackerinstructions&tracker=$tracker");
exit;

?>
