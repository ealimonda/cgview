/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: aboutwindow.cpp                                                  *
 * Description: About Dialog                                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "aboutwindow.h"

#include <QBoxLayout>
#include <QPushButton>
#include "opengl/intro/glintro.h"

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent)
{
	this->setBaseSize(640, 400);
	this->setMinimumSize(640, 400);
	this->resize(640, 400);
	this->setModal(true);

	QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	QScrollArea *glIntroArea = new QScrollArea(this);
	this->_glIntro = new GLIntro(glIntroArea, false);
	QLabel *aboutLabel = new QLabel("CGView\n\n"
			"A lightweight 3D viewer for computer graphics students\n"
			"http://code.google.com/p/cgview/", this);
	glIntroArea->setWidget(this->_glIntro);
	this->_glIntro->resize(600, 350);
	glIntroArea->setWidgetResizable(true);
	glIntroArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	glIntroArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	glIntroArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	glIntroArea->resize(600, 350);

	QPushButton *closeButton = new QPushButton("Close", this);
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	layout->addWidget(glIntroArea);
	layout->addWidget(aboutLabel);
	layout->addWidget(closeButton);
	this->setLayout(layout);
	this->setWindowTitle(tr("About CGView"));
}

void AboutWindow::showEvent(QShowEvent */*event*/)
{
	this->_glIntro->startCube();
}

void AboutWindow::closeEvent(QCloseEvent */*event*/)
{
	this->_glIntro->stopCube();
}
