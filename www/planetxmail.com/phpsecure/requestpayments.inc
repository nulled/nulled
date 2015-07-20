<?php

$db->SelectDB("pxm");

$db->Query("SELECT lastmailed FROM system WHERE (UNIX_TIMESTAMP(NOW()) - 86400) >= UNIX_TIMESTAMP(lastmailed)");
if ($db->rows)
{
	$table = "test"; // for debugging

  function mysql_timestamp_to_humandatetime1($dt){
	  $yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2)); $hr=strval(substr($dt,8,2));
	  $mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2)); return date("Y-m-d H:i:s", mktime ($hr,$mi,$se,$mo,$da,$yr));}

	$db->Query("SELECT datesubmitted, id, price, howheard, email, listtype, listnumber, listownername, listowneremail FROM $table WHERE verified='yes'");
	$data = $db->results;

	$currentdate = mysql_timestamp_to_humandatetime1(timestamp_to_mysql_timestamp(time()));
	list($cyear, $cmonth, $cday, $ctime) = preg_split('/[- ]/', $currentdate);

	$today = getdate();
	$senddate = $today[month]."/".$today[mday]."/".$today[year]." ".$today[hours].":".$today[minutes]." - ".$today[weekday];

	$subject = "PlanetXMail - Payment Due for your list";
	$headers = "From: PXM <do_not_reply@planetxmail.com>";

	while (list($date, $id, $price, $howheard, $email, $listtype, $listnumber, $listownername, $listowneremail) = mysqli_fetch_row($data))
	{
	  list($year, $month, $day, $time) = preg_split('/[- ]/', $date);

	  $price -= 25;

	  if ($cday==$day AND ($cmonth!=$month OR $cyear>$year))
	  {
	    $message = "Payment is due for your list hosted at www.planetxmail.com

Note: This pay notice will only be sent out once.
If after 7 days, payment is not received, your list
will be disabled and after 30 days deleted.

List Owner Name: $listownername
List Type: $listtype
List Size: $nummembers

Payment amount: \$$price

Click link below to choose method of payment:
http://www.planetxmail.com/listpayment.php?id=$id&listtype=$listtype&price=$price

Current date: $senddate
Date you signed up: $date

This is a new system we are adding.  If you feel there is something wrong and you
already paid please contact: accounts@planetxmail.com";

	    if (@mail($email, $subject, $message, $headers))
	    {
		    if ($email!=$listowneremail)
		      @mail($listowneremail, $subject, $message, $headers);

		    $db->Query("UPDATE $table SET paid='no' WHERE id='$id'");

		    @mail("elitescripts2000@yahoo.com", $subject, $message, $headers);
		  }
		  else
		  	exit('ERROR: file login.inc  Clean system code failure in pxm renewal area.  Contact: elitescripts2000@yahoo.com and notify.');
	  }
	}

	// end of daily system cleaning
	$db->Query("UPDATE system SET lastmailed='$midnight'");
	$db->SelectDB("mle");
}

?>
