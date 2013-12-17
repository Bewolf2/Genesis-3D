@echo #****************************************************************************
@echo  Copyright (c) 2011-2013,WebJet Business Division,CYOU
@echo   
@echo  http://www.genesis-3d.com.cn
@echo  
@echo  Permission is hereby granted, free of charge, to any person obtaining a copy
@echo  of this software and associated documentation files (the "Software"), to deal
@echo  in the Software without restriction, including without limitation the rights
@echo  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
@echo  copies of the Software, and to permit persons to whom the Software is
@echo  furnished to do so, subject to the following conditions:

@echo  The above copyright notice and this permission notice shall be included in
@echo  all copies or substantial portions of the Software.
@echo  
@echo  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
@echo  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
@echo  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
@echo  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
@echo  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
@echo  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
@echo  THE SOFTWARE.
@echo ****************************************************************************


@rem ���ݱ���cmake�İ�װ·�����޸�cmakeExe����
set cmakeExe="D:\Program Files\CMake 2.8\bin\cmake.exe"

set curPath=%cd%

set androidBuidPath="My_Android_Build"

@rem delete the folder first
RMDIR /S/Q %androidBuidPath%

@rem make a directory and put project files to it
MKDIR %androidBuidPath%

@rem entry the directory
cd %androidBuidPath%

%cmakeExe%  -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE:FILEPATH="%curPath%/CMake/AndroidToolChain.cmake" -DANDROID_BUILD:BOOL="1" -DCMAKE_MAKE_PROGRAM="%curPath%/extlibs\NDK\android-ndk-r8b-windows\prebuilt\windows\bin\make.exe" %curPath%
@rem %cmakeExe% .

set var1=becalled
call ../StandloneBuildAndroid.bat %var1%

pause

