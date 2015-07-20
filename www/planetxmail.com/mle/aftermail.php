<?php

$option = trim($_GET['option']);
$o      = trim($_GET['o']);

if (! in_array($option, array('none','mailed','alreadymailed')))
  $option = 'alreadymailed';

$div = '<div style="background-color:lightblue;color:black;width:100%;height:20px;text-align:left;font-family:verdana;font-size:12px;padding:3px;margin:0px;">
';

$urlly = '<a href="/mle/main.php" class="urlly">Continue On ...</a> OR <a href="/soloads.php?list=aftermail" class="urlly" target="_blank">Get YOUR AD Shown Here</a>';

if ($option == 'none')
{
  $ret =  $div . '
  A) No members to Mail. B) All are On Vacation. C) Emails are all Bounced or Full Box. ' . $urlly . '
  </div>
';
}
else if ($option == 'mailed')
{
  $ret = $div . '
  Your Message Was Queued for Delivery. You will see your Ad Tomorrow. ' . $urlly . '
  </div>
';
}
else if ($option == 'alreadymailed')
{
  $ret = $div . '
   A) You already sent mail today. B) Your Weekly Mail Limit was Reached. C) If from Credit Mailer, You may be Out of Credits. ' . $urlly . '
  </div>
';
}

if ($o) echo $ret;

?>