#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QLabel>
#include <QtGui>
#include <QWidget>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QDoubleSpinBox>

double calc_co(double par1, double par2, int par3, bool par4);

typedef struct{
    double Re;
    double Im;
}STRUCT_COOR_Z;


class MandelWidget : public QWidget
{
    Q_OBJECT
public:
    //MandelWidget(QWidget * parent = 0);
    MandelWidget(QRect par1,double par2,double par3,double par4);
    ~MandelWidget();

    double get_Im_Factor() const;
    double get_Re_Factor() const;
    double get_Max_Im() const;
    double get_Max_Re() const;
    double get_Min_Im() const;
    double get_Min_Re() const;
    MandelWidget* get_This();
    void trace_axis();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void valueChanged(QPoint par1);

public slots:
    void changeZone(double par1,double par2,double par3);

private:
    STRUCT_COOR_Z _C;
    STRUCT_COOR_Z _Z0;
    STRUCT_COOR_Z _Z1;
    bool _is_Inside;

    double _Min_Re;
    double _Max_Re;
    double _Min_Im;
    double _Max_Im;

    double _Re_Factor;
    double _Im_Factor;

    int _fen_x;
    int _fen_y;

    int _max_iter;

    QColor _color;
    QPainter *_painter;
};

class JuliaWidget : public QWidget
{
    Q_OBJECT
public:
    JuliaWidget(MandelWidget* par2);
    JuliaWidget(QRect par1,MandelWidget* par2);
    ~JuliaWidget();

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void chgC(QPoint par1);
private:
    STRUCT_COOR_Z _C;
    STRUCT_COOR_Z _Z0;
    STRUCT_COOR_Z _Z1;

    double _Min_Re;
    double _Max_Re;
    double _Min_Im;
    double _Max_Im;

    double _Re_Factor;
    double _Im_Factor;

    int _fen_x;
    int _fen_y;

    int  _max_iter;
    MandelWidget* _addr_wid;
};

class Win : public QMessageBox
{
    Q_OBJECT
public:
    Win();
    ~Win();

public slots:
    void show_info();
    void show_fractale();

private:
    QMessageBox *_info;
    QMessageBox *_fractale;
};

class fen : public QWidget
{
    Q_OBJECT
public:
    //fen();
    fen(QRect par1);
    ~fen();

    void coor_z_label();

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void posCur(QPoint par1);
    void apply_clicked();
    void restore_clicked();

signals:
    void apply(double var1,double var2,double var3);

private:

    MandelWidget *_wid;
    JuliaWidget *_wid1;

    /*QLabel *_txt_cur_x;
    QLabel *_pos_cur_x;
    QLabel *_txt_cur_y;
    QLabel *_pos_cur_y;*/
    QLabel *_txt_z;
    QPushButton *_f1;
    QDoubleSpinBox *_ent_Min_Re;
    QDoubleSpinBox *_ent_Max_Re;
    QDoubleSpinBox *_ent_Min_Im;
    QPushButton *_apply;
    QPushButton *_default;

    STRUCT_COOR_Z _z;

    QVBoxLayout *_layout1;
    QHBoxLayout *_layout2;
    QHBoxLayout *_layout3;

    Win *_fen;

};

#endif
