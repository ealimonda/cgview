#******************************************************************************
#*        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
#*      CC          GG           VV   VV    II   EE          WW       WW      *
#*      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
#*      CC          GG     GG      VVV      II   EE            WW W WW        *
#*        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
#******************************************************************************
#* Università degli Studi di Cagliari - Gruppo di Informatica Grafica         *
#* Filename: uiinput.pro                                                      *
#* Description: User Interface Input                                          *
#******************************************************************************
#* $Id::                                                       $: SVN Info    *
#* $Date::                                                     $: Last date   *
#* $Author::                                                   $: Last author *
#* $Revision::                                                 $: Revision    *
#******************************************************************************
TEMPLATE =	subdirs
SUBDIRS =	keyboard
SUBDIRS +=	mouse
mac:SUBDIRS+=	applemultitouch
# Add your plugins here
#SUBDIRS +=	sample
