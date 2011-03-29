/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: sampleplugin.cpp                                                 *
 * Description: Sample Input Plugin                                           *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "sampleplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2

/** Constructor.
 * The constructor shouls always set this->_menuName to the name you want to be
 * shown in the plugin's menu entry, as well as run this->setEnabled(false);
 * so that it won't be automatically enabled at startup
 */
SamplePlugin::SamplePlugin()
{
	this->_menuName = tr("Sample");
	this->setEnabled(false);
}

/** QEvent handler
 * This method is called whenever a supported (by the plugin system) QEvent is
 * received.  It should return true in case this plugin can handle the event,
 * false otherwise.
 * If the plugin doesn't use the QEvent system, simply return false.
 * Please ntoe that you'll probably need to cast the QEvent to one of its
 * subclasses in order to handle it.  Check the mouse and the keyboard plugins
 * for an example.
 * In case you don't want to use the QEvent system, you'll probably be using
 * some other way to obtain input events, which may or may not depend on
 * external libraries or system calls.  Feel free to add any methods
 * you may need in order to do that.
 * \param	QEvent *event	A pointer to the event object
 * \return	true if the event has been recognized and handled by this
 * 		plugin, false otherwise.
 */
bool SamplePlugin::handleEvent(QEvent *event)
{
	return false;
#if 0
	if (!this->isEnabled())
		return false;

	// Ignore unsupported event types
	if (event->type() != QEvent::Foo)
		return false;

	QFooEvent *fooEvent = (QFooEvent *)event;

	// Event handling here
	if (event->type() == QEvent::FooBarBaz)
	{
		if (fooEvent->quux() & Qt::Quuux)
		{
			emit receivedEvent(InputEvents::kFooBar, 0.2f);
			return true;
		}
	}
	return false;
#endif // 0
}

/** enable() slot
 * This is called whenever the user toggles the plugin's state by choosing
 * the plugin's menu entry.
 * Feel free to add anything here, but make sure you won't remove the
 * existing lines (this->setEnabled(state); emit(toggled()); or a lot of
 * things will break
 *
 * \param	bool state	Boolean flag of the on/off state we toggled to
 */
void SamplePlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

/** Post-initialization actions
 * This is called after the plugin is loaded and all of its slots/signals
 * are connected and set up
 */
void SamplePlugin::loaded(void) {
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(uiinput_sample, SamplePlugin)
QT_END_NAMESPACE
