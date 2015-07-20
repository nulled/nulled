<a href="http://msdn.microsoft.com/library/default.asp?url=/library/en-us/csspec/html/CSharpSpecStart.asp" target="_blank">MSDN C# Manual</a>
<br /><br />
<a href="http://www.csharp-station.com/Tutorial.aspx" target="_blank">C# Lessons</a>
<br /><br />
<a href="http://www.functionx.com/csharp/Lesson01.htm" target="_blank">More C# Lessons</a>
<br /><br />
<a href="http://msdn2.microsoft.com/en-us/vcsharp/aa336745.aspx" target="_blank">C# Future</a>
<br /><br />
<a href="http://www.csharp-home.com/articles/180/" target="_blank">Generic Objects</a>
<br /><br />
<a href="http://www.csharpfriends.com/Demos/color_code.aspx" target="_blank">C# Code Color Parser for HTML</a>
<br /><br />
<a href="http://www.blackwasp.co.uk/" target="_blank">C# Fundementals + Tricks - Great Site</a>















<br /><br />
<a href="javascript:Toggle('reference')">C# Reference Sheet</a>
<div id="reference" class="codearea">
<PRE><span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// CLASS1.CS -- Syntax-at-a-Glance for the C# programming language.
// A quick code reference for programmers who work in many languages.
// Executable code, minimal comments document the essence of the language.
// Copyright (C) 2001 St
</span>ructureByDesign.  All Rights Reserved.

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Collections;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.IO;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> StructureByDesign.Syntax
{
<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/********************************************************************/</span>
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Class1: Object
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> Main(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">string</span>[] args)       <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Entry point.
</span>    {
        System.Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Hello"</span>);
        Class2 aclass2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Class2();
        aclass2.run();
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> 0;
    }
}

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/********************************************************************/</span>
interface Interface1
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> run();
}

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/********************************************************************/</span>
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Class2: Class1, Interface1
{
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">const</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> CONSTANT <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 1;          <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Access not restricted, implicitly static.
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> m_intPrivateField;          <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Access limited to containing type.
</span>    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> Class2() : <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">base</span>()                <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Constructor.
</span>    {
        initialize();
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">protected</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> initialize()             <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Object initialization.
</span>    {                                       <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Access limited to containing class or types derived.
</span>        Number <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 1;
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">protected</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> Number                    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Language property feature.
</span>    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">get</span>
        {
            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> m_intPrivateField;
        }
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">set</span>
        {
            m_intPrivateField <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> value;      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Implicit parameter.
</span>        }
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> run()
    {
        anonymousCode();
        arrays();
        collections();
        comparison();
        control();
        filesStreamsAndExceptions();
        numbersAndMath();
        primitivesAndConstants();
        runtimeTyping();
        strings();
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> anonymousCode()
    {
        Delegate adelegate <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Delegate(Run);
        adelegate();
    }
    delegate <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Delegate();
    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Run()
    {
        Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Run"</span>);
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> arrays()
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span>[] arrayOfInts <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        arrayOfInts[0] <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 9;
        assert(arrayOfInts[0] == arrayOfInts[9]);

        String[] arrayOfStrings <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> String[10];
        assert(arrayOfStrings[0] == <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>);
        assert(arrayOfStrings.Length == 10);

        arrayOfStrings <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> String[] { <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span> };

        byte[,] arrayOfBytes <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> { {0,0,0},
                                 {0,1,2},
                                 {0,2,4}};
        assert(arrayOfBytes[2,2] == 4);
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> collections()
    {
        IList ailist <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> ArrayList();
        ailist.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"zero"</span>); ailist.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>); ailist.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"three"</span>);
        ailist[2] <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>;
        assert(ailist[2].Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>));
        ailist.Remove(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>);
        ((ArrayList)ailist).Sort();
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span>(IEnumerator aie <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> ((ArrayList)ailist).GetEnumerator(); aie.MoveNext(); )
            ;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>(String astring <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> ailist)
            ;

        IDictionary aidictionary <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Hashtable();
        aidictionary.Add(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"key"</span>, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"value"</span>);
        assert(aidictionary[<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"key"</span>].Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"value"</span>));

        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Set not available.
</span>    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> comparison()
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> aint1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 1;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> aint2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 2;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> aint <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 1;
        String astring1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>;
        String astring2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>;
        String astring <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> astring1;

        assert(aint == aint1);
        assert(aint1 !<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> aint2);
        assert(astring == astring1);
        assert(astring1 == String.Copy(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>));         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// For strings == is overloaded to compare values.
</span>        assert(!astring1.Equals(astring2));
        assert(astring1.Equals(String.Copy(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>)));

        astring <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (astring !<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span> &amp;&amp; astring.Length &gt; 0)      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Conditional evaluation.
</span>            assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>);

        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (aint2 &lt; 0 || 1 &lt; aint2)
            assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>);
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> control()
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>)
            assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
            assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>);
        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/////
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">switch</span> ('b') {
            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">case</span> 'a':
                assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>);
                <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">break</span>;
            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">case</span> 'b':
                assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>);
                <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">break</span>;
            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">default</span>:
                assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>);
                <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">break</span>;
        }
        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/////
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> ai1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0; ai1 &lt; 10; ai1++)
            assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>);
        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/////
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> ai <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span> (ai &lt; 10) {
            assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">true</span>);
            ai++;
        }
        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/////
