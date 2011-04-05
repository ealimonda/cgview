/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: statusbar.h                                                      *
 * Description: Status bar for the CGView application                         *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_STATUSBAR_H
#define CGVIEW_STATUSBAR_H

#include <QtGui> // QWidget

class StatusBar : public QStatusBar
{
	Q_OBJECT

public:
	StatusBar();

public slots:
	inline void setInfo(const unsigned int v, const unsigned int f, const unsigned int t)
	{
		this->_vert = v;
		this->_face = f;
		this->_edge = (3 * _face) / 2;
		this->_time = t;

		this->_loaded = true;
		this->refreshInfo();
	}
	inline void setTime(const unsigned int t)
	{
		this->_time = t;
		this->refreshInfo();
	}

	inline void reset(void)
	{
		this->_vert = 0;
		this->_face = 0;
		this->_edge = 0;
		this->_time = 0;
		this->_loaded = false;
		this->refreshInfo();
	}

private:
	void refreshInfo(void);

	QLabel* _vertLabel;
	QLabel* _faceLabel;
	QLabel* _edgeLabel;
	QLabel* _timeLabel;
	QLabel* _v;
	QLabel* _f;
	QLabel* _e;
	QLabel* _t;
	unsigned int _vert;
	unsigned int _face;
	unsigned int _edge;
	unsigned int _time;
	bool _loaded;
};

#endif // CGVIEW_STATUSBAR_H
