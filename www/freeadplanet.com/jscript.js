function xferCredits(which)
{
  var to = document.forms[0].to;
  var from = document.forms[0].from;
  var xfercredits = document.forms[0].xfercredits;

  if (which == 'set')
  {
    to.selectedIndex = 0;
    from.selectedIndex = 1;
    xfercredits.value = 0;
  }
  else if (which == 'from')
  {
    if (from.selectedIndex == 0)
      to.selectedIndex = 1;
    else
      to.selectedIndex = 0;
  }
  else
  {
    if (to.selectedIndex == 0)
      from.selectedIndex = 1;
    else
      from.selectedIndex = 0;
  }
}

function doubleCheck(typead)
{
  if (confirm('Are you sure you want to Purchase the AD below?\n\nType of AD: ' + typead + '\n\nYou will be charged based on Credits in your account.')) location.href='?c=buyads&t=' + typead;
}

function ToggleHelp(whichLayer)
{
  var style2 = document.getElementById(whichLayer).style;
  if (style2.display == 'none') style2.display = 'block';
  else style2.display = 'none';
  jsm.ajax.get('http://freeadplanet.com/members/?c=sethelp&s='+style2.display, null);
}

function Toggle(whichLayer)
{
  var style2 = document.getElementById(whichLayer).style;
  if (style2.display == 'none' || style2.display == '') style2.display = 'block';
  else style2.display = 'none';
}

function submitOnce()
{
  var inputs = document.getElementsByTagName('input');
  for (var i=0; i < inputs.length; i++) {
    var type = inputs[i].getAttribute('type');
    if (type == 'submit' || type == 'reset') {
      inputs[i].disabled = true;
    }
  }
}

// remove checkbox borders in IE
function addEvent(elm, evType, fn)
{
  if (elm.addEventListener) {
    elm.addEventListener(evType, fn, false);
  }
  else if (elm.attachEvent) {
    elm.attachEvent('on' + evType, fn);
  }
}

// removes the square border that IE
// insists on adding to checkboxes and radio
function removeCheckBoxBorders()
{
  var inputs = document.getElementsByTagName('input');
  for (var i=0; i < inputs.length; i++) {
    var type = inputs[i].getAttribute('type');
    if (type == 'checkbox' || type == 'radio') {
      inputs[i].style.background = inputs[i].style.border = 'none';
    }
  }
}

addEvent(window, 'load', removeCheckBoxBorders);
