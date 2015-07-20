<?php
set_time_limit(0);

die;

$numRecords = $dupUsernames = 0;
$IDs = array();
$usernames = array();

$db_connect   = 1;
$sql_file     = "list.txt";
$uid          = "AZ";
$listname     = "GlobalBusinessList";
$listownerID  = "1458613339";

include("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access();

// check if uid is taken
$db->Query("SELECT COUNT(*) FROM users WHERE RIGHT(userID, 2)='$uid' LIMIT 1");
list($uid_taken) = $db->FetchRow();
if ($uid_taken)
{
  echo "uid = $uid ... which is already taken!";
  exit;
}

$fp = fopen ($sql_file, "r");

$index=0;
echo "<pre>";
while (!feof ($fp))
{
  $parts = array();
  $fields = array();

  $line = trim(fgets($fp, 4096));

  if (! $line) continue;

  /******* use for inserts */
  // $parts    = explode("VALUES (", $line);
  // $parts[1] = substr($parts[1], 0, strlen($parts[1])-2);
  // $fields   = explode(",", $parts[1]);
  /*************************/

  /******* use for comma seperated */
  $fields = explode(",", $line);
  /******************************/

  for ($i=0; $i<count($fields); $i++)	$fields[$i] = trim(str_replace("'", "", $fields[$i]));

	// $fname = ucfirst(strtolower(trim($fname)));
	// $lname = ucfirst(strtolower(trim($lname)));

	//list($username) = explode("@", $line);
	$username = $fields[0];

  //$username  = $fields[2];
  $password  = strtolower($fields[1]);
  $email     = $fields[1];
  $listemail = "";
  $fname = $lname = "";

  //$status = trim($fields[5]);
  //if ($status=="PRO")     $status = "pro";
  //else if ($status=="EXE") $status = "exe";
  //else
  $status = "exe";
	$verified = "yes";

  /*********************************************************************/

  if (strtolower($email)==strtolower($listemail)) $listemail = "";

  // make sure ID is unique
  while (1)
  {
    $dup_found = 0;
    $userID = substr(uniqid(rand()), 0, 8).$uid;

    $numIDs = count($IDs);
    for ($i=0; $i < $numIDs; $i++)
    {
      if ($IDs[$i]==$userID)
      {
        $dup_found = 1;
        break;
      }
    }

    if ($dup_found) continue;

    $IDs[] = $userID;
    break;
  }

  // skip dup usernames
  while (1)
  {
    $dup_found = 0;

    $numuserIDs = count($usernames);
    for ($i=0; $i < $numuserIDs; $i++)
    {
      if (strtolower($usernames[$i])==strtolower($username))
      {
        $dup_found = 1;
        break;
      }
    }

    if ($dup_found) break;

    $usernames[] = $username;
    break;
  }

  // dup username so skip it
  if ($dup_found)
 {
    $dupUsernames++;
    continue;
  }

  $query = "INSERT INTO users VALUES ('$userID','$fname','$lname',LCASE('$email'),'$status','$username',MD5('$password'),NOW(),'$verified',LCASE('$listemail'),'$listname',0,0,NOW(),0,'$listownerID','',0,0,'0',0,'',1,NOW())";

  echo "$query\n";
  flush();

  if ($db_connect) $db->Query($query);

  $numRecords++;
}
echo "</pre>";
echo "Total Records: <b>$numRecords</b><br>\n";
echo "Dup Usernames: <b>$dupUsernames</b><br>\n";
if ($db_connect) echo "<h3>DataBase was filled with these users.</h3>";

fclose($fp);

?>