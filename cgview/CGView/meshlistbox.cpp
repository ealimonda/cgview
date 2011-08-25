#include "meshlistbox.h"

MeshListBox::MeshListBox(QWidget *parent)
	: QFrame(parent)
{
	_layout = new QBoxLayout(QBoxLayout::TopToBottom);
	_layout->setSpacing(0);

	this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	this->setContentsMargins(0,0,0,0);
	this->setLayout(_layout);

	_activeButtons = new QButtonGroup(this);
}

MeshListBox::~MeshListBox()
{

}

void MeshListBox::addMeshListItem(MeshListItem* item) {
	
	item->setParent(this);
	item->setVisible(true);
	item->update();

	QSize debug = item->size();

	active = meshlist.size();
	
	meshlist.push_back(item);

	_layout->addWidget(item);
	_layout->update();

	_activeButtons->addButton( item->getActiveButton() );
	item->getActiveButton()->setChecked(true);

	this->setMinimumHeight(meshlist.size()*item->size().height()+16);
	this->setMaximumHeight(meshlist.size()*item->size().height()+16);
	this->update();

	//connect radiobutton to the meshlist
	connect( item->getActiveButton(), SIGNAL(toggled(bool)), this, SLOT(updateActiveMesh()) );

	emit changeActiveMesh(active);
}

void MeshListBox::updateActiveMesh(void) {
	for (int i = 0; i < meshlist.size(); i ++)
		if ( meshlist[i]->getActiveButton()->isChecked() ) 
			active = i;

	emit changeActiveMesh(active);
}

void MeshListBox::reset(void) {
	
	this->setMinimumHeight(30);
	this->setMaximumHeight(60);
	this->update();

	QLayoutItem *item;
	while ((item = _layout->takeAt(0)))
		delete item;

	meshlist.clear();
}


/*** MeshListItem ***/

MeshListItem::MeshListItem(std::vector<GLMesh>& meshes, int index, QWidget *parent) 
	: QWidget(parent), _meshes(meshes)
{
	//not visible
	this->setVisible(false);

	_group = new QGroupBox(this);
	_layout = new QBoxLayout(QBoxLayout::LeftToRight);

	_name = new QLabel("");
	_activeButton = new QRadioButton("Active", this);
	_visibleBox = new QCheckBox("Visible", this);
	_visibleBox->setChecked(true);

	_layout->addWidget(_name);
	_layout->addWidget(_activeButton);
	_layout->addWidget(_visibleBox);

	_index = index;

	this->setLayout(_layout);
	this->setMinimumHeight(30);
	this->setMaximumHeight(60);
	this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
	this->setContentsMargins(0,0,0,0);

	//connect item with its own checkbox
	connect( _visibleBox, SIGNAL(toggled(bool)), this, SLOT(checkVisiblity(bool)) );
}


MeshListItem::MeshListItem(QString name, std::vector<GLMesh>& meshes, int index, QWidget *parent) 
	: QWidget(parent), _meshes(meshes)
{
	
	//not visible
	this->setVisible(false);

	_group = new QGroupBox(this);
	_layout = new QBoxLayout(QBoxLayout::LeftToRight);

	_name = new QLabel(name);
	_activeButton = new QRadioButton("Active", this);
	_visibleBox = new QCheckBox("Visible", this);
	_visibleBox->setChecked(true);

	_name->setVisible(true);
	_activeButton->setVisible(true);
	_visibleBox->setVisible(true);

	_index = index;

	_layout->setSpacing(0);
	_layout->addWidget(_name);
	_layout->addWidget(_activeButton);
	_layout->addWidget(_visibleBox);

	_group->setLayout(_layout);

	QBoxLayout* tmplayout = new QBoxLayout(QBoxLayout::TopToBottom);
	tmplayout->addWidget(_group);

	this->setLayout(tmplayout);
	this->setMinimumHeight(30);
	this->setMaximumHeight(60);
	this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
	this->setContentsMargins(0,0,0,0);

	//connect item with its own checkbox
	connect( _visibleBox, SIGNAL(toggled(bool)), this, SLOT(checkVisiblity(bool)) );
}

MeshListItem::~MeshListItem()
{

}

void MeshListItem::checkVisiblity(bool c) {
	if (c) _meshes[_index].show();
	else   _meshes[_index].hide();

	emit updateMesh();

}