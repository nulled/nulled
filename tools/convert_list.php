<?php
require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc");
require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");
require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc");

function get_pricing($totalmembers)
{
  if ($totalmembers < 1001) $price = 55;
	else if ($totalmembers < 2001) $price = 60;
	else if ($totalmembers < 3001) $price = 65;
	else if ($totalmembers < 4001) $price = 70;
	else if ($totalmembers < 8001) $price = 75;
	else if ($totalmembers < 10001) $price = 80;
	else if ($totalmembers < 15001) $price = 85;
	else $price = 90;

	return $price;
}

$db = new MySQL_Access("mle");

if ($_POST['submitted'] == 'convert')
{
  $newname = trim($_POST['newname']);

  if ($newname == '') $notValid = "ERROR: Missing required parameters.";
  else if (has_weird($newname)) $notValid = "ERROR: List Owner User Name can only have a-z, A-Z, 0-9 or _ in it. Please re-enter.";
  else if (strlen($newname)>20) $notValid = "ERROR: List Owner name is too long. 20 maximum characters.";
  else if (strlen($newname)<3) $notValid = "ERROR: List Owner name is too short. 3 minimum characters.";
  else if ($db->Query("SELECT username FROM listowner WHERE username='$newname'")) $notValid = "ERROR: List Owner User Name <i>$newname</i> is already taken.";
  else
  {
    list($id, $listownerID, $listownername, $listname) = explode(":", $_POST['oldlist']);

    $db->SelectDB("pxm");
    if (! $db->Query("SELECT id FROM orders WHERE id='$id'"))
      exit("id=$id not found in pxm.orders");

    $db->SelectDB("mle");

    if (! $db->Query("SELECT listownerID FROM listowner WHERE listownerID='$listownerID'"))
      exit("listownerID=$listownerID not found in mle.listowner");
    else if (! $db->Query("SELECT username FROM listowner WHERE username='$listownername'"))
      exit("listownername=$listownername not found in mle.listowner");
    else if (! $db->Query("SELECT listname FROM listmanager WHERE listname='$listname'"))
      exit("listname=$listname not found in mle.listmanager");
    else if (! $db->Query("SELECT listhash FROM listurls WHERE listownerID='$listownerID' AND listname='$listname'"))
      exit("listhash not found in mle.listurls");
    else
      list($listhash) = $db->FetchRow();

    if (! $header = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/header.txt')) exit('unable to read: header.txt');
    if (! $footer = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/footer.txt')) exit('unable to read: footer.txt');
    if (! $subconfirm = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/subconfirm.txt')) exit('unable to read: subconfirm.txt');
    if (! $subsuccess = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/subsuccess.txt')) exit('unable to read: subsuccess.txt');
    if (! $unsubsuccess = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/unsubsuccess.txt')) exit('unable to read: unsubsuccess.txt');
    if (! $homepage = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/html.txt')) exit('unable to read: html.txt');
    $homepage = $homepage."!N_T_W_S_4_0!".$homepage."!N_T_W_S_4_0!".$homepage;
    if (! $upgradeinfopro = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/upgradeinfopro.txt')) exit('unable to read: upgradeinfopro.txt');
    if (! $upgradeinfoexe = @file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/upgradeinfoexe.txt')) exit('unable to read: upgradeinfoexe.txt');
    $upgradeinfo = $upgradeinfopro."!N_T_W_S_4_0!".$upgradeinfoexe;

    $db->Query("UPDATE listmanager SET message='' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("UPDATE listmanager SET header='$header' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("UPDATE listmanager SET footer='$footer' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("UPDATE listmanager SET subconfirm='$subconfirm' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("UPDATE listmanager SET subsuccess='$subsuccess' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("UPDATE listmanager SET unsubsuccess='$unsubsuccess' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("UPDATE listmanager SET html='$homepage' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("UPDATE listmanager SET paylinkparams='|||||||||||||', fromname='$newname', adminemail='$newname@notavailable.com', paymenthtml='' WHERE listownerID='$listownerID' AND listname='$listname'");
    $db->Query("UPDATE listconfig SET testmode_username='0', allowupgrades='0', newmembernotice='0', programname='$newname', proupgradeform='', exeupgradeform='', costofpro='', costofexe='', memsendmailweek='3', prosendmailweek='5', numurltrackersPro='6', numurltrackersExe='10', numurltrackersMem='3', logoutlocation='http://www.pxmb.com', adminemailaddress='$newname@notavailable.com', commission='', referer='', defaultstatus='mem', upgradeinfo='$upgradeinfo' WHERE listname='$listname' AND listownerID='$listownerID'");
    $db->Query("DELETE FROM transactions WHERE listhash='$listhash'");
    $db->Query("DELETE FROM banneddomains WHERE listname='$listname' AND listownerID='$listownerID'");

    // set default title image
    $db->Query("SELECT banner FROM banners WHERE listname='$listname' AND listownerID='$listownerID' AND bannerlink='TITLE_GRAPHIC'");
    list($titleData) = $db->FetchRow();
    @unlink($titleData);
    $db->Query("DELETE FROM banners WHERE listname='$listname' AND listownerID='$listownerID' AND bannerlink='TITLE_GRAPHIC'");

    // change listname
    $db->Query("UPDATE users SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE upgrade SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE system SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE listmanager SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE listconfig SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE banners SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE banneddomains SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE ads SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->Query("UPDATE listurls SET listname='$newname' WHERE listname='$listname' AND listownerID='$listownerID'");
  	$db->SelectDB("pxm");
  	$db->Query("UPDATE orders SET listname='$newname' WHERE listname='$listname' AND listownername='$listownername'");
  	# $db->Query("UPDATE extended SET listname='$newname' WHERE listname='$listname' AND listownername='$listownername'");
  	$db->Query("DELETE FROM clients WHERE listownerID='$listownerID' AND listname='$listname'");

  	// change listowner name AND SET AS 'CANCELLED'
  	$db->SelectDB("mle");
  	$db->Query("UPDATE listowner SET username='$newname', password=MD5('ntws40') WHERE listownerID='$listownerID'");
  	$db->Query("SELECT COUNT(*) FROM users WHERE listname='$listname' AND listownerID='$listownerID'");
    list($totalmem) = $db->FetchRow();
  	$db->SelectDB("pxm");
  	$price = get_pricing($totalmem);
  	$db->Query("UPDATE orders SET listownername='$newname', paid='no', howheard='cancelled', email='$newname@notavailable.com', listowneremail='$newname@notavailable.com', price='$price' WHERE listownername='$listownername'");
  	# $db->Query("UPDATE extended SET listownername='$newname' WHERE listownername='$listownername'");

  	$notValid = "Successfully changed the list to: $newname";
  }
}

$db->SelectDB("pxm");
$ids = $listnames = $listownernames = $dayslate = $listownerIDs = array();
$where_clause = "howheard != 'cancelled' AND verified='yes' AND paid='no'";
if ($db->Query("SELECT id, listname, listownername, datesubmitted FROM orders WHERE $where_clause ORDER BY listownername"))
{
  $lists = $db->result;
  while (list($id, $listname, $listownername, $datesubmitted) = mysqli_fetch_row($lists))
  {
    $days_bill_late = 0;

    // skip owners that have more than 1 list, for now
    $db->SelectDB("pxm");
    if ($db->Query("SELECT listname FROM extended WHERE listownername='$listownername'"))
      continue;

    // get listownerID
    $db->SelectDB("mle");
    if ($db->Query("SELECT listownerID FROM listowner WHERE username='$listownername'"))
      list($listownerID) = $db->FetchRow();
    else
    {
      $notValid .= "<br />\nlistownerID not found for listowner=$listownername";
      continue;
    }

    $db->Query("SELECT COUNT(*) FROM users WHERE verified='yes' AND listname='$listname' AND listownerID='$listownerID'");
    list($totalmem) = $db->FetchRow();

    $days_bill_late = intval(DateDiff(mysql_datetime_to_timestamp($datesubmitted), time(), "d"));

    if (1 == 1)
    {
      $ids[]            = $id;
      $listnames[]      = $listname;
      $listownerIDs[]   = $listownerID;
      $listownernames[] = $listownername;
      $dayslate[]       = $days_bill_late;
      $totalmembers[]   = $totalmem;
    }
  }
}
else
  exit("No lists found to be convertable.");

?>

<html>
<head>
<title>Make a List 4 Sale</title>
</head>
<body>
<table>
  <tr>
    <td>
      <h3>Make a List 4 Sale</h3>

      <?php if ($notValid) echo '<font color="red"><b>'.$notValid.'</b></font>'; ?>

      <form name="convertlist" action="convert_list.php" method="POST">
        List Owner to Convert:
        <select name="oldlist">

<?php

          if (count($ids))
          {
            for ($i=0; $i<count($ids); $i++)
              echo '<option value="'.$ids[$i].':'.$listownerIDs[$i].':'.$listownernames[$i].':'.$listnames[$i].'">'.$dayslate[$i].' - '.$listownernames[$i].' - '.$listnames[$i].' - '.$totalmembers[$i].'</option>'."\n";
          }

?>

        </select>

        New List Name:
        <input type="text" name="newname" value="" size="20" />
        <input type="submit" value="Submit" />
        <input type="hidden" name="submitted" value="convert" />
      </form>
      <a href="convert_list.php">Refresh</a>
    </td>
  </tr>
</table>
</body>
</html>
