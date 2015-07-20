<?php
if ($u==""||$o=="")
{
	echo "Missing required params. Contact: <b>accounts@planetxmail.com</b>";
	exit;
}

include("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT verified, memtype FROM users WHERE username='$u' AND elpownername='$o'");

if ($db->rows)
{
  list($verified, $memtype) = $db->FetchRow();

  if (! $verified)
  {
    $db->Query("UPDATE users SET verified='1' WHERE username='$u' AND elpownername='$o'");

    echo "<h2>Your Contact email address has been verified.</h2>\nYou can now <b>log in</b> if you have made your payment.<br><br>";
    if ($memtype=="pro")
      echo "If you have <b>not</b> made your <b>Sign up payment</b> you can do so here: <a href=\"http://www.planetxmail.com/elp/memsignuppaylinks.php?u=$u&o=$o\">Sign up Paylinks</a><br><br>\n";
    echo "Please contact: <b>accounts@planetxmail.com</b> for questions.";
  }
  else
  {
    echo "<h2>You are already verified.</h2>";
    if ($memtype=="pro")
      echo "If you have not made your payment you can do so here: <a href=\"http://www.planetxmail.com/elp/memsignuppaylinks.php?u=$u&o=$o\">Sign up Paylinks</a>\n";
  }
}
else
  echo "Your not in the database. Contact: <b>accounts@planetxmail.com</b>";

?>