
Sync-my-Moodle links against OpenSSL at runtime. This page describes where we get the OpenSSL DLLs from.

### Why not use QT's precompiled OpenSSL DLLs?

On https://download.qt.io/ there are already prebuilt OpenSSL DLLs:

* https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/tools_openssl_x86/qt.tools.openssl.win_x86/
* https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/tools_openssl_x64/qt.tools.openssl.win_x64/

They are built with an older version of Visual Studio. Therefore they link to msvcr100.dll which has to be installed on some systems (e.g. Windows 7) through the Microsoft Visual C++ 2010 SP1 Redistributable. But since Sync-my-Moodle is built with a newer Visual Studio version, it ships with a newer Visual C++ Redistributable that doesn't contain msvcr100.dll. Therefore we compile OpenSSL ourselves with the same Visual Studio version as Sync-my-Moodle. This way we only need one Visual C++ Redistributable. To keep Sync-my-Moodle's build time short, we've checked in the precompiled DLLs.

### Prerequisites

* Perl
* nmake (comes with Visual Studio)
* nasm (https://www.nasm.us/)

### Source

The OpenSSL source code is downloaded from: https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/tools_openssl_src/qt.tools.openssl.src/

### x86 build steps

```batch
mkdir C:\dev\openssl-win32
cd C:\dev\openssl-win32
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
perl C:\dev\openssl-src\Tools\OpenSSL\src\Configure VC-WIN32
nmake
nmake test
```

### x64 build steps

```batch
mkdir C:\openssl-win64
cd C:\openssl-win64
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
perl C:\dev\openssl-src\Tools\OpenSSL\src\Configure VC-WIN64A
nmake
nmake test
```
