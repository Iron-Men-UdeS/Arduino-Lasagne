/*
Projet: Arduino Lasagne
Equipe: Iron Men
Description: Code pour l'arduino du RobUS controller par la manette
Date: 11/13/2025
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */
#include "main.h"
/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
uint8_t manette[5] = {0, 0, 0, 0, 0};
// []-> start condition ($)
// [0]-> avance (0-100)
// [1]-> recule (0-100)
// [2]-> joystick(0-100, 50 est la valeur ou le robot ne tourne pas)
// [3]-> dpad (up->1, down->2, gauche->8, droite->4)
// [4]-> checksum (verification(addition de toutes les valeurs))
void setup()
{
    BoardInit();
    Serial1.begin(115200);
    Serial.begin(9600);
    pinMode(LED_ROUGE, OUTPUT);
    pinMode(LED_VERTE, OUTPUT);
    pinMode(LED_JAUNE, OUTPUT);
    pinMode(LED_BLEUE, OUTPUT);
    digitalWrite(LED_JAUNE, HIGH);
    digitalWrite(LED_VERTE, HIGH);
    digitalWrite(LED_BLEUE, HIGH);
    digitalWrite(LED_ROUGE, HIGH);
}

int couleur=0;
int flagRouge=0;
int flagVert=0;
int flagBleu=0;
int flagJaune=0;
unsigned long clockR=0;
unsigned long clockV=0;
unsigned long clockB=0;
unsigned long clockJ=0;
unsigned long clockN=0;


/*******************************************************************************************
 * Auteur : Raphael
 *
 * Renvoie le flag rouge selon la couleur et les cooldown
 * 
 * Pas de return mais joue sur la variable globale flagRouge et les clockN et clockR
******************************************************************************************/
void malusRouge(){

couleur=detectCouleur();
clockN=millis();

if(clockN-clockR>5000){flagRouge=0;}  //Durée du bonus/malus

if (couleur==COULEURROUGE&&(clockN-clockR>10000||clockR==0)){     //Cooldown 
  flagRouge=1;
  clockR=millis();
  }
}


/*******************************************************************************************
 * Auteur : Raphael
 *
 * Renvoie le flag vert selon la couleur et les cooldown
 * 
 * Pas de return mais joue sur la variable globale flagVert et les clockN et clockV
******************************************************************************************/
void bonusVert(){

couleur=detectCouleur();
clockN=millis();

if(clockN-clockV>5000){flagVert=0;}             //Durée du bonus/malus

if (couleur==COULEURVERT&&(clockN-clockV>10000||clockV==0)){     //Cooldown 
  flagVert=1;
  clockV=millis();
  }
}

/*******************************************************************************************
 * Auteur : Raphael
 *
 * Renvoie le flag jaune selon la couleur et les cooldown
 * 
 * Pas de return mais joue sur la variable globale flagJaune et les clockN et clockJ
******************************************************************************************/
void bananeJaune(){

couleur=detectCouleur();
clockN=millis();

if (couleur==COULEURJAUNE&&(clockN-clockJ>7000||clockJ==0)){    //Cooldown 
  flagJaune=1;
  while(flagJaune==1){
  digitalWrite(LED_JAUNE,LOW);
  tourne(762,0.4,DROITE);
  digitalWrite(LED_JAUNE,HIGH);
  flagJaune=0;
  clockJ=millis();
  }
}
 else if (couleur!=COULEURJAUNE){flagJaune=0;}
}

/*******************************************************************************************
 * Auteur : Raphael
 *
 * Renvoie le flag bleu selon la couleur et les cooldown
 * 
 * Pas de return mais joue sur la variable globale flagBleu et les clockN et clockB
******************************************************************************************/
void gelBleu(){

couleur=detectCouleur();
clockN=millis();

if(clockN-clockB>5000){flagBleu=0;}         //Durée du bonus/malus

if (couleur==COULEURBLEU&&(clockN-clockB>10000||clockB==0)){    //Cooldown 
  flagBleu=1;
  clockB=millis();
  }
}


