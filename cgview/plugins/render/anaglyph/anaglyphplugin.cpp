/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: anaglyphplugin.cpp                                               *
 * Description: Anaglyph render mode plugin                                   *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "anaglyphplugin.h"

#include <QtPlugin> // Q_EXPORT_PLUGIN2
//#include <QtOpenGL> // QT_*
#include <opengl/glwindow.h> // GLWindow
#include <mesh_definition.h> // CGMesh

AnaglyphPlugin::AnaglyphPlugin()
{
	this->_menuName = tr("3D Anaglyph");
	this->setEnabled(false);
}

void AnaglyphPlugin::doRender(std::vector<GLMesh> &mesh, GLWindow *window) const
{
	if (!window)
		return;
	glDrawBuffer(GL_BACK);
	glReadBuffer(GL_BACK);

	glClear(GL_ACCUM_BUFFER_BIT);

	/* Left eye */
	glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
	window->camera()->camProjection();
	window->camera()->camPosition(GLCamera::kEyePositionLeft);
	for (unsigned int i = 0; i < mesh.size(); ++i)
	{
		mesh[i].drawMesh();
	}
	glFlush();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glAccum(GL_LOAD, 1.0); /* Could also use glAccum(GL_ACCUM, 1.0); */

	glDrawBuffer(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT
#ifdef Q_WS_X11
 /* TODO: Find a workaround for this.  Some computers or virtual machines need
  * it, while some others won't work properly with it at all.
  * Seems to depend on the OS and the graphics card. */
			| GL_COLOR_BUFFER_BIT
#endif // Q_WS_X11
	);

	/* Right eye */
	glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
	window->camera()->camProjection();
	window->camera()->camPosition(GLCamera::kEyePositionCenter);
	for (unsigned int i = 0; i < mesh.size(); ++i)
	{
		mesh[i].drawMesh();
	}
	glFlush();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glAccum(GL_ACCUM, 1.0);
	glAccum(GL_RETURN, 1.0);
}

void AnaglyphPlugin::enable(bool state)
{
	this->setEnabled(state);
	emit(toggled());
}

void AnaglyphPlugin::loaded(void) {
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(render_anaglyph, AnaglyphPlugin)
QT_END_NAMESPACE
