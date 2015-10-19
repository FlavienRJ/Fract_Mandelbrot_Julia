#include "Mainwindow.h"

/*
 * Constantes, ici ceus sont les valeurs par défault de
 * de la zone de mandelbrot
*/

double const MIN_RE=-1.80;
double const MAX_RE=0.50;
double const MIN_IM=-1.10;

/*
 * Constructeur de la fenetre
 *
*/

fen::fen(QRect par1) : QWidget()
{
    /*
     * INITIALISATION DES PARAMETRES DE LA FENETRE
     *
    */

    setMouseTracking(true);                 //permet le suivi de la souris
    setWindowState(Qt::WindowMaximized);    //fenetre par default en grand ecran
    setWindowTitle("Generateur de Fractale");      //nom de la fenetre
    setWindowIcon(QIcon("icon.png"));       //icone de la fenetre

    /*
     * CREATION DES WIDGETS DE LA FENETRE
     *
    */

    _wid = new MandelWidget(par1,MIN_RE,MAX_RE,MIN_IM); //creation du widget Mandelbrot
    _wid1= new JuliaWidget(par1,_wid->get_This());      //creation du widget Julia

    _f1 = new QPushButton(this);            //creation du bouton info
    _f1->setText("Info");                   //texte du bouton
    _f1->setFixedSize(60,60);               //sa taille

    _ent_Min_Re = new QDoubleSpinBox(this); //creation du widget de modification des modif min reel
    _ent_Min_Re->setPrefix("Minimum réel : ");//texte a afficher
    _ent_Min_Re->setDecimals(2);            //nombre de decimal
    _ent_Min_Re->setRange(MIN_RE,MAX_RE-0.01);//interval de modfif
    _ent_Min_Re->setSingleStep(0.01);       //le pas de modif
    _ent_Min_Re->setAccelerated(true);      //autorisation de l'acceration lorsque que l'on reste click
    _ent_Min_Re->setValue(MIN_RE);          //valeur de depart
    _ent_Min_Re->setFixedHeight(60);        //hauteur fixe du widget

    _ent_Max_Re = new QDoubleSpinBox(this); //creation du widget de modif des max reel
    _ent_Max_Re->setPrefix("Maximum réel : ");
    _ent_Max_Re->setDecimals(2);
    _ent_Max_Re->setRange(MIN_RE+0.01,MAX_RE);
    _ent_Max_Re->setSingleStep(0.01);
    _ent_Max_Re->setAccelerated(true);
    _ent_Max_Re->setValue(MAX_RE);
    _ent_Max_Re->setFixedHeight(60);

    _ent_Min_Im = new QDoubleSpinBox(this);  //creation du widget de modif des min imag
    _ent_Min_Im->setPrefix("Minimum imaginaire : ");
    _ent_Min_Im->setDecimals(2);
    _ent_Min_Im->setRange(MIN_IM,-MIN_IM);
    _ent_Min_Im->setSingleStep(0.01);
    _ent_Min_Im->setAccelerated(true);
    _ent_Min_Im->setValue(MIN_IM);
    _ent_Min_Im->setFixedHeight(60);

    _apply = new QPushButton(this);         //creation du bouton "appliquer" pour modifier la
    _apply->setText("Appliquer");           //zone de tracage
    _apply->setFixedHeight(60);

    _default = new QPushButton(this);       //creation du bouton "restaurer" pour remettre
    _default->setText("Retablir");          //l'affichage par défault
    _default->setFixedHeight(60);

    _txt_z = new QLabel(this);              //creation du label d'affichage de la val de Z
    _txt_z->setAutoFillBackground(true);
    _txt_z->setPalette(Qt::white);
    _txt_z->setAlignment(Qt::AlignCenter);
    _txt_z->setFixedSize(0.2*par1.width(),60);

    _fen = new Win();                       //creation du widget des fenetres d'information

    _z.Im=0;_z.Re=0;
    coor_z_label();                         //appele de la methode d'affichage de Z dans le label

    /*
     * "MISE EN PAGE" DE LA FENETRE PAR LES LAYOUTS
     *
    */

    _layout3 = new QHBoxLayout;             //creation du layout inferieur
    _layout3->setMargin(0);                 //suppression des marges
    _layout3->setSpacing(0);                //suppression de l'espace entre widget
    _layout3->addWidget(_f1);               //ajout de tout les widgets inferieurs au layout
    _layout3->addWidget(_ent_Min_Re);
    _layout3->addWidget(_ent_Max_Re);
    _layout3->addWidget(_ent_Min_Im);
    _layout3->addWidget(_apply);
    _layout3->addWidget(_default);
    _layout3->addWidget(_txt_z);


    _layout2 = new QHBoxLayout;             //creation du layout superieur
    _layout2->setMargin(0);
    _layout2->setSpacing(0);
    _layout2->addWidget(_wid);              //ajout des 2 widgets superieurs
    _layout2->addWidget(_wid1);


    _layout1 =  new QVBoxLayout;            //creation du layout global de la fenetre
    _layout1->setMargin(0);
    _layout1->setSpacing(0);
    _layout1->addLayout(_layout2);          //ajout du layout inf et sup au layout de la fen
    _layout1->addLayout(_layout3);
    setLayout(_layout1);                    //def du layout par default de la fen

    /*
     * CONNECTION DES DIFFERENTS EVENEMENT
     *
    */

    //si la souris bouge dans le widget mandelbrot, on modifie la valeur de Z afficher
    connect(_wid,SIGNAL(valueChanged(QPoint)),this,SLOT(posCur(QPoint)));
    //si la souris bouge dans le widget mandelbrot, on redessine l'ensemble de Julia associe
    connect(_wid,SIGNAL(valueChanged(QPoint)),_wid1,SLOT(chgC(QPoint)));
    //si le bouton info est clique, on affiche la fenetre d'information
    connect(_f1,SIGNAL(clicked()),_fen,SLOT(show_info()));
    //si le bouton appliquer est clique, on appele le slot apply_clicked
    connect(_apply,SIGNAL(clicked()),this,SLOT(apply_clicked()));
    //si le bouton restaurer est clique, on appele le solt restore_clicked
    connect(_default,SIGNAL(clicked()),this,SLOT(restore_clicked()));
    //si le signal apply actif (apply_clicked ou restore_clicked), on redessine l'ensemble de Mandelbrot
    connect(this,SIGNAL(apply(double,double,double)),_wid,SLOT(changeZone(double,double,double)));

}
/*
 * calcul de la position du curseur
 *
*/
void fen::posCur(QPoint par1) //SLOT qui redifinie la positon du curseur dans l'ensemble
{
    _z.Re=calc_co(_wid->get_Min_Re(),_wid->get_Re_Factor(),par1.x(),1);
    _z.Im=calc_co(_wid->get_Max_Im(),_wid->get_Im_Factor(),par1.y(),0);
    coor_z_label();
}
/*
 *affichage des coordonnées de Z
 *
*/
void fen::coor_z_label()
{
    QString text;
    if(_z.Im>0)
    {
        text = "Z = "+QString::number(_z.Re,'d',2)+" + "+QString::number(_z.Im,'d',2)+"i";
    }
    else
    {
        text = "Z = "+QString::number(_z.Re,'d',2)+" - "+QString::number(fabs(_z.Im),'d',2)+"i";
    }
    _txt_z->setText(text);
}

