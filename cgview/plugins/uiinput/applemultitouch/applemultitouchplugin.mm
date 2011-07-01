/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: applemultitouchplugin.cpp                                        *
 * Description: Apple Multitouch Input Plugin                                 *
 ******************************************************************************
 * $Id:: applemultitouchplugin.mm -1                           $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision:: -1                                              $: Revision    *
 ******************************************************************************/
#include "applemultitouchplugin.h"
//#define DEBUGGING_MULTITOUCH

#include <CoreFoundation/CoreFoundation.h> // NSArray
#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QKeyEvent> // QKeyEvent
#ifdef DEBUGGING_MULTITOUCH
#include <QDebug>
#endif // DEBUGGING_MULTITOUCH

#include "multitouch.h"

AppleMultitouchPlugin *AppleMultitouchPlugin::_pluginInstance = NULL;

static int callback(int device, Touch *data, int nTouches, double timestamp, int frame)
{
	AppleMultitouchPlugin *plugin;
	plugin = AppleMultitouchPlugin::pluginInstance();
	return plugin->processCallback(device, data, nTouches, timestamp, frame);
}

const AppleMultitouchPlugin::MTDeviceX AppleMultitouchPlugin::kMultiTouchSampleDevice =
{
	       0x0,
	       0x00007FFF,
	       0x00011080,
	       0x00000001,
	       0x0,
	       0x00000000,
	       0x0,
	       0x04000000,
	       0x0,
	       0x0,
	       0x0,
	       0x0,
	       0x0,
	       0x0,
	       0x00000001,
	       0x00000000,
	       0x0,
	       0x00007FFF,
};

AppleMultitouchPlugin::AppleMultitouchPlugin()
{
	qRegisterMetaType<InputEvents::EventType>("InputEvents::EventType");
	_pluginInstance = this;
	this->_menuName = tr("Apple Multitouch Device");
	this->setEnabled(true);

	this->_devices.clear();

	NSArray *devs = (NSArray*)MTDeviceCreateList(); //grab our device list
	for (unsigned int i = 0; i < [devs count]; ++i)
	{
		MTDeviceX *thisDevice = (MTDeviceX *)[devs objectAtIndex: i];
		MKDevice *mkDeviceInfo = new MKDevice();
		mkDeviceInfo->dev_id = i;
		mkDeviceInfo->state = false;
		mkDeviceInfo->device = thisDevice;
		for (int j = 0; j < kMultitouchMaxFingers; ++j)
		{
			mkDeviceInfo->fingers[j].last = 0;
			mkDeviceInfo->fingers[j].state = false;
		}
#ifdef DEBUGGING_MULTITOUCH
		if (!thisDevice
				|| thisDevice->unk_k0 != kMultiTouchSampleDevice.unk_k0
				|| thisDevice->unk_k1 != kMultiTouchSampleDevice.unk_k1
				|| thisDevice->unk_k2 != kMultiTouchSampleDevice.unk_k2
				|| thisDevice->unk_k3 != kMultiTouchSampleDevice.unk_k3
				|| thisDevice->unk_k4 != kMultiTouchSampleDevice.unk_k4
				|| thisDevice->unk_k5 != kMultiTouchSampleDevice.unk_k5
				|| thisDevice->unk_k6 != kMultiTouchSampleDevice.unk_k6
				|| thisDevice->unk_k7 != kMultiTouchSampleDevice.unk_k7
		)
		{
			qDebug() << "Unrecognized device (#" << i << "), please report.\nDevice info: "
					<< /*getInfoForDevice(*/thisDevice/*)*/;
		}
#endif // DEBUGGING_MULTITOUCH
		if (!thisDevice)
			continue;
		switch (thisDevice->family)
		{
		case 0x00000070:
#ifdef DEBUGGING_MULTITOUCH
			qDebug() << "Detected Magic Mouse (#" << i << ").  Ignoring it.";
			continue;
#endif // DEBUGGING_MULTITOUCH
		case 0x00000080:
#ifdef DEBUGGING_MULTITOUCH
			qDebug() << "Detected Magic Trackpad (#" << i << ").";
#endif // DEBUGGING_MULTITOUCH
			break;
		default:
#ifdef DEBUGGING_MULTITOUCH
			qDebug() << "Detected device (#" << i << ") family " << thisDevice->family <<".  Ignoring it.";
			qDebug() << "Device info: " << /*getInfoForDevice(*/thisDevice/*)*/;
#endif // DEBUGGING_MULTITOUCH
			continue;
		}
		mkDeviceInfo->state = true;
		this->_devices.push_back(mkDeviceInfo);
		MTRegisterContactFrameCallback((MTDeviceRef)thisDevice, callback); //assign callback for device
		MTDeviceStart((MTDeviceRef)thisDevice, 0); //start sending events
	}
}

int AppleMultitouchPlugin::processCallback(int device, Touch *data, int nTouches, double /*timestamp*/, int /*frame*/)
{
	for (int i = 0; i < nTouches; i++)
	{
		Touch *t = &data[i];
		MKDevice *thisDevice = nil;
		unsigned int j = 0;
		for (j = 0; j < this->_devices.size(); j++)
		{
			thisDevice = this->_devices[j];
			if( (int)(long)(thisDevice->device) == device )
				break;
		}
		if (j >= this->_devices.size())
		{
#ifdef DEBUGGING_MULTITOUCH
			qDebug() << "Device (" << device << ") not found.  Ignoring touch.";
#endif // DEBUGGING_MULTITOUCH
			continue;
		}
		this->processTouch(t, thisDevice);
	}
	return 0;
}

