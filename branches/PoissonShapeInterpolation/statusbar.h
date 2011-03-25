#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QtGui>

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    StatusBar();



private:

protected:
    void refreshInfo();

    QGridLayout* _layout;
    QLabel*      _vertLabel;
    QLabel*      _faceLabel;
    QLabel*      _edgeLabel;
    QLabel*      _timeLabel;
    QLabel*      _v;
    QLabel*      _f;
    QLabel*      _e;
    QLabel*      _t;

    unsigned int _vert;
    unsigned int _face;
    unsigned int _edge;
    unsigned int _time;
    bool _load;

signals:

public slots:
    inline void setInfo(const unsigned int v, const unsigned int f, const unsigned int t)
    {
        _vert = v;
        _face = f;
        _edge = (3 * _face) / 2;

        _time = t;

        _load = true;

        refreshInfo();
    }
    inline void Reset()
    {
        _vert = 0;
        _face = 0;
        _edge = 0;
        _time = 0;
        _load = false;

        refreshInfo();
    }

private slots:

};

#endif // STATUSBAR_H
