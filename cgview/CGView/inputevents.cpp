/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * Università degli Studi di Cagliari - Gruppo di Informatica Grafica         *
 * Filename: inputevents.cpp                                                  *
 * Description: UI Input Events                                               *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "inputevents.h"

#include "interfaces.h" // PluginUIInputInterface
#include "pluginmanager.h" // class PluginManager

InputEvents::InputEvents()
{
}

bool InputEvents::DispatchEvent(QEvent *event)
{
	bool handled = false;
	std::vector<PluginUIInputInterface *> uiInputPlugins = PluginManager::sharedInstance()->uiInputPlugins();
	for (unsigned int i = 0; i < uiInputPlugins.size(); ++i)
	{
		if (!uiInputPlugins[i]->isEnabled())
			continue;

		if (uiInputPlugins[i]->handleEvent(event))
			handled = true;
	}
	return handled;
}
