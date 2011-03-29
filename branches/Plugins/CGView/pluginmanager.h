/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: pluginmanager.h                                                  *
 * Description: Plugin Manager class                                          *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PLUGINMANAGER_H
#define CGVIEW_PLUGINMANAGER_H

#include <vector> // std::vector
#include <QObject> // class QObject
#include <QStringList> // class QStringList
#include <QMutex> // class QMutex
#include "interfaces.h" // Plugin*Interface

class PluginManager : public QObject
{
	Q_OBJECT
public:
	typedef enum
	{
		kTypeInvalid = -1,
		kTypeCollection = 0,
		kTypeTransform,
		kTypeRender,
		kTypeVisualization,
		kTypeUIInput,
	} PluginType;

	static PluginManager *sharedInstance()
	{
		static QMutex mutex;
		if (!_sharedInstance)
		{
			mutex.lock();
			if (!_sharedInstance)
				_sharedInstance = new PluginManager;
			mutex.unlock();
		}
		return _sharedInstance;
	}

	static void drop(void)
	{
		static QMutex mutex;
		mutex.lock();
		delete _sharedInstance;
		_sharedInstance = 0;
		mutex.unlock();
	}

	int loadPlugins(void);
	inline const std::vector<PluginTransformInterface *> &transformPlugins(void)
	{
		return this->_transformPlugins;
	}
	inline const std::vector<PluginRenderInterface *> &renderPlugins(void)
	{
		return this->_renderPlugins;
	}
	inline const std::vector<PluginVisualizationInterface *> &visualizationPlugins(void)
	{
		return this->_visualizationPlugins;
	}
	inline const std::vector<PluginUIInputInterface *> &uiInputPlugins(void)
	{
		return this->_uiInputPlugins;
	}

public slots:
	void setupPlugin(QObject *plugin, PluginManager::PluginType type);

private:
	PluginManager() {}
	PluginType getTypeForPlugin(QObject *plugin);
	int loadPlugins_sub(QObjectList plugins, bool recursive);
#ifdef Q_OS_MAC
	QString bundlePath(void);
#endif // Q_OS_MAC
	QStringList _pluginFileNames; // FIXME: Do we need this at all?
	std::vector<PluginTransformInterface *> _transformPlugins;
	std::vector<PluginRenderInterface *> _renderPlugins;
	std::vector<PluginVisualizationInterface *> _visualizationPlugins;
	std::vector<PluginUIInputInterface *> _uiInputPlugins;

	// Hide copy constructor and assign operator
	PluginManager(const PluginManager &);
	PluginManager& operator=(const PluginManager &);

	static PluginManager *_sharedInstance;

signals:
	void loadedPlugin(QObject *plugin, PluginManager::PluginType type);
	void visualizationPluginToggled(void);
	void renderPluginToggled(void);
	void uiInputEvent(InputEvents::EventType, int value);
};

#endif // CGVIEW_PLUGINMANAGER_H
