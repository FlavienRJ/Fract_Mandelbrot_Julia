#include "Mainwindow.h"

/*
 * fonction main du programme
 *
*/
int main( int argc, char **argv )
{
    QApplication app(argc,argv);                    //creation de l'application
    QRect screen = QApplication::desktop()->rect(); //recuperation de la taille de l'ecran

    fen win(screen);                                //creation de la fenetre avec la taille de l'ecran comme param
    win.show();                                     //affichage de la fenetre

    return app.exec();                              //lancement de l'application
}

