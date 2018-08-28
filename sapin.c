#include <unistd.h> // write
#include <stdlib.h> // atoi (pour le main)

////////////////////////////////////////////////////////////////////////
//                            PROTOTYPE
////////////////////////////////////////////////////////////////////////
int afficherEtoiles (int val, int print, int ret);
////////////////////////////////////////////////////////////////////////
// ÀFFICHERETOILE  (int val, int print, int ret)
// 1/ executer une première fois afficherEtoiles(val, 1, 0) pour récupérer le nbr * sur la dernière ligne
// 2/ une seconde fois afficherEtoiles(val, 0,ret) pour afficher les étoiles bien comme il faut =)
////////////////////////////////////////////////////////////////////////
void afficherTronc (int value, int ret);
void sapin (int value);

void my_putchar(char c);
void my_putstr(char *str);
int my_strlen(char *str);

////////////////////////////////////////////////////////////////////////
//                            FONCTIONS
////////////////////////////////////////////////////////////////////////
void my_putchar(char c)
{
  write(1, &c, 1);
}

void my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

int my_strlen(char *str){
  int i = -1;
  while(str[++i]);
  return (i);
}

int afficherEtoiles (int val, int print, int ret)
{
  int etage = val;

  int lineTotal = 0, lineArbre = 0, lineEtage = 0;
  int nbrEtoile = 1, etoile = 0, etoileMoins = -1;
  int espace = 0, nbrEspace = 0, espacePlus = 1;

  if (ret != 1)
    // Nbr d'espaces sur première ligne
    nbrEspace = (ret - 1) / 2;

  // lineTotal => Calcul du nbr total de lignes
  while (etage > 0)
  {
    lineTotal += etage + 3;
    etage--;
  }

  // On initialise etage à 1
  etage = 1;
  // Affichage de toutes les lineEtages // 0 < lineTotal
  while (lineArbre < lineTotal)
  {

    lineEtage = 0;
    // Affichage des lignes d'un étage
    while (lineEtage < etage + 3)
    {
      //if (print == 0)
        //printf("nbretoile %d\n",nbrEtoile);

      // Affichage des étoiles
      while (etoile < nbrEtoile)
      {
        if (print == 0)
        {
          // Affichage des espaces
          if (ret != 1)
          {
            // Affichage des espaces
            while (espace < nbrEspace)
            {
              my_putchar(' ');
              espace++;
            }
          }
          my_putchar('*');
        }
        etoile++;
      }

      lineEtage++;
      lineArbre++;

      // Pour renvoyer lineTotal et l'utiliser dans ret
      if ( (lineArbre == lineTotal) && (print != 0) )
        return nbrEtoile;

      // On incrémente nbrEtoile pour la line d'après
      nbrEtoile = etoile + 2;
      // On réinitialise étoile à 0 pour le prochain passage dans le while
      etoile = 0;

      // On décrémente nbrEspace pour la ligne d'après
      nbrEspace = espace - 1;
      // On réinitialise espace à 0 pour le prochain passage dans le while
      espace = 0;
      // Mise à la ligne
      if (print == 0)
        my_putchar('\n');
    }
    etage++;
    // FIN ETAGE

    // On enlève 1 étoile (de chaque côtés donc * 2) tous les rangs pairs
    if ((etage % 2) == 0)
    {
      // On enlève 1 étoile à chaque nouveau rang pair
      etoileMoins -= 1;
      // On ajoute 1 espace à chaque nouveau rang pair
      espacePlus += 1;
    }
    // On enlève des étoiles au rang d'après (-2 puis prochain rang pair -3...)
    nbrEtoile += etoileMoins * 2;

    //printf("\nnbrEspace %d  =  nbrEspace %d + EspacePlus %d * 2\n", nbrEspace, nbrEspace, espacePlus);
    nbrEspace += espacePlus;

  }
  return nbrEtoile;
}

void afficherTronc(int value, int ret)
{
  int barre = 0;
  int line = 0;
  int nbrEspace = 0;
  int espace = 0;

  // Calcul du nbr d'espace
  nbrEspace = (ret - value) / 2;

  // On affiche les line de barres
  while (line < value)
  {
    espace = 0;
    // espace avant les barres
    while (espace < nbrEspace)
    {
      my_putchar(' ');
      espace++;
    }
    barre = 0;
    // On affiche le nbr de barres
    while (barre < value)
    {
      my_putchar('|');
      barre++;
    }
    // Si value est pair on ajoute une barre
    if ( (value % 2) == 0 )
      my_putchar('|');

    // Retour à la ligne
    my_putchar('\n');
    line++;
  }
}

void sapin (int value)
{
  if (value > 0)
  {
    int ret = 0;
    // Recupere la size de la dernière line en lancant afficherEtoiles
    ret = afficherEtoiles(value,1,1);
    // Affichage des étoiles
    afficherEtoiles(value,0,ret);
    // affichage du tronc
    afficherTronc(value, ret);
  }
  else
  {
    my_putstr("The argument must be positive.\n");
  }
}


int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    my_putstr("Sapin takes its size as it first argument.\n");
    return (0);
  }
  sapin(atoi(argv[1]));

  return (0);
}
