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

#include "main.h"

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup() 
{
  BoardInit();
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_BLEUE, OUTPUT);
  SERVO_Enable(0);
  SERVO_Enable(1);
  eteindreToutesLesDELs();
  initCapteurCouleur();
}
  


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  int couleur=suivreLigne();
  switch (couleur){
    case couleurRouge:
    inverseDEL(LED_ROUGE);
    rouge();
    inverseDEL(LED_ROUGE);
    break;

    case couleurVert:
    inverseDEL(LED_VERTE);
    vert();
    inverseDEL(LED_VERTE);
    break;

    case couleurBleu:
    inverseDEL(LED_BLEUE);
    bleu();
    inverseDEL(LED_BLEUE);
    break;

    case couleurJaune:
    inverseDEL(LED_JAUNE);
    jaune();
    inverseDEL(LED_JAUNE);
    break;
  }
}

// void setup() 
// {
//   Wire.begin();
//   BoardInit();
//   pinMode(LED_ROUGE, OUTPUT);
//   pinMode(LED_VERTE, OUTPUT);
//   pinMode(LED_JAUNE, OUTPUT);
//   pinMode(LED_BLEUE, OUTPUT);

//   if (tcs.begin()) {        //S'assure que le capteur est detecte
//   tcs.setInterrupt(false);
//   delay(100);}
// }

// void loop() {
//    eteindreToutesLesLEDs();

//   if(detecCouleur()==couleurRouge){
//   inverseDEL(LED_ROUGE);
//   }
//   if(detecCouleur()==couleurBleu){
//   inverseDEL(LED_BLEUE);
//   }
//   if(detecCouleur()==couleurJaune){
//   inverseDEL(LED_JAUNE);
//   }
//   if(detecCouleur()==couleurVert){
//   inverseDEL(LED_VERTE);
//   }
//   delay(250);

// }