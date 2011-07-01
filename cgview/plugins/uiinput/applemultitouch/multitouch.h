/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: multitouch.h                                                     *
 * Description: Apple Multitouch Input Plugin                                 *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_UIINPUT_APPLEMULTITOUCH_MULTITOUCH_H
#define CGVIEW_PLUGINS_UIINPUT_APPLEMULTITOUCH_MULTITOUCH_H

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	float x,y;
} mtPoint;

typedef struct
{
	mtPoint pos,vel;
} mtReadout;

typedef struct
{
	int frame;
	double timestamp;
	int identifier, state, foo3, foo4;
	mtReadout normalized;
	float size;
	int zero1;
	float angle, majorAxis, minorAxis; // ellipsoid
	mtReadout mm;
	int zero2[2];
	float unk2;
} Touch;

typedef void* MTDeviceRef;
typedef int (*MTContactCallbackFunction)(int,Touch*,int,double,int);

MTDeviceRef MTDeviceCreateDefault();
void MTRegisterContactFrameCallback(MTDeviceRef, MTContactCallbackFunction);
void MTUnregisterContactFrameCallback(MTDeviceRef, MTContactCallbackFunction);
void MTDeviceStart(MTDeviceRef, int);
void MTDeviceStop(MTDeviceRef);
void MTDeviceRelease(MTDeviceRef);
CFArrayRef MTDeviceCreateList();

#ifdef __cplusplus
}
#endif

#endif // CGVIEW_PLUGINS_UIINPUT_APPLEMULTITOUCH_MULTITOUCH_H
