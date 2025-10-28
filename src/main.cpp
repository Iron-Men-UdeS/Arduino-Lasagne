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

suiveur suiveurGauche = {CAPTEUR0_GAUCHE,CAPTEUR0_DROITE,CAPTEUR0_CENTRE,800,800,800,0,0,0};
suiveur suiveurDroite = {CAPTEUR1_GAUCHE,CAPTEUR1_DROITE,CAPTEUR1_CENTRE,800,800,800,0,0,0};


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
  //SERVO_Enable(0);
  //SERVO_Enable(1);
  delay(500);
  inverseDEL(LED_BLEUE);
  inverseDEL(LED_ROUGE);
  inverseDEL(LED_VERTE);
  inverseDEL(LED_JAUNE);
  Serial.println("fin du setup");
}
  


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() 
{
//SERVO_SetAngle(1,0);
//SERVO_SetAngle(0,180);
//randomDEL();
// Serial.println("new del");
// delay(500);
tourne(QUART_DE_TOUR,0.25,GAUCHE);
avance(20, 0.25);
tourne(QUART_DE_TOUR,0.25,DROITE);
avance(20,0.25);
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