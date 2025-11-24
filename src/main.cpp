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
    initUART1();
}
int flagBumper=0;
int couleur=0;
int flagRouge=0;
int flagVert=0;
int flagBleu=1;
int flagJaune=0;
int etatJeu=2;
uint8_t listeLasagne[4];
uint8_t listeGarfield[2] = {1,2};
unsigned long clockR=0;
unsigned long clockV=0;
unsigned long clockB=0;
unsigned long clockJ=0;
unsigned long clockN=0;
unsigned long debutJeu=0;



//Flags simulant les données du mvmnt
int positionX=20;
int positionY=50;

//Les recu par comm
int flagBleuRecu=0;
int etatJeuRecu=0;



/*******************************************************************************************
 * Auteur : Alexandre Dionne
 *
 * Lit une trame sur UART1 et stocke les donnes dans un tableau
 *
 * @param trame (Tableau uint8_t) Addresse du tableau pour la trame recu
 * @param sizeTrame (uint8_t) longueur de la trame a recevoir (+2 pour start et checksum)
 ******************************************************************************************/


/*******************************************************************************************
 * Auteur : Alexandre Dionne
 *
 * Envoie une trame sur le port UART
 *
 * @param trame (Tableau uint8_t) Trame a evoyer
 ******************************************************************************************/
void envoieTrame(uint8_t *trame)
{
    uint8_t somme;
    for(int i = 0; i < (sizeof(trame)); i++)
    {
        somme = somme + trame[i];
    }
    Serial1.write(0x24);
    Serial1.write(trame, sizeof(trame));
    Serial1.write(somme);
}


/*******************************************************************************************
 * Auteur : Raphael
 *
 * Définit la variable etatJeu
 * 
 * 0=Jeu pas débuté
 * 1=Débuté
 * 2=Débuté mais bumper ON
 * 3=Terminé car deux bumper ON
******************************************************************************************/
void setEtatJeu(){
if((positionX!=0 || positionY!=0) && flagBumper==0 && debutJeu==0){etatJeu=1; debutJeu=millis();}
if((positionX!=0 || positionY!=0) && flagBumper==0){etatJeu=1;}
if((positionX!=0 || positionY!=0) && flagBumper==1){etatJeu=2;}
if((positionX!=0 || positionY!=0) && flagBumper==1 && etatJeuRecu==2){etatJeu=3;}
if(millis()-debutJeu>60000){etatJeu=3;}
}

/*******************************************************************************************
 * Auteur : Raphael
 *
 * Crée une liste avec les variables qu'on va communiquer
 * 
 * @return Tableau [x,y,gel,état du jeu]
******************************************************************************************/
void creationListe(){
  listeLasagne[0] = positionX;
  listeLasagne[1] = positionY;
  listeLasagne[2] = flagBleu;
  listeLasagne[3] = etatJeu;
}


/*******************************************************************************************
 * Auteur : Raphael
 *
 * Définit les variables avec la liste reçu
 * 
 * @return positionXRecu
 * @return positionYRecu
 * @return flagBleuRecu
 * @return etatJeuRecu
 * 
******************************************************************************************/
void receptionListe(){
flagBleuRecu=listeGarfield[0];
etatJeuRecu=listeGarfield[1];
}
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

if (flagBleuRecu==1){digitalWrite(LED_BLEUE,LOW);delay(5000);digitalWrite(LED_BLEUE,HIGH);}
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
if(flagRouge==1){digitalWrite(LED_ROUGE,LOW);}
if(flagVert==1){digitalWrite(LED_VERTE,LOW);}
if(flagRouge==0){digitalWrite(LED_ROUGE,HIGH);}
if(flagVert==0){digitalWrite(LED_VERTE,HIGH);}
if(etatJeu==3){digitalWrite(LED_BLEUE,LOW);digitalWrite(LED_ROUGE,LOW);digitalWrite(LED_VERTE,LOW);digitalWrite(LED_JAUNE,LOW);while(true){delay(10);}}
}

/*******************************************************************************************
 * Auteur : Raphael
 *
 * Regarde l'état des bumpers
 * 
 * Défini flagBumper à 1 si un bumper est ON
 ******************************************************************************************/
  void flagBumperSet(){
    bool bumpp=false;
    if(ROBUS_IsBumper(0)){bumpp=true;}
  if(ROBUS_IsBumper(1)){bumpp=true;}
  if(ROBUS_IsBumper(2)){bumpp=true;}
  if(ROBUS_IsBumper(3)){bumpp=true;}
    if(bumpp){flagBumper=1;}
    if(!bumpp){flagBumper=0;}
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

// int avance=0; //valeur recu par le esp32 (valeur au repos)
// int recule=0;  //valeur recu par le esp32 (valeur au repos)
// int joycon=50; //valeur recu par le esp32 (valeur au repos)




/*
Auteur: Samuel B. Manelli
Description: Permet le contrôle du robot à l'aide d'une manette. Reçois des
valeurs via le esp32
*/

//set speed pour faire deplacer le robot
// MOTOR_SetSpeed(DROITE,speedAvance*ratioD);
// MOTOR_SetSpeed(GAUCHE,speedAvance*ratioG);
// MOTOR_SetSpeed(DROITE,speedRecule*ratioD);
// MOTOR_SetSpeed(GAUCHE,speedRecule*ratioG);
//ecrit comme ca va surement creer des problemes puisque le code va faire avancer pour avance mais stoper pour recule

/* ****************************************************************************
Fonctions de boucle infini (loop())
*****************************************************************************/
void loop()
{   
    litUART(listeGarfield,4);
    //receptionListe(); 
    // flagBumperSet();
    // bananeJaune();
    // malusRouge();
    // bonusVert();
    // gelBleu();
    // setEtatJeu(); //DOIT ETRE AVANT DELBONUS()
    // delBonus();
    //creationListe();    //Doit être après les variables
    //envoieTrame(listeLasagne);
    // litUART(manette, 6);
    // deplacementmanette();
    Serial.print(listeGarfield[0]);
Serial.println(listeGarfield[1]);
    
}
