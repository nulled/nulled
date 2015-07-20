#!/usr/bin/php -q
<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

$db = new MySQL_Access('pxm');

function get_months($year)
{
  switch ($year)
  {
    case '02': return array('2002-12');
    case '03': return array('2003-01','2003-02','2003-03','2003-04','2003-05','2003-06','2003-07','2003-08','2003-09','2003-10','2003-11','2003-12');
    case '04': return array('2004-01','2004-02','2004-03','2004-04','2004-05','2004-06','2004-07','2004-08','2004-09','2004-10','2004-11','2004-12');
    case '05': return array('2005-01','2005-02','2005-03','2005-04','2005-05','2005-06','2005-07','2005-08','2005-09','2005-10','2005-11','2005-12');
    case '06': return array('2006-01','2006-02','2006-03','2006-04','2006-05','2006-06','2006-07','2006-08','2006-09','2006-10','2006-11','2006-12');
    case '07': return array('2007-01','2007-02','2007-03','2007-04','2007-05','2007-06','2007-07','2007-08','2007-09','2007-10','2007-11','2007-12');
    case '08': return array('2008-01','2008-02','2008-03','2008-04','2008-05','2008-06','2008-07','2008-08','2008-09','2008-10','2008-11','2008-12');
    case '09': return array('2009-01','2009-02','2009-03','2009-04','2009-05','2009-06','2009-07','2009-08','2009-09','2009-10','2009-11','2009-12');
    case '10': return array('2010-01','2010-02','2010-03','2010-04','2010-05','2010-06','2010-07','2010-08','2010-09','2010-10','2010-11','2010-12');
    case '11': return array('2011-01','2011-02','2011-03','2011-04','2011-05','2011-06','2011-07','2011-08','2011-09','2011-10','2011-11','2011-12');
    case '12': return array('2012-01','2012-02','2012-03','2012-04','2012-05','2012-06','2012-07','2012-08','2012-09','2012-10','2012-11','2012-12');
    case '13': return array('2013-01','2013-02','2013-03','2013-04','2013-05','2013-06','2013-07','2013-08','2013-09','2013-10','2013-11','2013-12');
    case '14': return array('2014-01','2014-02','2014-03','2014-04','2014-05','2014-06','2014-07','2014-08','2014-09','2014-10','2014-11','2014-12');
    default: exit('FATAL ERROR: in get_months()');
  }
}

$months = $products = $transactions = array();
$allowed_years = array('02','03','04','05','06','07','08','09','10','11','12','13');
$mns = array('01'=>'Jan','02'=>'Feb','03'=>'Mar','04'=>'Apr','05'=>'May','06'=>'Jun','07'=>'Jul','08'=>'Aug','09'=>'Sep','10'=>'Oct','11'=>'Nov','12'=>'Dec');
$dateformat = 8;
$colformat  = 8;
$total_all  = $curr_year = 0;
$str_years  = '';

if (count($argv) > 1)
{
  foreach ($argv as $y)
  {
    if (! in_array($y, $allowed_years)) continue;
    $str_years .= $y.' ';
    $months = array_merge($months, get_months($y));
  }
}
else
{
  $str_years = date('y');
  $months = array_merge(get_months(date('y')));
}

$db->Query("SELECT DISTINCT product FROM transactions WHERE 1");
while (list($p) = $db->FetchRow())
{
  $p2 = $p;
  switch($p)
  {
    case 'cb_referral':       $p2 = 'CB REF'; break;
    case 'directad':          $p2 = 'DirAD'; break;
    case 'digipanel_license': $p2 = 'DP'; break;
    case 'elp_mem_monthly':   $p2 = 'ELP R'; break;
    case 'elp_mem_signup':    $p2 = 'ELP S'; break;
    case 'elp_partner':       $p2 = 'ELP P'; break;
    case 'm2m_signup':        $p2 = 'M2M'; break;
    case 'pxmb_renewal':      $p2 = 'PXMB R'; break;
    case 'pxmb_signup':       $p2 = 'PXMB S'; break;
    case 'pxm_monthly':       $p2 = 'PXM R'; break;
    case 'pxm_signup':        $p2 = 'PXM S'; break;
    case 'pxm_member':        $p2 = 'PXM Subs'; break;
    case 'safelist4sale':     $p2 = 'S4S'; break;
    case 'soload':            $p2 = 'Solo ADs'; break;
    case 'ebooks':            $p2 = 'eBooks'; break;
    case 'fap':               $p2 = 'F A P'; break;
  }
  $products[$p2] = $p;
}

