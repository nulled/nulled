<a href="javascript:Toggle('stack')">Stacks - FILO</a>
<div id="stack" class="codearea">
<PRE>
A Stack is created and initialized with 10 elements, and then assigned the value null.
Once the variable s is assigned null, the Stack and the associated 10 Node instances become eligible for garbage collection.
The garbage collector is permitted to clean up immediately, but is not required to do so.

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Stack
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> Node first <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>;
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> Empty {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">get</span> {
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> (first == <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>);
      }
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> object Pop() {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (first == <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>)
         throw <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Exception(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Can't Pop from an empty Stack."</span>);
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span> {
         object temp <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> first.Value;
         first <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> first.Next;
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> temp;
      }
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Push(object o) {
      first <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Node(o, first);
   }
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Node
   {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> Node Next;
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> object Value;
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> Node(object value): <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">this</span>(value, <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>) {}
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> Node(object value, Node next) {
         Next <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> next;
         Value <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> value;
      }
   }
}

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Test
{
   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main() {
      Stack s <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Stack();
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0; i &lt; 10; i++)
         s.Push(i);
      s <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>;
   }
}

</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('stack2.0')">Stacks .NET 2.0</a>
<div id="stack2.0" class="codearea">
<PRE><span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// New to .NET 2.0
</span>
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Collections.Generic;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Example
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main()
    {
        Stack&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; numbers <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Stack&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt;();
        numbers.Push(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>);
        numbers.Push(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>);
        numbers.Push(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"three"</span>);
        numbers.Push(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"four"</span>);
        numbers.Push(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"five"</span>);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// A stack can be enumerated without disturbing its contents.
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> number <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> numbers )
        {
            Console.WriteLine(number);


        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nPopping '{0'"</span>, numbers.Pop());
        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Peek at next item to destack: {0"</span>,
            numbers.Peek());
        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Popping '{0'"</span>, numbers.Pop());

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create a copy of the stack, using the ToArray method and the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// constructor that accepts an IEnumerable&lt;T&gt;.
</span>        Stack&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; stack2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Stack&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt;(numbers.ToArray());

        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nContents of the first copy:"</span>);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> number <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> stack2 )
        {
            Console.WriteLine(number);


        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create an array twice the size of the stack and copy the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// elements of the stack, starting at the middle of the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// array.
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[] array2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[numbers.Count <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">*</span> 2];
        numbers.CopyTo(array2, numbers.Count);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create a second stack, using the constructor that accepts an
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// IEnumerable(Of T).
</span>        Stack&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; stack3 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Stack&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt;(array2);

        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nContents of the second copy, with duplicates and nulls:"</span>);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> number <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> stack3 )
        {
            Console.WriteLine(number);


        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nstack2.Contains(\"four\") = {0"</span>,
            stack2.Contains(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"four"</span>));

        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nstack2.Clear()"</span>);
        stack2.Clear();
        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nstack2.Count = {0"</span>, stack2.Count);



<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/* This code example produces the following output:

five
four
three
two
one

Popping 'five'
Peek at next item to destack: four
Popping 'four'

Contents of the first copy:
one
two
three

Contents of the second copy, with duplicates and nulls:
one
two
three
*/</span></PRE>
</div>

<br /><br />
<a href="javascript:Toggle('linklists')">Link Lists</a>
<div id="linklists" class="codearea">
<PRE>
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// New to .NET 2.0</span>

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Text;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Collections.Generic;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Example
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main()
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[] words <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span>
            {<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"the"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"fox"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"jumped"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"over"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"the"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"dog"</span>;
        LinkedList&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; sentence <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> LinkedList&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt;(words);
        Display(sentence);

        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"sentence.Contains(\"jumped\") = {0"</span>,
            sentence.Contains(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"jumped"</span>));

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Add the word "today" to the beginning of the linked list.
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Remove the new node, and add it to the end of the list.
</span>        sentence.AddFirst(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"today"</span>);
        Display(sentence);

        LinkedListNode&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; mark1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sentence.First;
        sentence.RemoveFirst();
        sentence.AddLast(mark1);
        Display(sentence);

        sentence.RemoveLast();
        sentence.AddLast(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"yesterday"</span>);
        Display(sentence);

        mark1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sentence.Last;
        sentence.RemoveLast();
        sentence.AddFirst(mark1);
        Display(sentence);

        sentence.RemoveFirst();

        LinkedListNode&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; current <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sentence.FindLast(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"the"</span>);
        DisplayNode(current);

        sentence.AddAfter(current, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"old"</span>);
        sentence.AddAfter(current, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"lazy"</span>);
        DisplayNode(current);

        current <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sentence.Find(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"fox"</span>);
        DisplayNode(current);

        sentence.AddBefore(current, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"quick"</span>);
        sentence.AddBefore(current, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"brown"</span>);
        DisplayNode(current);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Keep a reference to the current node, "fox", and to the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// previous node in the list. Use the Find method to locate
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// the node containing the value "dog". Show the position.
</span>        mark1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> current;
        LinkedListNode&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; mark2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> current.Previous;
        current <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sentence.Find(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"dog"</span>);
        DisplayNode(current);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// The AddBefore method throws an InvalidOperationException
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// if you try to add a node that already belongs to a list.
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">try</span>
        {
            sentence.AddBefore(current, mark1);

        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">catch</span>(InvalidOperationException ex)
        {
            Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Exception message: {0"</span>, ex.Message);


        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Remove the node referred to by mark1, and add it before
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// the node referred to by current. Show the sentence,
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// highlighting the position of the node referred to by
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// current.
</span>        sentence.Remove(mark1);
        sentence.AddBefore(current, mark1);
        DisplayNode(current);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Remove the node referred to by current. If you try to show
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// its position now, the DisplayNode method prints a message.
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Add the node after the node referred to by mark2, and
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// display the sentence, highlighting current.
</span>        sentence.Remove(current);
        DisplayNode(current);
        sentence.AddAfter(mark2, current);
        DisplayNode(current);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// The Remove method finds and removes the first node that
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// that has the specified value.
</span>        sentence.Remove(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"old"</span>);
        Display(sentence);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// When the linked list is cast to ICollection(Of String),
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// the Add method adds a node to the end of the list.
</span>        sentence.RemoveLast();
        ICollection&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; icoll <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> sentence;
        icoll.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"rhinoceros"</span>);
        Display(sentence);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create an array with the same number of elements as the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// linked list.
</span>        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nCopy the list to an array."</span>);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[] sArray <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[sentence.Count];
        sentence.CopyTo(sArray, 0);

        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> s <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> sArray )
        {
            Console.WriteLine(s);


        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Release all the nodes.
</span>        sentence.Clear();



    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Display(LinkedList&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; words)
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> word <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> words )
        {
            Console.Write(word <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">" "</span>);

        Console.WriteLine();


    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> DisplayNode(LinkedListNode&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; node)
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (node.List==<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>)
        {
            Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Node \"{0\" is not in a list."</span>,
                node.Value);
            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span>;


        StringBuilder result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> StringBuilder(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"("</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> node.Value <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">")"</span>);
        LinkedListNode&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; nodeP <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> node.Previous;

        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span> (nodeP !<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>)
        {
            result.Insert(0, nodeP.Value <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">" "</span>);
            nodeP <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> nodeP.Previous;


        node <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> node.Next;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span> (node !<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>)
        {
            result.Append(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">" "</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> node.Value);
            node <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> node.Next;


        Console.WriteLine(result);



<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//This code example produces the following output:
//
//the fox jumped over the dog
//sentence.Contains("jumped") = True
//today the fox jumped over the dog
//the fox jumped over the dog today
//the fox jumped over the dog yesterday
//yesterday the fox jumped over the dog
//the fox jumped over (the) dog
//the fox jumped over (the) lazy old dog
//the (fox) jumped over the lazy old dog
//the quick brown (fox) jumped over the lazy old dog
//the quick brown fox jumped over the lazy old (dog)
//Exception message: The LinkedList node belongs a LinkedList.
//the quick brown jumped over the lazy old fox (dog)
//Node "dog" is not in a list.
//the quick brown (dog) jumped over the lazy old fox
//the quick brown dog jumped over the lazy fox
//the quick brown dog jumped over the lazy rhinoceros
//
//Copy the list to an array.
//the
//quick
//brown
//dog
//jumped
//over
//the
//lazy
//rhinoceros
</span></PRE>
</div>

<br /><br />
<a href="javascript:Toggle('queue')">Queues - FIFO</a>
<div id="queue" class="codearea">
<PRE><span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// new to .NET 2.0
</span>
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Collections.Generic;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Example
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main()
    {
        Queue&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; numbers <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Queue&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt;();
        numbers.Enqueue(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>);
        numbers.Enqueue(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>);
        numbers.Enqueue(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"three"</span>);
        numbers.Enqueue(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"four"</span>);
        numbers.Enqueue(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"five"</span>);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// A queue can be enumerated without disturbing its contents.
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> number <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> numbers )
        {
            Console.WriteLine(number);


        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nDequeuing '{0'"</span>, numbers.Dequeue());
        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Peek at next item to dequeue: {0"</span>,
            numbers.Peek());
        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Dequeuing '{0'"</span>, numbers.Dequeue());

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create a copy of the queue, using the ToArray method and the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// constructor that accepts an IEnumerable&lt;T&gt;.
</span>        Queue&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; queueCopy <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Queue&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt;(numbers.ToArray());

        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nContents of the first copy:"</span>);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> number <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> queueCopy )
        {
            Console.WriteLine(number);


        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create an array twice the size of the queue and copy the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// elements of the queue, starting at the middle of the
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// array.
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[] array2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[numbers.Count <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">*</span> 2];
        numbers.CopyTo(array2, numbers.Count);

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create a second queue, using the constructor that accepts an
</span>        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// IEnumerable(Of T).
</span>        Queue&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt; queueCopy2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Queue&lt;<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>&gt;(array2);

        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nContents of the second copy, with duplicates and nulls:"</span>);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>( <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span> number <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> queueCopy2 )
        {
            Console.WriteLine(number);


        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nqueueCopy.Contains(\"four\") = {0"</span>,
            queueCopy.Contains(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"four"</span>));

        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nqueueCopy.Clear()"</span>);
        queueCopy.Clear();
        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nqueueCopy.Count = {0"</span>, queueCopy.Count);



<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/* This code example produces the following output:

one
two
three
four
five

Dequeuing 'one'
Peek at next item to dequeue: two
Dequeuing 'two'

Contents of the copy:
three
four
five

Contents of the second copy, with duplicates and nulls:



three
four
five

queueCopy.Contains("four") = True

queueCopy.Clear()

queueCopy.Count = 0
 */</span></PRE>
</div>

<br /><br />
<a href="javascript:Toggle('arraylist')">Array Lists</a>
<div id="arraylist" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Collections;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> TestArrayList {
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main() {
        ArrayList myList <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> ArrayList();
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i;

        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span>(i=0; i&lt;5; i++)
            myList.Add(i);

        myList.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Hello"</span>);

        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span>(i=0; iConsole.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Array Index [{0}]: {1}"</span>, i, myList[i].ToString());
    }
}</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('hashtable')">Hash Tables</a>
<div id="hashtable" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Collections;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> TestArrayList
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main()
    {
        Hashtable h <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Hashtable();

        h.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Key1"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Value1"</span>);
        h.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Key2"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Value2"</span>);
        h.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Key3"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Value3"</span>);
        h.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Key4"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Value4"</span>);
        h.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Key5"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Value5"</span>);

        Console.WriteLine(h.ContainsKey(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Key5"</span>))
        Console.WriteLine(h.ContainsValue(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Value2"</span>));

        IDictionaryEnumerator en <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> h.GetEnumerator();

        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span> (en.MoveNext())
        {
             Console.WriteLine(en.Key <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">" : "</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> en.Value);
        }
    }
}</PRE>
</div>