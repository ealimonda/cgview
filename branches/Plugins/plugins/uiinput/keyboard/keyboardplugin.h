/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * Università degli Studi di Cagliari - Gruppo di Informatica Grafica         *
 * Filename: keyboardplugin.h                                                 *
 * Description: Keyboard Input Plugin                                         *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_UIINPUT_KEYBOARD_KEYBOARDPLUGIN_H
#define CGVIEW_PLUGINS_UIINPUT_KEYBOARD_KEYBOARDPLUGIN_H

#include <QObject> // class QObject
#include <interfaces.h> // class PluginVisualizationInterface
QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE

//class GLMesh;
//class GLWindow;

class KeyboardPlugin : public virtual PluginUIInputInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginUIInputInterface)

public:
	// PluginUIInputInterface
	KeyboardPlugin();
	bool handleEvent(QEvent *event);
	void loaded(void);

public slots:
	void enable(bool state);

signals:
	void toggled(void);
	void receivedEvent(InputEvents::EventType, float value);
};

#endif // CGVIEW_PLUGINS_UIINPUT_KEYBOARD_KEYBOARDPLUGIN_H
