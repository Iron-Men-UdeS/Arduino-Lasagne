#include "Niveau1.h"
#include "Capteurs.h"
#include "Mouvement.h"
float correction = 0;

// int couleur=0;
// int flagRouge=0;
// int flagVert=0;
// int flagBleu=0;
// int flagJaune=0;
// unsigned long clockR=0;
// unsigned long clockV=0;
// unsigned long clockB=0;
// unsigned long clockJ=0;
// unsigned long clockN=0;


// /*******************************************************************************************
//  * Auteur : Raphael
//  *
//  * Renvoie le flag rouge selon la couleur et les cooldown
//  * 
//  * Pas de return mais joue sur la variable globale flagRouge et les clockN et clockR
// ******************************************************************************************/
// void malusRouge(){

// couleur=detectCouleur();
// clockN=millis();

// if(clockN-clockR>5000){flagRouge=0;}  //Durée du bonus/malus

// if (couleur==COULEURROUGE&&(clockN-clockR>10000||clockR==0)){     //Cooldown 
//   flagRouge=1;
//   clockR=millis();
//   }
// }


// /*******************************************************************************************
//  * Auteur : Raphael
//  *
//  * Renvoie le flag vert selon la couleur et les cooldown
//  * 
//  * Pas de return mais joue sur la variable globale flagVert et les clockN et clockV
// ******************************************************************************************/
// void bonusVert(){

// couleur=detectCouleur();
// clockN=millis();

// if(clockN-clockV>5000){flagVert=0;}             //Durée du bonus/malus

// if (couleur==COULEURVERT&&(clockN-clockV>10000||clockV==0)){     //Cooldown 
//   flagVert=1;
//   clockV=millis();
//   }
// }

// /*******************************************************************************************
//  * Auteur : Raphael
//  *
//  * Renvoie le flag jaune selon la couleur et les cooldown
//  * 
//  * Pas de return mais joue sur la variable globale flagJaune et les clockN et clockJ
// ******************************************************************************************/
// void bananeJaune(){

// couleur=detectCouleur();
// clockN=millis();

// if (couleur==COULEURJAUNE&&(clockN-clockJ>7000||clockJ==0)){    //Cooldown 
//   flagJaune=1;
//   while(flagJaune==1){
//   digitalWrite(LED_JAUNE,LOW);
//   tourne(762,0.4,DROITE);
//   digitalWrite(LED_JAUNE,HIGH);
//   flagJaune=0;
//   clockJ=millis();
//   }
// }
//  else if (couleur!=COULEURJAUNE){flagJaune=0;}
// }

// /*******************************************************************************************
//  * Auteur : Raphael
//  *
//  * Renvoie le flag bleu selon la couleur et les cooldown
//  * 
//  * Pas de return mais joue sur la variable globale flagBleu et les clockN et clockB
// ******************************************************************************************/
// void gelBleu(){

// couleur=detectCouleur();
// clockN=millis();

// if(clockN-clockB>5000){flagBleu=0;}         //Durée du bonus/malus

// if (couleur==COULEURBLEU&&(clockN-clockB>10000||clockB==0)){    //Cooldown 
//   flagBleu=1;
//   clockB=millis();
//   }
// }


// /*******************************************************************************************
//  * Auteur : Raphael
//  *
//  * Regarde quels flags des bonus/malus sont ON et allume la DEL durant la durée du flag
//  * 
//  * Jaune pas inclus car dans sa fct
//  * 
//  * Pas de return juste à mettre la fct dans le loop
// ******************************************************************************************/
// void delBonus(){
// if(flagBleu==1){digitalWrite(LED_BLEUE,LOW);}
// if(flagRouge==1){digitalWrite(LED_ROUGE,LOW);}
// if(flagVert==1){digitalWrite(LED_VERTE,LOW);}
// if(flagBleu==0){digitalWrite(LED_BLEUE,HIGH);}
// if(flagRouge==0){digitalWrite(LED_ROUGE,HIGH);}
// if(flagVert==0){digitalWrite(LED_VERTE,HIGH);}
// }

void randomDEL()
{
    int DEL = rand() % 4;
    switch (DEL)
    {
    case 0:
        inverseDEL(LED_BLEUE);
        break;

    case 1:
        inverseDEL(LED_ROUGE);
        break;

    case 2:
        inverseDEL(LED_JAUNE);
        break;

    case 3:
        inverseDEL(LED_VERTE);
        break;

    default:
        break;
    }
}

/*******************************************************************************************
 * Auteur : Samuel B. Manelli
 *
 * Permet de faire bouger le bras droit uniquement
 *
 * @param position AUCUN, AVANT, ARRIERE, HAUT, BAS
 *
 *
 ******************************************************************************************/
void bougeBrasDroit(int position)
{
    // enable juste celui a droite
    switch (position)
    {
    // Ne donne aucune instruction donc les servos ne bouge pas
    case AUCUN:
        break;

    // Met les bras vers l'avant du robot
    case AVANT:
        SERVO_SetAngle(BRAS_DROIT, 90);
        break;
    // Met les bras vers l'arrière du robot
    //  case ARRIERE:
    //  SERVO_SetAngle(BRAS_DROIT, voir angle au repos);
    //  break;
    //  //Met les bras vers le haut du robot
    case HAUT:
        SERVO_SetAngle(BRAS_DROIT, 175);
        break;
    // Met les bras vers le bas du robot
    case BAS:
        SERVO_SetAngle(BRAS_DROIT, 5);
        break;
    }
}

/*******************************************************************************************
 * Auteur : Samuel B. Manelli
 *
 * Permet de faire bouger le bras gauche uniquement
 *
 * @param position AUCUN, AVANT, ARRIERE, HAUT, BAS
 *
 ******************************************************************************************/
void bougeBrasGauche(int position)
{
    // enable juste celui utiliser a gauche
    switch (position)
    {
    // Ne donne aucune instruction donc les servos ne bouge pas
    case AUCUN:
        break;

    // Met les bras vers l'avant du robot
    case AVANT:
        SERVO_SetAngle(BRAS_GAUCHE, 90);
        break;
    // Met les bras vers l'arrière du robot
    //  case ARRIERE:
    //  SERVO_SetAngle(BRAS_GAUCHE, voir angle au repos);
    //  break;
    //  //Met les bras vers le haut du robot
    case HAUT:
        SERVO_SetAngle(BRAS_GAUCHE, 10);
        break;
    // Met les bras vers le bas du robot
    case BAS:
        SERVO_SetAngle(BRAS_GAUCHE, 175);
        break;
    }
}

/*******************************************************************************************
 * Auteur : Samuel B. Manelli
 *
 * Permet de faire bouger le bras et le bras droit simultanément
 *
 * @param posGauche AUCUN, AVANT, ARRIERE, HAUT, BAS
 * @param posDroit AUCUN, AVANT, ARRIERE, HAUT, BAS
 ******************************************************************************************/
void bouge2Bras(int posGauche, int posDroit)
{
    bougeBrasGauche(posGauche);
    bougeBrasDroit(posDroit);
}
