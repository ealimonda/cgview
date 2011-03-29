#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* University of Cagliari, Italy - Computer Graphics Group                    *
#* Filename: CGView.pro                                                       *
#* Description: Project file for CGView                                       *
#******************************************************************************
#* $Id::                                                       $: SVN Info    *
#* $Date::                                                     $: Last date   *
#* $Author::                                                   $: Last author *
#* $Revision::                                                 $: Revision    *
#******************************************************************************

TEMPLATE =	app
CONFIG += \
		opengl \
		thread

QT +=		opengl

INCLUDEPATH +=	. \
		../../../lib/vcglib

HEADERS = \
		opengl/glwindow.h \
		opengl/scene/camera/glcamera.h \
		opengl/scene/light/gllight.h \
		mainwindow.h \
		engine.h \
		mesh_definition.h \
		opengl/mesh/mode/visualmode.h \
		opengl/mesh/material/glmaterial.h \
		opengl/intro/glintro.h \
		opengl/scene/scene.h \
		opengl/mesh/glmesh.h \
		convex_hull/my_convhull.h \
		statusbar.h \
		interfaces.h \
		pluginmanager.h \
		inputevents.h

SOURCES = \
		opengl/glwindow.cpp \
		opengl/scene/camera/glcamera.cpp \
		opengl/scene/light/gllight.cpp \
		opengl/intro/glintro.cpp \
		main.cpp \
		mainwindow.cpp \
		engine.cpp \
		opengl/mesh/material/glmaterial.cpp \
		opengl/mesh/glmesh.cpp \
		statusbar.cpp \
		convex_hull/my_convhull.cpp \
		pluginmanager.cpp \
		inputevents.cpp \
		../../../lib/vcglib/wrap/ply/plylib.cpp

win32:RC_FILE =	icon.rc

mac {
	ICON =			logo.icns
	QMAKE_INFO_PLIST =	Info_mac.plist
	# CoreFoundation, AppKit
	LIBS += \
			/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation \
			-framework AppKit
}

QMAKE_CXXFLAGS += \
		-Wall \
		-Wextra \
		-Wswitch-enum \
		-Wconversion

DEFINES +=	NDEBUG
DESTDIR =	../output
