//Drop-down Document Viewer- © Dynamic Drive (www.dynamicdrive.com)
//For full source code, 100's more DHTML scripts, and TOS,
//visit http://www.dynamicdrive.com
var displaymode=0
var iframecode='<iframe id="external" style="width:100%;height:350px" src="http://www.planetxmail.com/directads_instr.php"></iframe>'
/////NO NEED TO EDIT BELOW HERE////////////
if (displaymode==0)
document.write(iframecode)
function gone(){
var selectedurl="http://www.planetxmail.com/directads_instr.php"
if (document.getElementById&&displaymode==0)
document.getElementById("external").src=selectedurl
else if (document.all&&displaymode==0)
document.all.external.src=selectedurl
else{
if (!window.win2||win2.closed)
win2=window.open(selectedurl)
else{
win2.location=selectedurl
win2.focus()}}}