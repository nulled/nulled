#!/usr/bin/php -q
<?php

set_time_limit(0);

function read_conf_file($conf_file='/etc/mysqlbackup.conf')
{
  $conf = array();

  $no_conf_msg  = "Unable to find config file: $conf_file\n";
  $no_conf_msg .= "Resorting to default settings... \n";
  $no_conf_msg .= "If mysqlbackup.php fails due to a misconfiguration,\n";
  $no_conf_msg .= "create a new config file named: $conf_file\n";

  if (! $lines = file($conf_file))
    echo $no_conf_msg;
  else
  {
    foreach ($lines as $line)
    {
      $line = trim($line);
      if (! $line OR $line[0] == '#') continue;
      list($param, $value) = preg_split('/[=#]/', $line);
      $conf[trim($param)] = trim($value);
    }
  }

  return $conf;
}

$date = date('M. j, Y G:i:s');

$TRIM_MLE = FALSE;

$date_str = "$date - Executing mysqlbackup.php";

echo str_repeat('-', strlen($date_str))."\n";
echo $date_str."\n";
echo str_repeat('-', strlen($date_str))."\n";

$conf = read_conf_file();

// print_r($conf);

// Defaults to use, if not found in configuration file

if ($conf['mysql_host'] == '')     $conf['mysql_host']     = 'localhost';
if ($conf['rotate_backups'] == '') $conf['rotate_backups'] = '0';
if ($conf['rotate_paths'] == '')   $conf['rotate_paths']   = $conf['backup_dir'];
if ($conf['rotate_time'] == '')    $conf['rotate_time']    = '432000';
if ($conf['mysqldump'] == '')      $conf['mysqldump']      = '/usr/bin/mysqldump';
if ($conf['mysql'] == '')          $conf['mysql']          = '/usr/bin/mysql';
if ($conf['crontab'] == '')        $conf['crontab']        = '/usr/bin/crontab';
if ($conf['tar'] == '')            $conf['tar']            = '/bin/tar';
if ($conf['bzip2'] == '')          $conf['bzip2']          = '/bin/bzip2';

$conf['dateformat'] = ($conf['dateformat'] == '') ? date('Y-m-d_H-i-s') : date($conf['dateformat']);

//////////////////////////////////////////////////////////////
// Validate
if (! is_dir($conf['backup_dir']))
  exit("ERROR: 'backup_dir'=".$conf['backup_dir']." does not exist or is not a directory\n\n");
if (! is_file($conf['mysqldump']))
  exit("ERROR: 'mysqldump'=".$conf['mysqldump']." does not exist, is not a file or is not an executable\n\n");
if (! is_file($conf['mysql']))
  exit("ERROR: 'mysql'=".$conf['mysql']." does not exist, is not a file or is not an executable\n\n");
if (! is_file($conf['crontab']))
  exit("ERROR: 'crontab'=".$conf['crontab']." does not exist, is not a file or is not an executable\n\n");
if (! is_file($conf['tar']) OR ! is_executable($conf['tar']))
  exit("ERROR: 'tar'=".$conf['tar']." does not exist, is not a file or is not an executable\n\n");
if (! is_file($conf['bzip2']) OR ! is_executable($conf['bzip2']))
  exit("ERROR: 'bzip2'=".$conf['bzip2']." does not exist, is not a file or is not an executable\n\n");
if (! is_numeric($conf['rotate_time']))
  exit("ERROR: 'rotate_time' parameter is not numeric\n\n");
if (! preg_match("/^[a-z0-9]+$/i", $conf['archive_name']))
  exit("ERROR: 'archive_name' parameter may only contain Letters or Numbers with no spaces allowed\n\n");


echo "\nConnecting to MYSQL Server: {$conf['mysql_username']}@{$conf['mysql_host']} ... ";
if (! $link=@mysqli_connect($conf['mysql_host'], $conf['mysql_username'], $conf['mysql_password'], 'mle'))
  exit("ERROR: Could not connect: " . mysqli_error($link) . "\n\n");
echo "done\n";

