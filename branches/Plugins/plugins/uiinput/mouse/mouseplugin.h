/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: mouseplugin.h                                                    *
 * Description: Mouse Input Plugin                                            *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_UIINPUT_MOUSE_MOUSEPLUGIN_H
#define CGVIEW_PLUGINS_UIINPUT_MOUSE_MOUSEPLUGIN_H

#include <QObject> // class QObject
#include <QPoint> // QPoint
#include <interfaces.h> // class PluginUIInputInterface
QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE

class MousePlugin : public virtual PluginUIInputInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginUIInputInterface)

public:
	// PluginUIInputInterface
	MousePlugin();
	bool handleEvent(QEvent *event);
	void loaded(void);

public slots:
	void enable(bool state);

private:
	/// MOUSE
	/// Last position clicked
	QPoint _lastPos;
	/// Sensivity of the mouse
	float _mouseSens;

signals:
	void toggled(void);
	void receivedEvent(InputEvents::EventType, float value);
};

#endif // CGVIEW_PLUGINS_UIINPUT_MOUSE_MOUSEPLUGIN_H
