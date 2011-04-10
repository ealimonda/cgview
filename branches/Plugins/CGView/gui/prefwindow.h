/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: prefwindow.h                                                     *
 * Description: Preferences Dialog                                            *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_GUI_PREFWINDOW_H
#define CGVIEW_GUI_PREFWINDOW_H

#include <QDialog>
QT_BEGIN_NAMESPACE
class QWidget;
class QShowEvent;
class QCloseEvent;
class QLineEdit;
class QGridLayout;
QT_END_NAMESPACE
class GLIntro;
class PrefController;

class PrefWindow : public QDialog
{
	Q_OBJECT
public:
	explicit PrefWindow(QWidget *parent = 0);

protected:
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	void setUI(void);

	QLineEdit *_generalBackgroundGradientTopLeftLine;
	QLineEdit *_generalBackgroundGradientBottomLeftLine;
	QLineEdit *_generalBackgroundGradientTopRightLine;
	QLineEdit *_generalBackgroundGradientBottomRightLine;
	QLineEdit *_generalDefaultDirectoryLine;

	QGridLayout *_pluginsRenderingLayout;
	QGridLayout *_pluginsVisualizationLayout;
	QGridLayout *_pluginsTransformationLayout;
	QGridLayout *_pluginsUIInputLayout;
};

#endif // CGVIEW_GUI_PREFWINDOW_H
