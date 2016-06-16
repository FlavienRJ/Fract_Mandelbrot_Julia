#include "Mainwindow.h"

/*
 * fonction globale de calcul des coordonnées du curseur et des coefficient
 *
*/
double calc_co(double par1, double par2,int par3,bool par4)//par4=1==>reel calcul de la position
{
    return (par4?par1+par2*par3:par1-par2*par3);
}
