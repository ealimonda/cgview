/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: interfaces.h                                                     *
 * Description: Plugin interfaces definition                                  *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_INTERFACES_H
#define CGVIEW_INTERFACES_H

#include <QtPlugin>
#include <vector>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE
class CGMesh;
class GLMesh;
class GLWindow;

class CGViewPluginInterface : public QObject
{
public:
	inline QString menuName(void) const
	{
		return this->_menuName;
	}

protected:
	QString _menuName;
private:
};

/** Plugin collection.  Include multiple plugins into the same library */
class CGViewPluginCollectionInterface : public QObject
{
public:
	inline QObjectList plugins() const
	{
		return this->_plugins;
	}
protected:
	QObjectList _plugins;
};

#if 0
// TODO
class PluginIOInterface
{
};
#endif // 0

/** Custom render method.  Gets called after clearing the screen and drawing the background */
class PluginRenderInterface : public CGViewPluginInterface
{
public:
	virtual void doRender(std::vector<GLMesh> &mesh, GLWindow *window) const = 0;
	inline bool isEnabled(void) const
	{
		return this->_state;
	}
	inline void setEnabled(bool state)
	{
		this->_state = state;
	}

public slots:
	virtual void enable(bool state) = 0;

signals:
	void toggled(void);

private:
	bool _state;
};

/** Transformation.  Acts on and alters the CGMesh */
class PluginTransformInterface : public CGViewPluginInterface
{
public:
	virtual ~PluginTransformInterface() {}

	virtual void runTransform(CGMesh *mesh) const = 0;
};

/** Visualization add-on.  Adds extra stuff to the scene (i.e. grids, axes, normals, etc) */
class PluginVisualizationInterface : public CGViewPluginInterface
{
public:
	virtual void doVisualize(CGMesh *mesh) const = 0;
	inline bool isEnabled(void) const
	{
		return this->_state;
	}

	inline void setEnabled(bool state)
	{
		this->_state = state;
	}

public slots:
	virtual void enable(bool state) = 0;

signals:
	void toggled( void );

private:
	bool _state;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(CGViewPluginCollectionInterface, "it.unica.informatica.cgview.CGViewPluginCollectionInterface/0.2")
//Q_DECLARE_INTERFACE(PluginIOInterface, "it.unica.informatica.cgview.PluginIOInterface/0.2")
Q_DECLARE_INTERFACE(PluginRenderInterface, "it.unica.informatica.cgview.PluginRenderInterface/0.2")
Q_DECLARE_INTERFACE(PluginTransformInterface, "it.unica.informatica.cgview.PluginTransformInterface/0.2")
Q_DECLARE_INTERFACE(PluginVisualizationInterface, "it.unica.informatica.cgview.PluginVisualizationInterface/0.2")
QT_END_NAMESPACE

#endif // CGVIEW_INTERFACES_H
