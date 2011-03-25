#include "psi_dialog.h"

PSI_dialog::PSI_dialog(QDialog *parent) : QDialog(parent)
{    
    //Setting the title of the main windows
    this->setWindowTitle(QString("Shape Interpolation"));

    this->setModal(true);

    //Setting the minimum height and width and the initial height and width
    this->setFixedSize(400,200);
    this->setContentsMargins(0, 0, 0, 0);

    // create dialog buttons
    create_buttons();

//    // create the line edits to read the file names
//    create_edits();

    create_combobox();

    // set up the layout
    create_main_layout();

    this->setLayout(_main_layout);

    // create the connections

    createConnections();

}

PSI_dialog::PSI_dialog(QDialog *parent, std::vector<CGMesh*> m) : QDialog(parent)
{
    meshes = m;

    //Setting the title of the main windows
    this->setWindowTitle(QString("Shape Interpolation"));

    this->setModal(true);

    //Setting the minimum height and width and the initial height and width
    this->setFixedSize(400,200);
    this->setContentsMargins(0, 0, 0, 0);

    // create dialog buttons
    create_buttons();

//    // create the line edits to read the file names
//    create_edits();

    create_combobox();

    // set up the layout
    create_main_layout();

    this->setLayout(_main_layout);

    // create the connections

//    createConnections();

}

void PSI_dialog::create_buttons()
{
//    _button[B_SELECT_1] =  new QPushButton("Browse...",this);
//    _button[B_SELECT_2] =  new QPushButton("Browse...",this);
    _button[B_OK] =        new QPushButton("OK",this);


}

void PSI_dialog::create_edits()
{
    _edit[E_SELECT_1] =  new QLineEdit(this);
    _edit[E_SELECT_2] =  new QLineEdit(this);


}


void PSI_dialog::create_main_layout()
{
    _main_layout = new QGridLayout;

//    _main_layout->addWidget(_edit[E_SELECT_1],1,1,0);
//    _main_layout->addWidget(_button[B_SELECT_1],1,2,0);
//    _main_layout->addWidget(_edit[E_SELECT_2],2,1,0);
//    _main_layout->addWidget(_button[B_SELECT_2],2,2,0);
    _main_layout->addWidget(_combobox[C_SELECT_1],0,0,0);
    _main_layout->addWidget(_combobox[C_SELECT_2],1,0,0);

    _main_layout->addWidget(_button[B_OK],3,2,0);
}


void PSI_dialog::createConnections()
{
    QObject::connect(_button[B_SELECT_1],
                     SIGNAL(clicked()),
                     this,
                     SLOT( choose_mesh_file()));
    QObject::connect(_button[B_SELECT_2],
                     SIGNAL(clicked()),
                     this,
                     SLOT( choose_mesh_file()));
}


void PSI_dialog::create_combobox()
{
    int i;

    _combobox[C_SELECT_1] = new QComboBox;
    _combobox[C_SELECT_2] = new QComboBox;

    for ( i = 0; i < meshes.size() ; i++)
    {
        _combobox[C_SELECT_1]->addItem(meshes[i]->get_name(),NULL);
        _combobox[C_SELECT_2]->addItem(meshes[i]->get_name(),NULL);
    }
}

void PSI_dialog::choose_mesh_file()
{
    QString filename = QFileDialog::getOpenFileName( NULL, "Open mesh", "examples", "3D Meshes (*.off *.ply);;OFF (*.off);;PLY (*.ply)");
    int i;

    if(_button[B_SELECT_1] == sender())
        i = E_SELECT_1;
    if(_button[B_SELECT_2] == sender())
        i = E_SELECT_2;

    _edit[i]->setText(filename);
}
