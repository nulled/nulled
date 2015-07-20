#!/usr/bin/php -q
<?php
require_once('/home/nulled/config.inc');

// /usr/bin/nohup /home/nulled/tor.php >> /root/tor_output_log &

class Tor extends MySQL_Access
{
  public $rm;
  public $tor_wget;
  public $dir_store;
  public $log_output;
  public $ips;
  public $ips_file;
  public $user_agents;
  public $wget_options;

  function __construct()
  {
    parent::__construct('mle');
    
    $this->rm           = '/bin/rm -f ';
    
    $this->wget_options = ' -nv -R mp3,avi,flv,mpg,mpeg,au,png,PNG,jpg,gif,css,swf --limit-rate=100k -w 3 --random-wait --waitretry=3 -p ';

    $this->tor_wget     = 'export TORSOCKS_DEBUG=-1; /usr/sbin/torsocks /usr/bin/wget' . $this->wget_options;
    $this->dir_store    = '/tmpfs/store_tor';
    $this->ips_file     = '/home/nulled/ips.txt';
    $this->log_output   = '>> /root/tor_log';
    $this->ips          = array();
    $this->user_agents  = array(
      'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4314)',
      'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)',
      'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)',
      'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; InfoPath.1; .NET CLR 2.0.50727)',
      'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1) ; .NET CLR 1.0.3705)',
      'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1) ; .NET CLR 2.0.50727 ; .NET CLR 4.0.30319)',
      'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; TencentTraveler ; Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1) ; .NET CLR 2.0.50727)',
      'Mozilla/4.0 (compatible; MSIE 6.0b; Windows NT 4.0)',
      'Mozilla/4.0 (compatible; MSIE 6.0b; Windows NT 5.1)',
      'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)',
      'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; .NET CLR 1.1.4322; InfoPath.1; .NET CLR 2.0.50727; .NET CLR 3.0.04506.30; .NET CLR 3.0.04506.648)',
      'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)',
      'Mozilla/4.0 (compatible; MSIE 8.0; AOL 9.7; AOLBuild 4343.55; Windows NT 5.1; Trident/4.0)',
      'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0)',
      'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET CLR 2.0.50727; BOIE8;ENUSMSCOM)',
      'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1)',
      'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:16.0) Gecko/20100101 Firefox/16.0',
      'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:20.0) Gecko/20100101 Firefox/20.0',
      'Mozilla/5.0 (Windows NT 5.1; rv:15.0) Gecko/20100101 Firefox/15.0.1',
      'Mozilla/5.0 (Windows NT 5.1; rv:22.0) Gecko/20100101 Firefox/22.0',
      'Mozilla/5.0 (Windows NT 5.1; rv:25.0) Gecko/20100101 Firefox/25.0',
      'Mozilla/5.0 (Windows NT 6.0; WOW64; rv:20.0) Gecko/20100101 Firefox/20.0 AlexaToolbar/alxf-2.19',
      'Mozilla/5.0 (Windows NT 6.0; rv:25.0) Gecko/20100101 Firefox/25.0',
      'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.57 Safari/537.36',
      'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.57 Safari/537.36',
      'Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko',
      'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:17.0) Gecko/17.0 Firefox/17.0',
      'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0',
      'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0 AlexaToolbar/alxf-2.19',
      'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:9.0.1) Gecko/20100101 Firefox/9.0.1',
      'Mozilla/5.0 (Windows NT 6.1; rv:24.0) Gecko/20100101 Firefox/24.0',
      'Mozilla/5.0 (Windows NT 6.1; rv:25.0) Gecko/20100101 Firefox/25.0',
      'Mozilla/5.0 (Windows NT 6.1; rv:26.0) Gecko/20100101 Firefox/26.0',
      'Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.48 Safari/537.36',
      'Mozilla/5.0 (Windows NT 6.3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.57 Safari/537.36',
      'Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko',
      'Mozilla/5.0 (Windows; U; Windows NT 5.1; pl; rv:1.9.0.8) Gecko/2009032609 Firefox/3.0.8',
      'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/536.11 (KHTML, like Gecko) DumpRenderTree/0.0.0.0 Safari/536.11',
      'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:25.0) Gecko/20100101 Firefox/25.0',
      'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Win64; x64; Trident/5.0)',
      'Mozilla/5.0 (iPhone; CPU iPhone OS 6_1_3 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Version/6.0 Mobile/10B329 Safari/8536.25',
      'Opera/9.20 (Windows NT 5.2; U; en)',
      'Opera/9.23 (Windows NT 5.1; U; ru)',
      'Opera/9.25 (Windows NT 5.1; U; en)',
      'Opera/9.64(Windows NT 5.1; U; en) Presto/2.1.1',
      'Opera/9.80 (Windows NT 5.1; U; YB/3.5.1; ru) Presto/2.10.229 Version/11.64',
      'Opera/9.80 (Windows NT 6.1; U; ru) Presto/2.8.131 Version/11.10',
      'Opera/9.80 (Windows NT 6.1; Win64; x64; Edition Yx) Presto/2.12.388 Version/12.11'
      );

      if (! $this->dir_store OR $this->dir_store == '/')
        exit("ERROR: dir_store is not set properly\n");
  }

  public function gdate()
  {
    return '---> ' . date('M d h:i:s A') . ' - ';
  }

