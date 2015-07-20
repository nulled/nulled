<?php
if (strstr(strtolower($_SERVER['HTTP_REFERER']), 'ihaveliftoff.com')) die();

require_once('/home/nulled/www/planetxmail.com/phpsecure/cbvalid.php');
require_once('/home/nulled/www/freeadplanet.com/secure/classes.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$allowed = array('home','joinfree','earncash','aboutus','contactus','memberlogin','processorder',
'validatesignup','memberexit','validatechangedemail','resendvalidation','dah','dav','remove');
if (! in_array($c, $allowed)) $c = 'home';

$db = new MySQL_Access('fap');

$ba = get_ads('', 'banner', 2, $db);

$bannerad_top = $bannerad_bot = '';
if ($ba[0]) $bannerad_top = '<a href="'.$ba[0]['url'].'" target="_blank"><img src="http://freeadplanet.com/_signs/'.$ba[0]['image'].'" width="468" height="60" border="0" /></a>';
if ($ba[1]) $bannerad_bot = '<a href="'.$ba[1]['url'].'" target="_blank"><img src="http://freeadplanet.com/_signs/'.$ba[1]['image'].'" width="468" height="60" border="0" /></a>';

// -------------------------------
// start affid cookie
$sponsor = '';
if (@is_numeric($affid)) // if affid in URL, set
{
  if ($db->Query("SELECT fname, lname FROM users WHERE affid='$affid' LIMIT 1"))
  {
    list($_fname, $_lname) = $db->FetchRow();
    $sponsor = "$_fname ".$_lname[0].".";
  }
}
// if affid in URL ok, set/reset cookie
if ($sponsor)
  setcookie('fap_sponsor', $affid, strtotime('+2 years'), '/', '.freeadplanet.com', 0, 1);
else // affid in URL was not OK
{
  // look for existing affid cookie
  if (@is_numeric($_COOKIE['fap_sponsor']))
  {
    $affid = $_COOKIE['fap_sponsor'];
    if ($db->Query("SELECT fname, lname FROM users WHERE affid='$affid' LIMIT 1"))
    {
      list($_fname, $_lname) = $db->FetchRow();
      $sponsor = "$_fname ".$_lname[0].".";
    }
  }

  // if existing cookie no good, set to myself
  if ($sponsor == '')
  {
    $affid   = '11187448';
    $sponsor = "Matt K.";
    setcookie('fap_sponsor', $affid, strtotime('+2 years'), '/', '.freeadplanet.com', 0, 1);
  }
}
// end affid cookie
// -------------------------------

