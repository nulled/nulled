<a href="javascript:Toggle('clientserver')">Client / Server - Simple</a>
<div id="clientserver" class="codearea">
<PRE><span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// client.cs
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.IO;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Net;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Text;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Net.Sockets;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> clnt {

	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main() {

		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">try</span> {
			TcpClient tcpclnt <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> TcpClient();
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Connecting....."</span>);

			tcpclnt.Connect(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"192.168.0.2"</span>,8001); <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// use the ipaddress as in the server program
</span>
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Connected"</span>);
			Console.Write(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Enter the string to be transmitted : "</span>);

			String str=Console.ReadLine();
			Stream stm <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> tcpclnt.GetStream();

			ASCIIEncoding asen= <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> ASCIIEncoding();
			byte[] ba=asen.GetBytes(str);
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Transmitting....."</span>);

			stm.Write(ba,0,ba.Length);

			byte[] bb=<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> byte[100];
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> k=stm.Read(bb,0,100);

			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i=0;i k;i++)
				Console.Write(Convert.ToChar(bb[i]));
			
			tcpclnt.Close();
		}

		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">catch</span> (Exception e) {
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Error..... "</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> e.StackTrace);
		}
	}

}

<span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">// server.cs
</span><span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Text;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Net;
<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">using</span> System.Net.Sockets;

<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">class</span> serv {

	<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">public</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">static</span> <span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">void</span> Main() {

		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">try</span> {
			IPAddress ipAd <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">=</span> IPAddress.Parse(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"192.168.0.2"</span>); <span style="color: Green; font-family: Courier New; font-size: 11px; background-color: White">//use local m/c IP address, and use the same in the client
</span>			TcpListener myList=<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> TcpListener(ipAd,8001);

			myList.Start();

			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The server is running at port 8001..."</span>);
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The local End point is  :"</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> myList.LocalEndpoint );
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Waiting for a connection....."</span>);

			Socket s=myList.AcceptSocket();
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Connection accepted from "</span>+s.RemoteEndPoint);

			byte[] b=<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> byte[100];
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> k=s.Receive(b);
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Recieved..."</span>);
			<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">for</span> (<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">int</span> i=0;i k;i++)
				Console.Write(Convert.ToChar(b[i]));

			ASCIIEncoding asen=<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">new</span> ASCIIEncoding();
			s.Send(asen.GetBytes(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"The string was recieved by the server."</span>));
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"\\nSent Acknowledgement"</span>);

			s.Close();
			myList.Stop();

		}

		<span style="color: Blue; font-family: Courier New; font-size: 11px; background-color: White">catch</span> (Exception e) {
			Console.WriteLine(<span style="color: #666666; font-family: Courier New; font-size: 11px; background-color: #ededed">"Error..... "</span> <span style="color: Red; font-family: Courier New; font-size: 11px; background-color: White">+</span> e.StackTrace);
		}
	}
}
</PRE>
</div>