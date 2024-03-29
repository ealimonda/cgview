/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: prefcontroller.h                                                 *
 * Description: Preferences Controller class                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_PREFCONTROLLER_H
#define CGVIEW_PREFCONTROLLER_H

#include <QObject>
#include <QMutex> // class QMutex
#include <QtOpenGL> // GLFloat
#include "opengl/scene/light/gllight.h"

class PrefController : public QObject
{
	Q_OBJECT
public:
	static PrefController *sharedInstance()
	{
		static QMutex mutex;
		if (!_sharedInstance)
		{
			mutex.lock();
			if (!_sharedInstance)
				_sharedInstance = new PrefController;
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
#ifdef Q_OS_MAC
	QString bundlePath(void);
#endif // Q_OS_MAC
	QString basePath(void);
	inline const GLfloat *gradientColors(unsigned int idx) const
	{
		if (idx <= sizeof(this->_gradientColors)/sizeof(this->_gradientColors[0]))
			return this->_gradientColors[idx];
		return NULL;
	}
	inline const unsigned int gradientColorComponent(unsigned int idx, unsigned int component) const
	{
		if (idx <= sizeof(this->_gradientColors)/sizeof(this->_gradientColors[0]))
			return (int)(this->_gradientColors[idx][component] * 255);
		return 0;
	}
	inline void setGradientColorComponent(unsigned int idx, unsigned int component, unsigned int value)
	{
		if (idx <= sizeof(this->_gradientColors)/sizeof(this->_gradientColors[0]))
			this->_gradientColors[idx][component] = value / 255.;
		return;
	}
	inline const QString defaultDirectory(void) const
	{
		return this->_defaultDirectory;
	}
	inline void setDefaultDirectory(QString directory)
	{
		this->_defaultDirectory = directory;
	}

public slots:
	void load(void);
	void save(void);

private:
	PrefController();

	// Hide copy constructor and assign operator
	PrefController(const PrefController &);
	PrefController& operator=(const PrefController &);

	static PrefController *_sharedInstance;
	static const GLfloat kDefaultGradientColors[4][GLLight::kChannelsRGBA];

	GLfloat _gradientColors[4][GLLight::kChannelsRGBA];
	QString _defaultDirectory;
};

#endif // CGVIEW_PREFCONTROLLER_H