/*
 * methode appele lorsque une touche est active (herité de QWidget)
 *
*/
void fen::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F1:
       _fen->show_info();           //si la touche est f1, on affiche la fenetre d'information
        break;
    case Qt::Key_F2:
        QMessageBox::aboutQt(this); //si la touche est f2, on affiche la fenetre a propos de Qt
        break;
    case Qt::Key_F3:
        _fen->show_fractale();      //si la touche est f3, on affiche la fenetre sur les fractales
        break;
    case Qt::Key_F7:
        QMessageBox::information(this,"Easter Egg","<h2>我爱师喻!</h2>");   //petit easter egg pour
        break;                      //ceux qui cherchent toutes les touches ;)
    default:
        break;
    }
}

/*
 * slots si le bouton apply est cliquer
 *
*/
void fen::apply_clicked()
{
    if(_ent_Max_Re->value()<_ent_Min_Re->value())
    {
        emit apply(_ent_Max_Re->value(),_ent_Min_Re->value(),_ent_Min_Im->value());
    }
    else
    {
        emit apply(_ent_Min_Re->value(),_ent_Max_Re->value(),_ent_Min_Im->value());
    }
    //emmision d'un signal "apply" avec comme parametre les nouvelles valeurs de zone
}

/*
 * slots si le bouton restaurer est cliquer
 *
*/
void fen::restore_clicked()
{
    emit apply(MIN_RE,MAX_RE,MIN_IM);   //emmision du signal "apply" mais avec les valeurs
                                        //par default
}

/*
 * destructeur du widget de la fenetre
 *
*/
fen::~fen()
{
    delete _txt_z;
    delete _f1;
    delete _ent_Min_Re;
    delete _ent_Max_Re;
    delete _ent_Min_Im;
    delete _apply;
    delete _default;
    delete _layout1;
    delete _layout2;
    _fen->~Win();
    _wid->~MandelWidget();
    _wid1->~JuliaWidget();
}
