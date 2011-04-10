/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: aboutwindow.h                                                    *
 * Description: About Dialog                                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_GUI_ABOUTWINDOW_H
#define CGVIEW_GUI_ABOUTWINDOW_H

#include <QDialog>
QT_BEGIN_NAMESPACE
class QWidget;
class QShowEvent;
class QCloseEvent;
QT_END_NAMESPACE
class GLIntro;

class AboutWindow : public QDialog
{
	Q_OBJECT
public:
	explicit AboutWindow(QWidget *parent = 0);

protected:
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	GLIntro *_glIntro;
};

#endif // CGVIEW_GUI_ABOUTWINDOW_H