if ($TRIM_MLE)
{
  echo "\nCreating a trimmed down version of database 'mle' called 'mle_tmp'\n";
  echo "------------------------------------------------------------------\n";

  echo "-> Creating database 'mle_tmp' ... ";
  if (! @mysqli_query($link, "DROP DATABASE IF EXISTS mle_tmp")) exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  if (! @mysqli_query($link, "CREATE DATABASE mle_tmp"))         exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  echo "done\n";

  echo "-> Dumping/Copying database 'mle' into 'mle_tmp' ... ";
  if (! $p=@popen("{$conf['mysqldump']} --user={$conf['mysql_username']} --password={$conf['mysql_password']} mle | {$conf['mysql']} --user={$conf['mysql_username']} --password={$conf['mysql_password']} mle_tmp", 'r'))
    exit("Unable to open pipe to mysqldump: ".$conf['mysqldump']."\n\n");
  @pclose($p);
  echo "done\n";

  echo "-> Selecting database 'mle_tmp' ... ";
  if (! @mysqli_select_db($link, "mle_tmp")) exit("ERROR: Could not select database: ".mysqli_error($link)."\n\n");
  echo "done\n";

  echo "-> Blanking out database 'mle_tmp' columns 'message' and 'messagecredit' ... ";
  if (! @mysqli_query($link, "UPDATE users SET message='', messagecredit=''")) exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  echo "done\n";

  echo "-> TRUNCATING TABLES bounced, earnedlinks, iptotal, queue and urldata ... ";
  if (! @mysqli_query($link, "TRUNCATE TABLE bounced"))     exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  if (! @mysqli_query($link, "TRUNCATE TABLE earnedlinks")) exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  if (! @mysqli_query($link, "TRUNCATE TABLE iptotal"))     exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  if (! @mysqli_query($link, "TRUNCATE TABLE queue"))       exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  if (! @mysqli_query($link, "TRUNCATE TABLE urldata"))     exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
  echo "done\n";
}

// Note: Below are 3 commands to copy mle to mle_tmp ... then trimmed down mle_tmp ... mle will be skipped during backup.
// Note: Besure to rename mle_tmp back to original name of 'mle' when restoring!
// mysql --user='root' --password='' --execute='DROP DATABASE IF EXISTS mle_tmp; CREATE DATABASE mle_tmp;';
// mysqldump --user='root' --password='' mle | mysql --user='root' --password='!ntwks40' mle_tmp;
// mysql --user='root' --password='' --execute="USE mle_tmp; UPDATE users SET message='', messagecredit=''; TRUNCATE TABLE iptotal; TRUNCATE TABLE earnedlinks; TRUNCATE TABLE queue; TRUNCATE TABLE urldata;"

$skip_databases = $database_names = array();

if ($TRIM_MLE)
  $skip_databases[] = 'mle';

// create db skip list array
if ($conf['skip_databases'] != '')
{
  $dbases = explode(',', $conf['skip_databases']);
  if (count($dbases))
  {
    foreach ($dbases as $dbase)
    {
      $dbase = trim($dbase);
      if ($dbase == '') continue;
      $skip_databases[] = $dbase;
    }
  }
}

// if $TRIM_MLE is ON, and mle was added to skip databases in mysqlbackup.conf, we drop the duplicate mle entry
$skip_databases = array_unique($skip_databases);

echo "\nDatabases in this MySQL Server\n";
echo "-------------------------------\n";
if (! $result=@mysqli_query($link, "SHOW DATABASES")) exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");

while(list($dbname) = mysqli_fetch_row($result))
{
  echo "$dbname\n";

  if (count($skip_databases) AND in_array($dbname, $skip_databases))
    continue;
  $database_names[] = $dbname;
}

echo "\n\nDatabases to be Skipped\n";
echo "-------------------------\n";
if (count($skip_databases))
  foreach ($skip_databases as $dbname) echo "$dbname\n";
else
  echo "No Databases will be Skipped\n";

