<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

$usr = strrev($u);

$db->Query("SELECT listname, listownerID FROM users WHERE userID='$usr' LIMIT 1");
list($list, $id) = $db->FetchRow();

require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

?>