if ($c == 'home')
{
  $main_content = '
  <center><div class="sponsor_header">My name is <font color="red">'.$sponsor.'</font>. I will be your sponsor.</div></center>
  <br />

  <center><font color="red" size="+1"><b>A Revolution in Internet Advertising.</b></font>
  <br /><br />
  <b>100% Free to Join.</b>
  </center>

  <br />
 <!--
  <script type="text/javascript" src="http://www.speechagents.com/char.cgs?options=300116300_5&hd=yes"></script>
 -->
  Featuring a <b>Push-Pull Credit and Commissions Based System</b> like nothing seen before.
  <br /><br />
  If people are not viewing <u>your</u> ADs then their ADs <i>disappear</i>!
  This compels them to View <u>your</u> ADs in order to keep their ADs visible.
  This connection with Advertiser and Consumer <i>will <u>finally</u> get your ADs viewed</i>.
  <br /><br />
  <b>Free Members</b> earn up to 20% commissions on all Sponsored Transactions.
  <br /><br />

  <a name="top"></a>
  <hr />
  <h3><font color="red">F</font>requently <font color="red">A</font>sk <font color="red">Q</font>uestions</h3>

  <ul>
    <li><a href="#porn">Is porn or other such ADs allowed?</a></li>
    <li><a href="#whatis">What is Free AD Planet?</a></li>
    <li><a href="#xfer">Can I use this service with planetxmail.com (Planet X Mail)?</a></li>
    <li><a href="#fap_pxm">Does Free AD Planet and Planet X Mail use the same Credit System?</a></li>
    <li><a href="#emails">Will I receive a ton of Email from Members?</a></li>
    <li><a href="#free">Is this service really FREE?</a></li>
    <li><a href="#privacy">Will my Email Address or Info be sold out?</a></li>
    <li><a href="#sessions">Why do I get kicked out when trying to Log-In?</a></li>
  </ul>

  <hr />
  <a name="porn">Is porn or other such ADs allowed?</a> - <a href="#top">Top</a><br /><br />
  <b>No</b>. Porn, scams or anti-goverment or anti-religious Ads are forbidden from freeadplanet.com. This includes banners,
  text ads or ANY type of AD submitted to freeadplanet.com. If it is found you are trying to promote Porn or the mentioned forbidden
  subject material, you will be deleted and your IP Address added to our banned list.
  <br /><br />
  Such material is forbidden, because too many users of our AD network get very upset in seeing anything remotely related. So, please
  save yourself some time, and do not even try to do it. We thank you for your understanding and cooperation in this matter.

  <hr />
  <a name="whatis">What is Free AD Planet?</a> - <a href="#top">Top</a><br /><br />
  Free AD Planet is a place to do Free <i>effective</i> Advertising to the planet!
  This is how the system works, because who has time these days?
  <ol>
    <li>Create a <i>Free</i> Account. Your privacy like last name and email are kept private.</li>
    <li>Our system is Double Optin, so no worries about spam.</li>
    <li>Once logged in you can...</li>
      <ol>
        <li>Submit Text ADs.</li>
        <li>Submit Logo and Text AD combos called Bill Board ADs.</li>
        <li>Submit Targeted Text ADs.</li>
        <li>Submit Exit ADs which people see when they log out or mail out.</li>
      </ol>
    <li>Credit Based, so people that participate are rewarded.</li>
    <li>People that do not participate get \'Credit Drain\' and their ADs become invisible.</li>
    <li>Build your Downline and earn 20-30% commissions on each purchase they make.</li>
    <li>Mail your Downline every couple days.</li>
  </ol>
  <font color="green"><b>If an AD system allows everyone to post an AD then run away, the consequence will be
  that everyone will do the same thing and no one will pay attention to <i>any</i> of the ADs. (Including your ADs.)</b></font>
  This post and run behavior is counter productive.
  <br /><br />
  This is not a Post \'n Run system/website.
  Tell me what benefit would that be if everyone was doing the same thing? We entice people to return
  because, if they do not, their ADs will become invisible. You keep your ADs visible to the public by <i>SIMPLY</i>...
  <ul>
    <li>Having Credits in your Account. (Earn them by viewing ADs. Takes only seconds.)</li>
  </ul>
  You benefit by knowing others are doing the same thing in order to Earn Credits! Give and Take is a phrase we have
  all learned that works.
  <br /><br />
  <b>Free AD Planet</b> <u>wants to help you succeed</u> by allowing you a way to Advertise to others.

  <hr />
  <a name="xfer">Can I use this service with planetxmail.com (Planet X Mail)?</a> - <a href="#top">Top</a><br /><br />
  <b>Yes</b>. Free AD Planet and <i>Planet X Mail</i> were produced by the same company.  We have arranged it so PRO Members
  can easily Transfer Credits Earned at planetxmail.com to be used at freeadplanet.com. This means you can Advertise
  using effective Email Advertising (planetxmail.com) and compliment that with Classified Style Advertising
  (freeadplanet.com).

  <hr />
  <a name="fap_pxm">Does Free AD Planet and Planet X Mail use the same Credit System?</a> - <a href="#top">Top</a><br /><br />
  <b>No</b>. Please, do not mistake Planet X Mail (planetxmail.com) with Free AD Planet (freeadplanet.com). We get
  a lot of confused folks that tend to mix the two sites up. Each site has it\'s <i>own</i> Credit System and
  Member Accounts! <i>As mentioned before it is possible to transfer Planet X Mail Credits to a Free AD Planet Account.</i>
  This is the only connection between the two sites. We think the mix up occurs because the word \'planet\' appears in both
  domain names. It is also true that both sites use similar styles with regards to how Credits are Earned and how the Earning
  System looks.

  <hr />
  <a name="emails">Will I receive a ton of Email from Members?</a> - <a href="#top">Top</a><br /><br />
  <b>No.</b> We do not put our focus on Email Advertising. The main focus is to Earn Credits by viewing Classified
  style ADs. These Credits can then be used to supply you with more
  options... like posting more of <u>your</u> own ADs!
  <br /><br />
  This site was created to <i>compliment</i> <a href="http://planetxmail.com" target="_blank">Planet X Mail</a>
  Safelist Services. You can transfer Credits you earned at planetxmail.com to your Free AD Planet Account!

  <hr />
  <a name="free">Is this service really FREE?</a> - <a href="#top">Top</a><br /><br />
  <b>Yes.</b> To sign up costs you nothing. Yet, as a Free Member you can still Earn Commissions from those
  that do decide to Upgrade or Purchase additional ADs and services. If, you build a Downline of people
  and they start Upgrading and/or Purchasing additional Services you earn a whopping 10-20%.

  <hr />
  <a name="privacy">Will my Email Address or Info be sold out?</a> - <a href="#top">Top</a><br /><br />
  <b>Absolutely Not.</b> Even your Sponsor does not know your Email Address. Our system allows people to Advertise safely.
  Free AD Planet itself will never give out any information to other AD Agencies.
  We run the <a href="http://planetxmail.com" target="_blank">Top SafeList Host on the Planet</a>
  with Hundreds of Thousands of accounts since 2001 and have never been in trouble with Privacy or SPAM Laws. This is because
  we are not in it for any short term gains. In fact, we are here to help you succeed at Advertising your Products and Services.
  Without active members, we could not exist.

  <hr />
  <a name="sessions">Why do I get kicked out when trying to Log-In?</a> - <a href="#top">Top</a><br /><br />
  The privacy settings in your Web Browser are too low. 95% of all Web sites require cookies;
  therefore, if you select a setting that does not allow cookies to be saved on your computer,
  you might not be able to view certain Web sites. Basically, any Web site that you log into using a Username and
  Password uses Cookies.
  <br /><br />
  Cookies are completely harmless, pose no security threat and are simply a way for a Web Site to know who is visiting
  the site by placing small bits of data on your computer to identify you from others. Mainly used for secure log ins to
  web sites.
  <br /><br />
  Internet Explorer users
  <a href="http://www.microsoft.com/resources/documentation/windows/xp/all/proddocs/en-us/set_priv_custom.mspx?mfr=true" target="_blank">Click Here</a>.
  <br /><br />
  We <i>highly recommend</i> you use <a href="http://www.mozilla.com/en-US/firefox/" target="_blank">FireFox Web Browser</a> instead. It is <i>free to download and use</i>
  and is more standards compliant then Internet Explorer. Remember
  Netscape web browser a few years back? Well through monopoly tactics Internet Explorer was forced upon us.
  <a href="http://www.mozilla.com/en-US/firefox/" target="_blank">FireFox</a> (post Netscape) was made free of charge and is now used by
  30% + of all Internet surfers and growing. FireFox is an international web browser following international standards, unlike Internet Explorer.
  You can view the
  <a href="http://www.w3schools.com/browsers/browsers_stats.asp" target="_blank">updated browser usage statistics</a>, if interested.
  <br /><br />
  Free AD Planet, of course, works in both web browsers. Including Safari (Mac) and Opera.

  <br />
  ';
}
else if ($c == 'memberexit')
{
  $why = urldecode($why);
  notValid($why);
  $main_content = $why;
}
else if ($c == 'validatechangedemail')
{
  $hash  = trim($h);
  $affid = trim($affid);
  $email = urldecode(trim($e));

  $vhash = substr(md5(strrev(md5($affid.$email))), 0, 5);

  if ($vhash == $hash)
  {
    if ($db->Query("SELECT username FROM users WHERE affid='$affid' AND verified='1'"))
      $main_content = 'This account is already verified.';
    else if (! $db->Query("SELECT email, fname, lname FROM users WHERE affid='$affid'"))
      $main_content = 'ERROR: No account with affid '.$affid.' was found.<br />You may need to resign up.';
    else
    {
      list($email, $fname, $lname) = $db->FetchRow();

      $db->Query("UPDATE users SET verified='1' WHERE affid='$affid' LIMIT 1");

      @mail($email,
            "Email Changed Notice",
            "Hello $fname $lname,\n\nYour Contact Email has been changed.\n\nRegards,\nhttp://freeadplanet.com Staff",
            "From: Free AD Planet <do_not_reply@freeadplanet.com>");

      $main_content = 'Contact Email has been changed.<br />You may now log in.';
    }
  }
  else
    $main_content = 'ERROR: Validation URL is not valid.';

  notValid($main_content);
}
else if ($c == 'validatesignup')
{
  $hash  = trim($h);
  $affid = trim($affid);

  $vhash = substr(md5(strrev(sha1($affid))), 0, 5);

  if ($vhash == $hash)
  {
    if ($db->Query("SELECT username FROM users WHERE affid='$affid' AND verified='1' LIMIT 1"))
      $main_content = 'This account is already verified.<br />You may now log in.';
    else if (! $db->Query("SELECT email, fname, lname, username, pass, sponsor, status FROM users WHERE affid='$affid' LIMIT 1"))
      $main_content = 'ERROR: No account with affid '.$affid.' was found.<br />You may need to re-sign up.';
    else
    {
      list($email, $fname, $lname, $username, $pass, $sponsor, $status) = $db->FetchRow();

      $ipaddress = $_SERVER['REMOTE_ADDR'];

      /*
      // allow only 1 Free account, but unlimited Pro accounts
      // trackable via cookies, so they can in theory delete the cookie and work around this
      // email alerts me of those trying to log in and failing
      if (! @is_numeric($_COOKIE['_fap_id_']) OR ! $db->Query("SELECT status FROM users WHERE affid='{$_COOKIE['_fap_id_']}' LIMIT 1"))
        setcookie('_fap_id_', $affid, strtotime('+2 years'), '/', '.freeadplanet.com', false, true);
      else if ($_COOKIE['_fap_id_'] != $affid AND $status == 0)
      {
        if ($db->Query("SELECT status FROM users WHERE affid='{$_COOKIE['_fap_id_']}' AND status = '0' LIMIT 1"))
        {
          @mail('elitescripts2000@yahoo.com',
                'illegal dup login',
                "affid=$affid\nusername=$username\ncookie={$_COOKIE['_fap_id_']}\nipaddress=$ipaddress",
                $headers);
          logout_session('ERROR: Only 1 Free account is allowed.<br />However, you <i>may</i> create multiple Pro accounts.');
        }
      }
      */

      $db->Query("UPDATE users SET verified='1' WHERE affid='$affid' LIMIT 1");

      // award the sponsor referral credits
      if (@is_numeric($sponsor) AND $sponsor != '11187448') // exclude my account 'nulled'
      {
        if ($db->Query("SELECT status, credits FROM users WHERE affid='$sponsor' AND verified='1' LIMIT 1"))
        {
          list($_status, $_credits) = $db->FetchRow();

          if ($_status == 0 OR $_status == 2)
            $earned_credits = $ref_credits_earned_free;
          else
            $earned_credits = $ref_credits_earned_pro;

          $_credits = $_credits + $earned_credits;

          $db->Query("UPDATE users SET credits='$_credits' WHERE affid='$sponsor' LIMIT 1");
        }
      }

      @mail($email,
            'Free AD Planet - Welcome Notice',
            "Greetings $fname $lname,\n\nWelcome to Free AD Planet!\n\nVisit the URL below to Log In.\n\nhttp://freeadplanet.com/?c=memberlogin\n\nUsername: $username\nPassword: $pass\n\nRegards,\nhttp://freeadplanet.com Staff",
            'From: Free AD Planet <do_not_reply@freeadplanet.com>');

      $main_content = 'Your Account has been verified.<br />You may now Log In.';
    }
  }
  else
    $main_content = 'ERROR: Validation URL is not valid.';

  notValid($main_content);
}
else if ($c == 'joinfree')
{
  if ($submitted == 'join')
  {
    $username = trim($username);
    $pass     = trim($pass);
    $fname    = ucwords(strtolower(trim($fname)));
    $lname    = ucwords(strtolower(trim($lname)));
    $email    = strtolower(trim($email));

    $cat_str = build_cat_str($cat);

    if (has_weird($username)) $notValid = 'ERROR: Username contains illegal characters.';
    else if ($notValid=LengthUsername($username)) {}
    else if ($notValid=LengthRealname($fname)) {}
    else if ($notValid=LengthRealname($lname)) {}
    else if (! ctype_alpha($fname)) $notValid = 'ERROR: First name may only contain Letters.';
    else if (! ctype_alpha($lname)) $notValid = 'ERROR: Last name may only contain Letters.';
    else if (has_space($pass)) $notValid = 'ERROR: Password may not contain spaces.';
    else if ($notValid=LengthPassword($pass)) {}
    else if ($notValid=EmailFormat($email)) {}
    else if ($db->Query("SELECT username FROM users WHERE username='$username' LIMIT 1")) $notValid = 'ERROR: Username: '.$username.' is already verified and registered.';
    else if ($db->Query("SELECT email FROM users WHERE email='$email' LIMIT 1")) $notValid = 'ERROR: Email: '.$email.' is already registered.';
    else if (turing_key_valid($turing_key_timeout))
    {
      $i = 0;
      while (1)
      {
        $i++;
        if ($i > 10000) exit('ERROR: Unable to generate affid. Contact Support.');
        $_affid = substr(mt_rand(), 0, 8);
        if (strlen($_affid) < 8) continue;
        if (! $db->Query("SELECT affid FROM users WHERE affid='$_affid' LIMIT 1") AND
            ! $db->Query("SELECT affid FROM pastaffs WHERE affid='$_affid' LIMIT 1"))
              break;
      }

      $hash = substr(md5(strrev(sha1($_affid))), 0, 5);

      $val_url = "http://freeadplanet.com/?c=validatesignup&affid=$_affid&h=$hash";

      $ipaddress = $_SERVER['REMOTE_ADDR'];

      $db->Query("INSERT INTO users (username,     pass,   fname,   lname,   email,   affid,   sponsor,    categories,  credits,          lockedcredits,         ipaddress,    datesignedup)
                              VALUES('$username','$pass','$fname','$lname','$email','$_affid','$affid',   '$cat_str',  '$start_credits', '$start_lockedcredits', '$ipaddress', NOW())");

      @mail($email,
            'Free AD Planet - Validate Account Notice',
            "Hello $fname $lname,\n\nVisit the URL below to Validate your Account.\n\n$val_url\n\nUsername: $username\nPassword: $pass\n\nThis Validation Notice is good for 5 days.\n\nRegards,\nhttp://freeadplanet.com Staff",
            'From: Free AD Planet <do_not_reply@freeadplanet.com>');

      $main_content = 'We have sent a confirmation email to: <font color="red">'.$email.'</font>.<br />You must validate your account before you can log in.';
      notValid($main_content);

      $show_email_confirmer = 1;
      $main_content .= '<div id="layer1" class="dnd"></div>';
      $hash = strrev(substr(md5(sha1(strrev($email))), 0, 5));
    }
    else
      $notValid = 'ERROR: Invalid Turing Key.<br />You have '.$turing_key_timeout.' seconds before the Key Expires.';
  }

  if (($notValid AND $submitted == 'join') OR $submitted == '')
  {
    $cats = build_cat_table($cat_str, $db);

    $category_summary = '
    Targeted ADs belonging to the Categories you choose here can be changed in the members area.<br /><br />
    ';

    notValid($notValid);

    list($v, $keyfilename) = turing_key_create();

    $main_content = '
    <form name="signup" action="?c=joinfree" onsubmit="javascript:submitOnce();" method="POST">

    <table align="center" border="0">

      <tr>
        <td align="center" colspan="2">
          <font size="+1"><b>Joining FREE is easy!</b></font>
          <br /><br />
          <b>Your Sponsor is <font color="red">'.$sponsor.'</font></b>
          <br /><br />
          '.$notValid.'
        </td>
      </tr>

      <tr>
        <td align="right"><b>Username:</b></td>
        <td nowrap><input type="text" name="username" value="'.$username.'" size="15" maxlength="20" /></td>
      </tr>

      <tr>
        <td align="right"><b>Password:</b></td>
        <td nowrap><input type="text" name="pass" value="'.$pass.'" size="15" maxlength="32" /></td>
      </tr>

      <tr>
        <td align="right"><b>First Name:</b></td>
        <td nowrap><input type="text" name="fname" value="'.$fname.'" size="15" maxlength="20" /></td>
      </tr>

      <tr>
        <td align="right"><b>Last Name:</b></td>
        <td nowrap><input type="text" name="lname" value="'.$lname.'" size="15" maxlength="20" /></td>
      </tr>

      <tr>
        <td align="right"><b>Email:</b></td>
        <td nowrap><input type="text" name="email" value="'.$email.'" size="30" maxlength="250" /> <i>Validation Required</i></td>
      </tr>

      <tr>
        <td colspan="2" align="center">
          <table width="350" style="border-collapse: collapse" bordercolor="#000000" border="0" cellspacing="0" cellpadding="0">
          <tr><td colspan="4" align="center"><h3>Categories</h3>'.$category_summary.'</td></tr>
          <tr><td>
          '.$cats.'
          </td></tr>
          </table>
        </td>
      </tr>

      <tr>
        <td colspan="2" align="center" nowrap>
          <hr />
          <b>Turing Key: </b><img src="http://freeadplanet.com/keys/'.$keyfilename.'" border="0" /> <input type="text" name="tkey" size="4" />
          <hr />
          <input id="submit" type="submit" value="Sign Up" />
        </td>
      </tr>

      <input type="hidden" name="c" value="joinfree" />
      <input type="hidden" name="submitted" value="join" />
      <input type="hidden" name="v" value="'.$v.'" />
      </form>

    </table>
    ';
  }
}
else if ($c == 'earncash')
{
  $main_content = '
  <center><img src="images/earncash.jpg" border="0" />
  <br /><br />
  <b>Knock out, Two birds, with <i>One</i> stone.
  <br />
  Earn CASH, <i>at the same time</i>, Advertise <i>your</i> own Website!</b>
  </center>
  <br />

  One of the best ways to get the word out about a product or service, is through hear say, or affiliate based reward systems.
  <br /><br />
  We pay, <u>all our members</u>, for people they refer to us. Not only that, but we pay up to 30% of purchases placed, by any member of your
  downline! Regardless, if your account is Pro or not, and regardless if your downline is Pro Level or not!
  <br /><br />
  <font color="red"><b>Tired of wasting your time or have doubts about affiliate based businesses, and their honesty?</b></font>
  We understand, as we know there are plenty of
  businesses that <i>claim</i> all kinds of non-sense, but never carry through! These fly-by-night, rip off sites, are all to common. They
  destroy the publics faith in the Industry, causing many, would-be-members, to pass up the <i>honest</i> businesses!
  <br /><br />
  But, you can protect yourself and your precious time and money.
  <br /><br />
  We have <i>thousands</i> of loyale members for a reason. <b>That reason is simple.</b> Run an honest commission based
  business, and pay your members their hard earned cut, and that business will <b>retain</b> members and grow! Word spreads like wild fire,
  on the Internet. People post reviews of happiness or anger, about their experiences. We know this, and
  <i>honor</i> our loyale members, by playing fair, and <i>pay</i> our members, what they rightfully earned, based on what was promised!
  <br /><br />
  We have already paid out, over $10,000 in commissions to our beloved and loyale members!
  <br /><br />
  We want to <i>Welcome you</i>, to our global family of members, here at Free AD Planet!
  <br /><br />
  <a href="?c=joinfree">Sign up Free</a>, <a href="?c=joinfree">Advertise Free</a> and <a href="?c=joinfree">Earn Money</a>.
  ';
}
else if ($c == 'aboutus')
{
  $main_content = '
  <center><img src="images/aboutus.jpg" border="0" /></center>
  <br />

  <!--
  <script type="text/javascript" src="http://www.speechagents.com/char.cgs?options=000216300_1&hd=yes"></script>
  -->

  <b>Free AD Planet</b> was designed by the same folks at
  <a href="http://planetxmail.com" target="_blank">Planet X Mail</a>. We have nearly a decade of experience, developing ultra secure,
  ultra effective and ultra user friendly Web Applications, as a result.
  <br /><br />
  The focus of this site, is on <i>active</i> member participation, in viewing Classified Style ADs, driven by our proudly developed,
  Push-Pull Credit System.
  <br /><br />
  What does this all mean?
  <br /><br />
  If the Credits (points) run out in an account, ADs associated with that account will not be displayed. This then <i>compels</i> the account
  holder, to Log in and Earn Credits, by viewing Ads, so their ADs <i>reappear</i>, for others to see!
  <br /><br />
  <b>This is a delightful way to connect Advertisers to Consumers.</b> Your ADs <u>will</u> get seen, because any member that
  becomes stagnant are temporarily removed, until they return, and view (potentially) <i>your</i> Ads!
  <br /><br />
  We ensure human beings are using the system, by using Turing Keys at Log in. We do not allow the use of automated bots or programs to
  enter the members area. We believe automated advertising is, without a doubt, a complete waste of effort.
  <br /><br />
  The Credits Earned play two roles. First, there must be at least one Credit (point) in the account which enables or makes visible the Ads
  associated with it. Second, Credits can be saved up, locked away, to then be used to place additional Ads. This is a very important feature
  of our system that acts as a reward system for participating members, as well as, <i>non</i>-participation resulting in
  the associated Ads, becoming disabled or invisible.
  <br /><br />
  Optionally, ADs can be <i>Targeted Ads</i> or placed in a broader marketing spectrum.
  <br /><br />
  For those short on time, can enjoy the option of purchasing Credits and Ads with money. To make things even more golden, a portion of that
  money, is distributed to whom ever referred them. (Known as a Downline.) This creates additional <i>insentives</i> to participate, knowing
  that if you do pay for Credits or Ads, the money is fed back into the system and to other members as a reward (commission), which creates
  an Advertising Environment that attracts more of the public to Free AD Planet and to <i>your</i> ADs!
  <br /><br />
  As a result, Free AD Planet members end up doing one or both of two activities. Earning money by referral and/or Advertising their own
  revenue generating Web Sites. Free AD Planet really is a flexible, effective and (dare we say) fun place to be! We try to make the site
  nice to look at, and the Ads as non intrusive, as possible.
  <br /><br />
  Finally, there are two modes of Advertising we allow, via Email. Emailing to your Downline or to the entire Free AD Planet membership database. Options
  to receive Email Ads can be turned on or off. But, it is beneficial to receive them for their bonuses in the form of a substantial Credit
  boost, per Email and Associated Web Site visited.
  <br /><br />
  A One-Two, knock out punch, that rewards and even becomes a <i>fun</i> way to Advertise. (Yes this is possible to achieve!)
  <br /><br />
  Free AD Planet is <i>Top Quality Advertising</i> directed at the General and Global Markets. Those seeking to expose their Products and/or
  Services, for free (as an option), <i>without</i> compromising Quality of Service or (most importantly) your Privacy.
  <br /><br />
  At no time, do we sell your Email or <i>any</i> information associated with your Free AD Planet Membership, to anyone at anytime.
  Memberships created, that wish to be removed or exit the program, can easily do so at <i>anytime</i>, without <i>any</i> preconditions.
  ';
}
else if ($c == 'contactus')
{
  $main_content = '
  Welcome, please, <a href="openticket.php">Contact Us</a>.
  ';
}
else if ($c == 'resendvalidation')
{
  $hash_check = substr(sha1(md5(strrev(sha1($affid)))), 0, 5);

  if ($hash_check == $h)
  {
    $db->Query("SELECT fname, lname, email, username, pass, verified FROM users WHERE affid='$affid'");
    list($fname, $lname, $email, $username, $pass, $verified) = $db->FetchRow();

    if ($verified != 0)
      $main_content = 'Your Account has already been verified.<br />You may now log in.';
    else
    {
      $hash = substr(md5(strrev(sha1($affid))), 0, 5);

      $val_url = "http://freeadplanet.com/?c=validatesignup&affid=$affid&h=$hash";

      @mail($email, 'Free AD Planet - Resending Validate Account Notice', "Hello $fname $lname,\n\nVisit the URL below to Validate your Account.\n\n$val_url\n\nUsername: $username\nPassword: $pass\n\nThis Validation Notice is good for 5 days.\n\nRegards,\nhttp://freeadplanet.com Staff", 'From: Free AD Planet <do_not_reply@freeadplanet.com>');

      $main_content = 'We resent the confirmation email to: <font color="blue">'.$email.'</font>.<br />You must validate your account before you can log in.';
    }
  }
  else
    $main_content = 'ERROR: Validation URL was not valid.';

  notValid($main_content);

  $show_email_confirmer = 1;
  $main_content .= '<div id="layer1" class="dnd"></div>';
  $hash = strrev(substr(md5(sha1(strrev($email))), 0, 5));
}
else if ($c == 'memberlogin')
{
  if ($submitted == 'login')
  {
    $username = trim($username);
    $pass     = trim($pass);

    if (! $db->Query("SELECT affid, verified, email, status FROM users WHERE username='$username' AND pass='$pass' LIMIT 1"))
      $notValid = 'ERROR: Username and/or Password are incorrect.';
    else if (turing_key_valid($turing_key_timeout))
    {
      list($affid, $verified, $email, $status) = $db->FetchRow();

      if ($verified == 0)
      {
        $hash = substr(sha1(md5(strrev(sha1($affid)))), 0, 5);
        $val_url = "http://freeadplanet.com/?c=resendvalidation&affid=$affid&h=$hash";

        $notValid = 'ERROR: Account is not yet verified.<br /><a href="'.$val_url.'">Click Here to resend the validation email to:</a> <font color="blue">'.$email.'</font>';
      }
      else
      {
        session_set_cookie_params(0, '/members', '.freeadplanet.com', 0, 1);
        session_start();
        session_destroy();
        session_set_cookie_params(0, '/members', '.freeadplanet.com', 0, 1);
        session_start();

        $ipaddress = $_SERVER['REMOTE_ADDR'];

/*
        // allow only 1 Free account, but unlimited Pro accounts
        // trackable via cookies, so they can in theory delete the cookie and work around this
        // email alerts me of those trying to log in and failing
        if (! @is_numeric($_COOKIE['_fap_id_']) OR ! $db->Query("SELECT status FROM users WHERE affid='{$_COOKIE['_fap_id_']}' LIMIT 1"))
        {
          setcookie('_fap_id_', $affid, time()+99999999, '/', '.freeadplanet.com', false, true);
        }
        else if ($_COOKIE['_fap_id_'] != $affid AND $status == 0)
        {
          if ($db->Query("SELECT status FROM users WHERE affid='{$_COOKIE['_fap_id_']}' AND status = '0' LIMIT 1"))
          {
            @mail('elitescripts2000@yahoo.com',
                'illegal dup login',
                "affid=$affid\nusername=$username\ncookie={$_COOKIE['_fap_id_']}\nipaddress=$ipaddress",
                $headers);
            logout_session('ERROR: Only 1 Free account is allowed.<br />However, you <i>may</i> create multiple Pro accounts.');
          }
        }
*/
        $_SESSION['affid'] = $affid;
        $_SESSION['key']   = strrev(md5(sha1(strrev($affid))));

        $ipaddress = $_SERVER['REMOTE_ADDR'];

        $db->Query("UPDATE users SET ipaddress='$ipaddress', dateloggedin=NOW() WHERE affid='$affid' LIMIT 1");

        fap_log("member login user:$username");

        header('Location: http://freeadplanet.com/members/?c=home');
        exit;
      }
    }
    else
      $notValid = 'ERROR: Invalid Turing Key.<br />You have ' . $turing_key_timeout . ' seconds before the Key Expires.';
  }

  $main_content2 = '';

  if ($submitted == 'lostpassword')
  {
    if ($notValid=EmailFormat($email, 0)) {}
    else
    {
      if (! $db->Query("SELECT affid, fname, username, pass, verified FROM users WHERE email='$email' LIMIT 1"))
        $notValid = 'ERROR: Email was not found in our Database.';
      else
      {
        list($affid, $fname, $username, $pass, $verified) = $db->FetchRow();

        $temp_pass = substr(sha1(bin2hex(openssl_random_pseudo_bytes(20))), 0, 6);

        $db->Query("UPDATE users SET pass='$temp_pass' WHERE affid='$affid' LIMIT 1");

        $subject = 'Lost Password Retrieval';
        $message = "Hello {$fname},

Your login information is below:

Username: {$username}
Password: {$temp_pass}

We created a random temporary password, shown above.
Once you login, you can change your password back to
one that is more familiar to you.

Thank You,
http://freeadplanet.com Staff
";
        @mail($email, $subject, $message, $headers);
        //@mail('elitescripts2000@yahoo.com', $subject, $message, $headers);

        unset($fname, $lname, $username, $pass, $verified, $subject, $message);

        $notValid = 'We mailed the requested information to: '.$email;

        $show_email_confirmer = 1;
        $main_content2 = '<div id="layer1" class="dnd"></div>';
        $hash = strrev(substr(md5(sha1(strrev($email))), 0, 5));
      }
    }
  }

  notValid($notValid);

  list($v, $keyfilename) = turing_key_create();

  $main_content = '
  <form name="login" action="?c=memberlogin" onsubmit="javascript:submitOnce();" method="POST">

  <table align="center" border="0" cellpadding="2" cellspacing="0">

    <tr>
      <td align="center" colspan="3">
        <font size="+1">Member Log In</font>
        <br /><br />
       '.$notValid.'
      </td>
    </tr>

    <tr>
      <td align="right"><b>Username:</b></td>
      <td colspan="2"><input type="text" name="username" value="'.$username.'" size="20" maxlength="20" /></td>
    </tr>

    <tr>
      <td align="right"><b>Password:</b></td>
      <td colspan="2"><input type="password" name="pass" value="" size="20" maxlength="20" /></td>
    </tr>

    <tr>
      <td align="right" valign="center" nowrap><b>Turing Key:</b></td>
      <td width="10"><img src="http://freeadplanet.com/keys/'.$keyfilename.'" border="0" /></td>
      <td align="left"><input type="text" name="tkey" size="3" maxlength="3" /></td>
    </tr>

    <tr>
      <td colspan="3" align="center">
        <hr />
        <input id="submit" type="submit" value="Log In" />
      </td>
    </tr>

  </table>

  <input type="hidden" name="v" value="'.$v.'">
  <input type="hidden" name="submitted" value="login" />
  </form>

  <br /><br />

  <form name="lostpassword" action="?c=memberlogin" onsubmit="javascript:submitOnce();" method="POST">

  <table align="center" border="0" cellpadding="2" cellspacing="0">

    <tr>
      <td align="center" colspan="3">
        <h2>Lost Your Password?</h2>
        <b>Email Address:</b>
        <br /><br />
        <input type="text" name="email" size="30" />
        <br /><br />
        <input id="submit" type="submit" value="Request Password" />
      </td>
    </tr>

  </table>

  <input type="hidden" name="submitted" value="lostpassword" />
  </form>
  '.$main_content2;
}
else if ($c == 'dah') // distributed ad horizontal
{
  $affid = trim($_GET['affid']);

  if (@is_numeric($affid))
  {
    $db->Query("SELECT categories FROM users WHERE affid='$affid' LIMIT 1");
    list($user_categories) = $db->FetchRow();
    if ($user_categories) $user_categories = explode(',', $user_categories);
  }
  else
    $user_categories = '';

  $ta = get_targeted_ads('all', $user_categories, $db, '');
  $sl = get_ads('', 'spotlight', 2, $db, '');

  $show_ads_by = '';
  if (! $no)
  {
    $show_ads_by = '
    <tr>
      <td colspan="4" width="100%" align="right" valign="top">
        <font face="Verdana" color="black" size="2">
          <a href="http://freeadplanet.com/?affid='.$affid.'" target="_blank">
            <b>ADs by Free AD Planet - Join Free!</b>
          </a>
        </font>
      </td>
    </tr>
    ';
  }

  exit('
  <table align="center" cellpadding="0" cellspacing="0" width="800" bgcolor="white" border="0">
    <tr>
      <td width="25%" valign="top">
        '.display_ad('targeted', $ta, '', '', 0).'
      </td>

      <td width="25%" valign="top">
        '.display_ad('targeted', $ta, '', '', 1).'
      </td>

      <td width="25%" valign="top">
        '.display_ad('spotlight', $sl, '', '', 0).'
      </td>

      <td width="25%" valign="top">
        '.display_ad('spotlight', $sl, '', '', 1).'
      </td>
    </tr>
    '.$show_ads_by.'
  </table>
');

}
else if ($c == 'remove')
{
  $affid = trim($_GET['a']);
  $hash  = trim($_GET['h']);
  $yes   = trim($_GET['y']);

  if (@is_numeric($affid)) {
    if (! $db->Query("SELECT username, fname, lname, email FROM users WHERE affid='$affid' LIMIT 1"))
      die('This account has already been removed. Or does not exist.');
  } else {
    die('This account has already been removed. Or does not exist.');
  }

  list($username, $fname, $lname, $email) = $db->FetchRow();

  $hash_check = substr(sha1($affid.'sjdhf3938483jhdsjh'), 0, 5); // do not change tied to fap/tap
  $yes_check  = substr(sha1($affid.'sjdhf3938483jhdsjh'.$hash), 0, 5);

  if (! $yes)
  {
    die('<div style="margin:10px auto;width:470px;"><img src="/images/banner2.jpg" border="0">
        <hr />Dear ' .
        $fname . ', <br /><br />You are about to <b>delete</b> your <a href="http://freeadplanet.com">Free Ad Planet</a> account!
        <br />
        All your credits, Ads and ability to log in will be gone.
        <br /><br />
        Your account Username is <b>' . $username . '</b>
        <br /><br />
        <a href="?c=remove&a=' . $affid . '&h=' . $hash . '&y=' . $yes_check . '">Click Here</a> to confirm the termination of Your Account.
        </div>');
  }

  if ($hash_check === $hash AND $yes_check === $yes)
  {
    delete_user($affid, $db);
    @mail($email, 'Free AD Planet - Account Deleted', "Hello $fname,\n\nYour Account has been Deleted.\n\nUsername: $username\n\nThank you for using our program,\nhttp://freeadplanet.com Staff", $headers);
    header("Location: ?c=memberexit&why=" . urlencode('Your Account has been Deleted.'));
    exit;
  }
  else
    die('Error: Make sure your remove link was pasted to your browser completely intact. Sometimes mail splits up URLs due to word wrapping, etc');
}
else if ($c == 'processorder')
{
  if (TEST_MODE) @mail('elitescripts2000@yahoo.com', "t=$t POST GET", print_r($_POST, 1).print_r($_GET, 1));

   $cbreceipt = $_REQUEST['cbreceipt'];
   $id        = $_REQUEST['vtid'];
   $t         = $_REQUEST['t'];

  if ($cbreceipt) // clickbank
  {
    if (! TEST_MODE AND substr($cbreceipt, 0, 4) == 'TEST')
    {
      $notValid = 'ERROR: Not in TEST_MODE yet TEST reciept was provided.';
      @mail("elitescripts2000@yahoo.com", "Free AD Planet - cbValid() FAILED", "Not in TEST_MODE yet got a TEST cbreceipt\n\nid=$id cbpop=$cbpop cbreceipt=$cbreceipt item=$item time=$time t=$type", $headers);
    }
    else if (! cbValid() AND $t == '')
    {
      $notValid = 'ERROR: Unable to validate this ClickBank transaction.';
      //@mail("elitescripts2000@yahoo.com", "Free AD Planet - cbValid() FAILED", "id=$id cbpop=$cbpop cbreceipt=$cbreceipt item=$item time=$time t=$type", $headers);
    }
    else
    {
      list($amount) = get_type_cost($t);

      $notValid = process_order(new MySQL_Access('fap'), $id, $t, 'clickbank', $cbreceipt, $headers, $amount);
    }
  }
  else if ($_POST['merchant_order_id']) // 2checkout
  {
    $merchant_order_id     = $_POST['merchant_order_id'];
    $order_number          = $_POST['order_number'];
    $credit_card_processed = $_POST['credit_card_processed'];
    $email                 = $_POST['email'];
    $key                   = $_POST['key'];
    $total                 = $_POST['total'];

    $cgikey     = 'ntws40ntws40';
    $merchantID = '25344';

    // uncomment when demo=Y
    if (TEST_MODE)
    {
      $order_number = 1;
      @mail('elitescripts2000@yahoo.com', '2co POST', print_r($_POST, 1));
    }

    // Y=creditcard OK, K=check but 2-3 days to clear
    if ($credit_card_processed != 'Y' AND $credit_card_processed != 'K')
      $notValid = 'ERROR: twocheckout: Credit card not processed. credit_card_processed='.$credit_card_processed;
    else
    {
      $uniquekey = strtoupper(md5($cgikey.$merchantID.$order_number.$total));

      if (TEST_MODE) $order_number = 'TEST'.$uniquekey;

      // make sure key is valid
      if (strcmp($key, $uniquekey) != 0)
      {
        @mail("elitescripts2000@yahoo.com", "Free AD Planet 2checkout Hash keys do not match", "uniquekey=$uniquekey key=$key t=$t", $headers);
        $notValid = 'ERROR: Unable to validated this 2checkout transaction.';
      }
      else
        $notValid = process_order(new MySQL_Access('fap'), $merchant_order_id, $t, 'twocheckout', $order_number, $headers, $total);
    }
  }
  else if ($_POST['ap_securitycode']) // payza
  {
    $ap_custfirstname    = $_POST['ap_custfirstname'];
    $ap_custlastname     = $_POST['ap_custlastname'];
    $ap_custemailaddress = $_POST['ap_custemailaddress'];
    $ap_itemname         = $_POST['ap_itemname'];
    $ap_quantity         = $_POST['ap_quantity'];
    $ap_amount           = $_POST['ap_amount'];
    $ap_totalamount      = $_POST['ap_totalamount'];
    $ap_referencenumber  = $_POST['ap_referencenumber'];
    $ap_status           = $_POST['ap_status'];
    $apc_1               = $_POST['apc_1'];
    $apc_2               = $_POST['apc_2'];
    $ap_securitycode     = $_POST['ap_securitycode'];

    $id = $apc_1;
    $t  = $apc_2;

    if (TEST_MODE)
    {
      $ap_referencenumber = 'TEST'.rand();
      @mail('elitescripts2000@yahoo.com', 'payza POST', print_r($_POST, 1));
   }

    // comment out if not testing
    if ($_POST['ap_test'] AND ! TEST_MODE)
    {
      $notValid = 'ERROR: AlertPay transaction must not be in Test Mode.';
      @mail("elitescripts2000@yahoo.com", "Free AD Planet - Payza in Test mode", "It should not be in Test Mode. t=$t", $headers);
    }
    else if ('lk7f53bPo/6P7oF5QgR6wQ' == $ap_securitycode)
      $notValid = process_order(new MySQL_Access('fap'), $id, $t, 'payza', $ap_referencenumber, $headers, $ap_totalamount);
    else
    {
      $notValid = 'ERROR: Unable to validate Payza transaction.';
      @mail("elitescripts2000@yahoo.com", "Free AD Planet - Payza Hash keys do not match", "ap_securitycode=$ap_securitycode t=$t", $headers);
    }
  }
  else if ($_GET['fap_alertpay_thankyou'] OR $_GET['V2_HASH'] OR $_GET['merchant_order_id'])
    $notValid = 'Your Order should have been Processed.';
  else
    $notValid = 'ERROR: There may have been an error with the Order.<br />Check your account. Open Service Ticket if not found.';

  header('Location: http://freeadplanet.com/members/?c=buyads&notValid='.urlencode($notValid));
  exit;
}

$bb = get_ads('', 'billboard', 5, $db, '');
$sl = get_ads('', 'spotlight', 5, $db, '');

?>