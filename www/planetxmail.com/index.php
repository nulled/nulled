<?php
if (strstr(strtolower($_SERVER['HTTP_REFERER']), 'ihaveliftoff.com')) die();

require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

if (! $option OR strstr($option, "/") OR $option == 'classes' OR
    ! file_exists("$option.php") OR
    ! file_exists("phpsecure/$option.inc")) $option = 'homecontent';

require_once("/home/nulled/www/planetxmail.com/phpsecure/$option.inc");

$date = date("F j, Y");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>SafeList Advertising</title>
<meta name="description" content="Free and Paid Credit Based Safelists using Double OPTIN SPAM FREE Email Advertising.">
<meta name="keywords" content="safelists, free safelists, paid safelists, email safelists, free join safelists, opt in safelists, web site promotion, web promotion, site promotion, internet promotion, online promotion, web site traffic, increase traffic, web traffic, increase web traffic, targeted traffic, advertising, internet advertising, online advertising, web site advertising, ads, selling, selling online, wealth, home business, internet business, work at home, internet marketing, starting a business online, home business promotion, home-based opportunities, small business, making money, working at home, business making money, mlm, business ideas, free stuff, home employment, internet opportunities, multi-level marketing, money making methods, opportunities, home office, independent business, advertising, promotion, internet, business, MLM, networking, mlm, multi-level, network marketing, money, sales, business, home work opportunities">
<meta name="revisit-after" content="30 days">
<meta name="robots" content="all">
<style>
body {
  margin: 25px 0 50px 0;
  background-color: #FFFFFF;
  font-family: verdana, tahoma, arial, helvetica, sans-serif;
}
table {
  color: #2a2a2a;
  font-size: 12px;
  font-family: verdana, tahoma, arial, helvetica, sans-serif;
}
b.red {
  color: red;
}
b.redlarge {
  font-size: 17px; color: red;
}
td.tdbgcolor1 {
  background-color: #F5F5F5;
}
td.tdbgcolor2 {
  background-color: #FBFDFD;
}
.submitblack {
  font-size: 12px;
  background: #666666;
  color: white;
  cursor: hand;
}
select.blue {
  font-size: 12px;
  color:#000066;
  background-color:#D6E7EF;
}
input.redbutton {
  font-size: 12px;
  background-color: #FA7C7C;
  color: #000000;
  border-style:solid;
  cursor: hand;
}
input.greenbutton {
  font-size: 12px;
  background-color: #99CC99;
  color: #000000;
  border-style: solid;
  cursor: hand;
}
input.beigebutton {
  font-size: 12px;
  background-color: #FFFFCC;
  color: #000000;
  border-style:solid;
  cursor: hand;
}
input.bluebutton {
  font-size: 12px;
  background-color: #000066;
  color: #000000;
  border-style:solid;
  cursor: hand;
}
a {
  font-size: 10px;
  color: black;
  text-decoration: none;
}
a:hover {
  font-size: 10px;
  color: red;
  text-decoration: underline;
}
select {
  color: #2a2a2a;
  font-size: 12px;
}
input,
textarea {
  color: #000000;
  font-size: 12px;
  padding: 3px;
  text-decoration: none;
  background-color: white;
  background-image: url(http://planetxmail.com/images/input.jpg);
  background-repeat: repeat-y;
  border: 1px solid black;
}
pre {font-size: 12px;}
h1 {font-size: 11px;}
h2 {font-size: 13px;}
h3 {font-size: 15px;}
.anylinkcss{
position:absolute;
visibility: hidden;
border:1px solid black;
border-bottom-width: 0;
font: normal 18px Verdana;
line-height: 18px;
z-index: 100;
background-color: beige;
width: 160px;
}
.anylinkcss a{
width: 100%;
display: block;
text-indent: 3px;
border-bottom: 1px solid black;
padding: 1px 0;
text-decoration: none;
text-indent: 5px;
text-align: left;
font: normal 14px Verdana;
}
.anylinkcss a:hover{ /*hover background color*/
background-color: lightblue;
color: black;
text-decoration: none;
font: normal 14px Verdana;
}
.anylinkcss_links {
color: blue;
background-color: beige;
width: 100%;
border: 1px solid lightgray;
padding: 3px;
text-decoration: none;
font: bold 18px Verdana;
}
</style>
<script language="javascript">
<!--
function submitonce(theform){
if (document.all||document.getElementById){
for (i=0;i<theform.length;i++){
var tempobj=theform.elements[i]
if(tempobj.type.toLowerCase()=="submit"||tempobj.type.toLowerCase()=="reset"||tempobj.type.toLowerCase()=="button")
tempobj.disabled=true;}}}
var highlightcolor="white"
var ns6=document.getElementById&&!document.all
var previous=''
var eventobj
var intended=/INPUT|TEXTAREA|SELECT|OPTION/
function checkel(which){
if (which.style&&intended.test(which.tagName)){
if (ns6&&eventobj.nodeType==3)
eventobj=eventobj.parentNode.parentNode
return true
}
else
return false
}
function highlight(e){
eventobj=ns6? e.target : event.srcElement
if (previous!=''){
if (checkel(previous))
previous.style.backgroundColor=''
previous=eventobj
if (checkel(eventobj))
eventobj.style.backgroundColor=highlightcolor
}
else{
if (checkel(eventobj))
eventobj.style.backgroundColor=highlightcolor
previous=eventobj;}}
// ---- anylink -----
var disappeardelay=250  //menu disappear speed onMouseout (in miliseconds)
var enableanchorlink=1 //Enable or disable the anchor link when clicked on? (1=e, 0=d)
var hidemenu_onclick=1 //hide menu when user clicks within menu? (1=yes, 0=no)
/////No further editting needed
var ie5=document.all
var ns6=document.getElementById&&!document.all
function getposOffset(what, offsettype){
var totaloffset=(offsettype=="left")? what.offsetLeft : what.offsetTop;
var parentEl=what.offsetParent;
while (parentEl!=null){
totaloffset=(offsettype=="left")? totaloffset+parentEl.offsetLeft : totaloffset+parentEl.offsetTop;
parentEl=parentEl.offsetParent;
}
return totaloffset;
}
function showhide(obj, e, visible, hidden){
if (ie5||ns6)
dropmenuobj.style.left=dropmenuobj.style.top=-500
if (e.type=="click" && obj.visibility==hidden || e.type=="mouseover")
obj.visibility=visible
else if (e.type=="click")
obj.visibility=hidden
}
function iecompattest(){
return (document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body
}
function clearbrowseredge(obj, whichedge){
var edgeoffset=0
if (whichedge=="rightedge"){
var windowedge=ie5 && !window.opera? iecompattest().scrollLeft+iecompattest().clientWidth-15 : window.pageXOffset+window.innerWidth-15
dropmenuobj.contentmeasure=dropmenuobj.offsetWidth
if (windowedge-dropmenuobj.x < dropmenuobj.contentmeasure)
edgeoffset=dropmenuobj.contentmeasure-obj.offsetWidth
}
else{
var topedge=ie5 && !window.opera? iecompattest().scrollTop : window.pageYOffset
var windowedge=ie5 && !window.opera? iecompattest().scrollTop+iecompattest().clientHeight-15 : window.pageYOffset+window.innerHeight-18
dropmenuobj.contentmeasure=dropmenuobj.offsetHeight
if (windowedge-dropmenuobj.y < dropmenuobj.contentmeasure){ //move up?
edgeoffset=dropmenuobj.contentmeasure+obj.offsetHeight
if ((dropmenuobj.y-topedge)<dropmenuobj.contentmeasure) //up no good either?
edgeoffset=dropmenuobj.y+obj.offsetHeight-topedge
}}
return edgeoffset
}
function dropdownmenu(obj, e, dropmenuID){
if (window.event) event.cancelBubble=true
else if (e.stopPropagation) e.stopPropagation()
if (typeof dropmenuobj!="undefined") //hide previous menu
dropmenuobj.style.visibility="hidden"
clearhidemenu()
if (ie5||ns6){
obj.onmouseout=delayhidemenu
dropmenuobj=document.getElementById(dropmenuID)
if (hidemenu_onclick) dropmenuobj.onclick=function(){dropmenuobj.style.visibility='hidden'}
dropmenuobj.onmouseover=clearhidemenu
dropmenuobj.onmouseout=ie5? function(){ dynamichide(event)} : function(event){ dynamichide(event)}
showhide(dropmenuobj.style, e, "visible", "hidden")
dropmenuobj.x=getposOffset(obj, "left")
dropmenuobj.y=getposOffset(obj, "top")
dropmenuobj.style.left=dropmenuobj.x-clearbrowseredge(obj, "rightedge")+"px"
dropmenuobj.style.top=dropmenuobj.y-clearbrowseredge(obj, "bottomedge")+obj.offsetHeight+"px"
}
return clickreturnvalue()
}
function clickreturnvalue(){
if ((ie5||ns6) && !enableanchorlink) return false
else return true
}
function contains_ns6(a, b) {
while (b.parentNode)
if ((b = b.parentNode) == a)
return true;
return false;
}
function dynamichide(e){
if (ie5&&!dropmenuobj.contains(e.toElement))
delayhidemenu()
else if (ns6&&e.currentTarget!= e.relatedTarget&& !contains_ns6(e.currentTarget, e.relatedTarget))
delayhidemenu()
}
function delayhidemenu(){
delayhide=setTimeout("dropmenuobj.style.visibility='hidden'",disappeardelay)
}
function clearhidemenu(){
if (typeof delayhide!="undefined")
clearTimeout(delayhide)
}
var current = '<?php echo $whichlist; ?>';
function changeColor(whichone)
{
  document.getElementById(''+whichone+'-1').style.backgroundColor = 'lightblue';
  document.getElementById(''+whichone+'-2').style.backgroundColor = 'lightblue';
  document.getElementById(''+whichone+'-3').style.backgroundColor = 'lightblue';
  if (current && current != whichone)
  {
    document.getElementById(''+current+'-1').style.backgroundColor = 'white';
    document.getElementById(''+current+'-2').style.backgroundColor = 'white';
    document.getElementById(''+current+'-3').style.backgroundColor = 'white';
  }
  current = whichone;
  document.signup.whichlist.value = current;
}
// Quantcast
  var _qevents = _qevents || [];

  (function() {
   var elem = document.createElement('script');

   elem.src = (document.location.protocol == "https:" ? "https://secure" : "http://edge") + ".quantserve.com/quant.js";
   elem.async = true;
   elem.type = "text/javascript";
   var scpt = document.getElementsByTagName('script')[0];
   scpt.parentNode.insertBefore(elem, scpt);
  })();
// end quantcast
//-->
</script>
</head>
<?php flush(); ?>
<body <?php
        if ($option!="homecontent") echo "style=\"width:100%;overflow-x:hidden;overflow-y:scroll\"";
        echo "style=\"background-color: #FFFFFF\" onLoad=\"";
        if ($option=="signup"||$option=="ownersignup") echo "if (current){ document.getElementById(''+current+'-1').style.backgroundColor = 'lightblue'; document.getElementById(''+current+'-2').style.backgroundColor = 'lightblue'; document.getElementById(''+current+'-3').style.backgroundColor = 'lightblue';}";
        else if ($option=="paylinks") echo "document.$mop.submit();";
        echo "\">\n";
      ?>
<table align="center" width="700" style="border-collapse: collapse" bordercolor="#000000" border="1" cellspacing="0" cellpadding="4">

<tr>
		  <td align="center">
			<script src="//fightforthefuture.github.io/battleforthenet-widget/widget.min.js"
    async></script>
		    <b>100% Double OPTIN - Beyond CAN-SPAM Act Compliant</b>
		    <br />
		    32811 7th Ave SW, Federal Way, WA 98023, USA - Contact: <a href="openticket.php">Support</a>
		  </td>
		  </tr>

<tr><td>
<table background="images/bg.jpg" cellspacing="0" cellpadding="5" border="0" align="center" width="90%">
  <tr>
    <td align="center">
      <a href="index.php"><img src="images/pxm_title_new.jpg" width="761" height="222" border="0"></a>
      <br>
      <!-- <img src="images/null.gif" border="0" width="600" height="1"> //-->
      <b><u>Reliable</u></b> SafeList/Newsletter Hosting - Hourly Database Backup - 99.9% uptime
      <br /><br />

      <a href="index.php" onClick="return clickreturnvalue()" onMouseover="dropdownmenu(this, event, 'anylinkmenu1')"><span class="anylinkcss_links">Home</span></a>
      <div id="anylinkmenu1" class="anylinkcss">
        <a href="http://planetxmail.com/index.php?option=whatisasafelist">SafeList Definition</a>
      	<a href="http://planetxmail.com/index.php?option=listtypes">List Types</a>
      	<a href="http://planetxmail.com/index.php?option=commonusages">Common Usages</a>
      	<a href="http://planetxmail.com/index.php?option=faq">F.A.Q.</a>
      	<a href="http://planetxmail.com/index.php?option=pricing">Price Table</a>
      	<a href="http://planetxmail.com/index.php?option=addons">Bonus Features</a>
      	<a href="http://planetxmail.com/index.php?option=scriptingtechnology">Program Language</a>
      	<a href="http://planetxmail.com/index.php?option=clients">Client SafeLists</a>
      	<a href="http://planetxmail.com/mle/admin/indexlistowner.php">ListOwner Log-In</a>
      	<!-- <a href="http://planetxmail.com/index.php?option=listowners">Free List Hosting</a> -->
      </div>

      <a href="index.php?option=signup" onClick="return clickreturnvalue()" onMouseover="dropdownmenu(this, event, 'anylinkmenu2')"><span class="anylinkcss_links">Order</span></a>
      <div id="anylinkmenu2" class="anylinkcss">
        <a href="http://planetxmail.com/index.php?option=signup">Order Form</a>
        <a href="http://planetxmail.com/index.php?option=pricing">Price Table</a>
      	<a href="http://planetxmail.com/index.php?option=clients">Client Testimonials</a>
      </div>

    	<a href="index.php" onClick="return clickreturnvalue()" onMouseover="dropdownmenu(this, event, 'anylinkmenu3')"><span class="anylinkcss_links">Advertise</span></a>
      <div id="anylinkmenu3" class="anylinkcss">
        <a href="http://targetedadplanet.com" target="_blank">Free ADs</a>
      	<a href="http://planetxmail.com/directads.php">Direct ADs</a>
      	<a href="http://planetxmail.com/soloads.php?list=pxm">Solo ADs</a>
      </div>

    	<a href="mle/admin/indexlistowner.php?username=demoit&password=222222" onClick="return clickreturnvalue()" onMouseover="dropdownmenu(this, event, 'anylinkmenu4')"><span class="anylinkcss_links">Demo</span></a>
      <div id="anylinkmenu4" class="anylinkcss">
        <a href="mle/admin/indexlistowner.php?username=demoit&password=222222">Demo List</a>
      </div>

    	<a href="index.php?option=clients" onClick="return clickreturnvalue()" onMouseover="dropdownmenu(this, event, 'anylinkmenu5')"><span class="anylinkcss_links">Clients</span></a>
      <div id="anylinkmenu5" class="anylinkcss">
        <a href="index.php?option=clients">Client Testimonials</a>
      </div>

    	<a href="index.php" onClick="return clickreturnvalue()" onMouseover="dropdownmenu(this, event, 'anylinkmenu6')"><span class="anylinkcss_links">Help</span></a>
      <div id="anylinkmenu6" class="anylinkcss">
        <a href="http://planetxmail.com/openticket.php">Open a Ticket</a>
        <a href="http://planetxmail.com/mle/requestlists.php" target="_self">All Signup URLs</a>
      	<a href="http://planetxmail.com/mle/requestlogins.php" target="_blank">Find your Login</a>
      	<a href="http://planetxmail.com/mle/requestremovelinks.php" target="_blank">Unsubscribe</a>
      	<a href="http://planetxmail.com/openticket.php">Report Abuse</a>
      </div>

      <br /><br />
      Serving the Internet Community since: October 2001<br>Today's date: <?php echo $date; ?></font>
      <hr>
    </td>
  </tr>
  <tr>
    <?php require_once("$option.php"); ?>
  </tr>
  <tr>
    <td align="center" valign="top">
      <hr>
      <font size="-2">All Rights Reserved &copy;2001-<?php echo date("Y"); ?> Planet X Mail<br>
      Contact: <a href="openticket.php">Support</a></font>
    </td>
  </tr>
</table>
<!-- Start Quantcast tag -->
<script type="text/javascript">
_qevents.push( { qacct:"p-a26V9rP8NfTY2"} );
</script>
<!-- End Quantcast tag -->
<script type="text/javascript">
  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-2323813-1']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();
</script>
</body>
</html>
