<?php
$c = $_GET['c'];
$allowed = array('home','users','edit','deleteuser','search','payout','payout_return','mailusers','login','logout');
if (! in_array($c, $allowed)) $c = 'home';

require_once('/home/nulled/www/freeadplanet.com/secure/classes.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc');

$db = new MySQL_Access('fap');

$allowed_groups = array('free', 'pro', 'unverified');

$allowed_orderBy = array('alertpay' => 'AlertPay',
                         'credits'  => 'Credits',
                         'datelastbilled' => 'Date Last Billed',
                         'dateloggedin'   => 'Date Logged In',
                         'datesignedup'   => 'Date Signed Up',
                         'email' => 'Email',
                         'fname' => 'First Name',
                         'lname' => 'Last Name',
                         'lockedcredits' => 'Locked Credits',
                         'status'   => 'Status',
                         'username' => 'User Name',
                         'vacation' => 'Vacation',
                         'verified' => 'Verified');

$allowed_order = array('DESC' => 'Descending',
                       'ASC'  => 'Ascending');

$allowed_by = array('alertpay'  => 'AlertPay',
                    'email'     => 'Email Address',
                    'fname'     => 'First Name',
                    'lname'     => 'Last Name',
                    'username'  => 'UserName',
                    'affid'     => 'Affiliate ID',
                    'ipaddress' => 'IP Address');

