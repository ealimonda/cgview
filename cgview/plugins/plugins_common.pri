#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* University of Cagliari, Italy - Computer Graphics Group                    *
#* Filename: plugins_common.pri                                               *
#* Description: Common definitions for plugins                                *
#******************************************************************************
#* $Id::                                                       $: SVN Info    *
#* $Date::                                                     $: Last date   *
#* $Author::                                                   $: Last author *
#* $Revision::                                                 $: Revision    *
#******************************************************************************

# Common configuration for all plugins
TEMPLATE =	lib
#CONFIG +=	plugin static
CONFIG +=	plugin
INCLUDEPATH +=	../../../CGView \
                ../../../../lib/vcglib
DESTDIR =	../../../output/plugins

# Don't remove -W* cflags unless strictly necessary.
QMAKE_CXXFLAGS +=	-Wall \
			# -Wextra \
			# -Wswitch-enum \
			# -Wconversion
