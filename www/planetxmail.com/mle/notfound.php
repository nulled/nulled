<?php
require_once('/home/nulled/config.inc');
?>
<!DOCTYPE html>
<head>
<meta charset="UTF=8" />
<title>Not Found</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body>
<?php flush(); ?>
<table align="center" width="500">
  <tr>
    <td>
      <center><img src="images/pxm_title.jpg"></center>
      <?php echo str_replace('[location]','notfound', $ads_ads_ads); ?>
      <hr>
      <h3>Your User Name / List Address was not found in our databases.</h3>
      </center>
      Below are the possible reasons why:
      <ol>
        <li>You are <b>already removed</b>. ( Either List Address or ENTIRE account ).</li>
        <li>You are signed to more than one list.  <a href="requestremovelinks.php" target="_BLANK">Click Here</a> to Use our MASTER REMOVAL ALL tool.</li>
        <li>Or, you pasted the <b>remove URL / LINK incorrectly</b>.</li>
        <li>Or, this is a <b>fake remove link</b> therefore the email did <b>NOT originate from our servers</b>.  ( Read below, please. )</li>
      </ol>
      Typically, the reason is #1, #2 or #3.  If you have <b>verified #1, #2 and #3 to not be the case</b> then <i>please read the information below:</i>
      <br><br>
      We hold a <b>SCRICT NO SPAM POLICY</b>.  And all remove links are mandatorily placed and are working on ALL out going mail from our servers.
      <br><br>
      <a href="spam_nfo/index.htm"><b>Click Here - How to track where the SPAM came from.</b></a>
      <br><br>
      <font size="+1" color="red">Important!</font>
      <br><br>
      <font size="3" color="red">If you think others are using <b>fake</b> remove links to our domain... <b>we need to know about this.</b></font>
      <br><br>
      In order to be sure that the email came from <b>our servers</b> you need to view the <b>EMAIL HEADERS</b>.
      They contain information on <b>all mail servers</b> as it travels <b><i>From</i></b> them <b><i>To</i></b> you.
      <br><br>
      To view email headers in OutLook do the following:
      <ul>
      <li>Right Click the Subject of the email.</li>
      <li>Goto Properties</li>
      </ul>
      The information shown is the path that the email took to get to your mail box.
      <br><br>
      <a href="spam_nfo/index.htm"><b>Click Here - How to track where the SPAM came from.</b></a>
      <br><br>
      Please email the <b>Email HEADER</b> information to: <a href="../openticket.php">Open a Ticket</a>
      <br><br>
      Along with the SPAM email.
      <br><br>
      But, emailing me will not stop the SPAM.  You really need to report the spam to Agencies that will take them down. <font size="+1">Please mention that the
      <b>remove link is a FAKE</b> and I am <u>not</u> responsible.</font>  If SPAMMERS enjoy sending their SPAM mail <b><i>DIRECTLY</i></b> to this handy
      <b>Headers LOOK UP guide</b> then more power to them. :)
      <h3>We DO NOT TOLERATE SPAM.</h3>
      Thanks,<br>
      <img src="../images/signature.jpg" border="0" />
    </td>
  </tr>
  <tr>
    <td>
      <hr>
      <H3>Deciphering Email Headers </H3><B>Why look at email headers?</B><BR>If you
  want to write to the domain administrators where the spam originated, you need
  to understand email headers. You cannot just 'Reply' to the message to give
  the spammer a piece of your mind, because it is very easy to fake an email
  address. <B>Searching through headers</B><BR>Here is a sample email header
  (colors added). The final receiver's address is 'you@your.domain.com'.
  <BLOCKQUOTE><font-family="Times New Roman"><FONT
    color="#800000"><B>Received:</B></FONT> (2228 bytes) by
    <B>&lt;</B>your.domain.com<B>&gt;</B> via sendmail with
    P:stdio/D:user/T:local <B><FONT color="#800080">(sender:
    &lt;29086328@compuserve.com&gt;)</FONT><FONT color=#ff8000> </FONT></B><FONT
    color="#000000">id m0xUFxr-001cL6C@your.domain.dom for
    <EM>you@your.domain.com</EM>; Sat, 8 Nov 1997 10:50:35 -0800 (PST)</FONT>
    (Smail-3.2.0.98 1997-Oct-16 #12 built 1997-Oct-28) <FONT
    color=#ff0080><B>Received</B><B>: from</B></FONT> simon.pacific.net.sg
    (<FONT color="#0000ff>"<B>simon.pacific.net.sg [203.120.90.72]</B></FONT>) by
    your.domain.com (8.8.7/8.7.3) with ESMTP id KAA01565; Sat, 8 Nov 1997
    10:43:34 -0800 (PST)</FONT><FONT face="Times New Roman" color="#996633">
    </FONT><font-family="Times New Roman"><FONT color="#800080"><B>From:
    29086328@compuserve.com </B></FONT><FONT color="#ff0080"><B>Received:
    from</B></FONT> pop1.pacific.net.sg (<font
    color="#0000ff"><B>pop1.pacific.net.sg [203.120.90.85]</B></FONT>) by
    simon.pacific.net.sg with ESMTP id CAA25373; Sun, 9 Nov 1997 02:44:51 +0800
    (SGT) <FONT color="#ff0080"><B>Received</B><B>: from</B></FONT>
    po.pacific.net.sg (<FONT color="#0000ff"><B>hd58-032.hil.compuserve.com
    [199.174.238.32]</B></FONT>) by pop1.pacific.net.sg with SMTP id CAA12179;
    Sun, 9 Nov 1997 02:43:10 +0800 (SGT) <FONT color="#ff0080"><B>Received:
    from</B></FONT> <FONT color="#000000">mail.compuserve.com (</FONT><B><FONT
    color="#0000ff">mail.compuserve.com (205.5.81.86)</FONT></B><FONT
    color="#000000">) by compuserve.com (8.8.5/8.6.5)</FONT> with SMTP id GAA04211
    for &lt;87789123456@aol.com&gt;</FONT> </BLOCKQUOTE>It may look confusing, but
  there are some patterns that tell you everything you need to know. The header
  can be broken into several sections, each beginning with the word "Received".
  <p>The first <b><font color="#800000">Received</FONT>'</B> is from your email
  server. This section lists the <b></b><font color="#800080">supposed sender,
  </font></b><font color="#000000">the message ID number, and when the message
  came in</font>. The other <b>'<font color="#ff0080">Received: from</font>'</b>
  tags are from remailers that the spammer used to make it more difficult to
  track him/her down.
  <OL>
    <li>Find the last '<font color="#ff0080"><b>Received: from</b></font>' entry
    in the header. This usually shows the originating server.
    <LI>Find and write down the <font color="#0000ff"><b>server domain and its IP
    address</b</font>. This information appears in parenthesis in each '
    <font color="#ff0080"><b>Received: from</b></font>' entry. </li></ol>
  <DIV align=center>
  <TABLE style="border: 1px solid #0000ff;" cellSpacing="3" cellPadding="3" width="330">
    <TBODY>
    <TR>
      <TD align=middle width="197"><B>Machine Name </B>
      <TD align=middle width="113"><B>IP Address </B>
    <TR>
      <TD align=middle width="197">mail.compuserve.com
      <TD align=middle width="113">205.5.81.86
    <TR>
      <TD align=middle width="197"><FONT
        color="#000000">hd58-032.</FONT>hil.compuserve.com
      <TD align=middle width="113">199.174.238.32
    <TR>
      <TD align=middle width="197">popl.pacific.net.sg
      <TD align=middle width="113">203.120.90.85
    <TR>
      <TD align=middle width="197">simon.pacific.net.sg
      <TD align=middle width="113">203.120.90.72
    </TR></TBODY></TABLE></DIV>
    <br><br>
      <center><a href="spam_nfo/index.htm"><b>Click Here - How to track where the SPAM came from.</b></a></center>
    </tr>
  </td>
</table>
</body>
</html>