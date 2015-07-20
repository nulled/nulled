function submitonce(theform)
{
  for (var i=0; i < theform.length; i++)
  {
    var tempobj = theform.elements[i];

    if (tempobj.type.toLowerCase() == 'submit' || tempobj.type.toLowerCase() == 'button')
    {
      tempobj.disabled = true;
      tempobj.value = 'Loading ...';
    }
  }
}

var highlightcolor = 'white';
var ns6 = document.getElementById && ! document.all;
var previous = '';
var eventobj;
var intended = /INPUT|TEXTAREA|SELECT|OPTION/;

function checkel(which)
{
  if (which.style && intended.test(which.tagName))
  {
    if (ns6 && eventobj.nodeType == 3)
      eventobj = eventobj.parentNode.parentNode;

    return true;
  }
  else
    return false;
}

function highlight(e)
{
  eventobj = ns6 ? e.target : event.srcElement;

  if (previous !== '')
  {
    if (checkel(previous))
      previous.style.backgroundColor = '';

    previous = eventobj;

    if (checkel(eventobj))
      eventobj.style.backgroundColor = highlightcolor;
  }
  else
  {
    if (checkel(eventobj))
      eventobj.style.backgroundColor = highlightcolor;

    previous = eventobj;
  }
}