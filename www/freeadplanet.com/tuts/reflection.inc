<a href="javascript:Toggle('reflectionassembly')">Reflection - Discovery on a Load Assembly</a>
<div id="reflectionassembly" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Reflection;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> Programming_CSharp
{
	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Tester
	{
		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main()
		{
			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// what is in the assembly
</span>			Assembly a <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Assembly.Load(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Mscorlib.dll"</span>);
			Type[] types <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> a.GetTypes(  );
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>(Type t <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> types)
			{
				Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Type is {0}"</span>, t);
			}
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"{0} types found"</span>, types.Length);
		}
	}
}
</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('reflectionontypes')">Reflection - Discovery on Member Types</a>
<div id="reflectionontypes" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Reflection;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> Programming_CSharp
{
	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Tester
	{
		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main(  )
		{
			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// examine a single object
</span>			Type theType <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Type.GetType(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"System.Reflection.Assembly"</span>);
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nSingle Type is {0}\n"</span>, theType);

			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// get all the members
</span>			MemberInfo[] mbrInfoArray <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> theType.GetMembers(  );
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span> (MemberInfo mbrInfo <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> mbrInfoArray )
			{
				Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"{0} is a {1}"</span>, mbrInfo, mbrInfo.MemberType);
			}
		}
	}
}


<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/* EXAMPLE... output is actually much longer

System.String s_localFilePrefix is a Field
Boolean IsDefined(System.Type) is a Method
Void .ctor(  ) is a Constructor
System.String CodeBase  is a Property
System.String CopiedCodeBase  is a Property

You might want to focus on methods only, excluding the fields, properties, and so forth. To do so, you remove the call to GetMembers( ):

MemberInfo[] mbrInfoArray =  theType.GetMembers(BindingFlags.LookupAll);

and add a call to GetMethods( ):

mbrInfoArray = theType.GetMethods(  );

The output now is nothing but the methods:

Output (excerpt):
Boolean Equals(System.Object) is a Method
System.String ToString(  ) is a Method
System.String CreateQualifiedName(
      System.String, System.String) is a Method
System.Reflection.MethodInfo get_EntryPoint(  ) is a Method

Finding particular type members

Finally, to narrow it down even further, you can use the FindMembers method to find particular members of the type.
For example, you can narrow your search to methods whose names begin with the letters Get.

To narrow the search, you use the FindMembers method, which takes four parameters: MemberTypes, BindingFlags, MemberFilter, and object.

MemberTypes
    A MemberTypes object that indicates the type of the member to search for. These include All,
    Constructor, Custom, Event, Field, Method, Nestedtype, Property, and TypeInfo. You will also use the MemberTypes.Method to find a method.

BindingFlags
    An enumeration that controls the way searches are conducted by reflection. There are a great many
    BindingFlag values, including IgnoreCase, Instance, Public, Static, and so forth. The BindingFlags
    default member indicates no binding flag, which is what you want because you do not want to restrict the binding.

MemberFilter
    A delegate (see Chapter 12) that is used to filter the list of members in the MemberInfo array of objects.
    The filter you'll use is Type.FilterName, a field of the Type class used for filtering on a name.

Object
    A string value that will be used by the filter. In this case you'll pass in "Get*" to match only those methods that begin with the letters Get.
*/</span>

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Reflection;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> Programming_CSharp
{
	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Tester
	{
		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main(  )
		{
			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// examine a single object
</span>			Type theType <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Type.GetType(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"System.Reflection.Assembly"</span>);

			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// just members which are methods beginning with Get
</span>			MemberInfo[] mbrInfoArray <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span>	theType.FindMembers(MemberTypes.Method, BindingFlags.Default, Type.FilterName, <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Get*"</span>);
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span> (MemberInfo mbrInfo <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> mbrInfoArray )
			{
				Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"{0} is a {1}"</span>, mbrInfo, mbrInfo.MemberType);
			}
		}
	}
}

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/*
Output (excerpt):
System.Type[] GetTypes(  ) is a Method
System.Type[] GetExportedTypes(  ) is a Method
System.Type GetType(System.String, Boolean) is a Method
System.Type GetType(System.String) is a Method
System.Reflection.AssemblyName GetName(Boolean) is a Method
System.Reflection.AssemblyName GetName(  ) is a Method
Int32 GetHashCode(  ) is a Method
*/</span>
</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('reflectmeta')">Reflection - Viewing MetaData</a>
<div id="reflectmeta" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Reflection;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> Programming_CSharp
{
	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Tester
	{
		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main(  )
		{
			MyMath mm <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> MyMath(  );
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Calling DoFunc(7). Result: {0}"</span>,	mm.DoFunc1(7));

			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// get the member information and use it to retrieve the custom attributes
</span>			System.Reflection.MemberInfo inf <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> typeof(MyMath);
			object[] attributes;
			attributes <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> inf.GetCustomAttributes(typeof(BugFixAttribute), <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">false</span>);

			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// iterate through the attributes, retrieving the properties
</span>			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">foreach</span>(Object attribute <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">in</span> attributes)
			{
				BugFixAttribute bfa <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> (BugFixAttribute) attribute;
				Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\nBugID: {0}"</span>, bfa.BugID);
				Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Programmer: {0}"</span>, bfa.Programmer);
				Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Date: {0}"</span>, bfa.Date);
				Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Comment: {0}"</span>, bfa.Comment);
			}
		}
	}
}

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/*
Output:
Calling DoFunc(7). Result: 9.3333333333333339

BugID: 121
Programmer: Jesse Liberty
				Date: 01/03/05
Comment:

BugID: 107
Programmer: Jesse Liberty
				Date: 01/04/05
Comment: Fixed off by one errors
*/</span>

