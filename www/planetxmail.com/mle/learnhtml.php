<table width="610" cellpadding="3" cellspacing="1" align="center">
  <tr>
    <td colspan="2">
    	<center>
      <h2>Learning Basic HTML</h2>
      </center>
      Anyone that works on the internet needs to understand BASIC HTML.
      <br><br>
      HTML is very simple and is designed logically.  I do not think you need to be a GURU at it, but understanding
      the very basics will help you down the road.  When reading emails and typing in a URL/Link to another
      person's websites, means you are using HTML.
      <br><br>
      The first thing you ought to know is what <b>http://</b> means, as you see this in every web link.  <b>http://</b> means
      <b>H</b>yper <b>T</b>ext <b>T</b>ransport <b>P</b>rotocol.  It just means that HTML is nothing more than TEXT that is "transported" vai the internet
      based on a protocol. ( A protocol is nothing more than the set of rules that governs HOW the data is managed so that
      all servers know how to use the incoming data which is the HTML or website data. )
      <br><br>
      Let's not get too wrapped up in it, but it's at least good to know why it's there and what it stands for.  Other times you
      may see <b>ftp://</b> which stands for <b>F</b>ile <b>T</b>ransfer <b>P</b>rotocol.  This means the same thing as http except it is meant for
      transferring files of all sizes in stead of just a text stream.
      <br><br>
      Next, you typically see <b>www</b> in front of a URL... this means <b>W</b>orld <b>W</b>ide <b>W</b>eb and is standard.  Then comes the <b>whatever.com</b>
      which is the domain or server were the web site resides.
      <br><br>
      The <b>.com</b> part of a domain name is run by the internet higher powers that be.  Along with all the .gov .org .net, and so on.
      You may have also seen .uk .fin each country has its own domain governed by that country. .uk being the United Kingdom and .fin being
      Finland. <a href="http://users.swing.be/hdepra/internet/domains.html" target="_BLANK">Click Here</a> to read more indepth about all the Top Domains out there.
      <br><br>
      So that describes what a URL/Link is at its parts.
      <br><br>
      <h3>Basic Web Pages</h3>
      There may come a time when you need to look through a web pages source code.  Either to find a link or if you just want to design
      your own pages.  Or make modifications to an existing.  I think that its generally a good idea to at least understand the most basic
      outline ALL web pages go by.
      <br><br>
      Its very simple.
      <pre>
      &lt;html&gt;
      &lt;head&gt;
      &lt;title&gt;Title of Browser&lt;/title&gt;
      &lt;/head&gt;
      &lt;body&gt;
      &lt;table&gt;
        &lt;tr&gt;
          &lt;td&gt;
           Web page content goes here.
          &lt;/td&gt;
        &lt;/tr&gt;
      &lt;/table&gt;
      &lt;/body&gt;
      &lt;/html&gt;
      </pre>
      Above is the MOST BASIC web page there is.  All web pages are based on this simple format.  HTML means Hyper Text Markup Language.
      The name states exactly what it is.  HTML is nothing more than TEXT that uses MARKUP ( tags ) and therefore is a language.  The word
      HYPER I guess would be a fansy way of saying that the internet is light speed since it travels through wires and so is HYPER actively
      fast!
      <br><br>
      Well if you quickly study the over example you will notice all the tags like head, title, body, etc.  These are called TAGS.  You
      may also have noticed that each "tag" has partnering tag with a "/" in it.  Meaning  /head, /title, /body, etc.  All tags need a
      closing tag to tell the system you are done using that particular tag.  So, hence we close all tags with a "/".
      <br><br>
      All web pages MUST begin with the tag HTML, have a HEAD and a TITLE is optional but always better than not having one.
      <br><br>
      In the HEAD is where you can place Javascripts, Cascading Style Sheets and Meta Tags.  But, all those things mentioned are for
      doing fansy stuff and not really meaningful to a beginner.  What I want you to get out this now is that BASIC framework ALL
      web pages take on.
      <br><br>
      After the HEAD and TITLE you notice the BODY tag.  This is where our content, or what will be presented to the surfer, will see.
      Within the BODY you can format your web page anyway you like.  There are three ways to organize and place data. They are:
      <ul>
      	<li>TABLE</li>
      	<li>TR - <b>T</b>able <b>R</b>ow</li>
      	<li>TD - <b>T</b>able <b>D</b>ata</li>
      </ul>
      There are many more other advanced tags but for now let's stay to the basics. First is the TABLE tag.  This can be thought of
      as any Platform/Table from which to work from.  A canvas if you will.  You can have more than one TABLE in an html page, buy typically
      you will just need one TABLE, in which this TABLE will content your web page.
      <br><br>
      Now, with in the TABLE you can organize your web page content vai a CELL system or GRID system.  Where each CELL contains maybe an
      image, or text, or links... etc.  Since, its a CELL/GRID system you can "break up" the table into smaller parts where in each part you
      place your content on the TABLE where you want it to be.
      <br><br>
      So, if its a GRID/CELL system, like a checker/chess board that means there will be two elements to that.  ROWS and COLUMNS.  Where
      the ROWS and COLUMNS combine to make up the GRID which sits in the TABLE.
      <br><br>
      An example of a 2 by 2 TABLE with 2 ROWs and 2 COLUMNs is below:
      <br><br>
      <table border="1" align="center">
      	<tr>
      		<td>Cell 1</td>
      		<td>Cell 2</td>
      	</tr>
      	<tr>
      		<td>Cell 3</td>
      		<td>Cell 4</td>
      	</tr>
      </table>
      <br>
      And this is what the HTML looks like for the above 2x2 TABLE.
      <pre>
      &lt;table border="1" align="center"&gt;
        &lt;tr&gt;
          &lt;td&gt;Cell 1&lt;/td&gt;
          &lt;td&gt;Cell 2&lt;/td&gt;
        &lt;/tr&gt;
        &lt;tr&gt;
          &lt;td&gt;Cell 3&lt;/td&gt;
          &lt;td&gt;Cell 4&lt;/td&gt;
        &lt;/tr&gt;
      &lt;/table&gt;
      </pre>
			<br>
			You will notice <b>border="1" align="center"</b> found in the TABLE tag... do not worry too much about it now, just know that
			this tells the table to be "centered" and have a "border" size of 1.
			<br><br>
			Anyways, you will notice that I am using the TR and TD html tags to create the GRID.  TR means Table Row and TD means Table Data.
			TD, Table Data, can be thought of as the COLUMNS of the GRID and TR can be thought of as the ROWs of the grid.  All TR and TD
			tags should reside in a TABLE. Also, keep in mind that the TABLE, of course, would also have the HTML, HEAD, BODY tags. Since,
			I am just trying to illustrate how the GRID system is created in HTML, I left that part out.
			<br><br>
			Study the Picture of the Grid and then observe my explaination and try to see how this is working.  If you failed simple geometry
			in High School or have problems learning new things, this may be a challedge for some.  If you get a headache and just wanna say
			forget this HTML crap altogether, do not worry, even "I" felt that when I first delved into all this HTML/Coding stuff.
			IT all depends how interested a person really is in learning.
			<br><br>
			Anyhow, if you think about it, that's all there is to web pages.  IF you spent 30 minutes REALLY trying to grasp what was just explained
			it just may sink in.  If it does not and you have a headache, you can always take a break come back and try again with a fresh mindset.
			Remember, that what was just explained is how the INTERNET is built!  It's all TABLEs and TDs and TRs in a BODY which has a HEAD and it
			all begins with the HTML tag. :)
			<h3>Hyper Links</h3>
			Once you feel somewhat confortable with how HTML web pages are Structured and Organized lets talk about URLs/HYPER Links.  A URL
			or Hyper Link is just something you can click on that will take you to another web page!  It is what web designers use to connect
			everything together.  It is what made the internet so great and HUGE, for that matter.  This is what a URL/HYPER Link looks like:
			<br>
			<pre>
      &lt;a href="http://www.planetxmail.com"&gt;Example Hyper Link/URL&lt;/a&gt;
			</pre>
			<a href="http://www.planetxmail.com" target="_BLANK">Example Hyper Link/URL</a>
			<br><br>
			A HYPER link has two parts.  First is the destination of where you are brought to if you decide to click the link.
			Second, is the Text that describes the Link.  So, the first part is what is "hidden" and the second part is what you see
			on the webpage.
			<br><br>
			<b>Example Hyper Link/URL</b> will take you to <b>http://www.planetxmail.com</b>.  The <b>a</b> means anchor, the <b>href</b> means Hyper Reference,
			or the location you want to take the clicker of your link.  Notice, also, that we end it all with <b>/a</b> tag.  Remember, that all
			html TAGS must have a closing tag!  If you were to leave out the closing tag then everything after <b>Example Hyper Link/URL</b> would become
			a clickable hyper link!

    </td>
  </tr>
</table>