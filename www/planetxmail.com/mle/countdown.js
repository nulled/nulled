<!--
var timerID;
var timerRunning = false;
var today = new Date();
var count = new Date();
var secPerDay = 0;
var minPerDay = 0;
var hourPerDay = 0;
var secsLeft = 0;
var secsRound = 0;
var secsRemain = 0;
var minLeft = 0;
var minRound = 0;
var dayRemain = 0;
var minRemain = 0;
var Expire = 0;
var timeRemain = 0;
var timeUp = "You can now send mail!";   // enter text to be displayed when countdown is finished
var time = "Logoff then on.";
var countto = "";
var servertime = "";
var start = 0;

function stopclock ()
{
  if(timerRunning)
    clearTimeout(timerID);

  timerRunning = false;
}

function startclock ()
{
  stopclock();
  clientstart = new Date(servertime);
  start = clientstart.getTime(); // store time page was started but based on the servers time

  showtime();
}

function showtime ()
{
  currentTime = new Date();
  elapsed = currentTime.getTime() - start;
  today = new Date();
  today.setTime(elapsed+start);

  count = new Date(countto);   // enter date to count down to (January 1, 2002)

  secsPerDay = 1000 ;
  minPerDay = 60 * 1000 ;
  hoursPerDay = 60 * 60 * 1000;
  PerDay = 24 * 60 * 60 * 1000;
  PerYear = 24 * 60 * 60 * 1000 * 365;
  Expire = (count.getTime() - today.getTime())

  /*Seconds*/
  secsLeft = (count.getTime() - today.getTime()) / minPerDay;
  secsRound = Math.round(secsLeft);
  secsRemain = secsLeft - secsRound;
  secsRemain = (secsRemain < 0) ? secsRemain = 60 - ((secsRound - secsLeft) * 60) : secsRemain = (secsLeft - secsRound) * 60;
  secsRemain = Math.round(secsRemain);


  /*Minutes*/
  minLeft = ((count.getTime() - today.getTime()) / hoursPerDay);
  minRound = Math.round(minLeft);
  minRemain = minLeft - minRound;
  minRemain = (minRemain < 0) ? minRemain = 60 - ((minRound - minLeft)  * 60) : minRemain = ((minLeft - minRound) * 60);
  minRemain = Math.round(minRemain - 0.495);

  /*Hours*/
  hoursLeft = ((count.getTime() - today.getTime()) / PerDay);
  hoursRound = Math.round(hoursLeft);
  hoursRemain = hoursLeft - hoursRound;
  hoursRemain = (hoursRemain < 0) ? hoursRemain = 24 - ((hoursRound - hoursLeft)  * 24) : hoursRemain = ((hoursLeft - hoursRound) * 24);
  hoursRemain = Math.round(hoursRemain - 0.5);

  /*Days*/
  daysLeft = ((count.getTime() - today.getTime()) / PerYear);
  daysRound = Math.round(daysLeft);
  daysRemain = daysLeft - daysRound;
  daysRemain = (daysRemain < 0) ? daysRemain = 365 - ((daysRound - daysLeft)  * 365) : daysRemain = ((daysLeft - daysRound) * 365);
  daysRemain = Math.round(daysRemain - 0.5);

  daysLeft = ((count.getTime() - today.getTime()) / PerDay);
  daysLeft = (daysLeft);
  daysRound = Math.round(daysLeft);
  daysRemain2 = daysRound;

  // NEW DISPLAY
  if (daysRemain == 1)
    daysRemain = daysRemain + " day, ";
  else
    daysRemain = daysRemain + " days, ";

  if (daysRemain2 == 1)
    daysRemain2 = daysRemain2 + " day, ";
  else
    daysRemain2 = daysRemain2 + " days, ";

  if (hoursRemain == 1)
    hoursRemain = hoursRemain + ":";
  else
    hoursRemain = hoursRemain + ":";

  if (minRemain == 1)
    minRemain = minRemain + ":";
  else
    minRemain = minRemain + ":";

  if (secsRemain == 1)
    secsRemain = secsRemain + "";
  else
    secsRemain = secsRemain + "";

  /*Time*/
  timeRemain = daysRemain + hoursRemain + minRemain + secsRemain;

  window.status = "";
  document.clock.face.value = timeRemain;
  timerID = setTimeout("showtime()",1000);
  timerRunning = true;

  if (Expire <= 0)
  {
    document.clock.face.value = time;  // choose either "time" or "timeUp"  (without quotes)
    stopclock()
  }
}

// -->