  public function get_urls()
  {
    $urls = array();

    if ($this->Query("SELECT crediturl FROM soloads WHERE receipt != '' AND crediturl != '' AND datemailed > DATE_SUB(NOW(), INTERVAL 5 DAY)"))
    {
      $result = $this->result;

      while (list($id) = mysqli_fetch_row($result))
      {
        if ($this->Query("SELECT url FROM userlinks WHERE id='$id' LIMIT 1"))
        {
          list($url) = $this->FetchRow();

          if ($url AND ! stristr($url, 'planetxmail.com') AND ! in_array($url, $urls))
            $urls[] = $url;
        }
      }
    }

    return $urls;
  }

  public function tor_renew_ip($recursive = 0)
  {
    $ip_addr = false;
    $regex   = '/^(([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]).){3}([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/';
    $ip_file = 'planetxmail.com/get_ip.php';
    $ip_path = "{$this->dir_store}/{$ip_file}";

    sleep(5);

    if (! $fs = fsockopen('127.0.0.1', '9051', $err_num, $err_str, 15))
      exit($this->gdate() . "ERROR: fsockopen() {$err_num} : {$err_str}\n");
    else
    {
      fwrite($fs, 'AUTHENTICATE "blah4blah"' . "\n");
      echo $this->gdate() . trim(fread($fs, 512)) . "\n";
      fwrite($fs, 'signal NEWNYM' . "\n");
      echo $this->gdate() . trim(fread($fs, 512)) . "\n";
    }
    fclose($fs);

    if (! is_dir($this->dir_store) AND ! mkdir($this->dir_store, 0755, true))
      exit($this->gdate() . "ERROR: Unable to mkdir({$this->dir_store}) in tor_renew_ip() ... exiting\n");
    
    system("{$this->rm} {$ip_path}");

    system("{$this->tor_wget} -P {$this->dir_store} http://{$ip_file} {$this->log_output}");

    if (is_file($ip_path))
    {
      $ip_addr = file_get_contents($ip_path);

      if (is_string($ip_addr) AND strlen($ip_addr))
      {
        $ip_addr = trim($ip_addr);

        if (preg_match($regex, $ip_addr) === 1)
          return $ip_addr;
      }
    }

    if ($recursive == 3)
      return false;

    $recursive++;
    echo $this->gdate() . "WARNING: Unable to preg_match({$ip_addr}) new ip - tor_renew_ip({$recursive}) ... retrying\n";
    $this->tor_renew_ip($recursive);
  }

  public function get_new_ip($sleep = 5)
  {
    for ($i = 0; $i < 20; $i++)
    {
      if (! $ip_addr = $this->tor_renew_ip())
      {
        echo $this->gdate() . "WARNING: tor_renew_ip() returned false ... i:{$i} sleeping for {$sleep} seconds ... retrying\n";
        sleep($sleep);
        $this->get_new_ip($sleep + 5);
      }

      if (! in_array($ip_addr, $this->ips))
      {
        $this->ips[] = $ip_addr;
        return $ip_addr;
      }
      else
        echo $this->gdate() . "WARNING: IP Address already in ips array, trying again i:{$i}...\n";
    }

    file_put_contents($this->ips_file, implode("\n", $this->ips) . "\n", FILE_APPEND);

    $this->ips = array();
    echo $this->gdate() . "WARNING: Tried to get unique ip i:{$i} times, \$ips array saved to file ...\n";
    $this->get_new_ip();
  }

  public function get_user_agent($prev_agent)
  {
    shuffle($this->user_agents);

    foreach ($this->user_agents as $new_agent)
      if ($new_agent != $prev_agent)
        return $new_agent;
  }

  public function get_referer()
  {
    if ($this->Query("SELECT link FROM earnedlinks WHERE 1 ORDER BY MD5(RAND()) LIMIT 1"))
    {
      list($e) = $this->FetchRow();
      return "http://planetxmail.com/earn.php?c={$e}&h=" . substr(sha1($e), 0, 5) . '&t=1';
    }
    else
      exit($this->gdate() . "ERROR: Unable to Query() for a new referer hash code...exiting\n");
  }

  public function Loop()
  {
    $user_agent = '';

    while (true)
    {
      $user_agent = $this->get_user_agent($user_agent);
      $ip_addr    = $this->get_new_ip();

      foreach ($this->ips as $aip) echo $this->gdate() . "PrevIP: {$aip}\n";
      echo $this->gdate() . "New User-Agent: {$user_agent}\n";
      echo $this->gdate() . "New IP Address: {$ip_addr}\n";
      echo $this->gdate() . "------------------------------\n";

      $url_count = 1;
      $urls      = $this->get_urls();
      $url_total = count($urls);

      shuffle($urls);

      foreach ($urls as $url)
      {
        $referer = $this->get_referer();

        # system("{$this->rm} {$this->dir_store}/*");

        $wget = "{$this->tor_wget} --user-agent='{$user_agent}' --referer='{$referer}' -P {$this->dir_store} {$url} {$this->log_output}";

        echo $this->gdate() . "$url_count/$url_total - {$url} - {$referer} ... \n";
        system($wget);

        $url_count++;
	sleep(mt_rand(10, 30));
      }

      //echo $this->gdate() . "NOTICE: Exiting after one round of url getting ... exiting\n";
      //return 0;
    }
  }
};

$tor = new Tor();
$tor->Loop();

?>
