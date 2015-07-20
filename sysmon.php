#!/usr/bin/php -q
<?php
set_time_limit(0);

require_once('/home/nulled/config.inc');

function c2f($cTemp, $prec = 0)
{
  $prec = (integer)$prec;
  $fTemp = (float)(1.8 * $cTemp) + 32;
  return round($fTemp, $prec);
}

function pws($data)
{
  if (is_array($data)) {
    $output = array();
    foreach ($data as $line) {
      $output[] = preg_replace("/( +)/", " ", preg_replace("/(\\t)/", " ", $line));
    }
  } else {
    $output = preg_replace("/( +)/", " ", preg_replace("/(\\t)/", " ", $data));
  }

  return $output;
}

function get_sales($day, $db)
{
  $db->SelectDB('pxm');
  $db->Query("SELECT SUM(amount) FROM transactions WHERE dateofsale LIKE '$day %'");
  list($total) = $db->FetchRow();
  $db->SelectDB('mle');

  return ($total) ? $total : '0.00';
}

function popen2($cmd)
{
  $data = array();

  $p = popen($cmd, 'r');

  while (! feof($p))
    $data[] = trim(fgets($p, 4096));

  pclose($p);

  if ($data[count($data)-1] == '')
    unset($data[count($data)-1]);

  return $data;
}

function parse_mdstat($lines)
{
  $output = array();
  $concat_next_line = 0;

  return $output;

  foreach ($lines as $line) {
    if (strstr($line, 'md') OR $concat_next_line) {
      if ($concat_next_line) {
        $output[count($output)-1] .= ' '.$line;
      } else {
        $output[] = $line;
      }
      $concat_next_line = $concat_next_line ? 0:1;
    }
  }

  return $output;
}

function parse_hddtemp($lines)
{
  list($l,, $c) = explode(':', $lines[0]);
  $l = trim($l);
  list($c) = explode(' ', trim($c)); // celcius
  $f = c2f($c); // convert Celcius to Fahrenhei
  $output = "$l: $c $f F";

  return $output;
}

function parse_mysql($lines)
{
  $output = array();
  $is_safe_mysqld = $mysqld_num = 0;

  $output[] = 'MySQL Status';
  $output[] = '------------';

  foreach ($lines as $line) {
    if (strstr($line, 'safe_mysqld')) {
      $is_safe_mysqld = 1;
    } else {
      $mysqld_num++;
    }
  }
  $output[] = $mysqld_num.' mysqld';

  return $output;
}

function parse_postfix($lines)
{
  $output = array();
  $is_master = $is_qmgr = $smtpd_num = $smtp_num = 0;

  $output[] = 'Postfix Status';
  $output[] = '--------------';

  foreach ($lines as $line) {
    if (strstr($line, '/master')) {
      $is_master = 1;
    } else if (strstr($line, 'qmgr')) {
      $is_qmgr = 1;
    } else if (strstr($line, 'smtpd -n')) {
      $smtpd_num++;
    } else if (strstr($line, 'smtp -t')) {
      $smtp_num++;
    }
  }

  if ($is_master) {
    $output[] = 'Yes, Master';
  } else {
    $output[] = 'No, Master';
  }

  if ($is_qmgr) {
    $output[] = 'Yes, Qmgr';
  } else {
    $output[] = 'No, Qmgr';
  }

  $output[] = $smtpd_num.' smtpd';
  $output[] = $smtp_num.' smtp';

  return $output;
}

function parse_server_prog($lines, $label)
{
  $output = array();
  $is_root = $num = 0;

  $output[] = $label . ' Status';
  $output[] = '-------------';

  foreach ($lines as $line) {
    if (strstr($line, 'root') AND strstr($line, $label)) {
      $is_root = 1;
    } else {
      $num++;
    }
  }

  if ($is_root) {
    $output[] = 'Yes, root ' . $label;
  } else {
    $output[] = 'No, root ' . $label;
  }

  $output[] = $num . ' ' . $label;

  return $output;
}

function parse_meminfo($lines)
{
  $output = array();

  $output[] = 'Memory Status';
  $output[] = '-------------';

  foreach ($lines as $line) {
    if (strstr($line, 'MemTotal:') OR strstr($line, 'MemFree:') OR strstr($line, 'SwapTotal:') OR strstr($line, 'SwapFree:')) {
      $output[] = $line;
    }
  }

  return $output;
}

function load_column($data, &$columns)
{
  $i = count($columns);
  $j = 0;

  foreach ($data as $line) {
    $columns[$i][$j] = $line;
    $j++;
  }
}

function echo_columns($columns)
{
  $col_length = $longest_col_line = array();
  $num_columns = count($columns);
  $longest_column = 0;
  $output = '';

  foreach ($columns as $i => $arr) {
    foreach ($arr as $line) {
      $col_length[$i]++;
      if (strlen($line) > $longest_col_line[$i]) {
        $longest_col_line[$i] = strlen($line);
      }
    }
  }

  rsort($col_length);
  $longest_column = $col_length[0];

  for ($i=0; $i < $longest_column; $i++) {
    $col = array();
    for ($j=0; $j < $num_columns; $j++) {
      $col[] = $columns[$j][$i];
    }
    $output .= sprintf("%-{$longest_col_line[0]}s %-{$longest_col_line[1]}s %s\n", $col[0], $col[1], $col[2]);
  }

  if ($argv[1] != 'cron') system('clear');
  return $output;
}

