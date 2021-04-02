
#pragma once

#include <algorithm>
#include "Plat.h"

using namespace std;

/////////////////////////////////////////////////
///NOM: 
///PARAMETRES: 
///RETOUR :
///DESCRIPTION : 
/////////////////////////////////////////////////
class FoncteurPlatMoinsCher
{ // TODO
public:

	FoncteurPlatMoinsCher() {};

	bool operator() (pair<string, Plat*> plat1 , pair<string, Plat*> plat2)  {
		
		return (plat1.second->getPrix() <= plat2.second->getPrix());
	}
	//comparaison et tri croissant 
};

/////////////////////////////////////////////////
///NOM: 
///PARAMETRES: 
///RETOUR :
///DESCRIPTION : 
/////////////////////////////////////////////////
class FoncteurIntervalle
{
   // TODO
	//map.at("poulet")
public:
	FoncteurIntervalle(double inferieur, double superieur) : borneInferieur_(inferieur), borneSuperieur_(superieur) {};
	bool operator () (const pair<string, Plat*> plat) {
		return (plat.second->getPrix() < borneSuperieur_ &&  plat.second->getPrix() > borneInferieur_);		
	}

private:
	double borneInferieur_;
	double borneSuperieur_;
};

