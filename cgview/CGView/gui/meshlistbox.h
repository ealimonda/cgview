#ifndef MESHLISTBOX_H
#define MESHLISTBOX_H

#include "opengl/mesh/glmesh.h"

#include <QFrame>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>

#include <QButtonGroup>


class MeshListItem : public QWidget
{
	Q_OBJECT

public:
	MeshListItem(std::vector<GLMesh>& meshes, int index, QWidget *parent = 0);
	MeshListItem(QString name, std::vector<GLMesh>& meshes, int index, QWidget *parent = 0);
	~MeshListItem();

	QLabel* getNameLabel(void)			{ return _name; }

	void	setName(QString name)		{ _name->setText(name); _name->update(); }

	QRadioButton* getActiveButton(void) { return _activeButton; }
	
	QCheckBox* getVisibleBox(void)		{ return _visibleBox; }

public slots:
	void checkVisiblity(bool c);

signals:
	void updateMesh();

private:
	//group
	QGroupBox* _group;
	//name of the mesh
	QLabel* _name;
	//radio button (is active?)
	QRadioButton* _activeButton;
	//check box (is visible?)
	QCheckBox* _visibleBox;
	//reference to the vector of meshes
	std::vector<GLMesh>& _meshes;
	//index of the mesh
	int _index;
	//layout
	QBoxLayout *_layout;
};

class MeshListBox : public QFrame
{
	Q_OBJECT

public:
	MeshListBox(QWidget *parent = 0);
	~MeshListBox();

public slots:
	void addMeshListItem(MeshListItem* item);
	void updateActiveMesh();
	void reset();

signals:
	void changeActiveMesh(int a);

private:
	std::vector<MeshListItem*> meshlist;

	//grid layout
	QBoxLayout *_layout;

	//group of radio button
	QButtonGroup *_activeButtons;

	//index of active mesh
	int active;

};

#endif // MESHLISTBOX_H
