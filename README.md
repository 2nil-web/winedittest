### Test of readline and history replacement for MSVC

The library comes from here : cf. https://github.com/winlibs/wineditline
To build with MSVC in a DOS terminal :
```dos
set CMAKE_DIR='C:\Program Files\CMake\bin'
set MSBUILD_DIR='C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\amd64'
set PATH=%CMAKE_DIR%:%MSBUILD_DIR%:%PATH%`

cd wineditline
md build
cd build
cmake -A x64 ..
MSBuild.exe /p:Configuration=Release INSTALL.vcxproj`
```

To build with MSVC in a msys2 terminal :
```bash
export CMAKE_DIR='/c/Program Files/CMake/bin'
export MSBUILD_DIR='/c/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/amd64'
export PATH=${CMAKE_DIR}:${MSBUILD_DIR}:$PATH

cd wineditline
mkdir -p build && cd $_
cmake -A x64 ..
MSBuild.exe /p:Configuration=Release INSTALL.vcxproj
cp src/Release/*.lib .
```
