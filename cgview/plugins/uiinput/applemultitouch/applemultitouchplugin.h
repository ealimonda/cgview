/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: applemultitouchplugin.h                                          *
 * Description: Apple Multitouch Input Plugin                                 *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_UIINPUT_APPLEMULTITOUCH_APPLEMULTITOUCHPLUGIN_H
#define CGVIEW_PLUGINS_UIINPUT_APPLEMULTITOUCH_APPLEMULTITOUCHPLUGIN_H

//#import <Cocoa/Cocoa.h>
#include <vector> // std::vector
#include <QObject> // class QObject
#include <QMutex> // class QMutex
#include <interfaces.h> // class PluginUIInputInterface
#include <inputevents.h>

#include "multitouch.h"

QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE

class AppleMultitouchPlugin : public virtual PluginUIInputInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginUIInputInterface)

public:
	// PluginUIInputInterface
	AppleMultitouchPlugin();
	bool handleEvent(QEvent *event);
	void loaded(void);
	inline static AppleMultitouchPlugin *pluginInstance(void) { return _pluginInstance; }
	int processCallback(int device, Touch *data, int nTouches, double timestamp, int frame);

public slots:
	void enable(bool state);

signals:
	void toggled(void);
	void receivedEvent(InputEvents::EventType, float value);

private:
	static const double kSamplingInterval = 0.05;
	static const int kMultitouchMaxFingers = 11;

	typedef struct
	{
		bool state;
		double last;
		mtPoint pos;
	} MKFinger;

	typedef struct
	{
		uint32_t unk_v0; // C8 B3 76 70  on both Mouse and Trackpad, but changes on other computers (i.e.: C8 23 FC 70)
		uint32_t unk_k0; // FF 7F 00 00
		uint32_t unk_k1; // 80 0E 01 00, then it changed to 80 10 01 00.  What is this?
		uint32_t unk_k2; // 01 00 00 00 - Could be Endianness
		uint32_t unk_v1; // 0F 35 00 00, 03 76 00 00, 03 6E 00 00 / 03 37 00 00, 03 77 00 00
		uint32_t unk_k3; // 00 00 00 00
		uint32_t address; // Last 4 bytes of the device address (or serial number?), as reported by the System Profiler Bluetooth tab
		uint32_t unk_k4; // 00 00 00 04 - Last byte might be Parser Options?
			// (uint64)address = Multitouch ID
		uint32_t family; // Family ID
		uint32_t bcdver; // bcdVersion
		uint32_t rows; // Sensor Rows
		uint32_t cols; // Sensor Columns
		uint32_t width; // Sensor Surface Width
		uint32_t height; // Sensor Surface Height
		uint32_t unk_k5; // 01 00 00 00 - Could be Endianness
		uint32_t unk_k6; // 00 00 00 00
		uint32_t unk_v2; // 90 04 75 70, 90 74 FA 70
		uint32_t unk_k7; // FF 7F 00 00
	} MTDeviceX;

	typedef struct
	{
		int dev_id;
		bool state;
		AppleMultitouchPlugin::MTDeviceX *device;
		//std::vector<MKFinger> fingers;
		MKFinger fingers[kMultitouchMaxFingers];	/* Magic trackpad can currently track 11 fingers.
								 * Magic Mouse 5.  I believe the trackpad on unibody
								 * MBPs is the same as the Magic Trackpad */
	} MKDevice;

	void processTouch(Touch *touch, MKDevice *deviceInfo);
	static AppleMultitouchPlugin *_pluginInstance;

	static const MTDeviceX kMultiTouchSampleDevice;

	std::vector<MKDevice*> _devices;
};

#endif // CGVIEW_PLUGINS_UIINPUT_APPLEMULTITOUCH_APPLEMULTITOUCHPLUGIN_H
