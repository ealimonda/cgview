#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QLayout>
#include "mesh_handler.h"

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = 0);


private:

    QGridLayout *_main_layout;
    QGridLayout *_box_layout;

    QComboBox   *_mesh_box;

    QGroupBox   *_mesh_info_box;
    QCheckBox   *_mesh_flag_select;
    QCheckBox   *_mesh_flag_active;
    QCheckBox   *_mesh_flag_draw;

    void create_main_layout();

    void create_mesh_box();

    void create_mesh_info();



    void create_connections();

signals:

    void ask_info(int);
    void engine_change_draw_state(int,bool);

public slots:

    void add_mesh(CGMesh*);

    void info_handler(int);

    void update_mesh_info(CGMesh*);

    void draw_set(bool);

};

#endif // SIDEBAR_H
