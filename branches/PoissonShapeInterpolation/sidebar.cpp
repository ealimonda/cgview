#include "sidebar.h"

SideBar::SideBar(QWidget *parent) :
    QWidget(parent)
{


    create_mesh_box();
    create_mesh_info();


    create_main_layout();

    this->setLayout(_main_layout);

    create_connections();

}


// metodi pubblici

void SideBar::add_mesh(CGMesh *m)
{
    _mesh_box->addItem(m->get_name(),NULL);
    _mesh_box->setCurrentIndex(_mesh_box->count()-1);

    update_mesh_info(m);

}


// metodi privati

void SideBar::create_main_layout()
{
    _main_layout = new QGridLayout;

    _main_layout->addWidget(_mesh_box,0,0);
    _main_layout->addWidget(_mesh_info_box,1,0);

}

void SideBar::create_mesh_box()
{
    _mesh_box = new QComboBox;

    _mesh_box->setEditable(false);

    _mesh_box->setMinimumWidth(100);

//    _mesh_box->addItem("Mesh List",NULL);
}

void SideBar::create_mesh_info()
{
    _box_layout       = new QGridLayout;

    _mesh_info_box    = new QGroupBox;

    _mesh_flag_select = new QCheckBox("Select",this);
    _mesh_flag_active = new QCheckBox("Active",this);
    _mesh_flag_draw   = new QCheckBox("Drawn",this);


    _mesh_info_box->setTitle("Mesh Info");

    _box_layout->addWidget(_mesh_flag_select,1,0);
    _box_layout->addWidget(_mesh_flag_active,2,0);
    _box_layout->addWidget(_mesh_flag_draw,3,0);

    _mesh_info_box->setLayout(_box_layout);

}

void SideBar::update_mesh_info(CGMesh *m)
{
    _mesh_info_box->setTitle(m->get_name());

    _mesh_flag_select->setChecked(m->is_select());
    _mesh_flag_active->setChecked(m->is_active());
    _mesh_flag_draw->setChecked(m->is_drawn());

}

void SideBar::create_connections()
{
    connect(_mesh_box,SIGNAL(activated(int)),this,SLOT(info_handler(int)));
    connect(_mesh_flag_draw,SIGNAL(toggled(bool)),this,SLOT(draw_set(bool)));
}

/// SLOTS

void SideBar::info_handler(int i)
{
    std::cout << "Emetto il segnale activated(" << i <<")" << std::endl;
    emit ask_info(i);
}

void SideBar::draw_set(bool state)
{
    emit engine_change_draw_state(_mesh_box->currentIndex(),state);
}