void AppleMultitouchPlugin::processTouch(Touch *touch, MKDevice *deviceInfo) {
	if (/*(touch->state != 7 && touch->state != 1) ||*/ !this->isEnabled())
		return;
	if( touch->identifier > kMultitouchMaxFingers || touch->identifier <= 0 ) // Sanity check
		return;
#if 0
	qDebug() << "Frame " << touch->frame << ": TS:" << touch->timestamp << " ID:" << touch->identifier <<
			" St:" << touch->state << " foo3:" << touch->foo3 << " foo4:" << touch->foo4 <<
			" norm.pos: [" << touch->normalized.pos.x << "," << touch->normalized.pos.y <<
			"] sz: " << touch->size << " unk2:" << touch->unk2;
#endif // 0
	switch (touch->state)
	{
	// FIXME: Constants
	case 1: // Touch initiated
		if (deviceInfo->fingers[touch->identifier-1].state)
			return;
#ifdef DEBUGGING_MULTITOUCH
		qDebug() << "Finger " << touch->identifier << " down";
#endif // DEBUGGING_MULTITOUCH
		deviceInfo->fingers[touch->identifier-1].last = touch->timestamp;
		deviceInfo->fingers[touch->identifier-1].state = true;
		deviceInfo->fingers[touch->identifier-1].pos = touch->normalized.pos;
		return;
	case 7: // Touch ended
		if( !deviceInfo->fingers[touch->identifier-1].state )
			return;
#ifdef DEBUGGING_MULTITOUCH
		qDebug() << "Finger " << touch->identifier << " up";
#endif // DEBUGGING_MULTITOUCH
		deviceInfo->fingers[touch->identifier-1].state = false;
		deviceInfo->fingers[touch->identifier-1].last = touch->timestamp;
		break;
	default: // Other states (moving, etc)
		if( touch->timestamp < deviceInfo->fingers[touch->identifier-1].last + kSamplingInterval )
			return;
		int count = 0;
		for (int i = 0; i < kMultitouchMaxFingers; ++i)
		{
			if (deviceInfo->fingers[i].state)
				++count;
		}
#ifdef DEBUGGING_MULTITOUCH
		qDebug() << "Finger " << touch->identifier << " moving (" << touch->state << ") - [" << count << "]";
#endif // DEBUGGING_MULTITOUCH
		deviceInfo->fingers[touch->identifier-1].last = touch->timestamp;
		switch (count)
		{
		case 0:
		case 1:
			break; // ignore
		case 2: // This could be a two finger scroll or a pinch
		  {
			float olddist = 0.0f;
			float newdist = 0.0f;
			for (int i = 0; i < kMultitouchMaxFingers; ++i)
			{
				if (i == touch->identifier-1)
					continue;
				if (!deviceInfo->fingers[i].state)
					continue;
				olddist = sqrt(pow(deviceInfo->fingers[i].pos.x - deviceInfo->fingers[touch->identifier-1].pos.x, 2) +
					       pow(deviceInfo->fingers[i].pos.y - deviceInfo->fingers[touch->identifier-1].pos.y, 2));
				newdist = sqrt(pow(deviceInfo->fingers[i].pos.x - touch->normalized.pos.x, 2) +
					       pow(deviceInfo->fingers[i].pos.y - touch->normalized.pos.y, 2));
				break;
			}
			float delta = olddist - newdist;
			emit receivedEvent(InputEvents::kDistanceCam, 2*delta);
			deviceInfo->fingers[touch->identifier-1].pos = touch->normalized.pos;
			break;
		  }
		case 3: // three finger scroll or pinch
		  {
			float xdelta = 0.0f;
			float ydelta = 0.0f;
			bool done = false;
			for (int i = 0; i < kMultitouchMaxFingers; ++i)
			{
				if (!deviceInfo->fingers[i].state)
					continue;
				if (done)
				{
					deviceInfo->fingers[i].last = touch->timestamp;
					continue;
				}
				xdelta = deviceInfo->fingers[touch->identifier-1].pos.x - touch->normalized.pos.x;
				ydelta = deviceInfo->fingers[touch->identifier-1].pos.y - touch->normalized.pos.y;
				done = true;
				break;
			}
#ifdef DEBUGGING_MULTITOUCH
			qDebug() << xdelta << " " << ydelta << " " << touch->identifier;
#endif // DEBUGGING_MULTITOUCH
			deviceInfo->fingers[touch->identifier-1].pos = touch->normalized.pos;
			if (xdelta > 0.002f || xdelta < -0.002f)
				emit receivedEvent(InputEvents::kRotateVUpCam, 5*xdelta);
			if (ydelta > 0.002f || ydelta < -0.002f)
				emit receivedEvent(InputEvents::kRotateVRCam, -5*ydelta);
			break;
		  }
		case 4: // four finger
			break;
		default:
			break;
		}
		return;
	}
}

bool AppleMultitouchPlugin::handleEvent(QEvent */*event*/)
{
	return false;
}

void AppleMultitouchPlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

void AppleMultitouchPlugin::loaded(void) {
	this->setEnabled(true);
	emit(toggled());
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(uiinput_applemultitouch, AppleMultitouchPlugin)
QT_END_NAMESPACE
