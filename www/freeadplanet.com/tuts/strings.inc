<a href="javascript:Toggle('indexof')">IndexOf Strings</a>
<div id="indexof" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> phrase <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick brown fox jumps over the lazy dog."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"brown"</span>);           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 10
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.LastIndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"dog"</span>);         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 40
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"green"</span>);           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is -1
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.LastIndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"blue"</span>);        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is -1
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// -----
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> phrase <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick brown fox jumps over the lazy dog."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"he"</span>);              <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 1
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"he"</span>, 1);           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 1
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"he"</span>, 2);           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 32
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.LastIndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"he"</span>);          <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 32
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.LastIndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"he"</span>,33);       <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 32
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.LastIndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"he"</span>,32);       <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 1
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// -----
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> phrase <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick brown fox jumps over the lazy dog."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"brown"</span>);           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 10
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"brown"</span>, 5, 4);     <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is -1
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.LastIndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"fox"</span>);         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is 16
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.LastIndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"he"</span>, 25, 5);   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is -1
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// -----
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> phrase <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick brown fox jumps over the lazy dog."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.StartsWith(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick"</span>);    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is true
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.StartsWith(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"lazy dog."</span>);    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is false
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.EndsWith(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"lazy dog."</span>);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is true
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.EndsWith(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick"</span>);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is false
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// -----
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> phrase <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick brown fox jumps over the lazy dog."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.Contains(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"brown fox"</span>);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is true
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> phrase.Contains(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"lazy fox."</span>);      // result is <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>
</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('midstr')">MID Char by Char</a>
<div id="midstr" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Text;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> Kukowski
{
	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Test
	{
		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> mid(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> offset, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> numcharstoread, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> s)
		{
			StringBuilder s1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> StringBuilder(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">""</span>);

			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (s.Length &lt; numcharstoread) numcharstoread <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s.Length;
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (s.Length &lt; offset) offset <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s.Length;

			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">try</span>
			{
				<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> offset; i &lt; numcharstoread; i++)
				{
					s1.Append(s[i]);
				}
			}
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">catch</span> ( Exception e )
			{
				Console.WriteLine ( e ) ;
			}

			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> s1.ToString();
		}

		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main()
		{
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> s2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> mid(8, 8, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"c-sharp"</span>);
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"{0}"</span>, s2);
		}
	}
}</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('strings')">String Functions + Extras</a>
<div id="strings" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> MyString
{
  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main()
  {
    String strData=<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"WeLcOmE tO c#.eNjoy FoLkS"</span>;

    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"String Value: {0}"</span>,strData);
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"LowerCase Equivalent: {0}"</span>,Lower(strData));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"UpperCase Equivalent: {0}"</span>,Upper(strData));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"PCase Equivalent: {0}"</span>,PCase(strData));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Reverse Equivalent: {0}"</span>,Reverse(strData));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Is 'rotator' PalinDrome:{0}"</span>,IsPalindrome(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"rotator"</span>));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Is 'visualc#' PalinDrome:{0}"</span>,IsPalindrome(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"visualc#"</span>));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Left(string,5): {0}"</span>,Left(strData,5));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Right(String,6): {0}"</span>,Right(strData,6));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"CharCount(Charcount,c):{0}"</span>,CharCount(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Charcount"</span>,<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"C"</span>));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"CharCount(CharCount,c,true):{0}"</span>,CharCount(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Charcount"</span>,<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"C"</span>,<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"CharCount(CharCount,d,true):{0}"</span>,CharCount(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Charcount"</span>,<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"d"</span>,<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"ToSingleSpace('welcome  to     C      Sharp'): {0}"</span>,ToSingleSpace(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"welcome  to     C      Sharp     "</span>));
    Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Replace(aaaaaa,aa,a):{0}"</span>,Replace(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"aaaaaa"</span>,<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"aa"</span>,<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"a"</span>));
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Convert string to LowerCase
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> String Lower(String strParam)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam.ToLower();
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Convert String to UpperCase
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> String Upper(String strParam)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam.ToUpper();
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Convert String to ProperCase
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> String PCase(String strParam)
  {
    String strProper=strParam.Substring(0,1).ToUpper();
    strParam=strParam.Substring(1).ToLower();
    String strPrev=<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">""</span>;

    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span>(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iIndex=0;iIndex &lt; strParam.Length;iIndex++)
    {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span>(iIndex &gt; 1)
      {
        strPrev=strParam.Substring(iIndex-1,1);
      }
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span>( strPrev.Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">" "</span>) ||
          strPrev.Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\t"</span>) ||
          strPrev.Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\n"</span>) ||
          strPrev.Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"."</span>))
      {
          strProper+=strParam.Substring(iIndex,1).ToUpper();
      }
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
      {
        strProper+=strParam.Substring(iIndex,1);
      }
    }
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strProper;
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Function to Reverse the String
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> String Reverse(String strParam)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span>(strParam.Length==1)
    {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam;
    }
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
    {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> Reverse(strParam.Substring(1)) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> strParam.Substring(0,1);
    }
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Function to Test for Palindrome
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> IsPalindrome(String strParam)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iLength,iHalfLen;
    iLength=strParam.Length-1;
    iHalfLen=iLength/2;
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span>(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iIndex=0;iIndex0)
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam.Substring(0,iLen);
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam;
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Function to get string from end
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> String Right(String strParam,<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iLen)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span>(iLen&gt;0)
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam.Substring(strParam.Length-iLen,iLen);
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam;
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Function to count no.of occurences of Substring in Main string
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> CharCount(String strSource,String strToCount)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iCount=0;
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iPos=strSource.IndexOf(strToCount);
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span>(iPos!=-1)
    {
      iCount++;
      strSource=strSource.Substring(iPos+1);
      iPos=strSource.IndexOf(strToCount);
    }
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> iCount;
  }

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Not available in C#
</span>  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Function to count no.of occurences of Substring in Main string
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> CharCount(String strSource,String strToCount,<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span>
IgnoreCase)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span>(IgnoreCase)
    {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> CharCount(strSource.ToLower(),strToCount.ToLower());
    }
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
    {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> CharCount(strSource,strToCount);
    }
  }

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Useful Function can be used whitespace stripping programs
</span>  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Function Trim the string to contain Single between words
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> String ToSingleSpace(String strParam)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iPosition=strParam.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"  "</span>);
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span>(iPosition==-1)
    {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strParam;
    }
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
    {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> ToSingleSpace(strParam.Substring(0,iPosition) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span>
strParam.Substring(iPosition+1));
    }
  }

  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Function Replace string function.
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Currently Not Available in C#
</span>  <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> String Replace(String strText,String strFind,String
strReplace)
  {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iPos=strText.IndexOf(strFind);
    String strReturn=<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">""</span>;
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span>(iPos!=-1)
    {
      strReturn+=strText.Substring(0,iPos) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> strReplace;
      strText=strText.Substring(iPos+strFind.Length);
      iPos=strText.IndexOf(strFind);
    }
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span>(strText.Length&gt;0)
      strReturn+=strText;
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> strReturn;
  }
}

