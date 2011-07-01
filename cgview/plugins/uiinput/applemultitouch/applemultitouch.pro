#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* University of Cagliari, Italy - Computer Graphics Group                    *
#* Filename: applemultitouchplugin.pro                                        *
#* Description: Apple Multitouch input plugin                                 *
#******************************************************************************
#* $Id::                                                       $: SVN Info    *
#* $Date::                                                     $: Last date   *
#* $Author::                                                   $: Last author *
#* $Revision::                                                 $: Revision    *
#******************************************************************************
! include( ../../plugins_common.pri ) {
    error( Couldn't find the common.pri file! )
}

HEADERS +=	applemultitouchplugin.h \
    multitouch.h
SOURCES +=	applemultitouchplugin.mm
TARGET =	$$qtLibraryTarget(uiinput_applemultitouch)
LIBS += \
		/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation \
		-framework AppKit \
		/System/Library/PrivateFrameworks/MultitouchSupport.framework/Versions/A/MultitouchSupport
