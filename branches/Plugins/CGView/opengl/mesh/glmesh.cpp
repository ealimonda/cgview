/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: glmesh.cpp                                                       *
 * Description: OpenGL mesh handling functions                                *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "glmesh.h"
#include "pluginmanager.h" // PluginManager
#include "interfaces.h" // PluginTransformInterface

/** Make the selected property of the mesh **/
GLuint GLMesh::makeProp(MeshProperty p)
{
	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	switch (p)
	{
	case kPropertyBox:
	  {
		CGPoint min = this->_m->bbox.min;
		CGPoint max = this->_m->bbox.max;

		/*
			     7----------6
			    /|         /|
			   / |        / |
			  3----------2  |
			  |  |       |  |
			  |  4-------|--5
			  | /        | /
			  |/         |/
			  0----------1
		 */

		// WIRED BOUNDING BOX
		if (this->_vis.isBoxWired())
		{
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			glLineWidth(1.5f);

			//01
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glEnd();
			//32
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glEnd();
			//45
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();
			//76
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();

			//03
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glEnd();
			//12
			glBegin(GL_LINES);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glEnd();
			//47
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();
			//56
			glBegin(GL_LINES);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();

			//04
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();
			//15
			glBegin(GL_LINES);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();
			//37
			glBegin(GL_LINES);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();
			//26
			glBegin(GL_LINES);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();

			glEnable(GL_LIGHTING);
			glPopMatrix();
		  }

		// OTHERS
		if (this->_vis.isBoxTrans() || this->_vis.isBoxSolid())
		{
			glPushMatrix();

			// SOLID BOUNDING BOX
			if (this->_vis.isBoxSolid())
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			// TRANSPARENT BOUNDING BOX
			if (this->_vis.isBoxTrans())
			{
				glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}

			//0123
			glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glEnd();

			//0154
			glBegin(GL_QUADS);
			glNormal3f(0, -1, 0);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();

			//1562
			glBegin(GL_QUADS);
			glNormal3f(1, 0, 0);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glEnd();

			//3267
			glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();

			//4037
			glBegin(GL_QUADS);
			glNormal3f(-1, 0, 0);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)min[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();

			//4567
			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)min[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)max[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glVertex3f((GLfloat)min[kCoordX], (GLfloat)max[kCoordY], (GLfloat)max[kCoordZ]);
			glEnd();

			if (this->_vis.isBoxTrans())
				glDisable(GL_BLEND);

			glPopMatrix();
		}
	  }
		break;

	case kPropertyMesh:
	  {
		/// Min quality
		double q_min = 0;
		/// Max quality
		double q_max = 0;

		// Calculate the vertex min and max quality
		if (this->_vis.isColorQualityV())
		{
			if (this->_m->vn > 0)
			{
				q_min = this->_m->vert[0].Q();
				q_max = q_min;

				for (int i = 1; i < this->_m->vn; ++i)
				{
					double q = this->_m->vert[i].Q();
					if (q < q_min)
						q_min = q;
					if (q > q_max)
						q_max = q;
				}
			}
		}
		// Calculate the face min and max quality
		if (this->_vis.isColorQualityF())
		{
			if (this->_m->fn > 0)
			{
				q_min = this->_m->face[0].Q();
				q_max = q_min;

				for (int i = 1; i < this->_m->fn; ++i)
				{
					double q = this->_m->face[i].Q();
					if (q < q_min)
						q_min = q;
					if (q > q_max)
						q_max = q;
				}
			}
		}

		glPushMatrix();

		// If the material is enabled
		if (this->_vis.isColorMaterial())
		{
			glDisable(GL_COLOR_MATERIAL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			this->_mat.getMaterial();
		}

		// If it's only a points cloud
		if (this->_m->fn == 0)
		{
			this->_vis.enableMeshPoint();
		}

		// If color is disabled
		if (!this->_vis.isColorEnabled())
		{
			glColor4f(1.0, 1.0, 1.0, 1.0);
			//glColor4f(0.8, 0.8, 0.8, 1.0);
		}

		////////////////////
		// TEXTURE TO BE IMPLEMENTED
		if (this->_vis.isColorTexture())
		{
			glColor4f(0.5, 0.5, 0.5, 1.0);
		}
		////////////////////

		// POINTS
		if (this->_vis.isMeshPoint())
		{
			for (int i = 0; i < this->_m->vn; ++i)
			{
				if ((this->_vis.isColorVertex()) || (this->_vis.isColorFace()))
					glColor4ubv(this->_m->vert[i].C().V());
				if (this->_vis.isColorQualityV())
				{
					vcg::Color4b c;
					double hue;
					if (q_min != q_max)
					{
						hue = ((this->_m->vert[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
						c.SetHSVColor(hue, 1.0f, 1.0f);
					}
					else
					{
						hue = 0.0f;
						c.SetHSVColor(hue, 0.0f, 0.5f);
					}

					glColor4ubv(c.V());
				}
				if (this->_vis.isColorQualityF())
					glColor4f(0.5, 0.5, 0.5, 1.0);
				glBegin(GL_POINTS);
				glNormal3f((GLfloat)this->_m->vert[i].N()[kCoordX],
						(GLfloat)this->_m->vert[i].N()[kCoordY],
						(GLfloat)this->_m->vert[i].N()[kCoordZ]);
				glVertex3f((GLfloat)this->_m->vert[i].P()[kCoordX],
						(GLfloat)this->_m->vert[i].P()[kCoordY],
						(GLfloat)this->_m->vert[i].P()[kCoordZ]);
				glEnd();
			}
		}

		// FLAT SHADING
		if (this->_vis.isMeshFlat())
		{
			for (int i = 0; i < this->_m->fn; ++i)
			{
				if (this->_vis.isColorFace())
					glColor4ubv(_m->face[i].C().V());
				if (this->_vis.isColorQualityF())
				{
					vcg::Color4b c;
					double hue;
					if (q_min != q_max)
					{
						hue = ((this->_m->face[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
						c.SetHSVColor(hue, 1.0f, 1.0f);
					}
					else
					{
						hue = 0.0f;
						c.SetHSVColor(hue, 0.0f, 0.5f);
					}

					glColor4ubv(c.V());
				}

				glBegin(GL_TRIANGLES);

				glNormal3f((GLfloat)this->_m->face[i].N()[kCoordX],
						(GLfloat)this->_m->face[i].N()[kCoordY],
						(GLfloat)this->_m->face[i].N()[kCoordZ]);
				for (unsigned int j = 0; j < 3; ++j)
				{
					if (this->_vis.isColorVertex() )
						glColor4ubv(this->_m->face[i].V(j)->C().V());
					if (this->_vis.isColorQualityV())
					{
						vcg::Color4b c;
						double hue;
						if (q_min != q_max)
						{
							hue = ((this->_m->face[i].V(j)->Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
							c.SetHSVColor(hue, 1.0f, 1.0f);
						}
						else
						{
							hue = 0.0f;
							c.SetHSVColor(hue, 0.0f, 0.5f);
						}

						glColor4ubv(c.V());
					}

					glVertex3f((GLfloat)this->_m->face[i].P(j)[kCoordX],
							(GLfloat)this->_m->face[i].P(j)[kCoordY],
							(GLfloat)this->_m->face[i].P(j)[kCoordZ]);
				}

				glEnd();
			}
		}

		// SMOOTH SHADING
		if (this->_vis.isMeshSmooth())
		{
			for (int i = 0; i < this->_m->fn; ++i)
			{
				if (this->_vis.isColorFace())
					glColor4ubv(this->_m->face[i].C().V());
				if (this->_vis.isColorQualityF())
				{
					vcg::Color4b c;
					double hue;
					if (q_min != q_max)
					{
						hue = ((this->_m->face[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
						c.SetHSVColor(hue, 1.0f, 1.0f);
					}
					else
					{
						hue = 0.0f;
						c.SetHSVColor(hue, 0.0f, 0.5f);
					}

					glColor4ubv(c.V());
				}

				glBegin(GL_TRIANGLES);

				for (unsigned int j = 0; j < 3; ++j)
				{
					if (this->_vis.isColorVertex())
						glColor4ubv(this->_m->face[i].V(j)->C().V());
					if (this->_vis.isColorQualityV())
					{
						vcg::Color4b c;
						double hue;
						if (q_min != q_max)
						{
							hue = ((this->_m->face[i].V(j)->Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
							c.SetHSVColor(hue, 1.0f, 1.0f);
						}
						else
						{
							hue = 0.0f;
							c.SetHSVColor(hue, 0.0f, 0.5f);
						}

						glColor4ubv(c.V());
					}
					glNormal3f((GLfloat)this->_m->face[i].V(j)->N()[kCoordX],
							(GLfloat)this->_m->face[i].V(j)->N()[kCoordY],
							(GLfloat)this->_m->face[i].V(j)->N()[kCoordZ]);
					glVertex3f((GLfloat)this->_m->face[i].P(j)[kCoordX],
							(GLfloat)this->_m->face[i].P(j)[kCoordY],
							(GLfloat)this->_m->face[i].P(j)[kCoordZ]);
				}

				glEnd();
			}
		}

		// VOXEL
		if (this->_vis.isMeshVoxel())
		{
			//////////////////////
			//under construction//
			//////////////////////
		}

		// If the material is enabled
		if (this->_vis.isColorMaterial())
		{
			glEnable(GL_COLOR_MATERIAL);
			glDisable(GL_BLEND);
		}

		glPopMatrix();
	  }
		break;

	case kPropertyWireframe:
	  {
		// Min quality
		double q_min = 0;
		// Max quality
		double q_max = 0;

		// Calculate the vertex min and max quality
		if (!this->_vis.isMeshEnabled() && this->_vis.isColorQualityV())
		{
			if (this->_m->vn > 0)
			{
				q_min = this->_m->vert[0].Q();
				q_max = q_min;

				for (int i = 1; i < this->_m->vn; ++i)
				{
					double q = this->_m->vert[i].Q();
					if (q < q_min)
						q_min = q;
					if (q > q_max)
						q_max = q;
				}
			}
		}
		// Calculate the face min and max quality
		if (!this->_vis.isMeshEnabled() && this->_vis.isColorQualityF())
		{
			if (this->_m->fn > 0)
			{
				q_min = this->_m->face[0].Q();
				q_max = q_min;

				for (int i = 1; i < this->_m->fn; ++i)
				{
					double q = this->_m->face[i].Q();
					if( q < q_min )
						q_min = q;
					if( q > q_max )
						q_max = q;
				}
			}
		}

		glPushMatrix();

		// If it's only a points cloud
		if (this->_m->fn == 0)
		{
			this->_vis.disableWireframe();
		}

		// WIREFRAME
		if (this->_vis.isWireframeEnabled())
		{
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

			if (this->_vis.isMeshEnabled())
				glLineWidth(1.5f);
			else
				glLineWidth(1.0f);

			for (int i = 0; i < this->_m->fn; ++i)
			{
				if (!this->_vis.isMeshEnabled() && this->_vis.isColorFace())
					glColor4ubv(this->_m->face[i].C().V());
				if (!this->_vis.isMeshEnabled() && this->_vis.isColorQualityF())
				{
					vcg::Color4b c;
					double hue;
					if (q_min != q_max)
						hue = ((this->_m->face[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
					else
						hue = 0.0f;
					c.SetHSVColor(hue, 1.0f, 1.0f);

					glColor4ubv(c.V());
				}

				glBegin(GL_LINE_LOOP);

				for (unsigned int j = 0; j < 3; ++j)
				{
					if (!this->_vis.isMeshEnabled() && this->_vis.isColorVertex())
						glColor4ubv(this->_m->face[i].V(j)->C().V());
					if (!this->_vis.isMeshEnabled() && this->_vis.isColorQualityV())
					{
						vcg::Color4b c;
						double hue;
						if (q_min != q_max)
							hue = ((this->_m->face[i].V(j)->Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
						else
							hue = 0.0f;
						c.SetHSVColor(hue, 1.0f, 1.0f);

						glColor4ubv(c.V());
					}

					glNormal3f((GLfloat)this->_m->face[i].V(j)->N()[kCoordX],
							(GLfloat)this->_m->face[i].V(j)->N()[kCoordY],
							(GLfloat)this->_m->face[i].V(j)->N()[kCoordZ]);
					glVertex3f((GLfloat)this->_m->face[i].P(j)[kCoordX],
							(GLfloat)this->_m->face[i].P(j)[kCoordY],
							(GLfloat)this->_m->face[i].P(j)[kCoordZ]);
				}

				glEnd();
			}
		}
		glPopMatrix();
	  }
		break;

	case kPropertyColor:
		// TODO: Implement color property
		break;

	case kPropertyPlugins:
	  {
		std::vector<PluginVisualizationInterface *> visualizationPlugins = PluginManager::sharedInstance()->visualizationPlugins();
		for (unsigned int i = 0; i < visualizationPlugins.size(); ++i)
		{
			if (visualizationPlugins[i]->isEnabled())
			{
				visualizationPlugins[i]->doVisualize(this->_m);
			}
		}
	  }
		break;

	case kPropertiesMax:
		assert(false);
		break;
	}
	glEndList();
	return list;
}
