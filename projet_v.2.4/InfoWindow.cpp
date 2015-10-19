#include "Mainwindow.h"

/*
 * Constructeur du widget des fenetre d'information
 *
*/
Win::Win(): QMessageBox()
{
    /*
     * CREATION DE LA FENETRE D'INFORMATION
     *
    */
    _info = new QMessageBox(this);
    _info->setWindowTitle("A propos de...");
    _info->setText("<center><h5>Version de logiciel 1.4</h5></center>"
                   "<h1><center>Fractales des ensembles de</center>"
                   "<center>Mandelbrot et de Julia</center></h1>"
                   "<center><h2>projet de 1ere année INSA Centre Val de Loire</h2></center>"
                   "<center><h5>2014-2015</h5></center>"
                   ""
                   "<h2>Mode d'emploi</h2>"
                   "<ul>"
                   "<li>N'hésitez pas à incliner votre écran pour mieux apprécier les variations de couleur</li>"
                   "<li>La barre vous montre les coordonnées de votre curseur ainsi que leur correspondance en nombres complexes</li>"
                   "<li>*à venir* cliquer sur un point noir de Mandelbrot affichera l'ensemble de Julia associé</li>"
                   "<li>*à venir*Vous pouvez vous aider de l'encart isinside pour savoir si le point où vous êtes générera l'ensemble de Julia</li>"
                   "</ul>"
                   "<br>-->F2 : informations à propos de Qt</br>"
                   "<br>-->F3 : informations à propos des fractales complexes</br>"
                   "    "
                   "<h4><center> RONTEIX-JACQUET Flavien, CHASTAIN Camille</center></h4>");
    _info->setDefaultButton(QMessageBox::Ok);
    _info->setFocus();

    /*
     * CREATION DE LA FENETRE D'INFORMAION SUR LES FRACTALES
     *
    */
    _fractale = new QMessageBox(this);
    _fractale->setWindowTitle("A propos des fractales...");
    _fractale->setText("<title>A propos de l'ensemble de MandelBrot et de Julia</title>"
                       "<h2>A peaufiner</h2>"
                       "<h2>Précisions sur Mandelbrot et Julia</h2>"
                       "L'ensemble de Mandelbrot et les ensembles de Julia associés sont créés à partir de la même <a href=\"https://fr.wikipedia.org/wiki/Suite_g%C3%A9om%C3%A9trique\">suite géométrique</a> définie dans <a href=\"https://fr.wikipedia.org/wiki/Nombre_complexe\">l'ensemble des nombres complexes</a> : Z<sub>n+1</sub> = Z<sub>n</sub><sup>2</sup> + C  avec C et Z<sub>0</sub> des nombres complexes."
                       "<br>On obtient Mandelbrot en fixant Z<sub>0</sub>=0 et en faisant varier les valeurs de C : la couleur du point est définie par la vitesse de variation de la suite."
                       "<br>Pour Julia c'est l'inverse : C est une valeur fixée et c'est la valeur de Z<sub>0</sub> qui varie."
                       "<center><h2>Liens</h2></center>"
                       "Pour plus de précisions et informations, nous vous proposons ces sites qui expliquent bien le fonctionnement des suites complexes ainsi que des autres types de suite :"
                       "<ul>"
                       "<li>Les articles Wikipédia : <a href=\"https://fr.wikipedia.org/wiki/Fractale\">Les fractales en général</a>, <a href=\"https://fr.wikipedia.org/wiki/Ensemble_de_Mandelbrot\">Ensemble de Mandelbrot</a>, <a href=\"https://fr.wikipedia.org/wiki/Ensemble_de_Julia\">Ensemble de Julia</a></li>"
                       "<li>L'article Futura-sciences sur les fractales : <a href=\"http://www.futura-sciences.com/magazines/mathematiques/infos/dossiers/d/mathematiques-fractales-234/\">cliquer ici</a></li>"
                       "<li>Une vidéo du youtuber français Mickaël Launay très bien faite : <a href=\"https://www.youtube.com/watch?v=iFA3g_4myFw\">cliquer ici</a></li>"
                       "</ul>");
    _fractale->setDefaultButton(QMessageBox::Ok);
    _fractale->setFocus();

}

/*
 * slot pour afficher la fenetre d'information
 *
*/
void Win::show_info()
{
    _info->show();
    _info->setFocus();
}

/*
 * slot pour afficher la fenetre d'information sur les fractales
 *
*/
void Win::show_fractale()
{
    _fractale->show();
    _info->setFocus();
}

/*
 * destructeurs des fenetres
 *
*/
Win::~Win()
{
    delete _info;
    delete _fractale;
}
