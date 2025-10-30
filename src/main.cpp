/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */
#include "Mouvement.h"
#include "main.h"
#define act 1

// suiveur suiveurGauche = {CAPTEUR0_GAUCHE,CAPTEUR0_DROITE,CAPTEUR0_CENTRE,800,800,800,0,0,0};
// suiveur suiveurDroite = {CAPTEUR1_GAUCHE,CAPTEUR1_DROITE,CAPTEUR1_CENTRE,800,800,800,0,0,0};

// float corr;

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales
int couleur;
int flagR = 0;
int flagV = 0;
int flagB = 0;
int flagJ = 0;
int flagS = 0;
void setup()
{
  BoardInit();
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_BLEUE, OUTPUT);
  // initCapteurCouleur();
}
  // pinMode(LED_ROUGE, OUTPUT);
  // pinMode(LED_VERTE, OUTPUT);
  // pinMode(LED_JAUNE, OUTPUT);
  // pinMode(LED_BLEUE, OUTPUT);
  // delay(500);
  // SERVO_Enable(0);
  // SERVO_Enable(1);

  // avance(20, -0.5);
// }

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

// float corr;
void loop()
{
  //############### ACT 1 ###############
  //#if act == 1

  // couleur = detectCouleur();
  // Serial.println(couleur);
  // delay(1000);
  while(sifflet_5kHz() == false && flagS == 0){}
  flagS = 1;
  int couleur = suivreLigne();
  switch (couleur)
  {
    case 0:
    if(flagR == 0)
    {
      flagR = 1;
      inverseDEL(LED_ROUGE);
      rouge2();
    }
    
    break;
    
    case 1:
    if(flagV == 0)
    {
      flagV = 1;
      inverseDEL(LED_VERTE);
      vert();
    }
    break;
    
    case 2:
    if(flagB == 0)
    {
      flagB = 1;
      inverseDEL(LED_BLEUE);
      bleu();
    }
    break;

    case 3:
    if(flagJ == 0)
    {
      flagJ = 1;
      inverseDEL(LED_JAUNE);
      jauneAntoine();
    }
    break;
  }
  if(flagR == 1 && flagV == 1 && flagB == 1 && flagJ == 1)
  {
    eteindreToutesLesDELs();
    while(1);
  }
//   #endif
// //#####################################


// //############### ACT 2 ###############
// #if act == 2




// #endif
// //#####################################



}

