#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* University of Cagliari, Italy - Computer Graphics Group                    *
#* Filename: axes.pro                                                         *
#* Description: Axes visualization plugin                                     *
#******************************************************************************
#* $Id::                                                       $: SVN Info    *
#* $Date::                                                     $: Last date   *
#* $Author::                                                   $: Last author *
#* $Revision::                                                 $: Revision    *
#******************************************************************************
! include( ../../plugins_common.pri ) {
    error( Couldn't find the common.pri file! )
}

CONFIG +=	opengl
QT +=		opengl

HEADERS +=	axesplugin.h
SOURCES +=	axesplugin.cpp
TARGET =	$$qtLibraryTarget(visualization_axes)
