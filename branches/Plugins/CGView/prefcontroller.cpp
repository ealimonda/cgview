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
	memcpy(&this->_gradientColors[0][0], &this->kDefaultGradientColors[0][0], sizeof(this->_gradientColors));
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
		basePath = new QString(this->bundlePath() + "/..");
#else // ! Q_OS_MAC
		basePath = qApp->applicationDirPath();
#endif
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
