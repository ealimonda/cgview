/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: sampleplugin.h                                                    *
 * Description: Sample Input Plugin                                            *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINS_UIINPUT_SAMPLE_SAMPLEPLUGIN_H
#define CGVIEW_PLUGINS_UIINPUT_SAMPLE_SAMPLEPLUGIN_H

#include <QObject> // class QObject
#include <QPoint> // QPoint
#include <interfaces.h> // class PluginUIInputInterface
QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE

/** The main plugin's class.
 * This must always implement the PluginUIInterface, else it won't
 * be loaded properly as an user interface input plugin.
 * All the following methods are required, but you're free to add your
 * own methods if you wish.
 */
class SamplePlugin : public virtual PluginUIInputInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginUIInputInterface)

public:
	// PluginUIInputInterface
	SamplePlugin();
	bool handleEvent(QEvent *event);
	void loaded(void);

public slots:
	void enable(bool state);

signals:
	void toggled(void);
	void receivedEvent(InputEvents::EventType, float value);
};

#endif // CGVIEW_PLUGINS_UIINPUT_SAMPLE_SAMPLEPLUGIN_H