/*******************************************************************************************
 * Auteur : Raphael
 *
 * Regarde quels flags des bonus/malus sont ON et allume la DEL durant la durée du flag
 * 
 * Jaune pas inclus car dans sa fct
 * 
 * Pas de return juste à mettre la fct dans le loop
******************************************************************************************/
void delBonus(){
if(flagBleu==1){digitalWrite(LED_BLEUE,LOW);}
if(flagRouge==1){digitalWrite(LED_ROUGE,LOW);}
if(flagVert==1){digitalWrite(LED_VERTE,LOW);}
if(flagBleu==0){digitalWrite(LED_BLEUE,HIGH);}
if(flagRouge==0){digitalWrite(LED_ROUGE,HIGH);}
if(flagVert==0){digitalWrite(LED_VERTE,HIGH);}
}

/*
Auteur: Samuel B. Manelli
Description: Permet le contrôle du robot à l'aide d'une manette. Reçois des
valeurs via le esp32
*/
void deplacementmanette()
{
    float speedAvance = float(manette[0]) / 100.0;
    float speedRecule = float(manette[1]) / 100.0;
    float ratioD = 1;
    float ratioG = 1;
    float vitesseDroite;
    float vitesseGauche;
    // Faire un stop ou une priorité sur avance et recule pour éviter qu'il ne soit appuyer en même temps
    // l'idée est que si les deux sont différent de 0 en même temps le robot stop
    if (manette[0] != 0 && manette[1] != 0)
    {
        MOTOR_SetSpeed(DROITE, 0);
        MOTOR_SetSpeed(GAUCHE, 0);
    }
    else
    {
        // permet de tourner a gauche
        if (manette[2] < 45)
        {
            ratioG = (manette[2] / 25);
        }

        // permet de tourner a droite
        if (manette[2] > 55)
        {
            ratioD = ((100 - manette[2]) / 25);
        }

        if (manette[2] > 45 && manette[2] < 55)
        {
            ratioD = 1;
            ratioG = 1;
            // mettre un interval au lieu d'une valeur fixe pour contre le driff
        }

        // permet de limiter la vitesse max
        if (speedAvance > 0.5 && flagRouge == flagVert)
        {
            speedAvance = maxSpeedAvance;
        }
        if (speedAvance > 0.5 && flagRouge == 0 && flagVert == 1)
        {
            speedAvance = maxSpeedVert;
        }
        if (speedAvance > 0.5 && flagRouge == 1 && flagVert == 0)
        {
            speedAvance = maxSpeedRouge;
        }
        // permet de limiter la vitesse de reculons max
        if (speedRecule < -0.5 && flagRouge == flagVert)
        {
            speedRecule = -maxSpeedRecule;
        }
        if (speedRecule < -0.5 && flagRouge == 0 && flagVert == 1)
        {
            speedRecule = -maxSpeedVert;
        }
        if (speedRecule < -0.5 && flagRouge == 1 && flagVert == 0)
        {
            speedRecule = -maxSpeedRouge;
        }

        if (speedAvance < speedRecule)
        {
            vitesseDroite = speedRecule * ratioD / -1;
            vitesseGauche = speedRecule * ratioG / -1;
        }
        else
        {
            vitesseDroite = speedAvance * ratioD;
            vitesseGauche = speedAvance * ratioG;
        }
        if (vitesseDroite < 0.15 && vitesseDroite > 0)
        {
            vitesseDroite = 0.2;
        }
        if (vitesseGauche < 0.15 && vitesseGauche > 0)
        {
            vitesseGauche = 0.2;
        }
        if (vitesseDroite > -0.15 && vitesseDroite < 0)
        {
            vitesseDroite = -0.2;
        }
        if (vitesseGauche > -0.15 && vitesseGauche < 0)
        {
            vitesseGauche = -0.2;
        }
        MOTOR_SetSpeed(DROITE, vitesseDroite);
        MOTOR_SetSpeed(GAUCHE, vitesseGauche);
    }
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
*****************************************************************************/
void loop()
{
    bananeJaune();
    malusRouge();
    bonusVert();
    gelBleu();
    delBonus();
    litUART(manette, 6);
    deplacementmanette();
}
