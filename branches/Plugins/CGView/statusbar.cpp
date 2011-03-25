/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: statusbar.cpp                                                    *
 * Description: Status Bar for the CGView application                         *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "statusbar.h"

StatusBar::StatusBar()
{
	this->_layout = new QGridLayout;
	this->_layout->setContentsMargins(10, 0, 0, 0);
	this->_layout->setColumnStretch(0, 0);
	this->_layout->setColumnStretch(1, 1);
	this->_layout->setColumnStretch(2, 0);
	this->_layout->setColumnStretch(3, 1);
	this->_layout->setColumnStretch(4, 0);
	this->_layout->setColumnStretch(5, 1);
	this->_layout->setColumnStretch(6, 0);
	this->_layout->setColumnStretch(7, 1);

	this->_vertLabel = new QLabel("Vertex : ");
	this->_faceLabel = new QLabel("Face : ");
	this->_edgeLabel = new QLabel("Edge : ");
	this->_timeLabel = new QLabel("Time(ms) : ");
	this->_v = new QLabel("");
	this->_f = new QLabel("");
	this->_e = new QLabel("");
	this->_t = new QLabel("");

	this->_layout->addWidget(this->_v, 0, 1);
	this->_layout->addWidget(this->_f, 0, 3);
	this->_layout->addWidget(this->_e, 0, 5);
	this->_layout->addWidget(this->_t, 0, 7);
	this->_layout->addWidget(this->_vertLabel, 0, 0);
	this->_layout->addWidget(this->_faceLabel, 0, 2);
	this->_layout->addWidget(this->_edgeLabel, 0, 4);
	this->_layout->addWidget(this->_timeLabel, 0, 6);

	this->setLayout(this->_layout);
	this->refreshInfo();
}

void StatusBar::refreshInfo(void)
{
	if (this->_loaded)
	{
		int v = this->_vert;
		int f = this->_face;
		int e = this->_edge;
		int t = this->_time;

		this->_v->setNum(v);
		this->_f->setNum(f);
		this->_e->setNum(e);
		this->_t->setNum(t);
	}
	else
	{
		this->_v->setText("");
		this->_f->setText("");
		this->_e->setText("");
		this->_t->setText("");
	}

	this->_v->update();
	this->_f->update();
	this->_e->update();
	this->_t->update();
}