!include "installer.properties"

!define PROJECT_ROOT ..\..

Name SpaceEvaders
OutFile "SpaceEvadersSetup.exe"

InstallDir $PROGRAMFILES\SpaceEvaders

Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section

    SetShellVarContext all

    SetOutPath $INSTDIR

    File ${PROJECT_ROOT}\bin\release\SpaceEvaders.exe
    File ${SFML_BIN}\sfml-audio-2.dll
    File ${SFML_BIN}\sfml-system-2.dll
    File ${SFML_BIN}\sfml-graphics-2.dll
    File ${SFML_BIN}\sfml-window-2.dll
    File ${SFML_BIN}\openal32.dll
    File ${SFML_BIN}\libsndfile-1.dll
    File ${MINGW_BIN}\libstdc++-6.dll
    File ${MINGW_BIN}\libgcc_s_dw2-1.dll

    File ${PROJECT_ROOT}\installer\win\evaders.ico

    SetOutPath "$INSTDIR\assets"

    File /r "${PROJECT_ROOT}\assets\*"

    WriteUninstaller "$INSTDIR\Uninstall.exe"

    CreateDirectory "$SMPROGRAMS\SpaceEvaders"
    CreateShortCut "$SMPROGRAMS\SpaceEvaders\SpaceEvaders.lnk" "$INSTDIR\SpaceEvaders.exe" "" "$INSTDIR\evaders.ico"
    CreateShortCut "$SMPROGRAMS\SpaceEvaders\Uninstall.lnk" "$INSTDIR\uninstall.exe"

SectionEnd

Section "uninstall"

    SetShellVarContext all

    Delete $INSTDIR\SpaceEvaders.exe
    Delete "$INSTDIR\sfml-*-2.dll"
    Delete $INSTDIR\openal32.dll
    Delete $INSTDIR\libsndfile-1.dll
    Delete $INSTDIR\libstdc++-6.dll
    Delete $INSTDIR\libgcc_s_dw2-1.dll

    Delete $INSTDIR\evaders.ico

    RMDir /r $INSTDIR\assets

    Delete "$INSTDIR\Uninstall.exe"

    Delete "$SMPROGRAMS\SpaceEvaders\SpaceEvaders.lnk"
    Delete "$SMPROGRAMS\SpaceEvaders\Uninstall.lnk"
    RMDir "$SMPROGRAMS\SpaceEvaders"

    # WARNING: NEVER use /r here, to ensure we only delete the installation directory once empty.
    # If a future version of this script allows selection of installation dir, we need to make sure we
    # don't attempt to delete ProgramFiles or similar if the user installed the application there.
    RMDir $INSTDIR

SectionEnd
