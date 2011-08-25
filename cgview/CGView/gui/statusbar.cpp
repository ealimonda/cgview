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

#include <QLabel> // QLabel

StatusBar::StatusBar()
{
	this->_vertLabel = new QLabel("Vertexes: ");
	this->_faceLabel = new QLabel("Faces: ");
	this->_edgeLabel = new QLabel("Edges: ");
	this->_timeLabel = new QLabel("Time(ms): ");
	this->_v = new QLabel("");
	this->_f = new QLabel("");
	this->_e = new QLabel("");
	this->_t = new QLabel("");

	this->_vert_total = 0;
	this->_edge_total = 0;
	this->_face_total = 0;

	this->addPermanentWidget(this->_vertLabel, 0);
	this->addPermanentWidget(this->_v, 1);
	this->addPermanentWidget(this->_faceLabel, 0);
	this->addPermanentWidget(this->_f, 1);
	this->addPermanentWidget(this->_edgeLabel, 0);
	this->addPermanentWidget(this->_e, 1);
	this->addPermanentWidget(this->_timeLabel, 0);
	this->addPermanentWidget(this->_t, 1);
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

		//this->_v->setNum(v);
		this->_v->setText(QString::number(v) + QString(" (") + QString::number(this->_vert_total) + QString(")"));
		this->_f->setText(QString::number(f) + QString(" (") + QString::number(this->_face_total) + QString(")"));
		this->_e->setText(QString::number(e) + QString(" (") + QString::number(this->_edge_total) + QString(")"));
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
