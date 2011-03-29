/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: mouseplugin.cpp                                                  *
 * Description: Mouse Input Plugin                                            *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "mouseplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
#include <QMouseEvent> // QMouseEvent
#include <QWheelEvent> // QWheelEvent
#include <vcg/math/base.h> // vcg::math

MousePlugin::MousePlugin()
{
	this->_menuName = tr("Mouse");
	this->setEnabled(true);
	this->_lastPos = QPoint(0,0);
	this->_mouseSens = 0.5f;
}

bool MousePlugin::handleEvent(QEvent *event)
{
	if (!this->isEnabled())
		return false;

	if (event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonPress)
	{

		QMouseEvent *mouseEvent = (QMouseEvent *)event;

		if (event->type() == QEvent::MouseButtonPress)
		{
			if (mouseEvent->buttons() & Qt::MidButton)
			{
				emit receivedEvent(InputEvents::kFitCam, 0.0f);
				return true;
			}
			this->_lastPos = mouseEvent->pos();
			return false;
		}
		if (event->type() == QEvent::MouseMove )
		{
			int dx = mouseEvent->x() - this->_lastPos.x();
			int dy = mouseEvent->y() - this->_lastPos.y();

			if (mouseEvent->modifiers() & Qt::ShiftModifier)
			{
				emit receivedEvent(InputEvents::kRotateVRCam, vcg::math::ToRad((float)-dy * this->_mouseSens));
			}
			else if (mouseEvent->modifiers() & Qt::ControlModifier)
			{
				emit receivedEvent(InputEvents::kDistanceCam, vcg::math::ToRad((float)-dy * this->_mouseSens));
			}
			else if (mouseEvent->modifiers() & Qt::AltModifier)
			{
				emit receivedEvent(InputEvents::kRotateVUpCam, vcg::math::ToRad((float)-dx * this->_mouseSens));
			}
			else if (mouseEvent->modifiers() & Qt::MetaModifier)
			{
				emit receivedEvent(InputEvents::kRotateDirCam, vcg::math::ToRad((float)dx * this->_mouseSens));
			}
			else if (mouseEvent->buttons() & Qt::LeftButton)
			{
				emit receivedEvent(InputEvents::kRotateVUpCam, vcg::math::ToRad((float)-dx * this->_mouseSens));
				emit receivedEvent(InputEvents::kRotateVRCam, vcg::math::ToRad((float)-dy * this->_mouseSens));
			}
			else if (mouseEvent->buttons() & Qt::RightButton)
			{
				emit receivedEvent(InputEvents::kRotateVRCam, vcg::math::ToRad((float)-dy * this->_mouseSens));
				emit receivedEvent(InputEvents::kRotateDirCam, vcg::math::ToRad((float)dx * this->_mouseSens));
			}
			this->_lastPos = mouseEvent->pos();
			return true;
		}
		return false;
	}
	if (event->type() == QEvent::Wheel)
	{
		QWheelEvent *wheelEvent = (QWheelEvent *)event;
		float rot = wheelEvent->delta() / 8;
		emit receivedEvent(InputEvents::kDistanceCam, vcg::math::ToRad(rot * this->_mouseSens));
		return true;
	}
	return false;
}

void MousePlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
#if 0
	if (state)
	{
	}
#endif // 0
}

void MousePlugin::loaded(void) {
	this->setEnabled(true);
	emit(toggled());
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(uiinput_mouse, MousePlugin)
QT_END_NAMESPACE
