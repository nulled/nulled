<?php

require_once('/home/nulled/config.inc');

class SoloADers extends MySQL_Access
{
  public $emails;
  public $message;
  public $headers;

  function __construct()
  {
    parent::__construct('mle');

    $this->emails  = array();
    $this->headers = "From: PXM Admin <admin.email@planetxmail.com>\nReply-To: admin.email@planetxmail.com";
    $this->message = 'Hello [name],

Remember us?  You ordered a Solo Ad from us and wanted to touch bases with you!
This is a one time mailing, containing important information since last you tried
planetxmail.com which you will find enlightening and a few warnings about how bad
things are getting in the Email Marketing World, and how we are countering those
trends with positive ones.

We noticed that other Mailing Services out there, that call themselves Viral Mailers
are not honoring the Unsubscribe Links and are therefore spammers.  I have put a
warning up, and got the attention of many of the owners! :)

Besides the bad news there.  Here is some Good News that we are doing for You.

1) Everytime someone Mails using our Mailers, will now see Your Solo AD Website!

2) Everytime someone uses the Link Exchange will Auto List Your Website at the Top
   of the Exchange and in addition your Website is shown to them after submiting
   their own link on the Exchange.

3) I have made numerious additions, like allowing people to upgrade from Free to
   Pro just by Earning Credits.  This means more people are clicking on Earn.php
   Solo AD Credit links and thus seeing your Website everytime!

It is a known fact, that it takes at least 7 views for the average person to finally
stop and have a real look.  So, the more views, even if they do not get you a Sale,
add to that magic number 7, or where there abouts.

Better Bounce messages for the Account Holders, so they can see the message for
themselves and decide to take whatever action they think is right in order to keep
Mailing out for free, using the Regular and Credit Mailers. Remember, the more they
use the Free Mailers, the more they see Your Website, based on which Credit URL you
enter in along with your Solo Ad Email.  The Credit URL is Very Important.

There are many other small things on the drawing board for planetxmail.com but I will
not bore you about them at this time.

if you are noticing new traffic coming in from referal locations like getad.php and
links.php, Now You Know Why.  I will be looking into new ways to get you more Views as
I think them up.

Finally, all Mailers are now HTML enabled.  You do not need to even know a lick of
HTML to create colorful, image rich new ADs, as the Editor is all Click-Drag and
Drop. However, good old Plain Text Ads still work, as long as you keep them short
and to the point. One Paragraph and using only the Credit URL to keep your Ad as
Clean and to the Point.

Here are some tips Not to do when submitting Any Advert to Any Mailer.

1) Never use All Upper case.  Instead use Camel Case. (HELLO THERE = Hello There)

2) Do not use a lot of puncuation like ON SALE!!! Or Did YOU KNOW????
   Instead use Camel Case and just one puncution.  On Sale!

3) Avoid terms like Get Rich Fast or Join Our Membership Affiliate Tier. Even try
   to reframe from using words like commissions or anything that is commonly used
   in Real Spam.

4) Do not use URL Shorteners like tinyurl.com or any of them.  They interfer with
   the way we display your Website as people Earn Credits.  It is best to post the
   direct URL as the Credit URL.  Does not matter how long it is, makes no diff-
   erence. And if you are using URL Shorteners to mask your domain when falsely
   being accused of spam, remember that the Credit URL will mask it for you in
   the Solo AD Emails.  Example: http://planetxmail.com/earn.php?c=JDHDHJDSDHF
   If you are using it to count the number of clicks, it is just as easy to place
   a free and simple counter script on your splash page.  In the future, we may
   just add the feature of how many clicks earn.php (Credit URL) is getting.
   Stay tuned for that, as I just though of it.

Regarding Mail Services like Yahoo and Gmail and Hotmail Selectively Filtering.
Selective Filtering, means instead of Black Listing the Entire Domains, just
Black List individual Emails.

The best thing you can do is search the Internet for Spam examples, and avoid any
pattern words and punctuations spam uses. Just use plain talk as if talking to a
friend, with minimal All Caps (no caps is best and again Camel Case as an Alter-
native) and you should be fine in regards to Selective Filtering.

Planetxmail.com is way ahead of the curve when it comes to any SafeList hosting I
have observed. Most of them have all gotten banned, except from Gmail.com, but
gmail.com will let anything go through, as they monitor all mail as we know know
from the news about Govt Spy programs.  This takes hard work and due dilegence.
They will Black List your Mail Server, even though you employ Double Optin and
Honor your Unsubscribe URLs. We at Planet X Mail are not trying to encourage
ways around Spam, but rather trying to ensure Marketing Emails that are in com-
plyance with CAN-SPAM 2005 Laws to better service and inform people like you and I.

Just a heads up with the improvements to the Solo AD click rates.  Please contact
me at anytime.  We Are Here To Help You Succeed.

admin.email@planetxmail.com
or
elitescripts2000@yahoo.com

Thank You,
Matt - Customer Service
http://planetxmail.com/soloads.php
';
  }

  private function GetEmails()
  {
    $i = 0;

    $this->emails = array();
    $emails       = array();
    $names        = array();

    if ($this->Query("SELECT email, name FROM soloads WHERE receipt != '' ORDER BY email"))
    {
      while (list($email, $name) = $this->FetchRow())
      {
        $email = strtolower(trim($email));
        $_name = strtolower(trim($name));

        if (in_array($email, $emails))
          continue;
        $emails[] = $email;

        if (in_array($_name, $names))
          continue;
        $names[] = $_name;

        $this->emails[$i]['email'] = $email;
        $this->emails[$i]['name']  = trim($name);
        $i++;
      }
    }
  }

  public function MailOut($test = false)
  {
    $range = range(1,3);

    $this->GetEmails();

    if (! $this->emails)
    {
      echo "No emails found that needed to be mailed.\n";
      return 1;
    }

    foreach ($this->emails as $i => $e)
    {
      $email = $e['email'];
      $name  = $e['name'];

      if ($test)
        $email = 'admin.email@planetxmail.com';

      $message = str_replace('[name]', $name, $this->message);

      shuffle($range);
      sleep($range[0]);

      if (mail($email, 'Good Evening, '.$name, $message, $this->headers))
        echo "$i - sleep({$range[0]}) - $email\n";
      else
        echo "$i - sleep({$range[0]}) - Bad: $email\n";
    }
  }
};

$sa = new SoloADers();
//$sa->MailOut();


?>
