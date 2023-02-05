
ifneq ($(shell uname -s),Linux)
ifeq (${HOSTNAME},PC-Denis)
CMAKE='/c/Program Files/CMake/bin/cmake.exe'
MSBUILD='C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\amd64\MSBuild.exe'
endif

ifneq (${MSYSTEM},MSYS)
PATH:=/$(shell echo $(MSYSTEM) | tr A-Z a-z)/bin:${PATH}
endif

ifeq (${MSYSTEM},CLANG64)
CC=clang
CXX=clang++
CXXFLAGS += -std=c++20
else
CXXFLAGS += -std=c++23
endif

LDFLAGS  += -static -Wl,--allow-multiple-definition
EXEXT=.exe
ECHO=echo -e
else
ECHO=echo
CC=g++
CXXFLAGS += -std=c++20
#LDFLAGS+=-static
endif

VERSION=$(shell git describe --abbrev=0 --tags 2>/dev/null || echo 'Unknown_version')
COMMIT=$(shell git rev-parse --short HEAD 2>/dev/null || echo 'Unknown_commit')
DECORATION=Nawak-Bidon

CFLAGS   += -Wall -Wextra -std=c18 -pedantic
CXXFLAGS += -Wall -Wextra -pedantic
#LDFLAGS  += -g
LDFLAGS  += -Os -s
LDLIBS += -lhistory -lreadline -ltermcap
GDB=gdb
STRIP=strip
UPX=upx

PREFIX=testwinedit
#SRCS=$(wildcard *.cpp)
SRCS=${PREFIX}.cpp
OBJS=$(SRCS:.cpp=.o)
TARGET=${PREFIX}${EXEXT}
ISO8601 := $(shell date +%Y-%m-%dT%H:%M:%SZ)
.PHONY: FORCE

all : version_check.txt version.h ${TARGET}
	make ${TARGET}

ifeq ($(MSBUILD),)
${TARGET} : ${OBJS}
else
${TARGET} : wineditline/lib64/edit_a.lib ${SRCS}
	${MSBUILD} ${PREFIX}.sln -p:Configuration=Release
	cp x64/Release/${TARGET} .
endif

wineditline/lib64/edit_a.lib : wineditline/src/*.c
	cd wineditline && test -d build && cd build || ( mkdir -p build && cd build && ${CMAKE} -A x64 .. ) && ${MSBUILD} -p:Configuration=Release INSTALL.vcxproj

strip : ${TARGET}
	@file ${TARGET} | grep stripped >/dev/null || ( $(STRIP) ${TARGET} && echo "Strip OK" )

upx : ${TARGET}
	$(STRIP) ${TARGET} 2>/dev/null || true
	$(UPX) -q ${TARGET} 2>/dev/null || true

cfg :
	@type ${CXX} ${CXX} ${LD} ${GDB} ${STRIP} ${UPX}
	@${ECHO} "CPPFLAGS=${CPPFLAGS}"
	@${ECHO} "CXXFLAGS=${CXXFLAGS}"
	@${ECHO} "LDFLAGS=${LDFLAGS}"
	@${ECHO} "LDLIBS=${LDLIBS}"
	@${ECHO} "SRCS=${SRCS}"
	@${ECHO} "OBJS=${OBJS}"
	@${ECHO} "TARGET=${TARGET}"

help :
	@${ECHO} "$(shell tput smul)Que faire pour livrer une nouvelle version ?$(shell tput rmul)"
	@${ECHO} "1-Vérifier les tags distants : git ls-remote --tags origin"
	@${ECHO} "2-Vérifier les tags locaux   : git describe --abbrev=0 --tags"
	@${ECHO} "3-Nouveau tag de version     : git tag -a X.Y.Z-nom_de_la_prereleasee -m 'commentaire' # De préférence un tag annoté (-a)."
	@${ECHO} "4-Pousser un tag             : git push --tags"
	@${ECHO} "5-Build applicatif           : make"
	@${ECHO} "6-Build du setup             : make setup # (ToDo)"
	@${ECHO} "7-Livraison                  : make deliv # (ToDo)"
	@${ECHO} "Pour le versionnage, respecter la sémantique de version (cf. semver.org, i.e.: MAJOR.MINOR.PATCH-pre_release+metadata ...)"

clean :
	rm -f *~ *.o $(OBJS)

rclean :
	rm -f *~ *.d *.o $(OBJS) ${TARGET} *.exe
	rm -rf x64 wineditline/build wineditline/bin64 wineditline/lib64 wineditline/include

# Génération du version.h intégré dans l'appli
version.h : version_check.txt
	@${ECHO} "Building C++ header $@"
	@${ECHO} "std::string name=\"${PREFIX}\", version=\"${VERSION}\", decoration=\"${DECORATION}\", commit=\"${COMMIT}\", created_at=\"${ISO8601}\";" >$@

# Génération du version.json intégré dans le paquetage
version.json : version_check.txt
	@${ECHO} "Building json file $@"
	@${ECHO} '{ "name":"${PREFIX}", "version":"${VERSION}", "decoration":"${DECORATION}", "commit":"${COMMIT}","created_at":"${ISO8601}" }' >$@

# Pour regénérer version.h et version.json dès qu'un des champs version ou decoration ou commit, est modifié.
version_check.txt : FORCE
	@${ECHO} "Version:${VERSION}, decoration:${DECORATION}, commit:${COMMIT}" >new_$@
	@if diff new_$@ $@ >/dev/null 2>&1; then rm -f new_$@; else mv -f new_$@ $@; rm -f ${PREFIX}.iss ${PREFIX}-standalone.iss; fi

# Ces régles implicites ne sont pas utiles quand on fait 'make rclean' (voir même make clean ...)
ifneq ($(MAKECMDGOALS),rclean)
%.exe: %.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.exe: %.cpp
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

#	@${ECHO} "Building "$@" from "$<
%.d: %.cpp
	@${ECHO} Checking header dependencies from $<
	@$(COMPILE.cpp) -isystem /usr/include -MM -MG $< > $@
# Inclusion des fichiers de dépendance .d
ifdef OBJS
-include $(OBJS:.o=.d)
endif
endif

