/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: pluginmanager.cpp                                                *
 * Description: Plugin Manager class                                          *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "pluginmanager.h"
#include <QObject>
#include <QDir> // class QDir
#include <QPluginLoader> // class QPluginLoader
#ifdef Q_OS_MAC
#include <CoreFoundation/CoreFoundation.h> // CF*
#else // ! Q_OS_MAC
#include <QApplication> // qApp
#endif // Q_OS_MAC
#include "interfaces.h" // class PluginTransformInterface

PluginManager *PluginManager::_sharedInstance = NULL;

int PluginManager::loadPlugins_sub(QObjectList plugins, bool recursive)
{
	int loadedCount = 0;
	foreach (QObject *plugin, plugins)
	{
		PluginType type = this->getTypeForPlugin(plugin);
		switch (type)
		{
		case PluginManager::kTypeInvalid:
			continue;
		case PluginManager::kTypeCollection:
			if (recursive)
			{
				CGViewPluginCollectionInterface * collection = qobject_cast<CGViewPluginCollectionInterface *>(plugin);
				loadedCount += this->loadPlugins_sub(collection->plugins(), false);
			}
			continue;
		case PluginManager::kTypeRender:
		case PluginManager::kTypeTransform:
		case PluginManager::kTypeVisualization:
			emit loadedPlugin(plugin, type);
			++loadedCount;
		}
	}
	return loadedCount;
}

int PluginManager::loadPlugins(void)
{
	QDir pluginsDir;
	int loadedCount = 0;
	this->_transformPlugins.clear();
	this->_renderPlugins.clear();
	this->_visualizationPlugins.clear();

#ifdef Q_OS_MAC
//	pluginsDir = QDir(this->getBundlePath() + "/Contents/Resources/Plugins");
	pluginsDir = QDir(this->bundlePath() + "/../plugins");
#else // ! Q_OS_MAC
	pluginsDir = QDir(qApp->applicationDirPath() + "/plugins");
#endif // !Q_OS_MAC

	// Load static plugins
	loadedCount += this->loadPlugins_sub(QPluginLoader::staticInstances(), true);

	// Load dynamic plugins
	QObjectList dynamicPlugins = QObjectList();
	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		QObject *plugin = loader.instance();
		if (!plugin)
			continue;
		dynamicPlugins.append(plugin);
	}
	loadedCount += this->loadPlugins_sub(dynamicPlugins, true);
	return loadedCount;
}

PluginManager::PluginType PluginManager::getTypeForPlugin( QObject *plugin ) {
	if (qobject_cast<CGViewPluginCollectionInterface *>(plugin))
		return PluginManager::kTypeCollection;
	if (qobject_cast<PluginTransformInterface *>(plugin))
		return PluginManager::kTypeTransform;
	if (qobject_cast<PluginRenderInterface *>(plugin))
		return PluginManager::kTypeRender;
	if (qobject_cast<PluginVisualizationInterface *>(plugin))
		return PluginManager::kTypeVisualization;
	return PluginManager::kTypeInvalid;
}

#ifdef Q_OS_MAC
/**
 * Get the path to the Application Bundle
 * \return	path
 */
QString PluginManager::bundlePath(void)
{
	static QString *bundlePath = NULL;
	if (!bundlePath)
	{
		CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
		CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef, kCFURLPOSIXPathStyle);
		const char *pathPtr = CFStringGetCStringPtr(macPath, CFStringGetSystemEncoding());
		bundlePath = new QString(pathPtr);
		CFRelease(appUrlRef);
		CFRelease(macPath);
	}
	return *bundlePath;
}
#endif // Q_WS_MAC

void PluginManager::setupPlugin(QObject *plugin, PluginManager::PluginType type)
{
	switch (type)
	{
	case PluginManager::kTypeTransform:
	  {
		PluginTransformInterface *thisPlugin = qobject_cast<PluginTransformInterface *>(plugin);
		if (thisPlugin)
			this->_transformPlugins.push_back(thisPlugin);
	  }
		return;
	case PluginManager::kTypeRender:
	  {
		PluginRenderInterface *thisPlugin = qobject_cast<PluginRenderInterface *>(plugin);
		if (thisPlugin)
			this->_renderPlugins.push_back(thisPlugin);
	  }
		return;
	case PluginManager::kTypeVisualization:
	  {
		PluginVisualizationInterface *thisPlugin = qobject_cast<PluginVisualizationInterface *>(plugin);
		if (thisPlugin)
			this->_visualizationPlugins.push_back(thisPlugin);
	  }
		return;
	case PluginManager::kTypeInvalid:
	case PluginManager::kTypeCollection:
		assert(false);
		return;
	}
}
