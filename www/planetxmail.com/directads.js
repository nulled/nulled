/*
Fading Scroller- By DynamicDrive.com
For full source code, 100's more DHTML scripts, and TOS,
visit http://www.dynamicdrive.com
*/
///No need to edit below this line/////////////////
var ie4=document.all&&!document.getElementById
var ns4=document.layers
var DOM2=document.getElementById
var faderdelay=0
var index=0
if (DOM2)
faderdelay=2000
//function to change content
function changecontent(){
if (index>=fcontent.length)
index=0
if (DOM2){
document.getElementById("fscroller").style.color="rgb(255,255,255)"
document.getElementById("fscroller").innerHTML=begintag+fcontent[index]+closetag
colorfade()
}
else if (ie4)
document.all.fscroller.innerHTML=begintag+fcontent[index]+closetag
else if (ns4){
document.fscrollerns.document.fscrollerns_sub.document.write(begintag+fcontent[index]+closetag)
document.fscrollerns.document.fscrollerns_sub.document.close()
}
index++
setTimeout("changecontent()",delay+faderdelay)
}
// colorfade() partially by Marcio Galli for Netscape Communications.  ////////////
// Modified by Dynamicdrive.com
frame=20;
hex=255  // Initial color value.
function colorfade() {
// 20 frames fading process
if(frame>0) {
hex-=12; // increase color value
document.getElementById("fscroller").style.color="rgb("+hex+","+hex+","+hex+")"; // Set color value.
frame--;
setTimeout("colorfade()",20);
}else{
document.getElementById("fscroller").style.color="rgb(0,0,0)";
frame=20;
hex=255
}}
if (ie4||DOM2) document.write('<div id="fscroller" style="border:1px solid black;width:'+fwidth+';height:'+fheight+';padding:2px;overflow:hidden"></div>')
