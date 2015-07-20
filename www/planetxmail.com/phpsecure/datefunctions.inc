<?php

    // MAIN PART
    //
    // File: datetime.php
    // Author: Andrzej Manczyk
    // email: amanczyk@poczta.onet.pl
    // Project: Date and time functions
    // Version: 1.0.0
    // PHP: 4.04
    // Functions list:
    // - DateDiff: return differences betwee
    //     n two timestamps measured in the number
    //     of
    // years, months, days, hours, minutes o
    //     r seconds
    // - DateAdd: add years, months, days, h
    //     ours, minutes or seconds to
    // specified timestamp
    // - MonthFirstDay: return first day of
    //     the month
    // - MonthLastDay: return last day of th
    //     e month
    // - cDateTime: create timestamp
    // - cDate: create timestamp only with d
    //     ate specification
    // - Year: return number of years from s
    //     pecified timestamp
    // - Month: return number of minutes fro
    //     m specified timestamp
    // - Day: return number of days from spe
    //     cified timestamp
    // - Hour: return number of hours from s
    //     pecified timestamp
    // - Minute: return number of minutes fr
    //     om specified timestamp
    // - Second: return number of seconds fr
    //     om specified timestamp
    // Inputs:
    // Date, Date1, Date2 - timestamp i.e. d
    //     ate and time
    // Year, Month, Day, Hour, Minute, Secon
    //     d - number of years,
    // months, days, hours, minutes or secon
    //     ds
    // Returns:
    // Integer - DateDiff, DateAdd, Year, Mo
    //     nth, Day, Hour, Minute, Second functions
    //
    // Timestamp - MonthFirstDay, MonthLastD
    //     ay, cDateTime, cDate
    Function DateDiff($Date1, $Date2, $Interval)
    {
    If ($Date1 < $Date2) {
    $dt1 = $Date1;
    $dt2 = $Date2;
    } Else {
    $dt1 = $Date2;
    $dt2 = $Date1;
    }
    $d1 = GetDate($dt1);
    $d2 = GetDate($dt2);
    $Date = $dt2 - $dt1;
    $d = GetDate($Date);
    Switch ($Interval) {
    Case "Y":
    //year
    $Number = GetYear($d1[year], $d2[year], $d1[mon], $d2[mon], $d1[mday], $d2[mday]);
    Break;
    Case "m":
    //month
    //1 part, the same as in "Y" case
    $y = GetYear($d1[year], $d2[year], $d1[mon], $d2[mon], $d1[mday], $d2[mday]);
    //2 part, rest months
    $dt1 = DateAdd($dt1, "Y", $y);
    $d1 = GetDate($dt1);
    While (True) {
    $m++;
    $dt1 = DateAdd($dt1, "m", 1);
    If ($dt1 >= $dt2) Break;
    }
    If ($dt1 > $dt2) $m--;
    $Number = ($y * 12) + $m;
    Break;
    Case "d":
    //day
    $Number = $Date / 86400; //60 sek. * 60 min. * 24 h.
    Break;
    Case "H":
    //hour
    $Number = $Date / 3600; //60 sek. * 60 min.
    Break;
    Case "M":
    //minute
    $Number = $Date / 60; //60 sek.
    Break;
    Case "S":
    //second
    $Number = $Date;
    Break;
    }
    If ($Date1 < $Date2) {
    Return $Number;
    } Else {
    Return $Number * (-1);
    }
    }
    Function DateAdd($Date, $Interval, $Number)
    {
    $d = GetDate($Date);
    Switch ($Interval) {
    Case ("Y"):
    //year
    $Date = MkTime($d[hours], $d[minutes], $d[seconds],
    $d[mon], $d[mday], $d[year] + $Number);
    Break;
    Case "m":
    //month
    $Date = MkTime($d[hours], $d[minutes], $d[seconds],
    $d[mon] + $Number, $d[mday], $d[year]);
    Break;
    Case "d":
    //day
    $Date = MkTime($d[hours], $d[minutes], $d[seconds],
    $d[mon], $d[mday] + $Number, $d[year]);
    Break;
    Case "H":
    //hour
    $Date = MkTime($d[hours] + $Number, $d[minutes], $d[seconds],
    $d[mon], $d[mday], $d[year]);
    Break;
    Case "M":
    //minute
    $Date = MkTime($d[hours], $d[minutes] + $Number, $d[seconds],
    $d[mon], $d[mday], $d[year]);
    Break;
    Case "S":
    //second
    $Date = MkTime($d[hours], $d[minutes], $d[seconds] + $Number,
    $d[mon], $d[mday], $d[year]);
    Break;
    }
    Return $Date;
    }
    Function GetYear($y1, $y2, $m1, $m2, $d1, $d2)
    {
    If ($y1 == $y2) {
    $Year = 0;
    } ElseIf (($m2 < $m1) Or ($m2 == $m1 And $d2 < $d1)) {
    $Year = $y2 - $y1 - 1;
    } Else {
    $Year = $y2 - $y1;
    }
    Return $Year;
    }
    Function MonthFirstDay($Year, $Month)
    {
    $Date = cDate($Year, $Month, 1);
    Return $Date;
    }
    Function MonthLastDay($Year, $Month)
    {
    If ($Month == 12) {
    $Date = cDate($Year, $Month, 31);
    } Else {
    $Date = MkTime(0, 0, 0, $Month + 1, 1 - 1, $Year);
    }
    Return $Date;
    }
    Function cDateTime($Year, $Month, $Day, $Hour, $Minute, $Second)
    {
    $Date = MkTime($Hour, $Minute, $Second, $Month, $Day, $Year);
    Return $Date;
    }
    Function cDate($Year, $Month, $Day)
    {
    $Date = MkTime(0, 0, 0, $Month, $Day, $Year);
    Return $Date;
    }
    Function Year($Date)
    {
    $d = GetDate($Date);
    Return $d[year];
    }
    Function Month($Date)
    {
    $d = GetDate($Date);
    Return $d[mon];
    }
    Function Day($Date)
    {
    $d = GetDate($Date);
    Return $d[mday];
    }
    Function Hour($Date)
    {
    $d = GetDate($Date);
    Return $d[hours];
    }
    Function Minute($Date)
    {
    $d = GetDate($Date);
    Return $d[minutes];
    }
    Function Second($Date)
    {
    $d = GetDate($Date);
    Return $d[second];
    }
    Function cDateTimePL($Date)
    {
    Return StrFTime("%Y-%m-%d %H:%M:%S", $Date);
    }
    Function cDatePL($Date)
    {
    Return StrFTime("%Y-%m-%d", $Date);
    }
    Function cTimePL($Date)
    {
    Return StrFTime("%Y-%m-%d %H:%M:%S", $Date);
    }
    Function cDateTimeUS($Date)
    {
    Return StrFTime("%m/%d/%y %I:%M:%S%p", $Date);
    }
    Function cDateUS($Date)
    {
    Return StrFTime("%m/%d/%y", $Date);
    }
    Function cTimeUS($Date)
    {
    Return StrFTime("%I:%M:%S%p", $Date);
    }
    // END MAIN PART

    // $dt = DateAdd(Time(), "Y" , 1);

?>
