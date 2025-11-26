#ifndef MAIN_H
#define MAIN_H

//Includes
#include <LibRobus.h> // Essentielle pour utiliser RobUS
//#include "Capteurs.h"// Capteurs ajoutes sur RobUS
#include "Mouvement.h"
//#include "Niveau1.h"
#include "Communication.h"



struct position{
  double x = 0;
  double y = 0;
  double angle = 0;
};

//define
#define maxSpeedAvance 0.5
#define maxSpeedRecule 0.5
#define maxSpeedVert 0.7
#define maxSpeedRouge 0.3

#endif 