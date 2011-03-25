#ifndef PSI_DIALOG_H
#define PSI_DIALOG_H

#include<QWidget>
#include<QDialog>
#include<QLayout>
#include<QLineEdit>
#include<QComboBox>
#include<QFileDialog>

#include<QPushButton>

#include "mesh_definition.h"

class PSI_dialog : public QDialog
{
    Q_OBJECT
public:
    PSI_dialog(QDialog *parent = 0);
    PSI_dialog(QDialog*, std::vector<CGMesh*>);


private:

    enum _button_type {
        B_SELECT_1,   // To select the first mesh
        B_SELECT_2,   // To select the second mesh

        B_OK,         // To confermate the selection

        B_NUM
    };


    static const int _button_num = B_NUM;

    enum _edit_type {
        E_SELECT_1,   // To select the first mesh
        E_SELECT_2,   // To select the second mesh

        E_NUM
    };


    static const int _edit_num = E_NUM;

    enum _combobox_type {
        C_SELECT_1,   // To select the first mesh
        C_SELECT_2,   // To select the second mesh

        C_NUM
    };


    static const int _combobox_num = C_NUM;


    // The main dialog Widget
    QWidget *_mainWidget;

    // Buttons
    QPushButton *_button[_button_num];

    // Comboboxes
    QComboBox *_combobox[_combobox_num];

    // Edit Lines
    QLineEdit *_edit[_edit_num];


    // The layout of the dialog
    QGridLayout *_main_layout;

    // meshes in the scene
    std::vector<CGMesh*> meshes;


    // Create buttons
    void create_buttons();

    // Create edit lines fot file selection
    void create_edits();

    void create_combobox();

    // Set the main layout
    void create_main_layout();

    //Create connections between actions and objects
    void createConnections();

private slots:

    // opens the file selection dialog and let the user to select a mesh
    void choose_mesh_file();


};

#endif // PSI_DIALOG_H
