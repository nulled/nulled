<?php
include("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc");

// Note:
// Need to update pxm DB
// Need to delete the listowner from mle.listowner if no more remaing lists

$listownerID = "1019244831";  // id to move list to
$listname_to_move  = "SharedProfitClub"; // list to move
$move_from_id  = "4394402383"; // id to move from

exit;

$db = new MySQL_Access("mle");

$db->Query("UPDATE users SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE upgrade SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE system SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE listurls SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE listmanager SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE listconfig SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE banners SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE ads SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");
$db->Query("UPDATE banneddomains SET listownerID='$listownerID' WHERE listname='$listname_to_move' AND listownerID='$move_from_id'");

echo "Done";

?>