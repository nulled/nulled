faderdelay = 2000;
index = 0;

function changecontent()
{
  if (index >= fcontent.length)
    index = 0;

  document.getElementById("fscroller").style.color = "rgb(255,255,255)";
  document.getElementById("fscroller").innerHTML = begintag + fcontent[index] + closetag;

  colorfade();
  index++;
  setTimeout("changecontent()", delay + faderdelay);
}

frame = 20;
hex   = 255;  // Initial color value.
function colorfade()
{
  // 20 frames fading process
  if (frame > 0)
  {
    hex -= 12; // increase color value
    document.getElementById("fscroller").style.color = "rgb("+hex+","+hex+","+hex+")"; // Set color value.
    frame--;
    setTimeout("colorfade()", 20);
  }
  else
  {
    document.getElementById("fscroller").style.color="rgb(0,0,0)";
    frame = 20;
    hex = 255;
  }
}

document.write('<div id="fscroller" style="border:1px solid black;width:150px;height:400px;padding:2px;overflow:hidden"></div>');