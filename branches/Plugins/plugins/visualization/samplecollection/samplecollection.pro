#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* University of Cagliari, Italy - Computer Graphics Group                    *
#* Filename: samplecollection.pro                                             *
#* Description: Collection of visualization (sample) plugins                  *
#******************************************************************************
#* $Id::                                                       $: SVN Info    *
#* $Date::                                                     $: Last date   *
#* $Author::                                                   $: Last author *
#* $Revision::                                                 $: Revision    *
#******************************************************************************
# This is required in order to setup the build environment properly
! include( ../../plugins_common.pri ) {
    error( Couldn't find the common.pri file! )
}

# Required if you want to use OpenGL in the plugin
CONFIG +=	opengl
QT +=		opengl

HEADERS +=	samplecollectionplugin.h \
		firstsampleplugin.h \
		secondsampleplugin.h
SOURCES +=	samplecollectionplugin.cpp \
		firstsampleplugin.cpp \
		secondsampleplugin.cpp
# This is the name the plugin compiled library will take
TARGET =	$$qtLibraryTarget(visualization_samplecollectionplugin)
