; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Cheque Printer"
#define MyAppVersion "1.0"
#define MyAppPublisher "Smart Software"
#define MyAppURL "http://www.smartsoftware.co.ke"
#define MyAppExeName "cheque_printer.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2F441C89-2E5F-440F-BEAF-64C9E7B8A5D1}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir=Y:\Joshua\cp_1.0
OutputBaseFilename=setup
SetupIconFile=E:\Programming\Qt\smarterp\source\other_projects\cheque_printer\app.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "Y:\Joshua\cp_1.0\cheque_printer.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\icudt51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\icuin51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\icuuc51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\libmysql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\Qt5Xml.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Y:\Joshua\cp_1.0\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Y:\Joshua\cp_1.0\printsupport\*"; DestDir: "{app}\printsupport"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Y:\Joshua\cp_1.0\sqldrivers\*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

