<a href="javascript:Toggle('stopwatch')">Stop Watch</a>
<div id="stopwatch" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Diagnostics;

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/*
Execution time was 1493.7 microseconds.
Press any key to continue . . .
*/</span>

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> StopWatchExample
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Example
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[] args)
        {
            Stopwatch timer <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Stopwatch();
            long total <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;

            timer.Start();          <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Start the timer
</span>
            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i=1;i&lt;=1000000;i++)
                total += i;

            timer.Stop();           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Stop the timer
</span>
            decimal micro <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> (decimal)timer.Elapsed.Ticks <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">/</span> 10M;
            Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Execution time was {0:F1} microseconds."</span>, micro);
        }
    }
}</PRE>
</div>
