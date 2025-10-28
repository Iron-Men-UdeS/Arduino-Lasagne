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

//suiveur suiveurGauche = {CAPTEUR0_GAUCHE,CAPTEUR0_DROITE,CAPTEUR0_CENTRE,800,800,800,0,0,0};
//suiveur suiveurDroite = {CAPTEUR1_GAUCHE,CAPTEUR1_DROITE,CAPTEUR1_CENTRE,800,800,800,0,0,0};

//float corr;

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
  //delay(500);
  //SERVO_Enable(0);
  //SERVO_Enable(1);
  jauneAntoine();

  //avance(20, -0.5);
  
}
  


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

//float corr;
void loop() 
{
//SERVO_SetAngle(1,0);
//SERVO_SetAngle(0,180);
//randomDEL();
// Serial.println("new del");
// delay(500);



  // int couleur=suivreLigne();
  // switch (couleur){
  //   case couleurRouge:
  //   inverseDEL(LED_ROUGE);
  //   rouge();
  //   inverseDEL(LED_ROUGE);
  //   break;

  //   case couleurVert:
  //   inverseDEL(LED_VERTE);
  //   vert();
  //   inverseDEL(LED_VERTE);
  //   break;

  //   case couleurBleu:
  //   inverseDEL(LED_BLEUE);
  //   bleu();
  //   inverseDEL(LED_BLEUE);
  //   break;

  //   case couleurJaune:
  //   inverseDEL(LED_JAUNE);
  //   jaune();
  //   inverseDEL(LED_JAUNE);
  //   break;
  // }
  // float angle = angleEnco(45);
  // float dist = ENCODER_Read(GAUCHE);
  // bool action1 = false;
  // if(dist<angle){
  //   robotSetSpeed(0.2,1,corr);
  // }
  // else{
  //   action1 = true;
  // }
  // if(action1 == true);
  // {
  //   ENCODER_Reset(GAUCHE);
  //   ENCODER_Reset(DROITE);
  // }
  // float depl = distanceEnco(20);
  // dist = ENCODER_Read(2);
  // robotSetSpeed(0.5,0,corr);

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