if ($c == 'login')
{
  if ($submitted == 'login')
  {
    $db->Query("SELECT username, pass FROM admin WHERE 1 LIMIT 1");
    list($_username, $_pass) = $db->FetchRow();

    $pass = md5($pass);

    if ($pass == $_pass AND $username == $_username)
    {
      session_set_cookie_params(0, '/admin', '.freeadplanet.com', false, true);
      @session_start();
      @session_destroy();
      session_set_cookie_params(0, '/admin', '.freeadplanet.com', false, true);
      @session_start();

      $_SESSION['key'] = strrev(sha1(md5(md5(strrev($username.$pass)))));

      header('Location: http://freeadplanet.com/admin/?c=home');
      exit;
    }
    else
      $notValid = 'ERROR: Username and/or Password are not correct.';
  }

  $aform = '
  <form name="login" action="?c=login" method="POST">

  <table align="center" width="150" border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td align="center">
        <h3>Admin Login</h3>
        Username:
        <br />
        <input type="text" name="username" value="'.$username.'" size="20" maxlength="20" />
        <br /><br />
        Password:
        <br />
        <input type="password" name="pass" value="" size="20" maxlength="20" />
        <br /><br />
        <input type="submit" value="Login" />
      </td>
    </tr>
  </table>

  <input type="hidden" name="c" value="login" />
  <input type="hidden" name="submitted" value="login" />
  </form>
  ';

  notValid($notValid);

  $main_content = '
  '.$notValid.'
  '.$aform.'
  ';
}
else
{
  session_set_cookie_params(0, '/admin', '.freeadplanet.com', false, true);
  session_start();

  $db->Query("SELECT username, pass FROM admin WHERE 1 LIMIT 1");
  list($_username, $_pass) = $db->FetchRow();

  $key  = $_SESSION['key'];
  $vkey = strrev(sha1(md5(md5(strrev($_username.$_pass)))));

  if ($key == '')
    logout_session('Your Session has timed out.', 1);
  else if ($vkey != $key)
    logout_session('ERROR: Session is invalid.', 1);

  // for security
  unset($key, $vkey, $_pass);

  $title  = '<center><h3>Free AD Planet - Admin Control</h3>';
  $title .= '<a href="?c=home">Home</a> - <a href="?c=users">Users</a> - <a href="?c=logout">Log Out</a></center><br />';

  if ($c == 'home')
  {
    $main_content = '
    <center>
      <h3>Welcome to Free AD Planet<br />Administrator Site Control Panel</h3>
      <b>Menu</b>
      <br />
      <select size="2" onChange="window.location.href=\'?c=\'+this.options[this.selectedIndex].value">
        <option value="users">View Users</option>
        <option value="mailusers">Mail Users</option>
      </select>
    </center>
    <br /><br />
    ';
  }
  else if ($c == 'logout')
  {
    logout_session('You have logged out of Admin Control.', 1);
  }
  else if ($c == 'deleteuser')
  {
    if ($db->Query("SELECT email, fname, lname, username FROM users WHERE affid='$sponsor'"))
    {
      list($email, $fname, $lname, $username) = $db->FetchRow();

      delete_user($sponsor, $db);

      @mail($email, 'Account Deletion Notification', "Hello $fname $lname,\n\nYour Free AD Planet Account has been Deleted by the Admins.\n\nYour Username: $username\n\nThank you for using our system.\n\nRegards,\nMatt - Customer Care\nhttp://freeadplanet.com", "From: Free AD Planet <do_not_reply@freeadplanet.com>");
      @mail('elitescripts2000@yahoo.com', 'Account Deletion Notification', "Hello $fname $lname,\n\nYour Free AD Planet Account has been Deleted by the Admins.\n\nYour Username: $username\n\nThank you for using our system.\n\nRegards,\nMatt - Customer Care\nhttp://freeadplanet.com", "From: Free AD Planet <do_not_reply@freeadplanet.com>");

      $notValid = 'Successfully deleted Username: <i>'.$username.'</i> from the system.';
    }
    else
      $notValid = 'ERROR: Affid: '.$sponsor.' was not found in the system, nothing was removed from the system.';

    notValid($notValid);

    $main_content = '
    <center>
      <h3>Welcome to Admin Control</h3>
      '.$notValid.'
      <b>Menu</b>
      <br />
      <select size="2" onChange="window.location.href=\'?c=\'+this.options[this.selectedIndex].value">
        <option value="users">View Users</option>
        <option value="mailusers">Mail Users</option>
      </select>
    </center>
    <br /><br />
    ';
  }
  else if ($c == 'users')
  {
    $selected1 = $selected2 = $selected3 = $tableshow = '';

    // start paganation
    $pageSize = 750;
    $page  = abs($_GET['page']);

    if (! @is_int($page)) $page = 0;

    $offset = $page * $pageSize;
    $limit = "LIMIT $offset,$pageSize";
    // echo $limit;
    // end paganation

    $group = strtolower(trim($_REQUEST['group']));
    if (! in_array($group, $allowed_groups))
      $group = 'pro';

    $orderby = strtolower(trim($_REQUEST['orderby']));
    if (! @array_key_exists($orderby, $allowed_orderBy))
      $orderby = 'alertpay';

    $order = strtoupper(trim($_REQUEST['order']));
    if (! @array_key_exists($order, $allowed_order))
      $order = 'DESC';

    $by = strtolower(trim($_REQUEST['by']));
    if (! @array_key_exists($by, $allowed_by))
      $by = 'username';

    if ($group == 'free')
    {
      $selected1 = ' selected';

      $tableshow = '
      <table border="0" align="center" cellpadding="2" cellspacing="2">
      <tr bgcolor="lightblue">
        <td><b>Name</b></td>
        <td><b>Username</b></td>
        <td><b>Credits</b></td>
        <td align="center" colspan="3"><b>Action</b></td>
      </tr>
      ';

      // Free
      if ($db->Query("SELECT affid, fname, lname, username, status, credits, email, ipaddress FROM users WHERE status='0' AND verified != '0' ORDER BY $orderby $order $limit"))
      {
        $i = 0;
        $result = $db->result;
        $num_members = $db->rows;
        while (list($affid, $fname, $lname, $username, $status, $credits, $email, $ipaddress) = mysqli_fetch_row($result))
        {
          if ($i % 2)
            $bgcolor = '#FFFFFF';
          else
            $bgcolor = '#EEEEEE';

          // start --- owe commissions or not
          $downline = array();
          if ($db->Query("SELECT affid FROM users WHERE sponsor='$affid' ORDER BY fname"))
            while(list($_downline) = $db->FetchRow()) $downline[] = $_downline;

          if (count($downline))
          {
            foreach ($downline as $dl)
            {
              if ($db->Query("SELECT matured FROM commissions WHERE id_paid='0' AND sponsor='$dl'"))
              {
                $dl_result = $db->result;
                while (list($matured) = mysqli_fetch_row($dl_result))
                {
                  if ($matured)
                  {
                    $bgcolor = '#FCDEDE'; // red
                    break 2;
                  }
                  else
                    $bgcolor = '#F5FF9F'; // yellow
                }
              }
            }
          }
          // end --- owe commissions or not

          if ($db->Query("SELECT alertpay, egold, paypal FROM users WHERE affid='$affid'"))
            list($alertpay, $egold, $paypal) = $db->FetchRow();

          $paybutton = 'Pay -';

          if ($alertpay == '') // AND $egold == '' AND $paypal == '')
            $paybutton .= ' None';
          else
          {
            // if ($paypal) $paybutton .= ' P';
            // if ($egold) $paybutton .= ' E';
            if ($alertpay) $paybutton .= ' <b>AlertPay</b>';
          }

          $tableshow .= '
          <tr bgcolor="'.$bgcolor.'">
            <td nowrap>'.$fname.' '.$lname.'</td>
            <td>'.$username.'</td>
            <td align="center">'.$credits.'</td>
            <td><a href="?c=edit&sponsor='.$affid.'">Edit</a></td>
            <td><a href="javascript:void(0)" onclick="if (confirm(\'Are you sure you want to delete this user?\')) location.href=\'?c=deleteuser&sponsor='.$affid.'\'">Delete</a></td>
            <td nowrap><a href="?c=payout&sponsor='.$affid.'">'.$paybutton.'</a></td>
          </tr>
          ';

          $i++;
        }

        $db->Query("SELECT COUNT(*) FROM users WHERE status='0' AND verified != '0'");
        list($all_members) = $db->FetchRow();
      }
      else
        $tableshow .= '<tr><td align="center" colspan="10"><b>No Records at this time.</b></td></tr>';
    }
    else if ($group == 'pro')
    {
      $selected2 = ' selected';

      $tableshow = '
      <table border="0" width="100" align="center" cellpadding="1" cellspacing="1">
      <tr bgcolor="lightblue">
        <td nowrap><b>Name</b></td>
        <td><b>Username</b></td>
        <td><b>Billing</b></td>
        <td><b>Credits</b></td>
        <td align="center" colspan="3"><b>Action</b></td>
      </tr>
      ';

      // Pro
      if ($db->Query("SELECT affid, fname, lname, username, status, credits, email, ipaddress, datelastbilled FROM users WHERE status != '0' AND verified != '0' ORDER BY $orderby $order $limit"))
      {
        $i = 0;
        $result = $db->result;
        $num_members = $db->rows;
        while (list($affid, $fname, $lname, $username, $status, $credits, $email, $ipaddress, $datelastbilled) = mysqli_fetch_row($result))
        {
          $billing = '';
          if ($status == 1)
            $billing = (30 - round(DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'd'))).' Days';
          else if ($status == 2)
            $billing = 'Bill is Due';

          if ($i % 2)
            $bgcolor = '#FFFFFF';
          else
            $bgcolor = '#EEEEEE';

          // start --- owe commissions or not
          $downline = array();
          if ($db->Query("SELECT affid FROM users WHERE sponsor='$affid' ORDER BY fname"))
            while(list($_downline) = $db->FetchRow()) $downline[] = $_downline;

          if (count($downline))
          {
            foreach ($downline as $dl)
            {
              if ($db->Query("SELECT matured FROM commissions WHERE id_paid='0' AND sponsor='$dl'"))
              {
                $dl_result = $db->result;
                while (list($matured) = mysqli_fetch_row($dl_result))
                {
                  if ($matured)
                  {
                    $bgcolor = '#FCDEDE'; // red
                    break 2;
                  }
                  else
                    $bgcolor = '#F5FF9F'; // yellow
                }
              }
            }
          }
          // end --- owe commissions or not

          if ($db->Query("SELECT alertpay, egold, paypal FROM users WHERE affid='$affid'"))
            list($alertpay, $egold, $paypal) = $db->FetchRow();

          $paybutton = 'Pay -';

          if ($alertpay == '') // AND $egold == '' AND $paypal == '')
            $paybutton .= ' None';
          else
          {
            // if ($paypal) $paybutton .= ' P';
            // if ($egold) $paybutton .= ' E';
            if ($alertpay) $paybutton .= ' <b>AlertPay</b>';
          }

          $tableshow .= '
          <tr bgcolor="'.$bgcolor.'">
            <td nowrap>'.$fname.' '.$lname.'</td>
            <td>'.$username.'</td>
            <td nowrap align="center">'.$billing.'</td>
            <td align="center">'.$credits.'</td>
            <td><a href="?c=edit&sponsor='.$affid.'">Edit</a></td>
            <td><a href="?c=payout&sponsor='.$affid.'">Delete</a></td>
            <td nowrap><a href="?c=payout&sponsor='.$affid.'">'.$paybutton.'</a></td>
          </tr>
          ';

          $i++;
        }

        $db->Query("SELECT COUNT(*) FROM users WHERE status != '0' AND verified != '0'");
        list($all_members) = $db->FetchRow();
      }
      else
        $tableshow .= '<tr><td align="center" colspan="10"><b>No Records at this time.</b></td></tr>';
    }
    else if ($group == 'unverified')
    {
      $selected3 = ' selected';

      $tableshow = '
      <table border="0" width="100" align="center" cellpadding="1" cellspacing="1">
      <tr bgcolor="lightblue">
        <td nowrap><b>First Name</b></td>
        <td nowrap><b>Last Name</b></td>
        <td><b>Username</b></td>
        <td align="center"><b>Email</b></td>
        <td nowrap align="center"><b>Unverified</b></td>
      </tr>
      ';

      // Unverified
      if ($db->Query("SELECT affid, fname, lname, username, email, datesignedup FROM users WHERE verified='0' ORDER BY $orderby $order"))
      {
        $i = 0;
        $result = $db->result;
        $num_members = $db->rows;
        while (list($affid, $fname, $lname, $username, $email, $datesignedup) = mysqli_fetch_row($result))
        {
          if ($i % 2) $bgcolor = '#E6F0FF'; else $bgcolor = '#DBE7F9';

          $num_days = round(DateDiff(mysql_datetime_to_timestamp($datesignedup), time(), 'd')).' Days';

          $tableshow .= '<tr bgcolor="'.$bgcolor.'">
          <td nowrap>'.$fname.'</td>
          <td nowrap>'.$lname.'</td>
          <td>'.$username.'</td>
          <td>'.$email.'</td>
          <td align="center">'.$num_days.'</td>
          </tr>
          ';

          $i++;
        }

        $db->Query("SELECT COUNT(*) FROM users WHERE verified='0'");
        list($all_members) = $db->FetchRow();
      }
      else
        $tableshow .= '<tr><td align="center" colspan="4"><b>No Records at this time.</b></td></tr>';
    }

    // start paganation
    $page_prev = $page - 1;
    $page_next = $page + 1;

    if ($all_members)
      $num_pages = ceil($all_members / $pageSize);
    else
      $num_pages = 0;

    if ($page_prev < 0)
      $page_prev = 0;
    if ($all_members < ($pageSize + 1))
      $page = 0;
    if ( ! ($page_next < $num_pages) )
      $page_next = $num_pages - 1;

    $pageEnd = ($pageSize * ($page + 1));

    if ($pageEnd > $all_members) $pageEnd = $all_members;

    $pageShow = $offset.' - '.$pageEnd.' of '.$all_members;

    $selectOrderBy = '';
    foreach ($allowed_orderBy as $key => $label)
    {
      //echo "$key => $label<br />\n";
      $selected = '';
      if ($orderby == $key) $selected = ' selected="select"';
      $selectOrderBy .= '<option value="'.$key.'"'.$selected.'>'.$label.'</option>'."\n";
    }

    $selectOrder = '';
    foreach ($allowed_order as $key => $label)
    {
      //echo "$key => $label<br />\n";
      $selected = '';
      if ($order == $key) $selected = ' selected="select"';
      $selectOrder .= '<option value="'.$key.'"'.$selected.'>'.$label.'</option>'."\n";
    }

    $selectBy = '';
    foreach ($allowed_by as $key => $label)
    {
      //echo "$key => $label<br />\n";
      $selected = '';
      if ($by == $key) $selected = ' selected="select"';
      $selectBy .= '<option value="'.$key.'"'.$selected.'>'.$label.'</option>'."\n";
    }

    $selectOrderBy = '
    <select size="1" onchange="window.location.href=\'?c=users&order='.$order.'&by='.$by.'&page='.$page.'&group='.$group.'&orderby=\'+this.options[this.selectedIndex].value">
    '.$selectOrderBy.'
    </select>
    ';

    $selectOrder = '
    <select size="1" onchange="window.location.href=\'?c=users&by='.$by.'&orderby='.$orderby.'&page='.$page.'&group='.$group.'&order=\'+this.options[this.selectedIndex].value">
    '.$selectOrder.'
    </select>
    ';

    $selectBy = '
    <select size="1" onchange="window.location.href=\'?c=users&order='.$order.'&orderby='.$orderby.'&page='.$page.'&group='.$group.'&by=\'+this.options[this.selectedIndex].value">
    '.$selectBy.'
    </select>
    ';

    $go_first = '<a href="?c=users&by='.$by.'&order='.$order.'&orderby='.$orderby.'&group='.$group.'&page=0">&lt;&lt;</a>';
    $go_last  = '<a href="?c=users&by='.$by.'&order='.$order.'&orderby='.$orderby.'&group='.$group.'&page='.($num_pages-1).'">&gt;&gt;</a>';
    $pager    = $go_first.'&nbsp;&nbsp;&nbsp;&nbsp;<a href="?c=users&order='.$order.'&orderby='.$orderby.'&group='.$group.'&page='.$page_prev.'">&lt;</a> | <a href="?c=users&order='.$order.'&orderby='.$orderby.'&group='.$group.'&page='.$page_next.'">&gt;</a>&nbsp;&nbsp;&nbsp;&nbsp;'.$go_last;
    $pager   .= '<br />Page '.($page + 1).' of '.($num_pages);
    $pager    = '<b><font size="2">'.$pageShow.'</font><br /><font size="2">'.$pager.'</font></b>';
    // end pagenation

    $searchbox = '
    <form name="search" action="?c=search" method="POST">
      Search for:
      <input type="text" name="item" value="" size="15" maxlength="255" /> by:
      '.$selectBy.'
      &nbsp;&nbsp;&nbsp;&nbsp;<input type="submit" value="Search" />
      <input type="hidden" name="page" value="'.$page.'" />
      <input type="hidden" name="group" value="'.$group.'" />
      <input type="hidden" name="orderby" value="'.$orderby.'" />
      <input type="hidden" name="order" value="'.$order.'" />
      <input type="hidden" name="by" value="'.$by.'" />
    </form>
    ';

    $tableshow .= '</table>';

    $selectbox = '
    <select size="3" onchange="window.location.href=\'?c=users&by='.$by.'&order='.$order.'&orderby='.$orderby.'&group=\'+this.options[this.selectedIndex].value">
      <option value="free"'.$selected1.'>Free Members</option>
      <option value="pro"'.$selected2.'>Pro Members</option>
      <option value="unverified"'.$selected3.'>Unverified Members</option>
    </select>
    ';

    if ($num_members)
      $num_members = '<h3><b>'.$num_members.' '.ucwords($group).' Members</b></h3>';

    $notValid = urldecode($notValid);

    notValid($notValid);

    $main_content = '
    <center>
    '.$title.'
    '.$notValid.'
    <font size="3"><b>Sort List By: '.$selectOrderBy.'&nbsp;in&nbsp;'.$selectOrder.'&nbsp;Order</b></font>
    <br /><br />
    <table align="center" border="0" cellpadding="2" cellspacing="2"><tr>
      <td>'.$selectbox.'</td>
      <td align="center">'.$pager.'</td>
    </tr></table>
    <br />
    '.$searchbox.'
    '.$num_members.'
    '.$tableshow.'
    <hr />
    '.$pager.'
    <br /><br />
    </center>
    ';
  }
  else if ($c == 'mailusers')
  {
    $headers = 'From: Free AD Planet <elitescripts2000@yahoo.com>';

    if ($_POST['submitted'] == 'mailout' OR $_POST['submitted'] == 'save')
    {
      $subject = trim($_POST['subject']);
      $message = trim($_POST['message']);
      $which   = trim($_POST['which']);

      if ($subject == '' OR $message == '')
        $notValid = 'ERROR: Subject and/or Message is missing.';
      else
      {
        $db->Query("UPDATE admin SET subject='$subject', message='$message' WHERE username='admin'");

        if ($_POST['submitted'] == 'mailout')
        {
          $subject = stripslashes($subject);
          $message = stripslashes($message);

          set_time_limit(0);

          if ($which == 'free') $sql_which = "AND status='0'";
          else if ($which == 'pro') $sql_which = "AND (status='1' OR status='2')";
          else if ($which == 'all') $sql_which = "";
          else die('ERROR: which!=free,pro,all ... did not mail anything');

          $num_mailed = 0;
          $db->Query("SELECT email FROM users WHERE verified='1' $sql_which ORDER BY email");
          while(list($email) = $db->FetchRow())
          {
            if (@mail($email, $subject, $message, $headers))
            {
              $strRepeat = str_repeat(' ', 3515);
              $str = "Mailed to $email".$strRepeat."<br />\n";
              echo $str;
              flush();
              usleep(10000);
              $num_mailed++;
            }
          }

          $notValid = 'Successfully mailed <b>'.$num_mailed.'</b> '.ucfirst($which).' users.';
        }
        else
          $notValid = 'Successfully saved Message.<br />No users were mailed.';
      }
    }

    $db->Query("SELECT subject, message FROM admin LIMIT 1");
    list($subject, $message) = $db->FetchRow();

    switch ($which)
    {
      case 'free':
        $checked_free = ' CHECKED';
        $checked_pro = ' ';
        $checked_all = ' ';
        break;
      case 'all':
        $checked_free = ' ';
        $checked_pro = ' ';
        $checked_all = ' CHECKED';
        break;
      case 'pro':
      default:
        $checked_free = ' ';
        $checked_pro = ' CHECKED';
        $checked_all = ' ';
        break;
    }

    $form = '
    <form name="mailer" action="?c=mailusers" method="POST">
    <b>Subject:<b>
    <br />
    <input type="text" name="subject" value="'.$subject.'" size="70" maxlength="70" />
    <br /><br />
    <b>Message:</b>
    <br />
    <textarea name="message" cols="70" rows="20" wrap="physical">'.stripslashes(htmlentities($message)).'</textarea>

    <center>
      <br />
      <input type="radio" name="which" value="free"'.$checked_free.'/> Free
      <input type="radio" name="which" value="pro"'.$checked_pro.'/> Pro
      <input type="radio" name="which" value="all"'.$checked_all.'/> All
      <br /><br />
      <input type="submit" value="Send Mail" />&nbsp;&nbsp;&nbsp;&nbsp;<input type="button" value="Save Only" onclick="javascript:saveOnly();" />
    </center>

    <input type="hidden" name="c" value="mailusers" />
    <input id="submitted" type="hidden" name="submitted" value="mailout" />
    </form>
    ';

    notValid($notValid);

    $main_content = '
    '.$title.'
    <center>
    <h3>Mail All Members</h3>
    '.$notValid.'
    '.$form.'
    </center>
    ';
  }
  else if ($c == 'edit')
  {
    $sponsor = trim($_REQUEST['sponsor']);
    $action  = trim($_POST['action']);

    $table_data = '
      <form name="edituser" action="?c=edit" method="POST">
        <table width="640" align="center" cellpadding="1" cellspacing="1">
    ';

    if (! @is_numeric($sponsor))
      $notValid = 'ERROR: Sponsor in edit mode is not numerical.';
    else if ($db->Query("SELECT username, pass, status, verified, vacation, alertpay, fname, lname, email, credits, lockedcredits, datesignedup, dateloggedin, datelastbilled, ipaddress FROM users WHERE affid='$sponsor' LIMIT 1"))
    {
      // fetchRow after action == save
      // fetchRow after any updates
      $result = $db->result;

      if ($action == 'save')
      {
        // editable data
        $username = trim($_POST['username']);
        $fname    = ucwords(strtolower(trim($_POST['fname'])));
        $lname    = ucwords(strtolower(trim($_POST['lname'])));
        $email    = strtolower(trim($_POST['email']));
        $pass     = trim($_POST['pass']);
        $status   = trim($_POST['status']);
        $vacation = trim($_POST['vacation']);
        $alertpay = strtolower(trim($_POST['alertpay']));
        $credits  = trim($_POST['credits']);

        // readonly data
        $datalastbilled = trim($_POST['datelastbilled']);
        $datasignedup   = trim($_POST['datesignedup']);
        $dateloggedin   = trim($_POST['dateloggedin']);
        $verified       = trim($_POST['verified']);
        $lockedcredits  = trim($_POST['lockedcredits']);
        $ipaddress      = trim($_POST['ipaddress']);

        if (! $db->Query("SELECT username, email FROM users WHERE affid='$sponsor' LIMIT 1"))
          logout_session('ERROR: Contact Support Team.  Report error code: 1100');
        list($prev_username, $prev_email) = $db->FetchRow();

        if (has_weird($username)) $notValid = 'ERROR: Username contains illegal characters.';
        else if ($notValid=LengthUsername($username)) {}
        else if ($notValid=LengthRealname($fname)) {}
        else if ($notValid=LengthRealname($lname)) {}
        else if (has_space($pass)) $notValid = 'ERROR: Password may not contain spaces.';
        else if ($notValid=LengthPassword($pass)) {}
        else if ($notValid=EmailFormat($email,0)) {}
        else if ($alertpay AND ($notValid=EmailFormat($alertpay,0))) {}
        else if (strtolower($prev_username) != strtolower($username) AND $db->Query("SELECT username FROM users WHERE username='$username' LIMIT 1"))
          $notValid = 'ERROR: Username: <i>'.$username.'</i> is already taken.';
        else if (strtolower($prev_email) != strtolower($email) AND $db->Query("SELECT email FROM users WHERE email='$email' AND affid != '$sponsor'"))
        {
          $notValid = 'ERROR: Email: <i>'.$email.'</i> is already registered with another account.';
          $email = $prev_email;
        }
        else
        {
          if (! @is_int($vacation) OR $vacation < 0 OR $vacation > 1)
            $vacation = 0;

          $db->Query("UPDATE users SET username='$username', fname='$fname', lname='$lname', email='$email', pass='$pass',
                                       status='$status', vacation='$vacation', alertpay='$alertpay', credits='$credits'
                                       WHERE affid='$sponsor' LIMIT 1");

          $notValid = 'Successfully MODIFIED user profile.';
        }
      }
      else
      {
        // if edited input had anything wrong with it, query original data and use it instead
        list($username, $pass, $status, $verified, $vacation, $alertpay, $fname, $lname, $email, $credits, $lockedcredits, $datesignedup, $dateloggedin, $datelastbilled, $ipaddress) = mysqli_fetch_row($result);
        $notValid = 'Successfully LOADED user profile.';
      }

      $table_data .= '
        <tr bgcolor="#EEEEEE">
          <td align="right"><b><a href="?c=payout&sponsor='.$sponsor.'">Username:</a></b></td>
          <td><input type="text" name="username" value="'.$username.'" size="15" maxlength="20" /></td>
        </tr>
        <tr bgcolor="#FFFFFF">
          <td align="right"><b>First Name:</b></td>
          <td><input type="text" name="fname" value="'.$fname.'" size="10" maxlength="20" /></td>
        </tr>
        <tr bgcolor="#EEEEEE">
          <td align="right"><b>Last Name:</b></td>
          <td><input type="text" name="lname" value="'.$lname.'" size="10" maxlength="20" /></td>
        </tr>
        <tr bgcolor="#FFFFFF">
          <td align="right"><b>Email:</b></td>
          <td><input type="text" name="email" value="'.$email.'" size="25" maxlength="255" /></td>
        </tr>
        <tr bgcolor="#EEEEEE">
          <td align="right"><b>Password:</b></td>
          <td><input type="text" name="pass" value="'.$pass.'" size="20" maxlength="200" /></td>
        </tr>
        <tr bgcolor="#FFFFFF">
          <td align="right"><b>Verified:</b></td>
          <td><input type="text" name="verified" value="'.$verified.'" size="1" maxlength="1" readonly /> readonly</td>
        </tr>
        <tr bgcolor="#EEEEEE">
          <td align="right"><b>Status:</b></td>
          <td><input type="text" name="status" value="'.$status.'" size="1" maxlength="1" /></td>
        </tr>
        <tr bgcolor="#FFFFFF">
          <td align="right"><b>Vacation:</b></td>
          <td><input type="text" name="vacation" value="'.$vacation.'" size="1" maxlength="1" /></td>
        </tr>
        <tr bgcolor="#EEEEEE">
          <td align="right"><b>AlertPay:</b></td>
          <td><input type="text" name="alertpay" value="'.$alertpay.'" size="25" maxlength="255" /></td>
        </tr>
        <tr bgcolor="#FFFFFF">
          <td align="right"><b>Credits:</b></td>
          <td><input type="text" name="credits" value="'.$credits.'" size="8" maxlength="20" /></td>
        </tr>
        <tr bgcolor="#EEEEEE">
          <td align="right"><b>Locked Credits:</b></td>
          <td><input type="text" name="lockedcredits" value="'.$lockedcredits.'" size="8" maxlength="20" readonly /> readonly</td>
        </tr>
        <tr bgcolor="#FFFFFF">
          <td align="right"><b>Date Signed Up:</b></td>
          <td><input type="text" name="datesignedup" value="'.$datesignedup.'" size="18" maxlength="25" readonly /> readonly</td>
        </tr>
        <tr bgcolor="#EEEEEE">
          <td align="right"><b>Date Last Billed:</b></td>
          <td><input type="text" name="datelastbilled" value="'.$datelastbilled.'" size="18" maxlength="25" readonly /> readonly</td>
        </tr>
        <tr bgcolor="#FFFFFF">
          <td align="right"><b>Date Logged In:</b></td>
          <td><input type="text" name="dateloggedin" value="'.$dateloggedin.'" size="18" maxlength="25" readonly /> readonly</td>
        </tr>
        <tr bgcolor="#EEEEEE">
          <td align="right"><b>IP Address:</b></td>
          <td><input type="text" name="ipaddress" value="'.$ipaddress.'" size="12" maxlength="15" readonly /> readonly</td>
        </tr>
      ';
    }
    else
    {
      header('Location: ?c=users&notValid='.urlencode('Username was not found for editing.'));
      exit;
    }

    $table_data .= '
      <tr>
        <td colspan="10" align="center">
          <hr />
          <input type="submit" value="Save Changes" />
        </td>
      </tr>
      </table>

      <input type="hidden" name="sponsor" value="'.$sponsor.'" />
      <input type="hidden" name="action" value="save" />
    </form>
    ';

    notValid($notValid);

    $main_content = '
    <center>
    '.$title.'
    <font size="3"><b>Edit a Member</b></font>
    <br /><br />
    '.$notValid.'
    '.$table_data.'
    </center>
    ';
  }
  else if ($c == 'search')
  {
    $item    = trim($_POST['item']);
    $by      = trim($_POST['by']);
    $page    = trim($_POST['page']);
    $group   = trim($_POST['group']);
    $orderby = trim($_POST['orderby']);
    $order   = trim($_POST['order']);

    /*
    $allowed_by = array('alertpay'  => 'AlertPay'
                        'email'     => 'Email Address',
                        'fname'     => 'First Name',
                        'lname'     => 'Last Name',
                        'username'  => 'UserName',
                        'ipaddress' => 'IP Address');
    */

    //die(print_r($allowed_by));

    if (array_key_exists($by, $allowed_by) AND strstr($item, ';') == FALSE AND strstr($item, "'") == FALSE)
    //if (array_key_exists($by, $allowed_by))
    {
      if ($db->Query("SELECT affid FROM users WHERE $by = '$item' AND verified != '0' LIMIT 1"))
      {
        list($affid) = $db->FetchRow();
        header("Location: ?c=payout&sponsor=$affid");
      }
      else
       header("Location: ?c=users&by=$by&order=$order&orderby=$orderby&group=$group&page=$page&notValid=".urlencode('ERROR: Search by '.$by.' returned no match.'));
    }
    else
      header("Location: ?c=users&by=$by&order=$order&orderby=$orderby&group=$group&page=$page&notValid=".urlencode('ERROR: Search input contains illegal characters.'));

    exit;
  }
  else if ($c == 'payout')
  {
    if (! @is_numeric($sponsor))
      $notValid = 'ERROR: Sponsor is not numeric.';
    else
    {
      // get payee data
      $db->Query("SELECT username, fname, lname, status, datesignedup, dateloggedin, paypal, alertpay, egold FROM users WHERE affid='$sponsor'");
      list($username, $fname, $lname, $status, $datesignedup, $dateloggedin, $paypal, $alertpay, $egold) = $db->FetchRow();

      // 2007-07-27 21:22:36
      list($y, $m, $d) = preg_split("/[- ]/", $dateloggedin);
      $dateloggedin = date("M. j, Y", mktime(0, 0, 0, $m, $d, $y));

      list($y, $m, $d) = preg_split("/[- ]/", $datesignedup);
      $datesignedup = date("M. j, Y", mktime(0, 0, 0, $m, $d, $y));

      if ($status == 1)
        $status = 'Pro';
      else if ($status == 2)
        $status = 'Debt Pro';
      else
        $status = 'Free';

      $tableshow = '
        <form name="myform" action="index.php" method="get" class="blankform">

        <table border="0" align="center" cellpadding="3" cellspacing="1">
        <tr bgcolor="lightblue">
          <td><b>Amount</b></td>
          <td align="center"><b>Sale Type</b></td>
          <td align="center" nowrap><b>Sale Status</b></td>
          <td align="center" nowrap><b>Sale Date</b></td>
          <td align="center"><b>Downline/Status</b></td>
          <td align="center"><b>Matured?</b></td>
          <td align="center"><b>Pay?</b></td>
        </tr>
      ';

      $downline = array();
      if ($db->Query("SELECT affid FROM users WHERE sponsor='$sponsor' ORDER BY fname"))
        while(list($_downline) = $db->FetchRow()) $downline[] = $_downline;

      if (count($downline))
      {
        $i = 0;

        foreach ($downline as $dl)
        {
          if ($db->Query("SELECT id, amount, type, status, id_paid, matured, dateofsale FROM commissions WHERE sponsor='$dl' ORDER BY dateofsale DESC"))
          {
            $result = $db->result;
            while (list($id, $amount, $type, $status_at_time, $id_paid, $matured, $dateofsale) = mysqli_fetch_row($result))
            {
              // get data of member who purchased
              $db->Query("SELECT fname, lname, status FROM users WHERE affid='$dl' LIMIT 1");
              list($_fname, $_lname, $_status) = $db->FetchRow();

              $paid = $id_paid ? 'Yes' : 'No';

              if (! $matured)
              {
                $num_days = DateDiff(mysql_datetime_to_timestamp($dateofsale), time(), 'd');
                $num_days = round($num_days);
                if ($num_days < 0)
                  $num_days = 'Matured';
                else
                  $num_days = $commissions_days_mature - $num_days.' Days';
              }
              else
                $num_days = 'Matured';

              $i++;

              if ($i % 2)
                $bgcolor = '#FFFFFF';
              else
                $bgcolor = '#EEEEEE';

              $matured = $matured ? 'Yes' : 'No';

              // 2007-07-27 21:22:36
              list($y, $m, $d) = preg_split("/[- ]/", $dateofsale);
              $dateofsale = date("M. j, Y", mktime(0, 0, 0, $m, $d, $y));

              if ($status_at_time == 1)
                $status_at_time = '<b>Pro</b>';
              else if ($status_at_time == 2)
                $status_at_time = '<b><i>Debt</i> Pro</b>';
              else
                $status_at_time = '<i>Free</i>';

              $_status = $_status ? 'Pro' : 'Free';

              $tableshow .= '
              <tr bgcolor="'.$bgcolor.'">
                <td>'.$amount.'</td>
                <td>'.$type.'</td>
                <td nowrap align="center">'.$status_at_time.'</td>
                <td nowrap>'.$dateofsale.'</td>
                <td align="center" nowrap>'.$_fname.' '.$_lname[0].'. / '.$_status.'</td>
                <td align="center">'.$matured.'</td>
              ';

              // major error after trying to payout, said could not find or already paid out, after $28+ payment
              // SELECT * FROM `commissions` WHERE id='489' OR id='638' OR id='348' OR id='342' OR id='226' OR id='174' OR id='199'
              // SELECT * FROM `users` WHERE affid='12775604' OR affid='70835968' OR affid='12775604' OR affid='65418487' OR affid='65418487' OR affid='16380462' OR affid='17064601'
              // http://freeadplanet.com/admin/?c=payout_return&mop=alertpay&sponsor=16651186&ids=489.638.348.342.226.174.199

              $checkBox = '';
              if ($matured == 'Yes' AND $paid == 'No')
                $checkBox = '<input id="'.$id.'" type="checkbox" name="amount" value="'.$amount.'" onclick="javascript:updateTotal('.$id.')" />';

              $tableshow .= '
                <td align="center">'.$checkBox.'</td>
              </tr>
              ';
            }
          }
        }

        $tableshow .= '
        <tr>
          <td><input id="total" type="text" name="total" size="5" readonly /></td>
          <td colspan="3"><b>Total to Pay</b></td>
        </tr>
        ';

        $pp = $ap = $eg = $paybutton = '';
        // if ($paypal)   $pp = '<input id="paypal" type="radio" name="mop" value="paypal" /> Paypal';
        if ($alertpay) $ap = '<input id="alertpay" type="radio" name="mop" value="alertpay" /> Alertpay';
        // if ($egold)    $eg = '<input id="egold" type="radio" name="mop" value="egold" /> Egold';
        if (! $pp AND ! $ap AND ! $eg) $pp = '<b>No Method of Payment specified.</b>';
        else
        {
          $paybutton  = '<hr /><input type="button" value="Pay Out Now" onclick="javascript:payOut(0)" />&nbsp;&nbsp;&nbsp;&nbsp;';
          $paybutton .= '<input type="button" value="Update Return URL" onclick="javascript:payOut(1)" />';
        }

        $tableshow .= '
        <tr>
          <td colspan="10" align="center">
          '.$pp.'
          '.$eg.'
          '.$ap.'
          '.$paybutton.'
          </td>
        </tr>
        </table>
        </form>
        ';
      }
      else
        $notValid = 'No commissions recorded or matured.';
    }

    notValid($notValid);

    $user_data = '
    <table border="0" align="center" cellpadding="3" cellspacing="1">
      <tr bgcolor="lightblue">
        <td align="center"><b>Username</b></td>
        <td align="center"><b>Name</b></td>
        <td align="center"><b>Status</b></td>
        <td align="center"><b>Signed Up</b></td>
        <td align="center"><b>Last Logged In</b></td>
      </tr>
      <tr bgcolor="#EEEEEE">
        <td align="center"><a href="?c=edit&sponsor='.$sponsor.'">'.$username.'</a></td>
        <td align="center">'.$fname.' '.$lname.'</td>
        <td align="center">'.$status.'</td>
        <td align="center">'.$datesignedup.'</td>
        <td align="center">'.$dateloggedin.'</td>
      </tr>
    </table>
    ';

    $main_content = '
    <center>
    '.$title.'
    <font size="3"><b>Commission Pay Out</b></font>
    <br /><br />
    '.$user_data.'
    <br />
    </center>
    '.$notValid.'
    '.$tableshow.'
    <table align="center" cellpadding="0" cellspacing="0">
    <tr>
      <td align="center">
        <textarea id="returnURL" rows="2" cols="70"></textarea>
      </td>
    </tr>
    </table>
    ';
  }
  else if ($c == 'payout_return')
  {
    $total_paid = '';
    $commission_ids = array();
    $mops = array('alertpay'); // , 'egold', 'paypal');

    $sponsor = $_GET['sponsor'];
    $ids = $_GET['ids'];
    $mop = $_GET['mop'];


    if (! @is_numeric($sponsor))
      $notValid = 'ERROR: Sponsor is not numeric.';
    else if ($ids == '')
      $notValid = 'ERROR: No ids returned. No commission payouts were updated.';
    else if (! $db->Query("SELECT id FROM commissions WHERE sponsor='$sponsor' LIMIT 1"))
      $notValid = 'ERROR: Sponsor does not exist or does not have any commissions that are unpaid.';
    else if (! $db->Query("SELECT username, fname, lname, email FROM users WHERE affid='$sponsor' LIMIT 1"))
      $notValid = "ERROR: Username=$sponsor not found, yet have commissions pending? This should never occur!<br />\n";
    else
    {
      list($username, $fname, $lname, $email) = $db->FetchRow();

      $ids_returned = explode('.', $ids);

      foreach ($ids_returned as $id_returned)
      {
        $id_returned = trim($id_returned);

        if (! @is_numeric($id_returned))
        {
          $notValid .= "BAD: id_returned=$id_returned is not numeric.<br />\n";
          continue;
        }

        // commissions = id, sponsor, amount, type, status, matured, id_pxm, id_paid, dateofsale
        // commissions_paid = id, amount, mop, receipt, commissions_ids, datepaid

        /*
        // ensure owner of comission was sponsored by the affid that is being paid out
        if ($db->Query("SELECT sponsor FROM commissions WHERE id='$id_returned'"))
        {
          list($_sponsor) = $db->FetchRow();

          if (! $db->Query("SELECT sponsor FROM users WHERE affid='$_sponsor' AND sponsor='$sponsor' LIMIT 1"))
          {
            $notValid .= "BAD: FROM users WHERE affid=$_sponsor AND sponsor=$sponsor does not belong to owner of commission of id=$id_returned<br />\n";
            continue;
          }
        }
        */

        if (in_array($id_returned, $commission_ids))
          $notValid .= "BAD: id_returned=$id_returned was a duplicate.<br />\n";
        else if ($db->Query("SELECT amount FROM commissions WHERE id_paid='0' AND id='$id_returned' LIMIT 1"))
        {
          list($amount) = $db->FetchRow();
          $commission_ids[] = $id_returned;
          $total_paid += $amount;
          $notValid .= "GOOD: id_returned=$id_returned found and amount=$amount<br />\n";
        }
        else
          $notValid .= "BAD: id_returned=$id_returned was not found or was already paid.<br />\n";
      }

      if (count($commission_ids))
      {
        $commission_ids = implode('.', $commission_ids);

        $total_paid = number_format($total_paid, 2, '.', '');

        if (! @in_array($mop, $mops))
          $mop = 'unknown';

        $db->Query("INSERT INTO commissions_paid (id,   amount,        mop,   receipt,   commission_ids,  datepaid)
                                           VALUES('', '$total_paid', '$mop', 'XXXXXX', '$commission_ids', NOW())");

        $commissions_paid_id = mysqli_insert_id($db->link);

        $commission_ids = explode('.', $commission_ids);

        foreach ($commission_ids as $id_returned)
        {
          $db->Query("UPDATE commissions SET id_paid='$commissions_paid_id' WHERE id='$id_returned'");
          $notValid .= "GOOD: id_returned=$id_returned set as id_inserted=$commissions_paid_id<br />\n";
        }

        $mess = "Hello $fname,\n\nYou have just been paid commissions!\n\nFree AD Planet would like to congratulate you!\n\nThe amount of \$$total_paid was deposited into your ".ucfirst($mop)." account.\n\nYour freeadplanet.com Username is: $username\n\nThe amount deposited reflects what your Downline has ordered from us.\nPlease, Login for further information.\nWe also hope freeadplanet.com helps you to succeed.\n\nRegards,\nMatt - Customer Care\nhttp://freeadplanet.com";

        @mail($email,
              'Free AD Planet has Paid You',
              $mess,
              $headers);

        @mail('elitescripts2000@yahoo.com',
              'Free AD Planet has Paid You',
              $mess,
              $headers);

        $notValid .= "SUCCESS: commissions_paid_id=$commissions_paid_id - total_paid=$total_paid - mop=$mop";
      }
      else
        $notValid .= "ERROR: ids_paid was empty. Nothing was updated.";
    }

    notValid($notValid);

    $debug_return = '<br /><pre>'.print_r($_GET, 1).'</pre>';

    $main_content = '
    '.$title.'
    <center><h3>Commission Pay Out Return Status</h3></center>
    '.$notValid.'
    '.$debug_return.'
    ';
  }
}

?>
