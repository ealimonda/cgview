#include "statusbar.h"

StatusBar::StatusBar()
{
    _layout = new QGridLayout;
    _layout->setContentsMargins(10, 0, 0, 0);
    _layout->setColumnStretch(0, 0);
    _layout->setColumnStretch(1, 1);
    _layout->setColumnStretch(2, 0);
    _layout->setColumnStretch(3, 1);
    _layout->setColumnStretch(4, 0);
    _layout->setColumnStretch(5, 1);
    _layout->setColumnStretch(6, 0);
    _layout->setColumnStretch(7, 1);

    _vertLabel = new QLabel("Vertex : ");
    _faceLabel = new QLabel("Face : ");
    _edgeLabel = new QLabel("Edge : ");
    _timeLabel = new QLabel("Time(ms) : ");
    _v = new QLabel("");
    _f = new QLabel("");
    _e = new QLabel("");
    _t = new QLabel("");


    _layout->addWidget(_v, 0, 1);
    _layout->addWidget(_f, 0, 3);
    _layout->addWidget(_e, 0, 5);
    _layout->addWidget(_t, 0, 7);
    _layout->addWidget(_vertLabel, 0, 0);
    _layout->addWidget(_faceLabel, 0, 2);
    _layout->addWidget(_edgeLabel, 0, 4);
    _layout->addWidget(_timeLabel, 0, 6);

    this->setLayout(_layout);

    refreshInfo();
}

void StatusBar::refreshInfo()
{
    if(_load)
    {
        int v = _vert;
        int f = _face;
        int e = _edge;
        int t = _time;

        _v->setNum(v);
        _f->setNum(f);
        _e->setNum(e);
        _t->setNum(t);
    }
    else
    {
        _v->setText("");
        _f->setText("");
        _e->setText("");
        _t->setText("");
    }

    _v->update();
    _f->update();
    _e->update();
    _t->update();
}
