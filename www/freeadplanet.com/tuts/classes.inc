<a href="javascript:Toggle('classes')">Classes</a>
<div id="classes" class="codearea">
<PRE>

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> - Access not limited.
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">protected</span> - Access limited to the containing class or types derived from the containing class.
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">internal</span> - Access limited to this program.
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">protected internal</span> - Access limited to this program or types derived from the containing class.
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> - Access limited to the containing type.


<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> MyClass
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> MyClass() {
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Instance constructor"</span>);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> MyClass(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> value) {
      MyField <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> value;
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Instance constructor"</span>);
   }
   ~MyClass() {
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Destructor"</span>);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">const</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> MyConst <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 12;
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> MyField <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 34;
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> MyMethod(){
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"MyClass.MyMethod"</span>);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> MyProperty {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">get</span> {
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> MyField;
      }
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">set</span> {
         MyField <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> value;
      }
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">this</span>[<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> index] {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">get</span> {
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> 0;
      }
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">set</span> {
         Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"this[{0}] = {1}"</span>, index, value);
      }
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> event EventHandler MyEvent;
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> MyClass operator+(MyClass a, MyClass b) {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> MyClass(a.MyField <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> b.MyField);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">internal</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> MyNestedClass
   {}
}

This shows uses of these members.

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Test
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main() {
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Instance constructor usage
</span>      MyClass a <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> MyClass();
      MyClass b <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> MyClass(123);
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Constant usage
</span>      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"MyConst = {0}"</span>, MyClass.MyConst);
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Field usage
</span>      a.MyField++;
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"a.MyField = {0}"</span>, a.MyField);
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Method usage
</span>      a.MyMethod();
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Property usage
</span>      a.MyProperty++;
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"a.MyProperty = {0}"</span>, a.MyProperty);
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Indexer usage
</span>      a[3] <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> a[1] <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> a[2];
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"a[3] = {0}"</span>, a[3]);
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Event usage
</span>      a.MyEvent += <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> EventHandler(MyHandler);
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Overloaded operator usage
</span>      MyClass c <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> a <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> b;
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> MyHandler(object sender, EventArgs e) {
      Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Test.MyHandler"</span>);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">internal</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> MyNestedClass
   {}
}</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('structsclasses')">Structs vs Classes</a>
<div id="structsclasses" class="codearea">
<PRE>
The list of similarities between classes and structs is long — structs can implement interfaces, and can have the same kinds of members as classes.
Structs differ from classes in several important ways, however: structs are value types rather than reference types, and inheritance is not supported
for structs. Struct values are stored "on the stack" or "in-line". Careful programmers can sometimes enhance performance through judicious use of structs.

For example, the use of a struct rather than a class for a Point can make a large difference in the number of memory allocations performed at run time.
The program below creates and initializes an array of 100 points. With Point implemented as a class, 101 separate objects are instantiated — one for the
array and one each for the 100 elements.

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Point
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> x, y;
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> Point(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> x, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> y) {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">this</span>.x <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> x;
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">this</span>.y <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> y;
   }
}
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Test
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main() {
      Point[] points <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Point[100];
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0; i &lt; 100; i++)
         points[i] <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Point(i, i*i);
   }
}

If Point is instead implemented as a struct, as in

struct Point
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> x, y;
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> Point(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> x, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> y) {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">this</span>.x <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> x;
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">this</span>.y <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> y;
   }
}

only one object is instantiated — the one for the array. The Point instances are allocated in-line within the array.
This optimization can be misused. Using structs instead of classes can also make an application run slower, or take up more memory,
as passing a struct instance by value causes a copy of that struct to be created.
</PRE>
</div>