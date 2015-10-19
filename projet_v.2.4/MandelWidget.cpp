#include "Mainwindow.h"

/*
 * constructeur du widget qui affiche l'ensemble de mandelbrot
 *
*/

MandelWidget::MandelWidget(QRect par1=QRect(0,0,1000,1000),double par2=-1.80,double par3=0.50,double par4=-1.10)
{
    setMouseTracking(true);                                 //suivi de la souris dans le widget
    setFixedSize(((par1.width()/2)),((par1.width()/2)));    //definition de la taille du widget
    _fen_x = this->size().width();
    _fen_y = this->size().height();

    _Z0.Re=0.0;_Z0.Im=0.0;_Z1.Re=0.0;_Z1.Im=0.0;_C.Re=0.0;_C.Im=0.0;

    _Min_Re=par2;                                           //def des valeurs par default
    _Max_Re=par3;
    _Min_Im=par4;
    _Max_Im = _Min_Im+(_Max_Re-_Min_Re)*_fen_y/_fen_x;      //calcul des max im pour garder les proportions

    _Re_Factor = (_Max_Re-_Min_Re)/(_fen_x-1);
    _Im_Factor = (_Max_Im-_Min_Im)/(_fen_y-1);

    //_pos=0;
}

/*
 * slot de dessin de l'ensemble
 *
*/
void MandelWidget::paintEvent(QPaintEvent *event)
{
    _painter = new QPainter(this);
    _color.setRgb(0,0,0);
    _painter->setPen(_color);

    for(int z=0;z<256;z++)                                  //boucle des nombres d'iterations avant la limite
    {
        for(int y=0; y<_fen_y; y++)                         //parcour des pixels sur y (imaginaire)
        {
            _C.Im = calc_co(_Max_Im,_Im_Factor,y,0);        //valeur img au point de la fenetre parcouru
            for(int x=0; x<_fen_x; x++)                     //parcour des pixels sur x (reel)
            {      
                _C.Re = calc_co(_Min_Re,_Re_Factor,x,1);    //valeur reel au point de la fenetre

                _Z0.Re = _C.Re;_Z0.Im = _C.Im;              //definition du nombre complexe associé
                _is_Inside =true;
                for(int n=0; n<z; n++)                      //calul des iteration en fonction du nombre d'iteration voulu z
                {
                    if(pow(_Z0.Re,2) + pow(_Z0.Im,2) > 4.0) //on verifie si le module est >2 (sqrt(Re²+Im²)>2 ==> Re2+Im2>4)
                    {
                        _is_Inside = false;                 //si le module >2 alors en dehors de l'ensemble
                        break;                              //on sort de la boucle
                    }
                    _Z1.Im = 2*_Z0.Re*_Z0.Im + _C.Im;         //Im(Z) = 2*Re(Z)*Im(Z) + C_Im<==Z=Z²+C
                    _Z1.Re = pow(_Z0.Re,2) - pow(_Z0.Im,2) + _C.Re;//Re(Z) = Re(Z)²-Im(Z)² + C_Re<==i²=-1
                    _Z0.Im=_Z1.Im;_Z0.Re=_Z1.Re;
                }
                if(_is_Inside)                              //si le point est dans l'ensemble
                {
                    _color.setRgb((255-z),(255-z),(255-z)); //couleur depend de l'iteration
                    _painter->setPen(_color);               //definition du pinceau
                    _painter->drawPoint(x, y);              //dessin du point
                }
            }
        }
        switch (z) { //switch pour limiter le nombre de calcul [1,2,3,4,5,6,7,8,9,20,30,50,100,255]
        case 10:
            z=19;
            break;
        case 20:
            z=29;
            break;
        case 30:
            z=49;
            break;
        case 50:
            z=99;
            break;
        case 100:
            z=254;
            break;
        default:
            break;
        }
    }
    trace_axis();                   //methode pour tracer les axes

}

/*
 * methode de tracage des axes
 *
*/
void MandelWidget::trace_axis()
{
    _color.setRgb(128,128,128);
    _painter->setPen(_color);
    _painter->drawLine(QPoint(0,(_Max_Im/_Im_Factor)),QPoint(_fen_x,(_Max_Im/_Im_Factor))); //dessin de l'axe imagninaire
    _painter->drawLine(QPoint(-1*(_Min_Re/_Re_Factor),0),QPoint(-1*(_Min_Re/_Re_Factor),_fen_y)); //dessin de l'axe reel
}

/*
 * signal lorque la souris bouge dans le widget
 *
*/
void MandelWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit valueChanged(event->pos());        //emet la postion de la souris
}

/*
 * slot de modification de la zone de tracage
 *
*/
void MandelWidget::changeZone(double par1, double par2, double par3)
{
    //modification des zones
    _Min_Re=par1;
    _Max_Re=par2;
    _Min_Im=par3;
    _Max_Im = _Min_Im+(_Max_Re-_Min_Re)*_fen_y/_fen_x;

    _Re_Factor = (_Max_Re-_Min_Re)/(_fen_x-1);
    _Im_Factor = (_Max_Im-_Min_Im)/(_fen_y-1);

    repaint(); //redessin de l'ensemble avec la nouvelle zone
}
/*
 * accesseur des differents arguments du widget Mandelbrot
 *
*/
double MandelWidget::get_Im_Factor() const{return _Im_Factor;}
double MandelWidget::get_Re_Factor() const{return _Re_Factor;}
double MandelWidget::get_Max_Im() const{return _Max_Im;}
double MandelWidget::get_Max_Re() const{return _Max_Re;}
double MandelWidget::get_Min_Im() const{return _Min_Im;}
double MandelWidget::get_Min_Re() const{return _Min_Re;}
MandelWidget* MandelWidget::get_This() {return this;}

/*
 * destructeur du widget
 *
*/
MandelWidget::~MandelWidget()
{
    //delete _painter;
}
