/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * Università degli Studi di Cagliari - Gruppo di Informatica Grafica         *
 * Filename: inputevents.h                                                    *
 * Description: UI Input Events                                               *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_INPUTEVENTS_H
#define CGVIEW_INPUTEVENTS_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE
class InputEvents
{
public:
	typedef enum
	{
		kEventNoop = 0,
		kLiftCam,
		kStrafeCam,
		kDistanceCam,
		kFitCam,
	} EventType;
	InputEvents();
	static bool DispatchEvent(QEvent *event);
};

#endif // CGVIEW_INPUTEVENTS_H
