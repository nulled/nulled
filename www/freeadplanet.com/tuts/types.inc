<a href="javascript:Toggle('generaltypes')">Generate Types</a>
<div id="generaltypes" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> enum Color
{
   Red, Blue, Green
}
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> struct Point
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> x, y;
}
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> interface IBase
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> F();
}
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> interface IDerived: IBase
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> G();
}
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> A
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">protected</span> virtual <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> H() {
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"A.H"</span>);
   }
}
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> B: A, IDerived
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> F() {
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"B.F, implementation of IDerived.F"</span>);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> G() {
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"B.G, implementation of IDerived.G"</span>);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">override</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">protected</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> H() {
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"B.H, override of A.H"</span>);
   }
}</PRE>
</div>