</span>        do
            ai--;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span> (ai &gt; 0);
        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/////
</span>        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> x <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0; x &lt; 10; x++)        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Labeled break/continue not available.
</span>            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> y <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0; y &lt; 10; y++)
                <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (x == 9)
                    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">break</span>;
                <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">else</span>
                    continue;
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> filesStreamsAndExceptions()
    {
        FileInfo afileinfo <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> FileInfo(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"list.txt"</span>);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">try</span> {
            StreamWriter asw <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> StreamWriter(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"list.txt"</span>);
            asw.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"line"</span>);
            asw.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"line"</span>);
            asw.Close();

            assert(afileinfo.Exists);

            StreamReader asr <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> StreamReader(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"list.txt"</span>);
            String astringLine;
            <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">while</span> ((astringLine <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> asr.ReadLine()) !<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>)
                assert(astringLine.Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"line"</span>));
            asr.Close();
        } <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">catch</span> (IOException aexception) {
            System.Console.WriteLine(aexception.Message);
            throw <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> NotSupportedException();
        }
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">finally</span> {
            afileinfo.Delete();
        }
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> numbersAndMath()
    {
        assert(Int32.Parse(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"123"</span>) == 123);
        assert(123.ToString().Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"123"</span>));

        assert(Math.PI.ToString(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"n3"</span>).Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"3.142"</span>));

        assert(Int32.MaxValue &lt; Int64.MaxValue);

        assert(Math.Abs(Math.Sin(0) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> 0) &lt;= Double.Epsilon);
        assert(Math.Abs(Math.Cos(0) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> 1) &lt;= Double.Epsilon);
        assert(Math.Abs(Math.Tan(0) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> 0) &lt;= Double.Epsilon);

        assert(Math.Abs(Math.Sqrt(4) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> 2) &lt;= Double.Epsilon);
        assert(Math.Abs(Math.Pow(3,3) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> 27) &lt;= Double.Epsilon);

        assert(Math.Max(0,1) == 1);
        assert(Math.Min(0,1) == 0);

        assert(Math.Abs(Math.Ceiling(9.87) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> 10.0) &lt;= Double.Epsilon);
        assert(Math.Abs(Math.Floor(9.87) <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> 9.0) &lt;= Double.Epsilon);
        assert(Math.Round(9.87) == 10);

        Random arandom <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Random();
        double adouble <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> arandom.NextDouble();
        assert(0.0 &lt;= adouble &amp;&amp; adouble &lt; 1.0);
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> aint <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> arandom.Next(10);
        assert(0 &lt;= aint &amp;&amp; aint &lt; 10);
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    enum Season: byte { Spring=0, Summer, Fall, Winter };

    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> primitivesAndConstants()
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> abool <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>;
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">char</span> achar <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 'A';           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 16 bits, Unicode
</span>
        byte abyte <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0x0;           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 8 bits, unsigned, hex constant
</span>        sbyte asbyte <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 8 bits, signed
</span>
        short ashort <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 16 bits, signed
</span>        ushort aushort <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 16 bits, unsigned
</span>
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> aint <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;               <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 32 bits, signed
</span>        uint aunit <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;             <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 32 bits, unsigned
</span>
        long along <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0L;            <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 64 bits, signed
</span>        ulong aulong <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;           <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 64 bits, unsigned
</span>
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">float</span> afloat <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0.0F;        <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 32 bits
</span>        double adouble <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0.0;       <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 64 bits
</span>
        decimal adecimal <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;       <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 128 bits, financial calculations
</span>
        Season aseason <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Season.Fall;
        assert((byte)aseason == 2);
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> runtimeTyping()
    {
        assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span>[] { 1 } is <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span>[]);
        assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> ArrayList() is ArrayList);

        assert((<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> ArrayList()).GetType() == typeof(ArrayList));
        assert(typeof(Int32) is Type);      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Type of primitive type.
</span>
        assert(Type.GetType(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"System.Collections.ArrayList"</span>) == typeof(ArrayList));
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> strings()
    {
        String astring1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one"</span>;
        String astring2 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"TWO"</span>;

        assert((astring1 <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"/"</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> astring2).Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"one/TWO"</span>));
        assert(astring2.ToLower().Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>));   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Equals ignoring case not available.
</span>        assert(astring1.Length == 3);
        assert(astring1.Substring(0,2).Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"on"</span>));
        assert(astring1[2] == 'e');
        assert(astring1.ToUpper().Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"ONE"</span>));
        assert(astring2.ToLower().Equals(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"two"</span>));
        assert(astring1.CompareTo(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"p"</span>) &lt; 0);
        assert(astring1.IndexOf('e') == 2);
        assert(astring1.IndexOf(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"ne"</span>) == 1);
        assert(astring1.Trim().Length == astring1.Length);

        assert(Char.IsDigit('1'));
        assert(Char.IsLetter('a'));
        assert(Char.IsWhiteSpace('\t'));
        assert(Char.ToLower('A') == 'a');
        assert(Char.ToUpper('a') == 'A');
    }
    <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//////////////////////////////////////////////////////////////
</span>    <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> assert(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">bool</span> abool)
    {
        <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (!abool)
            throw <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Exception(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"assert failed"</span>);
    }
}
}</PRE>
</div>