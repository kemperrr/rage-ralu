solution "Plugin"
	configurations {"Debug", "Release"}
	platforms { "x64" }	 
	
	location "build"	
	flags "C++14"
	
	configuration "windows"
		defines "WIN32"
	configuration "linux"
		defines "LINUX"
	configuration "*"
	
	includedirs { "./sdk", "C:\\Program Files\\Java\jdk1.8.0_144\\include\\win32", "C:\\Program Files\\Java\\jdk1.8.0_144\\include" }
	
	configuration "Debug*"
		libdirs { "../plugins" }
		targetdir ("../plugins")
	
	configuration "Release*"
		libdirs { "../plugins" }
		targetdir ("../plugins")
		flags { "Optimize" }
		
	configuration "*"
		include "helloworld"