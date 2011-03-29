/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: keyboardplugin.cpp                                               *
 * Description: Keyboard Input Plugin                                         *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "keyboardplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QKeyEvent> // QKeyEvent

KeyboardPlugin::KeyboardPlugin()
{
	this->_menuName = tr("Keyboard");
	this->setEnabled(true);
}

bool KeyboardPlugin::handleEvent(QEvent *event)
{
	if (!this->isEnabled())
		return false;

	if (event->type() != QEvent::KeyPress)
		return false;

	QKeyEvent *keyEvent = (QKeyEvent *)event;

	switch (keyEvent->key())
	{
	case Qt::Key_Up:
	case Qt::Key_8:
	case Qt::Key_K:
		emit receivedEvent(InputEvents::kLiftCam, 0.2f);
		return true;
	case Qt::Key_Down:
	case Qt::Key_2:
	case Qt::Key_J:
		emit receivedEvent(InputEvents::kLiftCam, -0.2f);
		return true;
	case Qt::Key_Left:
	case Qt::Key_4:
	case Qt::Key_H:
		emit receivedEvent(InputEvents::kStrafeCam, 0.2f);
		return true;
	case Qt::Key_Right:
	case Qt::Key_6:
	case Qt::Key_L:
		emit receivedEvent(InputEvents::kStrafeCam, -0.2f);
		return true;
		break;
	case Qt::Key_PageUp:
	case Qt::Key_7:
	case Qt::Key_Z:
		emit receivedEvent(InputEvents::kDistanceCam, 0.2f);
		return true;
	case Qt::Key_PageDown:
	case Qt::Key_1:
	case Qt::Key_X:
		emit receivedEvent(InputEvents::kDistanceCam, -0.2f);
		return true;
	case Qt::Key_Home:
	case Qt::Key_5:
	case Qt::Key_C:
		emit receivedEvent(InputEvents::kFitCam, 0.0f);
		return true;
	default:
		break;
	}
	return false;
}

void KeyboardPlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
#if 0
	if (state)
	{
	}
#endif // 0
}

void KeyboardPlugin::loaded(void) {
	this->setEnabled(true);
	emit(toggled());
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(uiinput_keyboard, KeyboardPlugin)
QT_END_NAMESPACE
