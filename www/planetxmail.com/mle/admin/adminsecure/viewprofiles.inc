<?php
if ($submitted == 'getprofile')
{
  header("Location: showmember.php?user=$member");
  exit;
}
else if ($submitted == 'deleteunverifiedmember')
{
  require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

  $db = new MySQL_Access('mle');

  $db->Query("DELETE FROM users WHERE userID='$member' AND listownerID='{$_SESSION['aalistownerID']}' AND listname='{$_SESSION['aalistname']} LIMIT 1'");
}

$getData = 1;

require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/getmembers.inc');

?>