$postfix_queue = '/var/spool/postfix';

$SPACER = array('');
$num_sec_sleep = 20;

list(, $_num) = $_SERVER['argv'];
if (is_numeric($_num))
  $num_sec_sleep = $_num;

$db = new MySQL_Access('mle');

while (true)
{
  $mem    = parse_meminfo(popen2('cat /proc/meminfo'));
  // check my yahoo notes 'ECCM Help'
  list($eccm) = popen2('cat /sys/devices/system/edac/mc/mc0/ce_count');
  $mem[]  = 'ErrorCount:            ' . $eccm;
  $df     = popen2('df -h');
  $mdstat = parse_mdstat(popen2('cat /proc/mdstat'));
  $nginx  = parse_server_prog(popen2('ps aux | grep nginx: | grep -v grep'), 'nginx:');
  $php5fpm= parse_server_prog(popen2('ps aux | grep php-fpm | grep -v grep'), 'php-fpm');

  $uptime    = pws(popen2('uptime'));
  $uptime[0] = str_replace('load average:', '', $uptime[0]);

  $postfix = parse_postfix(popen2('ps aux | grep postfix | grep -v grep'));
  $postfix_queue_size = popen2("find $postfix_queue/active -type f -print | wc -l");
  $postfix[] = $postfix_queue_size[0] .= ' active queue';
  $postfix_queue_size = popen2("find /$postfix_queue/deferred -type f -print | wc -l");
  $postfix[] = $postfix_queue_size[0] .= ' deferred queue';

  $mysql = parse_mysql(popen2('ps aux | grep mysql | grep -v grep'));
  $db->Query("SELECT COUNT(*) FROM queue WHERE 1");
  list($mle_queue_num) = $db->FetchRow();
  $mysql[] = $mle_queue_num.' mle.queue';
  $db->Query("SELECT COUNT(*) FROM bounced WHERE 1");
  list($mle_bounced_num) = $db->FetchRow();
  $mysql[] = $mle_bounced_num.' mle.bounced';

  $db->Query("SELECT totalcount, bouncedcount FROM mailcount WHERE id='1'");
  list($mle_totalcount_num, $mle_bouncedcount_num) = $db->FetchRow();
  $mysql[] = $mle_bouncedcount_num.' mle.mc.bounced';
  $mysql[] = $mle_totalcount_num.' mle.mc.total';

  $db->Query("SELECT COUNT(*) FROM soloads WHERE receipt != '' AND datemailed='0000-00-00 00:00:00'");
  list($mle_pending_soloads) = $db->FetchRow();
  $mysql[] = $mle_pending_soloads.' mle.soloads';

  $db->SelectDB('fap');
  $db->Query("SELECT COUNT(*) FROM mailqueue WHERE 1");
  list($fap_queue_num) = $db->FetchRow();
  $mysql[] = $fap_queue_num.' fap.queue';
  $db->SelectDB('mle');

  $sales   = array();
  $sales[] = 'Sales';
  $sales[] = '-----';
  for ($i = 6; $i > -1; $i--) {
    $db->Query("SELECT DATE_SUB(CURDATE(), INTERVAL $i DAY)");
    list($prev_day) = $db->FetchRow();
    $sales[] = "$prev_day \$" . get_sales($prev_day, $db);
  }

  $hdtemp = array();
  $hdtemp[] = 'Disk Temp';
  $hdtemp[] = '---------';
  $hdtemp[] = parse_hddtemp(popen2('/usr/sbin/hddtemp /dev/sda'));
  $hdtemp[] = parse_hddtemp(popen2('/usr/sbin/hddtemp /dev/sdb'));
  $hdtemp[] = parse_hddtemp(popen2('/usr/sbin/hddtemp /dev/sdc'));
  $hdtemp[] = parse_hddtemp(popen2('/usr/sbin/hddtemp /dev/sdd'));

  $procbounce = array();
  $procbounce[] = 'Daemons';
  $procbounce[] = '-------';
  list(, $procbounce[]) = explode('-q ', system('ps aux | grep procbounce.php | grep -v grep'));
  list(, $procbounce[]) = explode('-q ', system('ps aux | grep sendqueue.php | grep -v grep'));
  list(, $procbounce[]) = explode('-q ', system('ps aux | grep sendsoload.php | grep -v grep'));

  $col_1 = array_merge($mysql, $SPACER, $postfix, $SPACER, $nginx);
  $col_2 = array_merge($df, $SPACER, $mdstat, $SPACER, $uptime, $SPACER, $php5fpm, $SPACER, $procbounce);
  $col_3 = array_merge($sales, $SPACER, $mem, $SPACER, $hdtemp);

  $columns = array();
  load_column($col_1, $columns);
  load_column($col_2, $columns);
  load_column($col_3, $columns);

  $output = echo_columns($columns);

  if ($argv[1] == 'cron')
  {
    $filename = '/home/nulled/www/planetxmail.com/tools/sysmon.html';
    $template = '/home/nulled/www/planetxmail.com/tools/sysmon_html.txt';

    $html = file_get_contents($template);

    $html = str_replace(array('[output]'),
                        array($output),
                        $html);

    touch($filename);
    file_put_contents($filename, $html);
    chmod($filename, 0740);
    chown($filename, 'nulled');
    chgrp($filename, 'nulled');
    break;
  }
  else
    echo "{$output}\n\n";

  sleep($num_sec_sleep);
}

$db->Close();

?>
