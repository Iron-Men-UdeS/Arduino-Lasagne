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
void setup()
{

}

<<<<<<< Updated upstream
=======
// int avance=0; //valeur recu par le esp32 (valeur au repos)
// int recule=0;  //valeur recu par le esp32 (valeur au repos)
// int joycon=50; //valeur recu par le esp32 (valeur au repos)




/*
Auteur: Samuel B. Manelli
Description: Permet le contrôle du robot à l'aide d'une manette. Reçois des
valeurs via le esp32
*/
void deplacementmanette()
{
    float speedAvance=float(manette[0])/100.0;
    float speedRecule=float(manette[1])/100.0;
    float ratioD=1;
    float ratioG=1;
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
        //permet de tourner a gauche
        if (manette[2] < 45 )
        {
            ratioG = (manette[2] / 25);
        }

        // permet de tourner a droite
        if (manette[2] > 55)
        {
            ratioD = ((100-manette[2]) / 25);
        }

        if (manette[2] > 45 && manette[2] < 55)
        {
            ratioD = 1;
            ratioG = 1;
            //mettre un interval au lieu d'une valeur fixe pour contre le driff
        }

       // permet de limiter la vitesse max
        if (speedAvance > 0.5 )
        {
            speedAvance = maxSpeedAvance;
        }
        //permet de limiter la vitesse de reculons max
        if (speedRecule < -0.5)
        {
            speedRecule = maxSpeedRecule;
        }
        if (speedAvance<speedRecule){
            vitesseDroite=speedRecule * ratioD/-1;
            vitesseGauche=speedRecule * ratioG/-1;
        }
         else{
            vitesseDroite = speedAvance * ratioD;
            vitesseGauche= speedAvance * ratioG;
        }
        if (vitesseDroite<0.15 && vitesseDroite > 0){
            vitesseDroite=0.2;
        }
        if (vitesseGauche<0.15 && vitesseGauche > 0){
            vitesseGauche=0.2;
        }
        if (vitesseDroite>-0.15 && vitesseDroite < 0){
            vitesseDroite=-0.2;
        }
        if (vitesseGauche>-0.15 && vitesseGauche < 0){
            vitesseGauche=-0.2;
        }
        MOTOR_SetSpeed(DROITE, vitesseDroite);
        MOTOR_SetSpeed(GAUCHE, vitesseGauche);
    }
}
//set speed pour faire deplacer le robot
// MOTOR_SetSpeed(DROITE,speedAvance*ratioD);
// MOTOR_SetSpeed(GAUCHE,speedAvance*ratioG);
// MOTOR_SetSpeed(DROITE,speedRecule*ratioD);
// MOTOR_SetSpeed(GAUCHE,speedRecule*ratioG);
//ecrit comme ca va surement creer des problemes puisque le code va faire avancer pour avance mais stoper pour recule

>>>>>>> Stashed changes
/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
void loop()
{

}