</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('reflectlatebind')">Reflection - Late Binding or Dynamic Invocation</a>
<div id="reflectlatebind" class="codearea">
<PRE><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Reflection;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> Programming_CSharp
{
	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> Tester
	{
		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main(  )
		{
			Type theMathType <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Type.GetType(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"System.Math"</span>);
			Object theObj <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Activator.CreateInstance(theMathType);

			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// array with one member
</span>			Type[] paramTypes <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Type[1];
			paramTypes[0]<span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Type.GetType(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"System.Double"</span>);

			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Get method info for Cos(  )
</span>			MethodInfo CosineInfo <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> theMathType.GetMethod(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Cos"</span>,paramTypes);

			<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// fill an array with the actual parameters
</span>			Object[] parameters <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Object[1];
			parameters[0] <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 45;
			Object returnVal <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 	CosineInfo.Invoke(theObj,parameters);
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The cosine of a 45 degree angle {0}"</span>, returnVal);

		}
	}
}

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/*
 That was a lot of work just to invoke a single method.
 The power, however, is that you can use reflection to discover an assembly on the user's machine,
 use reflection to query what methods are available, and then use reflection to invoke one of those members dynamically!
*/</span>
</PRE>
</div>

<br /><br />
<a href="javascript:Toggle('reflectemit')">Reflection - Emit</a>
<div id="reflectemit" class="codearea">
<PRE><span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/*
Reflection emit allows you to skip a few steps and just "emit" the op codes directly.
This is writing assembly code directly from your C# program and then invoking the result.
It just doesn't get any cooler than that.
*/</span>

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Diagnostics;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.IO;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Reflection;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Reflection.Emit;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Threading;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">namespace</span> Programming_CSharp
{
   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// used to benchmark the looping approach
</span>   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> MyMath
   {
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// sum numbers with a loop
</span>      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> DoSumLooping(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> initialVal)
      {
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span>(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 1; i &lt;= initialVal; i++)
         {
            result += i;
         }
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> result;
      }
   }

   <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// declare the interface
</span>   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> interface IComputer
   {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> ComputeSum(  );
   }

   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> ReflectionTest
   {
      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// the private method which emits the assembly
</span>      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// using op codes
</span>      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">private</span> Assembly EmitAssembly(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> theValue)
      {
         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create an assembly name
</span>         AssemblyName assemblyName <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> AssemblyName(  );
         assemblyName.Name <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"DoSumAssembly"</span>;

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create a new assembly with one module
</span>         AssemblyBuilder newAssembly <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> Thread.GetDomain(  ).DefineDynamicAssembly(assemblyName, AssemblyBuilderAccess.Run);
         ModuleBuilder newModule <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> newAssembly.DefineDynamicModule(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Sum"</span>);

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//  Define a public class named "BruteForceSums" in the assembly.
</span>         TypeBuilder myType <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> newModule.DefineType(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"BruteForceSums"</span>, TypeAttributes.Public);

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Mark the class as implementing IComputer.
</span>         myType.AddInterfaceImplementation(typeof(IComputer));

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Define a method on the type to call. Pass an
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// array that defines the types of the parameters,
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// the type of the return type, the name of the
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// method, and the method attributes.
</span>         Type[] paramTypes <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> Type[0];
         Type returnType <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> typeof(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span>);
         MethodBuilder simpleMethod <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> myType.DefineMethod(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"ComputeSum"</span>, MethodAttributes.Public | MethodAttributes.Virtual, returnType, paramTypes);

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Get an ILGenerator. This is used
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// to emit the IL that you want.
</span>         ILGenerator generator <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> simpleMethod.GetILGenerator(  );

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Emit the IL that you'd get if you
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// compiled the code example
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// and then ran ILDasm on the output.
</span>
         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Push zero onto the stack. For each 'i'
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// less than 'theValue',
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// push 'i' onto the stack as a constant
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// add the two values at the top of the stack.
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// The sum is left on the stack.
</span>         generator.Emit(OpCodes.Ldc_I4, 0);
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 1 ; i &lt;= theValue; i++)
         {
            generator.Emit(OpCodes.Ldc_I4, i);
            generator.Emit(OpCodes.Add);

         }

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// return the value
</span>         generator.Emit(OpCodes.Ret);

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//Encapsulate information about the method and
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//provide access to the method's metadata
</span>         MethodInfo computeSumInfo <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> typeof(IComputer).GetMethod(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"ComputeSum"</span>);

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// specify the method implementation.
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Pass in the MethodBuilder that was returned
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// by calling DefineMethod and the methodInfo
</span>         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// just created
</span>         myType.DefineMethodOverride(simpleMethod, computeSumInfo);

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Create the type.
</span>         myType.CreateType(  );
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> newAssembly;
      }

      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// check if the interface is null
</span>      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// if so, call Setup.
</span>      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> double DoSum(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> theValue)
      {
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">if</span> (theComputer == <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>)
         {
            GenerateCode(theValue);
         }

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// call the method through the interface
</span>         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">return</span> (theComputer.ComputeSum(  ));
      }

      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// emit the assembly, create an instance
</span>      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// and get the interface
</span>      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> GenerateCode(<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> theValue)
      {
         Assembly theAssembly <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> EmitAssembly(theValue);
         theComputer <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> (IComputer)theAssembly.CreateInstance(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"BruteForceSums"</span>);
      }

      <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// private member data
</span>      IComputer theComputer <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">null</span>;
   }

   <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> TestDriver
   {
      <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main(  )
      {
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">const</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> val <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 2000;  <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// Note 2,000
</span>
         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// 1 million iterations!
</span>         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">const</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> iterations <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 1000000;
         double result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0;

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// run the benchmark
</span>         MyMath m <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> MyMath(  );
         DateTime startTime <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> DateTime.Now;
		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0; i &lt; iterations; i++)
		{
			result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> m.DoSumLooping(val);
		}

         TimeSpan elapsed <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> DateTime.Now <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> startTime;
         Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Sum of ({0}) = {1}"</span>, val, result);
         Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Looping. Elapsed milliseconds: "</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> elapsed.TotalMilliseconds <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">" for {0} iterations"</span>, iterations);

         <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// run our reflection alternative
</span>         ReflectionTest t <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> ReflectionTest(  );

         startTime <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> DateTime.Now;
         <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> 0; i &lt; iterations; i++)
         {
            result <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> t.DoSum(val);
         }

         elapsed <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> DateTime.Now <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">-</span> startTime;
         Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Sum of ({0}) = {1}"</span>,val, result);
         Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Brute Force. Elapsed milliseconds: "</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> elapsed.TotalMilliseconds <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> <span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">" for {0} iterations"</span>, iterations);
      }
   }
}

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">/*
OK, I didn't say it was easy, but it is really cool, and the resulting code runs very fast.
The normal loop runs 1,000,000 iterations in 11.5 seconds, but the emitted code runs in .4 second! A full 3,000% faster.

Output:
Sum of (2000) = 2001000
Looping. Elapsed milliseconds:
11468.75 for 1000000 iterations
Sum of (2000) = 2001000
Brute Force. Elapsed milliseconds:
406.25 for 1000000 iterations

Reflection emit is a powerful technique for emitting op codes.
Although today's compilers are very fast and today's machines have
lots of memory and processing speed, it is comforting to know that
when you must, you can get right down to the virtual metal.
*/</span></PRE>
</div>

<br /><br />
<a href="ch18_attrib_reflections.html" target="_blank">Reflection - From O'reilly Chapter 18</a>