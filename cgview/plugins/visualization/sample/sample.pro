#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* University of Cagliari, Italy - Computer Graphics Group                    *
#* Filename: sample.pro                                                       *
#* Description: Sample visualization plugin                                   *
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

# Please be careful with (and if possible, avoid to) adding sources from
#  CGView, as if you do that, they must always match the version of CGView you
#  load the plugin into!
HEADERS +=	sampleplugin.h
SOURCES +=	sampleplugin.cpp
TARGET =	$$qtLibraryTarget(visualization_sample)
