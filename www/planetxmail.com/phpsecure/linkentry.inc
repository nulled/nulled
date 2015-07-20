<?php
require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc");

function ad_link_exchange($link, $description)
{
  global $db;

  $db->Query("REPLACE INTO links VALUES('','$link','$description')");
  $num = $db->Query("SELECT id FROM links");
  if ($num > 30)
  {
    if ($db->Query("SELECT id FROM links ORDER BY id LIMIT 1"))
    {
      list($id) = $db->FetchRow();
      $db->Query("DELETE FROM links WHERE id='$id' LIMIT 1");
    }
  }
}

$db = new MySQL_Access('mle');

if ($_POST['submitted'] == 'postlink')
{
  $link        = trim($_POST['link']);
  $prevlink    = trim(stripslashes($_POST['prevlink']));
  $description = substr(trim(strip_tags($_POST['description'])), 0, 80);

  if ($link == 'http://' OR ! $link)
    $link = 'http://planetxmail.com/soloads.php';

  if (! $description)
    $description = 'SOLO ADS to 123,000+';

  $banned = false;

  $str = $link . $description;

  if (stristr($str, 'adultfriendfinder')    OR
      stristr($str, 'planetxmail.com/link') OR
      stristr($str, 'planetxmail.com/show') OR
      stristr($str, 'pleasureandprofit')    OR
      stristr($str, 'camboy')  OR
      stristr($str, 'camgirl') OR
      stristr($str, 'cumtv')   OR
      stristr($str, 'pussy')   OR
      stristr($str, 'sex')     OR
      stristr($str, 'cunt')    OR
      stristr($str, 'teen')    OR
      stristr($str, 'cock')    OR
      stristr($str, 'xxx')     OR
      stristr($str, 'porn')) $banned = true;

  if ($banned)
  {
    $link = 'http://planetxmail.com/soloads.php';
    $description = 'SOLO ADS to 123,000+';
  }

  // get a solo ad crediturl to display on redirect as variable 'entered=$soloadID'
  // also add it to link exchange, below the link for the current submittor ...
  // this adds solo ad URLs to the list and will append the solo ad URL ...
  // now we tell solo ad buyers their traffic is coming from showlink.php because people are clicking the link exchange
  // as well as the 'ghost append' ...
  $url = '';
  if ($db->Query("SELECT id, subject, crediturl FROM soloads WHERE receipt != '' AND crediturl != '' AND datemailed > DATE_SUB(NOW(), INTERVAL 5 DAY) ORDER BY MD5(RAND()) LIMIT 1"))
    list($soloadID, $soloadSubject, $urlID) = $db->FetchRow();
  if ($db->Query("SELECT url FROM userlinks WHERE id='$urlID' LIMIT 1"))
    list($url) = $db->FetchRow();

  // make sure the subject line is clear of [] place holders
  $firstnames    = array('~firstname~','FNAME','FIRST_NAME','FIRSTNAME','[fname]','[first_name]','[firstname]','%firstname%','{firstname}','{first_name}','{!firstname}','(firstname)','(first_name)');
  $lastnames     = array('~lastname~','LNAME','LAST_NAME','LASTNAME','[lname]','[last_name]','[lastname]','%lastname%','{lastname}','{last_name}','{!lastname}','(lastname)','(last_name)');
  $soloadSubject = str_ireplace($firstnames, '', $soloadSubject);
  $soloadSubject = str_ireplace($lastnames,  '', $soloadSubject);

  $link2        = $url; // soload url
  $description2 = $db->EscapeString($soloadSubject);

  // first add the solo ad we are going to iframe append
  if ($link2) ad_link_exchange($link2, $description2);
  // second add the actual link second, so it will appear on top
  ad_link_exchange($link, $description);

  $_prevlink = urlencode($prevlink);

  $hash = substr(sha1('fK#4_b87HwZOOOg!gDDuw' . $prevlink . $soloadID), 0, 5);

  header("Location: showlink.php?link={$_prevlink}&entered={$soloadID}&h={$hash}");
  exit;
}

// $url        - will be populated and timer set to 6000 when someone posts a link
// $url_hidden - will be populated and timer shorter when the page is first loaded
$url = $url_hidden = '';
$fresh_page = 0;
// generated when a POST is done, then we know this is a $url and NOT a $url_hidden
if ($_GET['link'] AND $_GET['entered'] AND $_GET['h'])
{
  $vhash = substr(sha1('fK#4_b87HwZOOOg!gDDuw' . urldecode($_GET['link']) . $_GET['entered']), 0, 5);

  if ($vhash != $_GET['h'])
  {
    // someone is tampering with URL params, bail out
    header('Location: links.php');
    exit;
  }
}
else
  $fresh_page = 1;

if (! $fresh_page)
  $soloadID = $_GET['entered'];
else if (! $_GET['d']) // d = done, to prevent endless loop
{
  if ($db->Query("SELECT id, subject FROM soloads WHERE receipt != '' AND crediturl != '' AND datemailed > DATE_SUB(NOW(), INTERVAL 5 DAY) ORDER BY MD5(RAND()) LIMIT 1"))
    list($soloadID, $soloadSubject) = $db->FetchRow();
}

if ($soloadID AND $db->Query("SELECT id, crediturl, datemailed FROM soloads WHERE id='$soloadID' LIMIT 1"))
{
  list($soloadID, $urlID, $datemailed) = $db->FetchRow();

  if ($db->Query("SELECT url FROM userlinks WHERE id='$urlID' LIMIT 1"))
  {
    if (! $fresh_page) // someone did a POST, no need to add it to links.php, because it was added in the POST
      list($url) = $db->FetchRow();
    else
    {
      list($url_hidden) = $db->FetchRow();

      $_link        = $url_hidden;
      $_description = $db->EscapeString($soloadSubject);

      // add the url_hidden to the links.php list
      ad_link_exchange($_link, $_description);
      unset($_link, $_description, $soloadSubject);
    }

    $_url = ($url) ? $url : $url_hidden;

    $db->Query("INSERT INTO iframe_stats (soloadID, urlID, counter, url, datemailed, lastupdate)
                                  VALUES ('$soloadID','$urlID','1','{$_url}','$datemailed',NOW()) ON DUPLICATE KEY UPDATE counter=counter+1, lastupdate=NOW()");
  }
}

?>