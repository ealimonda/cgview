#include "glmesh.h"

//Make the selected property of the mesh
GLuint GLMesh::makeProp(MeshProp p = MESH)
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    switch(p)
    {
    case BOX:
        {
            CGPoint min = _m->bbox.min;
            CGPoint max = _m->bbox.max;

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

            //WIRED BOUNDING BOX
            if(_vis.isBoxWired())
            {
                glPushMatrix();
                glDisable(GL_LIGHTING);
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

                glLineWidth(1.5f);

                //01
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)min[2]);
                glEnd();
                //32
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)min[2]);
                glEnd();
                //45
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)max[2]);
                glEnd();
                //76
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();

                //03
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)min[2]);
                glEnd();
                //12
                glBegin(GL_LINES);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)min[2]);
                glEnd();
                //47
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();
                //56
                glBegin(GL_LINES);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();

                //04
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)max[2]);
                glEnd();
                //15
                glBegin(GL_LINES);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)max[2]);
                glEnd();
                //37
                glBegin(GL_LINES);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();
                //26
                glBegin(GL_LINES);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();

                glEnable(GL_LIGHTING);
                glPopMatrix();
            }

            //OTHERS
            if(_vis.isBoxTrans() || _vis.isBoxSolid())
            {
                glPushMatrix();

                //SOLID BOUNDING BOX
                if(_vis.isBoxSolid()) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

                //TRANSPARENT BOUNDING BOX
                if(_vis.isBoxTrans())
                {
                    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }

                //0123
                glBegin(GL_QUADS);
                glNormal3f(0,0,-1);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)min[2]);
                glEnd();

                //0154
                glBegin(GL_QUADS);
                glNormal3f(0,-1,0);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)max[2]);
                glEnd();

                //1562
                glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)min[2]);
                glEnd();

                //3267
                glBegin(GL_QUADS);
                glNormal3f(0,1,0);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();

                //4037
                glBegin(GL_QUADS);
                glNormal3f(-1,0,0);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)min[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();

                //4567
                glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glVertex3f((GLfloat)min[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)min[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)max[0],(GLfloat)max[1],(GLfloat)max[2]);
                glVertex3f((GLfloat)min[0],(GLfloat)max[1],(GLfloat)max[2]);
                glEnd();

                if(_vis.isBoxTrans()) glDisable(GL_BLEND);

                glPopMatrix();
            }
        }
        break;

    case MESH:
        {
            //Min quality
            double q_min;
            //Max quality
            double q_max;

            //Calculate the vertex min and max quality
            if(_vis.isColorQualityV())
            {
                if(_m->vn > 0)
                {
                    q_min = _m->vert[0].Q();
                    q_max = q_min;

                    for(int i = 1; i < _m->vn; i++)
                    {
                        double q = _m->vert[i].Q();
                        if(q < q_min) q_min = q;
                        if(q > q_max) q_max = q;
                    }
                }
            }
            //Calculate the face min and max quality
            if(_vis.isColorQualityF())
            {
                if(_m->fn > 0)
                {
                    q_min = _m->face[0].Q();
                    q_max = q_min;

                    for(int i = 1; i < _m->fn; i++)
                    {
                        double q = _m->face[i].Q();
                        if(q < q_min) q_min = q;
                        if(q > q_max) q_max = q;
                    }
                }
            }

            glPushMatrix();

            //If the material is enabled
            if(_vis.isColorMaterial())
            {
                glDisable(GL_COLOR_MATERIAL);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                _mat.getMaterial();
            }

            //If it's only a points cloud
            if(_m->fn == 0)
            {
                _vis.Enable_Mesh_Point();
            }

            //If color is disabled
            if(_vis.isColorDisabled())
            {
                glColor4f(1.0, 1.0, 1.0, 1.0);
                //glColor4f(0.8, 0.8, 0.8, 1.0);
            }

            ////////////////////
            //TEXTURE TO BE IMPLEMENTED
            if(_vis.isColorTexture())
            {
                glColor4f(0.5, 0.5, 0.5, 1.0);
            }
            ////////////////////

            //POINTS
            if(_vis.isMeshPoint())
            {
                for(int i = 0; i < _m->vn; i++)
                {
                    if((_vis.isColorVertex()) || (_vis.isColorFace())) glColor4ubv(_m->vert[i].C().V());
                    if(_vis.isColorQualityV())
                    {
                        vcg::Color4b c;
                        double hue;
                        if(q_min != q_max)
                        {
                            hue = ((_m->vert[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
                            c.SetHSVColor(hue, 1.0f, 1.0f);
                        }
                        else
                        {
                            hue = 0.0f;
                            c.SetHSVColor(hue, 0.0f, 0.5f);
                        }

                        glColor4ubv(c.V());
                    }
                    if(_vis.isColorQualityF()) glColor4f(0.5, 0.5, 0.5, 1.0);

                    glBegin(GL_POINTS);
                    glNormal3f((GLfloat)_m->vert[i].N()[0],(GLfloat)_m->vert[i].N()[1],(GLfloat)_m->vert[i].N()[2]);
                    glVertex3f((GLfloat)_m->vert[i].P()[0],(GLfloat)_m->vert[i].P()[1],(GLfloat)_m->vert[i].P()[2]);
                    glEnd();
                }
            }

            //FLAT SHADING
            if(_vis.isMeshFlat())
            {
                for(int i = 0; i < _m->fn; i++)
                {
                    if(_vis.isColorFace()) glColor4ubv(_m->face[i].C().V());
                    if(_vis.isColorQualityF())
                    {
                        vcg::Color4b c;
                        double hue;
                        if(q_min != q_max)
                        {
                            hue = ((_m->face[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
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

                    glNormal3f((GLfloat)_m->face[i].N()[0],(GLfloat)_m->face[i].N()[1],(GLfloat)_m->face[i].N()[2]);
                    for(unsigned int j = 0; j < 3; j++)
                    {
                        if(_vis.isColorVertex()) glColor4ubv(_m->face[i].V(j)->C().V());
                        if(_vis.isColorQualityV())
                        {
                            vcg::Color4b c;
                            double hue;
                            if(q_min != q_max)
                            {
                                hue = ((_m->face[i].V(j)->Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
                                c.SetHSVColor(hue, 1.0f, 1.0f);
                            }
                            else
                            {
                                hue = 0.0f;
                                c.SetHSVColor(hue, 0.0f, 0.5f);
                            }

                            glColor4ubv(c.V());
                        }

                        glVertex3f((GLfloat)_m->face[i].P(j)[0],(GLfloat)_m->face[i].P(j)[1],(GLfloat)_m->face[i].P(j)[2]);
                    }

                    glEnd();
                }
            }

            //SMOOTH SHADING
            if(_vis.isMeshSmooth())
            {
                for(int i = 0; i < _m->fn; i++)
                {
                    if(_vis.isColorFace()) glColor4ubv(_m->face[i].C().V());
                    if(_vis.isColorQualityF())
                    {
                        vcg::Color4b c;
                        double hue;
                        if(q_min != q_max)
                        {
                            hue = ((_m->face[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
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

                    for(unsigned int j = 0; j < 3; j++)
                    {
                        if(_vis.isColorVertex()) glColor4ubv(_m->face[i].V(j)->C().V());
                        if(_vis.isColorQualityV())
                        {
                            vcg::Color4b c;
                            double hue;
                            if(q_min != q_max)
                            {
                                hue = ((_m->face[i].V(j)->Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
                                c.SetHSVColor(hue, 1.0f, 1.0f);
                            }
                            else
                            {
                                hue = 0.0f;
                                c.SetHSVColor(hue, 0.0f, 0.5f);
                            }

                            glColor4ubv(c.V());
                        }
                        glNormal3f((GLfloat)_m->face[i].V(j)->N()[0],(GLfloat)_m->face[i].V(j)->N()[1],(GLfloat)_m->face[i].V(j)->N()[2]);
                        glVertex3f((GLfloat)_m->face[i].P(j)[0],(GLfloat)_m->face[i].P(j)[1],(GLfloat)_m->face[i].P(j)[2]);
                    }

                    glEnd();
                }
            }

            //VOXEL
            if(_vis.isMeshVoxel())
            {
                //////////////////////
                //under construction//
                //////////////////////
            }

            //If the material is enabled
            //if(_vis.isColorMaterial())
            {
                glEnable(GL_COLOR_MATERIAL);
                glDisable(GL_BLEND);
            }

            glPopMatrix();
        }
        break;

    case NORMAL:
        {
            glPushMatrix();

            glDisable(GL_LIGHTING);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glLineWidth(1.0f);

            //VERTEX
            if(_vis.isNormalVertex())
            {
                glColor4f(1.0f, 0.0f, 0.0f, 0.15f);

                for(int i = 0; i < _m->vn; i++)
                {
                    CGPoint p = _m->vert[i].P();
                    CGPoint n = _m->vert[i].N() * (_m->bbox.Diag() * 0.1f);

                    glBegin(GL_LINES);
                    glVertex3f((GLfloat)p[0], (GLfloat)p[1], (GLfloat)p[2]);
                    glVertex3f((GLfloat)(p[0] + n[0]), (GLfloat)(p[1] + n[1]), (GLfloat)(p[2] + n[2]));
                    glEnd();
                }
            }

            //FACE
            if(_vis.isNormalFace())
            {
                glColor4f(0.0f, 0.0f, 1.0f, 0.15f);

                for(int i = 0; i < _m->fn; i++)
                {
                    CGPoint p = vcg::Barycenter(_m->face[i]);
                    CGPoint n = _m->face[i].N() * (_m->bbox.Diag() * 0.1f);

                    glBegin(GL_LINES);
                    glVertex3f((GLfloat)p[0], (GLfloat)p[1], (GLfloat)p[2]);
                    glVertex3f((GLfloat)(p[0] + n[0]), (GLfloat)(p[1] + n[1]), (GLfloat)(p[2] + n[2]));
                    glEnd();
                }
            }

            glDisable(GL_BLEND);
            glEnable(GL_LIGHTING);

            glPopMatrix();
        }
        break;

    case WIRE:
        {
            //Min quality
            double q_min;
            //Max quality
            double q_max;

            //Calculate the vertex min and max quality
            if(!_vis.isMeshEnabled() && _vis.isColorQualityV())
            {
                if(_m->vn > 0)
                {
                    q_min = _m->vert[0].Q();
                    q_max = q_min;

                    for(int i = 1; i < _m->vn; i++)
                    {
                        double q = _m->vert[i].Q();
                        if(q < q_min) q_min = q;
                        if(q > q_max) q_max = q;
                    }
                }
            }
            //Calculate the face min and max quality
            if(!_vis.isMeshEnabled() && _vis.isColorQualityF())
            {
                if(_m->fn > 0)
                {
                    q_min = _m->face[0].Q();
                    q_max = q_min;

                    for(int i = 1; i < _m->fn; i++)
                    {
                        double q = _m->face[i].Q();
                        if(q < q_min) q_min = q;
                        if(q > q_max) q_max = q;
                    }
                }
            }

            glPushMatrix();

            //If it's only a points cloud
            if(_m->fn == 0)
            {
                _vis.Disable_Wireframe();
            }

            //WIREFRAME
            if(_vis.isWireframeEnabled())
            {
                glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

                if(_vis.isMeshEnabled()) glLineWidth(1.5f);
                else glLineWidth(1.0f);

                for(int i = 0; i < _m->fn; i++)
                {
                    if(!_vis.isMeshEnabled() && _vis.isColorFace()) glColor4ubv(_m->face[i].C().V());
                    if(!_vis.isMeshEnabled() && _vis.isColorQualityF())
                    {
                        vcg::Color4b c;
                        double hue;
                        if(q_min != q_max) hue = ((_m->face[i].Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
                        else hue = 0.0f;
                        c.SetHSVColor(hue, 1.0f, 1.0f);

                        glColor4ubv(c.V());
                    }

                    glBegin(GL_LINE_LOOP);

                    for(unsigned int j = 0; j < 3; j++)
                    {
                        if(!_vis.isMeshEnabled() && _vis.isColorVertex()) glColor4ubv(_m->face[i].V(j)->C().V());
                        if(!_vis.isMeshEnabled() && _vis.isColorQualityV())
                        {
                            vcg::Color4b c;
                            double hue;
                            if(q_min != q_max) hue = ((_m->face[i].V(j)->Q() - q_min) / (q_max - q_min)) * (2.0f * (1.0f / 3.0f));
                            else hue = 0.0f;
                            c.SetHSVColor(hue, 1.0f, 1.0f);

                            glColor4ubv(c.V());
                        }

                        glNormal3f((GLfloat)_m->face[i].V(j)->N()[0],(GLfloat)_m->face[i].V(j)->N()[1],(GLfloat)_m->face[i].V(j)->N()[2]);
                        glVertex3f((GLfloat)_m->face[i].P(j)[0],(GLfloat)_m->face[i].P(j)[1],(GLfloat)_m->face[i].P(j)[2]);
                    }

                    glEnd();
                }
            }

            glPopMatrix();
        }
        break;

    case GRID:
        {
            //GRID
            if(_vis.isGridEnabled())
            {
                CGPoint min = _m->bbox.min;
                CGPoint max = _m->bbox.max;
                double dx = _m->bbox.DimX() / _grid;
                double dy = _m->bbox.DimY() / _grid;
                double dz = _m->bbox.DimZ() / _grid;
                unsigned int div = _grid;

                glPushMatrix();

                glDisable(GL_LIGHTING);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
                glLineWidth(1.0f);

                for(unsigned int i = 0; i < (div + 1); i++)
                {
                    for(unsigned int j = 0; j < (div + 1); j++)
                    {
                        //Davanti
                        glBegin(GL_LINES);
                        glVertex3f((GLfloat)min[0] + (i * dx), (GLfloat)min[1] + (j * dy), (GLfloat)min[2]);
                        glVertex3f((GLfloat)min[0] + (i * dx), (GLfloat)min[1] + (j * dy), (GLfloat)max[2]);
                        glEnd();

                        //Lato
                        glBegin(GL_LINES);
                        glVertex3f((GLfloat)min[0], (GLfloat)min[1] + (j * dy), (GLfloat)min[2] + (i * dz));
                        glVertex3f((GLfloat)max[0], (GLfloat)min[1] + (j * dy), (GLfloat)min[2] + (i * dz));
                        glEnd();

                        //Sotto
                        glBegin(GL_LINES);
                        glVertex3f((GLfloat)min[0] + (j * dx), (GLfloat)min[1], (GLfloat)min[2] + (i * dz));
                        glVertex3f((GLfloat)min[0] + (j * dx), (GLfloat)max[1], (GLfloat)min[2] + (i * dz));
                        glEnd();
                    }
                }
                glDisable(GL_BLEND);
                glEnable(GL_LIGHTING);
                glPopMatrix();
            }
        }
        break;

    case AXIS:
        {
            //AXIS
            if(_vis.isAxisEnabled())
            {
                double tot_lenght = _m->bbox.Diag() * 0.1f;
                double body_lenght = tot_lenght * 0.7f;
                double head_lenght = tot_lenght * 0.3f;
                double body_radius = body_lenght * 0.1f;
                double head_radius = 2 * body_radius;

                GLUquadric* body = gluNewQuadric();
                GLUquadric* head = gluNewQuadric();
                gluQuadricDrawStyle(body, GLU_FILL);
                gluQuadricDrawStyle(head, GLU_FILL);

                glPushMatrix();
                glDisable(GL_LIGHTING);

                glTranslatef(_m->bbox.min[0], _m->bbox.min[1], _m->bbox.min[2]);

                /// SPHERE
                glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
                glPushMatrix();
                gluSphere(body, head_radius, 20, 20);
                glPopMatrix();

                /// Z
                glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
                //BODY
                glPushMatrix();
                gluCylinder(body, body_radius, body_radius, body_lenght, 20, 10);
                glPopMatrix();
                //HEAD
                glPushMatrix();
                glTranslatef(0, 0, body_lenght);
                gluCylinder(head, head_radius, 0, head_lenght, 20, 10);
                glPopMatrix();

                /// Y
                glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
                //BODY
                glPushMatrix();
                glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(body, body_radius, body_radius, body_lenght, 20, 10);
                glPopMatrix();
                //HEAD
                glPushMatrix();
                glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                glTranslatef(0, 0, body_lenght);
                gluCylinder(head, head_radius, 0, head_lenght, 20, 10);
                glPopMatrix();

                /// X
                glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                //BODY
                glPushMatrix();
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
                gluCylinder(body, body_radius, body_radius, body_lenght, 20, 10);
                glPopMatrix();
                //HEAD
                glPushMatrix();
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
                glTranslatef(0, 0, body_lenght);
                gluCylinder(head, head_radius, 0, head_lenght, 20, 10);
                glPopMatrix();

                glEnable(GL_LIGHTING);
                glPopMatrix();
            }
        }
        break;

    default: break;
    }

    glEndList();
    return list;
}
