/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: prefcontroller.cpp                                               *
 * Description: Preferences Controller class                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "prefcontroller.h"
#include <QSettings>
#include <QDir>
#ifdef Q_OS_MAC
#include <CoreFoundation/CoreFoundation.h> // CF*
#else // ! Q_OS_MAC
#include <QApplication> // qApp
#endif // Q_OS_MAC

PrefController *PrefController::_sharedInstance = NULL;

const GLfloat PrefController::kDefaultGradientColors[4][GLLight::kChannelsRGBA] =
{
	{ 0.196f, 0.423f, 0.384f, 1.0f },
	{ 0.254f, 0.086f, 0.333f, 1.0f },
	{ 0.196f, 0.423f, 0.384f, 1.0f },
	{ 0.254f, 0.086f, 0.333f, 1.0f },
};

PrefController::PrefController()
{
	this->load();
	this->save();
}

/**
 * Get the base application path
 * \return	path
 */
QString PrefController::basePath(void)
{
	static QString *basePath = NULL;
	if (!basePath)
	{
#ifdef Q_OS_MAC
		QDir pathDir(this->bundlePath() + "/..");
#else // ! Q_OS_MAC
		static QDir pathDir(qApp->applicationDirPath());
#endif
		basePath = new QString(pathDir.canonicalPath());
	}
	return *basePath;
}

#ifdef Q_OS_MAC
/**
 * Get the path to the Application Bundle
 * \return	path
 */
QString PrefController::bundlePath(void)
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

void PrefController::load(void)
{
	QSettings settings(QString(this->basePath() + "/cgview.ini"), QSettings::IniFormat);
	this->_defaultDirectory = settings.value("directories/defaultDirectory", this->basePath()).toString();
	char kRGBALetters[4] = {'R', 'G', 'B', 'A'};
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			this->_gradientColors[i][j] = settings.value(
					QString("colors/gradient%1_%2").arg(i).arg(kRGBALetters[j]),
					(int)(255 * this->kDefaultGradientColors[i][j])).toInt() / 255.0f;
}

void PrefController::save(void)
{
	QSettings settings(QString(this->basePath() + "/cgview.ini"), QSettings::IniFormat);
	settings.clear();
	settings.setValue("directories/defaultDirectory", this->_defaultDirectory);
	char kRGBALetters[4] = {'R', 'G', 'B', 'A'};
	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			settings.setValue(QString("colors/gradient%1_%2").arg(i).arg(kRGBALetters[j]),
					(int)(255 * this->_gradientColors[i][j]));
	settings.sync();
}
