#include "Mainwindow.h"

/*
 * constructeur du widget qui affiche l'ensemble de Julia
 *
*/
JuliaWidget::JuliaWidget( QRect par1=QRect(0,0,750,750),MandelWidget* par2=NULL)
{
    setFixedSize(((par1.width()/2)),((par1.width()/2)));    //taille du widget
    _addr_wid = par2;                                       //addresse du widget de l'ensemble de Mandelbrot

    _C.Im=0.00;
    _C.Re=0.00;

    _fen_x = this->size().width();
    _fen_y = this->size().height();

    _max_iter = 50;                                         //nombre d'iteration

}

/*
 * Dessin de l'ensemble de Julia
 *
*/
void JuliaWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);                 //widget Qpainter

    QColor color(0,0,0);                    //initialisation de la variable qui contiendra la couleur
    QPen myPen;                             //creation du pinceau
    painter.setPen(myPen);                  //definition du pinceau du widget

    _Min_Re = -2.0;                         //valeur min des reel
    _Max_Re = 2.0;                          //valeur max des reel
    _Min_Im = -2.0;                         //valeur min des imgs
    _Max_Im = 2.0;                          //valeur max des imgs

    _Re_Factor = (_Max_Re-_Min_Re)/(_fen_x-1);          //facteur de distorision sur l'axe des reels
    _Im_Factor = (_Max_Im-_Min_Im)/(_fen_y-1);          //facteur de distorision sur l'axe des imgs

    for(int y=0; y<_fen_y; y++)                         //parcour des pixels sur y (imaginaire)
    {
        double im = _Max_Im - y* (_Im_Factor);                  //valeur img au point de la fenetre
        for(int x=0; x<_fen_x; x++)                             //parcour des pixels sur x (reel)
        {
            double re = _Min_Re + x*(_Re_Factor);               //valeur reel au point de la fenetre
            _Z0.Im=im;_Z0.Re=re;
            int n;
            for(n=0; n<_max_iter; n++)                          //calul des iteration en fonction du nombre d'iteration voulu Z
            {
                                                                //Zn+1=Zn²+C
                                                                //Re(Zn+1)=Re(Zn)²-Im(Zn)²+Re(C)
                                                                //Im(Zn+1)=2*Re(Zn)*Im(Zn)+Im(C)
                _Z1.Re=pow(_Z0.Re,2)-pow(_Z0.Im,2)+_C.Re;
                _Z1.Im=2*_Z0.Im*_Z0.Re+_C.Im;                   //calcul de la nouvelle partie imaginaire et reel du nombre complexe (Z²)
                if(pow(_Z0.Im,2) + pow(_Z0.Re,2) > 4.0)         //on verifie si le module est >2 (sqrt(Re²+Im²)>2 ==> Re2+Im2>4)
                {                                               //si le module >2 alors en dehors de l'ensemble
                    break;                                      //on sort de la condition
                }
                _Z0.Re=_Z1.Re;
                _Z0.Im=_Z1.Im;
            }
            if(n<2)                                             //si n<2==> on est pas dans l'ensemble à la 2eme itération
            {
                color.setRgb(255,255,255);                      //on choisit de mettre en blanc
            }
            else                                                //sinon on met une nuance de gris suivant l'itération à laquelle
            {                                                   //on est plus dans l'ensemble; dans l'ensemble au bout de 50= noir
                color.setRgb((int)(255-(n*255/_max_iter)),(int)(255-(n*255/_max_iter)),(int)(255-(n*255/_max_iter)));
            }
            myPen.setColor(color);              //definition de la nouvelle couleur du pinceau
            painter.setPen(myPen);              //definition du pinceau
            painter.drawPoint(x, y);            //remplissage du point

        }
    }
}

/*
 * slot qui redessine l'ensemble avec les nouvelles valeurs de C de depart
 *
*/
void JuliaWidget::chgC(QPoint par1)
{
    _C.Re=calc_co(_addr_wid->get_Min_Re(),_addr_wid->get_Re_Factor(),par1.x(),1);
    _C.Im=calc_co(_addr_wid->get_Max_Im(),_addr_wid->get_Im_Factor(),par1.y(),0);
    repaint();                                  //slot de redessinement de l'ensemble
}

/*
 *destructeur du widget
 *
*/
JuliaWidget::~JuliaWidget()
{
    delete _addr_wid;
}
