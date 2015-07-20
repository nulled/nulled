<?php
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
    <head>
        <META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html; charset=UTF-8">
        <title>Free AD Planet's Community - Ad View Quota Guide</title>
        <style>
            body {
                font-family: verdana, arial, helvetica, sans-serif;
                font-size: 14px;
                color: black;
            }

            a {
                color: blue;
                text-decoration: none
            }

            a:hover {
                color: red;
                text-decoration: underline;
            }

            .main {
                text-align: left;
                border: 1px solid black;
                width: 85%;
                padding: 10px;
                margin: 5px auto;
                margin-top: 0px;
                margin-bottom: 50px;
                color: black;
            }

            .title {
                color: green;
                font-size: 16px;
                font-weight: bold;
            }
        </style>
    </head>
    <body>
        <div class="main">
            <center>
                <h2>Free AD Planet's Community - Ad View Quota Guide</h2>
            </center>
            <hr/><b>Why</b> use an Ad View Quota system? Simple! To ensure community participation.
            <br/>
            <br/>
            The <i>more participation</i>
            there is, the more Web Traffic, Page Views, and Click Through Rates, Free AD Planet will generate,
            on your Web Sites!<u>Bottom line!</u>
            <br/>
            <br/>
            We <i>highly encourage</i>, each Free AD Planet Community Member, to view the recommended number of ADs per Day and per Week.
            This ensures that Members do not become stagnant.  More importantly, <i>ensures</i> that
            <u>your</u> ADs (as well as others) are getting viewed.
            <br/>
            <br/>
            There are
            <font color="green">
                <b>Bonuses</b>
            </font>
            for Members that decide to meet the Minimum Recommendations.
            <br/>
            And, there are even <i>more</i>
            <font color="green">
                <b>Bonuses</b>
            </font>
            for Members that decide to <i>Exceed</i>
            the Minimum Recommendations!
            <br/>
            <br/>
            <b><i>Free</i> Community Members</b>
            <ul>
                <li>
                    Please, View <?php echo $quotaDailyRequirement[0]; ?> ADs per Day. <i>At 15 seconds per AD, that is a mere, <b>ONE minute</b> of your time!</i>
                </li>
                <li>
                    For a total of <?php echo $quotaRequirement[0]; ?> ADs spread across the Week.
                </li>
            </ul>
            <b><i>Professional</i> Community Members</b>
            <ul>
                <li>
                    Kindly, View <?php echo $quotaDailyRequirement[1]; ?> ADs per Day.
                </li>
                <li>
                    For a total of <?php echo $quotaRequirement[1]; ?> ADs spread across the Week.
                </li>
            </ul>
            <b>Penalty for not participating in the minimum Quota Recommendation. (<i>All</i> Community Members)</b>
            <ul>
                <li>
                    <?php echo $creds_deducted_daily; ?> credits per day will be deducted from your Open Credits.
                    <b>Locked Credits will never be deducted, for any reason.</b>
                </li>
                <li>
                    If you do not meet Quota for the week, it will carry over into the <i>next</i>
                    Quota Week. Up to 4 Weeks may Carry Over, but no more than 4. We placed a 4 Week cap, so members that were
                    absent from Free Ad Planet, can reasonably catch back up, even if that member was absent for 6 months or more.
                </li>
                <li>
                    If you have unmet past Weekly Quota(s) the 'grace period days' (Mon, Tue, Wed) will not apply and you will be deducted
                    <?php echo $creds_deducted_daily; ?> Open Credits, per those days.
                </li>
            </ul>
            <b>If your Open Credits reach 0 (zero), some or all of your ADs, will become invisible.</b>
            <br/>
            <br/>
            Therefore, not seen by other members!
            The exception are Purchased ADs, which expire 30 days from purchase date. Pro Members receive, Red Bordered ADs, which will stay visible
            when Open Credits reach 0 (zero). However, those are the only exceptions, and all other ADs, will be invisible, as if never created, until
            the account holder either A) Transfers some saved Locked Credits or B) Earns Credits, by viewing some ADs.
            <br/>
            <br/>
            <font color="green">
                <b>Credit Bonuses (<i>All</i> Members)</b>
            </font>
            <ul>
                <li>
                    You will earn <?php echo $creds_earn_missed_week; ?> Credits as a Bonus each time you meet Weekly Recommended Quota.
                    <i>Including Quota Weeks you make up for, that you may have missed!</i>
                </li>
                <li>
                    You will earn <u>Double</u>
                    the normal Credits, per AD View, as a Bonus, after your Total Recommended Quota is met!
                </li>
                <li>
                    Clicking on the Credit URLs found in <b>Email sent from your Sponsor</b>, will earn you <?php echo $creds_earn_regmail; ?>
                    <i>times</i> the amount normally earned.
                </li>
                <li>
                    Clicking on the Credit URLs found in <b>SOLO ADs</b>, will earn you <?php echo $creds_earn_soload; ?>
                    <i>times</i> the amount normally earned!
                 </li>
                 <li>
                    Each Free Member that refers a new member, earns a <?php echo $ref_credits_earned_free; ?> Credit Bonus!
                 </li>
                 <li>
                    Each Pro Member that refers a new member, earns a <?php echo $ref_credits_earned_pro; ?> Credit Bonus!
                 </li>
            </ul>
            <b><i>All</i> Community Members</b>
            <ul>
                <li>
                    <b>Monday</b>
                    marks the start of a New Quota Week. Which means, if you reached the point where you were Doubling your Credits, will
                    reset as the new week begins.
                </li>
                <li>
                    <b>Monday</b>, <b>Tuesday</b>
                    and <b>Wednesday</b>
                    are 'grace period days'. No penalties occur, <i>as long as, you have no unmet past Weekly Quota(s).</i>
                </li>
            </ul>
            <font color="blue">
              <b>There are <i>two</i> reasons for Earning Credits.</b> <i>Firstly</i>, to keep your Open Credits above 0, so that all your ADs remain
              visible
              to members. <i>Secondly</i>, is the option to <i>save up your Credits</i>, by transfering them to your Locked Credits vault. Locked
              Credits are never deducted for any reason, even if your Open Credits run out. That way, you can save up for additional
              placement of Ads, using the Buy Ads section, and using Credits to obtain more Ads.
              <br /><br />
              Note also, that <b>we use Turing Keys at the Log in to the members area</b>. This is to ensure, no automated bots or programs
              are used. We believe Automated Advertising, such as auto-submitters, of any kind, <i>to be a complete waste of effort</i>. Imagine
              a system, where everyone was simply schedualing a program or bot, to do all the clicking
              and posting, that a Human Being should be doing? Automated advertising, leads to nothing more, than a bunch of
              computers talking to each other, <b>with not a single Human Being, viewing any of the Ads!</b>
              <br /><br />
              If, you think you are on to something,
              that no one else knows about, by using Automated Advertising (auto-submitters of any kind), you are dead wrong.
              (Just, being honest here!) Just about everyone knows
              about the same Automation Programs, you know about and are using. Especially, if that Automation Site is popular, with lots of
              paying members. Therefore, no one is actually there, at the computer, viewing any ADs.
              <br /><br />
              We <i>highly
              recommend</i>, you stay far away, from any Advertising sites, that lack Turing Key checks. Sites without them, are wide open to Automation
              Bots, which will quickly render that Web Site ineffective at getting your ADs viewed. Turing Keys, ensure a Human Being is at the
              computer and not a bot or program. Trust us, when we mean Automated Advertising, does not work. If it did, we would simply create
              a few Automation Tools of our own! We do not bother, because in our experience, it is a complete waste of time.
              <br /><br />
              The following is a special and somewhat hidden little trick, that you can use, to earn the largest credit bonuses possible! We figured,
              that if you are still reading, at this point, you deserve a little secret treat! The trick is to keep your Free Ad Planet Email Ads
              (which contain Earnable Credit URLs) and do not click the Earn URLs, just yet! If, you remember previously,
              about how much Solo Email ADs and Downline Email Ads earn, <?php echo $creds_earn_soload; ?>x and <?php echo $creds_earn_regmail; ?>x,
              times the normal amount, respectively. <i>And</i>, that you Earn <?php echo $creds_earn_missed_week; ?> Credits,
              which is the largest Bonus possible, when
              you reach a Weekly Quota, including any Carry Over or past unmet Weekly Quotas. The trick is to use your saved Email Ad
              Credit URLs and click them, exactly at the moment, you would earn the Weekly Quota Bonus! Since, Email Ads earn you credits, based on a
              multiplier, and not a fixed amount, you can maximize your return, by combining the two! Thank you for taking the time to read this
              Ad View Quota rules page. Please continue to the end, for more valuable information.
              <br /><br />
              By following our simple Quota system, much like a daily workout routine, the
              better the chances of your ADs receiving loads of traffic. (Actual, Human Traffic.) People must participate, by Earning Credits, for an
              Ad sharing Network to become effective. So, if you decide to simply, Earn Credits, to keep a positive Open Credit balance,
              is a good base line to start with. It ensures that your ADs are visible. So, this base line is really the bare minimum level of
              participation we require, which will lead to decent Traffic flow to your Web Sites.
              <br /><br />
              However, <b>those that do more than the minimum</b>, are not only rewarded with bonuses at every step of the way, but also
              are able to place <i>additional ADs</i>, without having to spend money. Buying ADs, via Earned Credits, allows you to Internet Market
              <i>effectively</i> without spending a dime. If, only a third, of our members, follow this level of participation, Free AD Planet
              will become <i>extraordinarily effective</i> at getting your ADs, in front of interested eyes. In other words, loads of incoming Web
              Traffic into your Web sites.
              <br /><br />
              <i>Those that are short on time</i>, can purchase Credits and ADs with money. <b>The great thing about Free AD Planet</b>, is
              that a portion of that money, is <i>fed back into the system</i>, by paying a commission to whom ever referred you. This creates
              more <i>insentive for more people to participate</i>, by viewing ADs (potentially your ADs), because that money spent, is reinvested, back
              into the Free AD Planet system. Thereby, rewarding people and creating much insentive to continue to participate. The more participation,
              the more Traffic that flows to (potentially) your ADs.
            </font>
            <br/>
            <br/>
            <b>Your Member Profile will tell you the current status of your AD View Quota.</b>
            You are also advised to activate Email Alerts.
            You are given a friendly Email reminder when you need to start viewing ADs or when your Open Credits reach 0 (zero).
            <br/>
            <br/>
            Note, that Free AD Planet (freeadplanet.com) is a completely seperate system and web site in regards to our sister site, Planet X Mail
            (planetxmail.com). The only connection, between the two sites, is that we created them. We also allow all Professional Level Free AD
            Planet Members, the ability to transfer credits from any Planet X Mail account, they may hold.
            <br/>
            <br/>
            <a href="http://freeadplanet.com/openticket.php" target="_blank">Open a Service Ticket</a>
            and we will happily reply within
            1-3 days (Including Weekends).
        </div>
    </body>
</html>
