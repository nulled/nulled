<?php
function writeproc($str)
{
  if ($fp = @fopen("secure/2c_proctrans.log","a"))
  {
  	chmod("secure/2c_proctrans.log", 0777);
    fwrite($fp, "$str\n");
    fclose($fp);
  }
  else
  	@mail("accounts@planetxmail.com", "2c_proctrans error", "unable to open log file for writting.");
}

function soload($id, $receipt, $profits)
{
  writeproc("soload attempt - id: $id - receipt: $receipt");

  $db = new MySQL_Access("mle");

  $date = date("F j, Y");
  $headers = "From: PXM <accounts@planetxmail.com>";

  if ($db->Query("SELECT email, subject, message, listname FROM soloads WHERE id='$id'"))
  {
    list($email, $adsubject, $admessage, $type) = $db->FetchRow();

    include("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

    $db->Query("UPDATE soloads SET receipt='$receipt', mop='Paypal' WHERE id='$id'");

    // mail buyer
    $subject = "Planet X Mail SOLO AD receipt.";
    $message = file_get_contents("/home/nulled/www/planetxmail.com/messages/soloadreceipt.txt");

    if (strstr($type, "HTMLSOLOAD"))
    {
      $message = str_replace("\n", "<br>\n", $message);
      $headers .= "\r\nContent-Type: text/html; charset=iso-8859-1";
    }

    $message = str_replace("[subject]", $adsubject, $message);
    $message = str_replace("[message]", $admessage, $message);
    $message = str_replace("[mop]", "Paypal", $message);
    $message = str_replace("[date]", $date, $message);

    $message = wordwrap($message, 70);

    @mail($email, $subject, $message, $headers);
    @mail("kukowski74@hotmail.com", $subject, $message, $headers);

    // record in transactions table
		$db->SelectDB("pxm");
		$db->Query("INSERT INTO transactions VALUES('','soload','$profits','paypal','$receipt',NOW())");
  }
  else
  {
    writeproc("ID not found when in soload()\n");
    exit;
  }
}

writeproc(" $order_number;");
writeproc(" $card_holder_name;");
writeproc(" $email;");
writeproc(" $merchant_order_id;");
writeproc(" $credit_card_processed;");
writeproc(" $total;");
writeproc(" $product_id;");
writeproc(" $merchant_product_id;");
writeproc(" $product_description;");
writeproc(" $receiver_email;");


?>
