var highlight_color = '#CCD6F5';
var selected_color = '#CCD6F5';

function checkAll()
{
  var el;

  if (document.listmail.checkdeleteall.checked)
  {
    for (i=0, j=1; i < document.listmail.elements.length; i++, j++)
    {
      document.listmail.elements[i].checked = true;
      el = document.getElementById(j);
      if (el) el.style.backgroundColor = selected_color;
    }
  }
  else
  {
    for (i=0, j=1; i < document.listmail.elements.length; i++, j++)
    {
      document.listmail.elements[i].checked = false;
      el = document.getElementById(j);
      if (el) el.style.backgroundColor = el.bgColor;
    }
  }
}

function changeColor(id, checkedState)
{
  var el = document.getElementById(id);

  if (checkedState)
    el.style.backgroundColor = selected_color;
  else
    el.style.backgroundColor = el.bgColor;
}

function changeColorMouseOver(id)
{
  var el = document.getElementById(id);
  if (el) el.style.backgroundColor = highlight_color;
}

function changeColorMouseOut(id)
{
  var el = document.getElementById(id);
  var cb = document.getElementById('cb_' + id);

  if (cb.checked)
    el.style.backgroundColor = selected_color;
  else
    el.style.backgroundColor = el.bgColor;
}