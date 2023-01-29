

# Test wineditline; cf. https://github.com/winlibs/wineditline
# cd wineditline
# md build
# cd build
# cmake -A x64 ..
# build edit_test under visual studio and get static lib + ../src/editline
# C:\Users\casal\Documents\home\wineditline\build\src\Release\edit_a.lib
LDLFLAGS+=-static
LDLIBS+=-lreadline -lhistory

libedit_test :


rclean :
	rm -rf libedit_test.exe *.o *.d x64

