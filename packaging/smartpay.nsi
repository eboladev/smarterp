#
# SmartPay NSIS installer script
#
# This installer creator needs to be run with:
# makensis erp.nsi
#

#--------------------------------
# Include Modern UI

    !include "MUI2.nsh"

#--------------------------------
# General

    # Program version
    !define SMARTPAY_VERSION "1.9"

    # VIProductVersion requires version in x.x.x.x format
    !define SMARTPAY_VIPRODUCTVERSION "1.9.0.0"

    # Installer name and filename
    Name "SmartPay"
    Caption "SmartPay ${SMARTPAY_VERSION} Setup"
    OutFile "SmartPay-${SMARTPAY_VERSION}.exe"

    # Icon to use for the installer
    !define MUI_ICON "smartpay.ico"

    # Default installation folder
    InstallDir "$PROGRAMFILES\SmartPay"

    # Get installation folder from registry if available
    InstallDirRegKey HKCU "Software\SmartPay" ""

    # Request application privileges
    RequestExecutionLevel admin

    #Disable compression
    SetCompress auto

#--------------------------------
# Version information

    VIProductVersion "${SMARTPAY_VIPRODUCTVERSION}"
    VIAddVersionKey "ProductName" "SmartPay"
    VIAddVersionKey "FileDescription" "Payroll Management System"
    VIAddVersionKey "FileVersion" "${SMARTPAY_VERSION}"
    VIAddVersionKey "LegalCopyright" "GPL v.3"
    VIAddVersionKey "ProductVersion" "${SMARTPAY_VERSION}"

#--------------------------------
# Settings

    # Show a warn on aborting installation
    !define MUI_ABORTWARNING

    # Defines the target start menu folder
    !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
    !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\SmartPay"
    !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"

#--------------------------------
# Variables

    Var StartMenuFolder

#--------------------------------
# Pages

    # Installer pages
    !insertmacro MUI_PAGE_LICENSE "licence.txt"
    !insertmacro MUI_PAGE_DIRECTORY
    !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
    !insertmacro MUI_PAGE_INSTFILES

    # Uninstaller pages
    !insertmacro MUI_UNPAGE_CONFIRM
    !insertmacro MUI_UNPAGE_INSTFILES

# Languages

    !insertmacro MUI_LANGUAGE "English"

#--------------------------------
# Default installer section

Section
    SetShellVarContext all

    # Installation path
    SetOutPath "$INSTDIR"

    # Delete any already installed DLLs to avoid buildup of various
    # versions of the same library when upgrading
    Delete "$INSTDIR\*.dll"

    # Files to include in installer
    #File /r build\imageformats
    File /r build\platforms
    File /r build\printsupport
    File /r build\sqldrivers
    File build\*.dll
    File build\SmartPay.exe
    File licence.txt
    File smartpay.ico

    # Store installation folder in registry
    WriteRegStr HKCU "Software/SmartPay" "" $INSTDIR

# Create shortcuts
    !insertMacro MUI_STARTMENU_WRITE_BEGIN Application
	CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
	CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Smart Pay.lnk" \
		"$INSTDIR\SmartPay.exe" "" "$INSTDIR\smartpay.ico"
	CreateShortcut "$DESKTOP\Smart Pay.lnk" \
		"$INSTDIR\SmartPay.exe" "" "$INSTDIR\smartpay.ico"
	CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Uninstall Smart Pay.lnk" \
		"$INSTDIR\Uninstall.exe"
    !insertMacro MUI_STARTMENU_WRITE_END

    # Create the uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\SmartPay" \
        "DisplayName" "SmartPay"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\SmartPay" \
        "DisplayIcon" "$INSTDIR\smartpay.ico"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\SmartPay" \
        "UninstallString" "$INSTDIR\Uninstall.exe"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\SmartPay" \
        "DisplayVersion" ${SMARTPAY_VERSION}

SectionEnd
#--------------------------------
# Uninstaller section

Section "Uninstall"
    SetShellVarContext all

    # Delete installed files
    Delete "$INSTDIR\*.*"
    RMDir /r "$INSTDIR\imageformats"
    RMDir /r "$INSTDIR\platforms"
    RMDir /r "$INSTDIR\translations"
    RMDir /r "$INSTDIR\printsupport"
    RMDir /r "$INSTDIR\sqldrivers"
    RMDir "$INSTDIR"

    # Remove shortcuts
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    Delete "$SMPROGRAMS\$StartMenuFolder\Smart Pay.lnk"
    Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall Smart Pay.lnk"
    RMDir "$SMPROGRAMS\$StartMenuFolder"
    Delete "$DESKTOP\Smart Pay.lnk"

    # Remove registry entries
    DeleteRegKey /ifempty HKCU "Software\SmartPay"
    DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\SmartPay"

SectionEnd



