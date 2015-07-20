<?php
die;
$headers   = 'From: Planet X Mail Solo AD <do_not_reply@planetxmail.com>';
$subject = 'Planet X Mail SOLO AD Receipt';
$message = file_get_contents('/home/nulled/www/planetxmail.com/messages/soloadreceipt.txt');

mail('elitescripts2000@gmail.com', $subject, $message, $headers);
?>