for ($increment=0; $increment < count($months); $increment++)
{
	if (! $db->Query("SELECT product, amount, dateofsale FROM transactions WHERE dateofsale LIKE '".$months[$increment]."-%' ORDER BY dateofsale"))
    continue;

	$product_total_month = $dates_processed = $day = $month_transactions = array();
	
	$prev_day = '01';
  $last_day = '01';

	while (list($product, $amount, $dateofsale) = $db->FetchRow())
	{
	  $amount = number_format($amount, 2, '.', '');

	  list($dateofsale) = explode(' ', $dateofsale);
	  list($year, $month, $day) = explode('-', $dateofsale);
    
    if ($day > $prev_day) 
    {
      if ($day > $last_day) 
      {
        //$month_transactions[$year . '-' . $month . '-' . $prev_day]['soload'] = 0;
        //exit($year . '-' . $month . '-' . $prev_day . "\n");
      }

      $prev_day = $day;
    }

	  if ($month_transactions[$dateofsale][$product])
	    $month_transactions[$dateofsale][$product] += $amount;
	  else
	    $month_transactions[$dateofsale][$product] = $amount;
    
    $last_day = $day;
	}

	// display end of year info
	if ($year != $curr_year)
	{
	  // if curr_year was previously set then display years totals
	  if ($curr_year) echo "\n------------\nTotal $curr_year: = $total_year";

	  $curr_year = $year;
	  $total_year = 0;
	}

	list(,$m) = explode('-', $months[$increment]);
  $m = $mns[$m];
  $date_text = $m.':'.$year;

	$transactions = array_merge_recursive($transactions, $month_transactions);

	$date_title = sprintf("\n\n%-".$dateformat."s ", $date_text);

	foreach ($products as $p2 => $p) $date_title .= sprintf("%-".$colformat."s ", $p2);

	$date_title .= sprintf("%-".$colformat."s ", 'Total');

	echo $date_title."\n".str_repeat('-', strlen($date_title));

  // process the month
  $last_date = '';

	while (1)
	{
	  $day = array();
	  $total_day = $curr_date = $processed = 0;
  	foreach ($month_transactions as $date => $arr)
  	{
  	  foreach($arr as $prod => $amount)
  	  {
  	    if (in_array($date, $dates_processed))
    	    continue;

  	    if (! $curr_date)
  	      $last_date = $curr_date = $date;

   	    if ($curr_date != $date)
    	    continue;

        $total_all  += $amount;
        $total_year += $amount;
	      $total_day  += $amount;
	      $day[$prod] =  $amount;
        $processed  =  1;
  	  }
  	}

  	if (! $processed) break; // end of month
  	$dates_processed[] = $curr_date;

  	// end of day show results
  	list(,$m,$d) = explode('-', $curr_date);
  	$m = $mns[$m];
  	echo sprintf("\n%-".$dateformat."s ", "$m $d");

  	foreach ($products as $p2 => $p)
  	{
  	  if ($day[$p])
  	    $result = $day[$p];
  	  else
  	    $result = '0';

  	  $product_total_month[$p] += $result;

 	    echo sprintf("%-".$colformat."s ", $result);
  	}

  	echo sprintf("%-".$colformat."s ", $total_day);
  }

  list(,,$day_num) = explode('-', $last_date);

  echo "\n".str_repeat('-', strlen($date_title));

  $total_display      = sprintf("\n%-".$dateformat."s ", $m.' Earn');
  $avergage_display   = sprintf("%-".$dateformat."s ", 'Avg/Day');
  $percentage_display = sprintf("%-".$dateformat."s ", 'Percent');

  $total_month_amount = array_sum($product_total_month);

  foreach ($product_total_month as $p => $a)
  {
    $total_display      .= sprintf("%-".$colformat."s ", $a);
    $avergage_display   .= sprintf("%-".$colformat."s ", number_format($a / $day_num, 2, '.', ''));
    $percentage_display .= sprintf("%-".$colformat."s ", number_format(($a / $total_month_amount) * 100, 2, '.', '').' %');
  }

  $total_display      .= sprintf("%-".$colformat."s ", $total_month_amount)."\n";
  $avergage_display   .= sprintf("%-".$colformat."s ", number_format($total_month_amount / $day_num, 2, '.', ''))."\n";
  $percentage_display .= sprintf("%-".$colformat."s ", number_format(($total_month_amount / $total_month_amount) * 100, 2, '.', '').' %')."\n";

  echo $total_display;
  echo $avergage_display;
  echo $percentage_display;
}

echo "\nEarned for Years (".trim($str_years)."): ".number_format($total_all, 2, '.', ',')."\n\n";

?>