$filestr = $databases_backedup = $mysql_tarball = $files_tarball = $all_tarball = '';
$files = array();
if (count($database_names))
{
  echo "\n";

	foreach ($database_names as $dbname)
	{
		$filename = $conf['dateformat'].'_'.$dbname.'.sql';

		echo "-> Dumping $dbname to: $filename ... ";
		if (! $p=@popen($conf['mysqldump']." -eq --user=".$conf['mysql_username']." --password=".$conf['mysql_password']." --databases ".$dbname." > ".$conf['backup_dir']."/".$filename, "r"))
			exit("Unable to open pipe to mysqldump: ".$conf['mysqldump']."\n\n");
		@pclose($p);
		echo "done\n";

		$databases_backedup .= "$dbname\n";

		chmod($conf['backup_dir'].'/'.$filename, 0660);
		$files[] = $filename;
	}

  if ($TRIM_MLE)
  {
    echo "\n-> Dropping/Erasing database 'mle_tmp' ... ";
    if (! @mysqli_query($link, "DROP DATABASE IF EXISTS mle_tmp")) exit("ERROR: Could not query: ".mysqli_error($link)."\n\n");
    echo "done\n";
  }

  echo "\n-> Closing connection to MYSQL Server ... ";
  @mysqli_close($link);
  echo "done\n";

	foreach ($files as $file) $filestr .= $file.' ';

	$filestr = trim($filestr);

	$mysql_tarball = $conf['dateformat'].'_'.$conf['archive_name'].'_mysql.tar';

  echo "\n-> Archiving all .sql files into: $mysql_tarball ... ";
	if (! $p=@popen('cd '.$conf['backup_dir'].'; '.$conf['tar'].' -cf '.$mysql_tarball.' '.$filestr, 'r'))
	  exit('ERROR1: Unable to open pipe to tar all .sql files to one archive'."\n\n");
	@pclose($p);
  echo "done\n";

	chmod($conf['backup_dir'].'/'.$mysql_tarball, 0660);

  echo "\n-> Moving to: {$conf['backup_dir']}/{$mysql_tarball}\n\n";

	foreach ($files as $file)
	{
	  @unlink($conf['backup_dir'].'/'.$file);
	  echo "-> Cleaning up: $file\n";
	}

	echo "\n--------------------\n";
  echo "Databases backed up:\n";
  echo "--------------------\n";
  echo "$databases_backedup\n";
}
else
	exit("No Databases found!\n\n");

if (@mysqli_ping($link))
{
  echo "-> Closing connection to MYSQL Server ... ";
  @mysqli_close($link);
  echo "done\n";
}

echo "\n--------------------\n";
echo "File system back up:\n";
echo "--------------------\n";
echo "-> Dumping root crontab to: /home/nulled/root_crontab.txt\n";
if (! $p=@popen($conf['crontab'].' -l > /home/nulled/root_crontab.txt; /bin/chown nulled:nulled /home/nulled/root_crontab.txt;', 'r'))
  echo 'ERROR: Unable to open pipe dump root crontab'."\n\n";
@pclose($p);
$files_tarball = $conf['dateformat'].'_'.$conf['archive_name'].'_files.tar';
echo "-> Backing up /etc /home/nulled to: $files_tarball\n";
if (! $p=@popen('cd '.$conf['backup_dir'].'; '.$conf['tar'].' -cf '.$files_tarball.' /etc /home/nulled --exclude /home/nulled/backup', 'r'))
  exit('ERROR2: Unable to open pipe to tar and archive system files.'."\n\n");
@pclose($p);

$all_tarball = $conf['dateformat'].'_'.$conf['archive_name'].'.tar.bz2';
echo "-> Compressing $mysql_tarball and $files_tarball to: $all_tarball\n";
if (! $p=@popen('cd '.$conf['backup_dir'].'; '.$conf['tar'].' -cjf '.$all_tarball.' '.$mysql_tarball.' '.$files_tarball, 'r'))
  exit('ERROR3: Unable to open pipe to tar and compress files.'."\n\n");
@pclose($p);

chmod($conf['backup_dir'].'/'.$all_tarball, 0660);
chown($conf['backup_dir'].'/'.$all_tarball, 'nulled');

@unlink($conf['backup_dir'].'/'.$mysql_tarball);
echo "-> Cleaning up: $mysql_tarball\n";
@unlink($conf['backup_dir'].'/'.$files_tarball);
echo "-> Cleaning up: $files_tarball\n\n";

if ($conf['rotate_backups'] == '1' OR strtolower($conf['rotate_backups']) == 'yes' OR strtolower($conf['rotate_backups']) == 'y')
{
  $rotate_paths = explode(',', $conf['rotate_paths']);

  if (count($rotate_paths))
  {
    $num_rotated = 0;

    echo "\n-----------------\n";
    echo "Rotating Archives\n";
    echo "-----------------\n";

    foreach ($rotate_paths as $path)
    {
      $path = trim($path);

      foreach (@glob($path.'/*') as $file)
      {
        $deletetime = time() - $conf['rotate_time'];
        $modified = stat($file);

        if ($modified[9] < $deletetime)
        {
          $num_rotated++;
          echo '-> Rotated/Deleted: '.$file."\n";
          @unlink($file);
        }
      }
    }

    if (! $num_rotated)
      echo "No Archives Rotated\n\n";
  }
  else
    echo "-> INFO: rotate_backups=true, however, rotate_paths is blank\n\n";
}

?>