Here is what the output should look like:

String Value: WeLcOmE? tO c#.eNjoy FoLkS?
LowerCase? Equivalent:welcome to c#.enjoy folks
UpperCase? Equivalent:WELCOME TO C#.ENJOY FOLKS
PCase Equivalent:Welcome To C#.Enjoy Folks
Reverse Equivalent:SkLoF yojNe.#c Ot EmOcLeW?
Is 'rotator' Palindrome :True
Is 'visualc#' Palindrome:False
Left(string,5):WeLcO
Right(string,6):FolkS
CharCount(CharCount,c):1
CharCount(CharCount,c,true):2
CharCount(CharCount,d,true):0
ToSingleSpace('welcome to C Sharp '):Welcome to C Sharp
Replace(aaaaaa,aa,a):aaa
</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('comparison')">Comparing Strings</a>
<div id="comparison" class="codearea">
<PRE><span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//  ----------- Equality and Inequality Operators
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> s1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"String to compare."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> s2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"String to compare."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> s3 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"String to Compare."</span>;   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Note the capital 'C'
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s1 == s2;                  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = true
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s1 == s3;                  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = false
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s1 !<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s2;                  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = false
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s1 !<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> s3;                  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = true
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/*  Relative Comparison
Zero  	       - The two strings are equal.
Less than Zero - The first string has a value that is less than the second.
More than Zero - The first string has a value that is greater than the second or the second string is undefined (null).
*/</span>
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Dog"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> animal1.CompareTo(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>);          <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is zero
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> animal2.CompareTo(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>);          <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is greater than zero
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> animal1.CompareTo(animal2);        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is less than zero
</span>
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;
result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> animal.CompareTo(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>);           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Causes an exception
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// ----------- Similar functionality to CompareTo but allows more options to be specified
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Dog"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(animal1, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>);    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is zero
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(animal2, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>);    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is greater than zero
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(animal1, animal2);  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is less than zero
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//  ----------- Null Comparison
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(animal, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is greater than zero
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>, animal);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is less than zero
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>);        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is zero
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//  ----------- Case Sensitivity
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"cat"</span>;                             <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Note use of lower case
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(animal1, animal2, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>);    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Strings are equal
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(animal1, animal2, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>);   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Strings are not equal
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//  ----------- CompareOrdinal Method
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"cat"</span>;                             <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Note use of lower case
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Compare(animal1, animal2);          <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is greater than zero
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.CompareOrdinal(animal1, animal2);   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result is less than zero
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//  ----------- Equals Method
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> animal.Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>);                      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = true
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> animal.Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"cat"</span>);                      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = false
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Equals(animal, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>);              <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = true
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.Equals(animal, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"cat"</span>);              <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = false
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//  ----------- .NET 2.0 IsNullOrEmpty Method
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cat"</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">""</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> animal3 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> result;

result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.IsNullOrEmpty(animal1);             <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = false
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.IsNullOrEmpty(animal2);             <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = true
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> String.IsNullOrEmpty(animal3);             // result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>
</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('manipulating')">Manipulating Strings</a>
<div id="manipulating" class="codearea">
<PRE><span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// ------------- String Concatenation
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> start <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"This is a "</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> end <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"concatenated string!"</span>;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> concat <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> start <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> end;    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// concat = "This is a concatenated string!"
</span>
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> start <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"This is a "</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> end <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"concatenated string!"</span>;

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// ------------- Inserting Strings into Strings
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> template <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Please ask for  on arrival."</span>;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> tutor <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Lisa"</span>;

Console.WriteLine(template.Insert(15, tutor));

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/* Outputs: "Please ask for Lisa on arrival." */</span>

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// ------------- Removing Characters from a String
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> sample <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick brown fox jumps over the lazy dog."</span>;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sample.Remove(16);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = "The quick brown "
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sample.Remove(16, 24);         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = "The quick brown dog."
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// ------------- Extracting Text from a String
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> sample <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The quick brown fox jumps over the lazy dog."</span>;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sample.Substring(16);   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = "fox jumps over the lazy dog."
</span>result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sample.Substring(16, 24);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = "fox jumps over the lazy "
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// ------------- Search and Replace
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> sample <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The brown fox."</span>;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sample.Replace(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"brown"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"red"</span>));   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// result = "The red fox."
</span>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// ------------- Copying Strings
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> sample <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The brown fox."</span>;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>.Copy(sample);    // result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The brown fox."</span></PRE>
</div>