/***************************************************************************** 
* 
* PROJECT: MTADiag
* LICENSE: GNU GPL v3
* FILE: CDiag.h
* PURPOSE: Header for static diagnostic class
* DEVELOPERS: Matthew "Towncivilian" Wolfe <ligushka@gmail.com>
* 
* 
* 
* Multi Theft Auto is available from http://www.multitheftauto.com/
* 
*****************************************************************************/ 

#ifndef CDIAG_H
#define CDIAG_H

#include "Common.h"

#define buffSize 255
#define CUR_MTA_VERSIONS 5 // beginning at 1; encompasses 1.1, 1.2, 1.3, 1.4

#define MTAPathValue	"Last Install Location"
#define MTA11PathSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.1"
#define MTA12PathSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.2"
#define MTA13PathSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.3"
#define MTA14PathSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.4"

#define MTAGTAPathValue  "GTA:SA Path"
#define MTAGTAPathSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\Common"

#define MTAVerValue    "mta-version-ext"
#define MTA11VerSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.1\\Settings\\general"
#define MTA12VerSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.2\\Settings\\general"
#define MTA13VerSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.3\\Settings\\general"
#define MTA14VerSubKey "SOFTWARE\\Multi Theft Auto: San Andreas All\\1.4\\Settings\\general"

#define MTA11NightlyURL "http://nightly.mtasa.com/?mtasa-1.1.1-rc-latest"
#define MTA12NightlyURL "http://nightly.mtasa.com/?mtasa-1.2-rc-latest"
#define MTA13NightlyURL "http://nightly.mtasa.com/?mtasa-1.3-rc-latest"
#define MTA14NightlyURL "http://nightly.mtasa.com/?mtasa-1.4-unstable-latest"

class CDiag {
public:
	static void             Init                        ( void );
	static void             Destroy                     ( void );

	static std::string      CDiag::diagLogPath;
private:
	// gather all currently installed MTA:SA versions and ask the user to pick between them if necessary
	static bool             PollMTAVersions             ( void );
	static void             UserPickVersion             ( void );

	// gather MTA's path and version, and GTA:SA's path
	static std::string      GetMTAPath                  ( void );
	static std::string      GetGamePath                 ( void );
	static std::string      GetMTAVersion               ( void );

	// check whether DirectX is up to date (actually whether D3DX9_43.dll is present in %systemroot%\system32)
	// and check if a D3D9.dll is present in the GTA:SA directory
	static bool             IsDirectXUpToDate           ( void );
	static bool             CheckForD3D9                ( void );

	// update MTA:SA to the latest nightly/unstable build
	// and update DirectX if necessary
	static void             UpdateMTA                   ( void );
	static void             UpdateDirectX               ( void );

	// generate a DXDiag log, a list of currently running processes
	// then concatenate those logs, MTA's logs, and some other miscellaneous info
	static void             GenerateDXDiag              ( void );
	static void             GenerateTaskList            ( void );
	static bool             ConcatenateLogs             ( void );

	// used for storing environment variables & current system time
	static char             tempDir[255];
	static char             systemRoot[255];
	static SYSTEMTIME       sysTime;

	// strings to store various paths
	static std::string      nightlyPath;
	static std::string      dxDiagLogPath;
	static std::string      taskListPath;
	static std::string      D3DX9_43Path;
	static std::string      MTAPath;
	static std::string      GTAPath;

	// store current MTA version when GetMTAVersion() is called, and store the original version to dump in the log file
	static std::string      MTAVersion;
	static std::string      OriginalMTAVersion;

	static std::string      MTAVersionsInstalled[CUR_MTA_VERSIONS]; // array to store paths of all MTA versions currently installed
	static int              MTAVerChoice;                           // stores user's choice of which MTA version to diagnose

	static bool             DXUpdated;                              // was DirectX updated by MTADiag?
};

#endif