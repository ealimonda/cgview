#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* Università degli Studi di Cagliari - Gruppo di Informatica Grafica         *
#* Filename: keyboard.pro                                                     *
#* Description: Keyboard input plugin                                         *
#******************************************************************************
#* $Id::                                                       $: SVN Info    *
#* $Date::                                                     $: Last date   *
#* $Author::                                                   $: Last author *
#* $Revision::                                                 $: Revision    *
#******************************************************************************
! include( ../../plugins_common.pri ) {
    error( Couldn't find the common.pri file! )
}

HEADERS +=	keyboardplugin.h
SOURCES +=	keyboardplugin.cpp
TARGET =	$$qtLibraryTarget(uiinput_keyboard)
