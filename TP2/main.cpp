﻿

////////////////////////////////////////
//REPONSES AUX QUESTIONS

//1. Quelle est l'utilite de l'operateur = et du constructeur par copie?
/// Les deux ont une fonctionnalites semblable, c'est a dire obtenir un objet en 
///	tout point identique avec un objet existant (memes attributs).

//2. Qu'est ce qui differencie l'operateur = du constructeur par copie?
/// Bien que les deux ont une fonctionnalite semblable, le constructeur par copie 
///	cree un nouvel objet ayant les attribut d'un objet existant, tandis que l'operateur = 
///	ecrase un objet existant avec les attributs d'un autre objet. Ainsi, le l'operateur = 
///	necessite un objet pour ecraser, alors que le constructeur cree lui-meme le nouveau objet.
////////////////////////////////////////

#include "Restaurant.h"
using namespace std; 

int main() {
	

	////creation du restaurant
	Restaurant poly("polyFood.txt", "PolyFood", Soir);

	///creer plusieurs clients 
	int nbclient1 = 1;
	int nbclient2 = 5;
	int nbclient3 = 15;
	int nbclient4 = 3;
	int nbclient5 = 2;


	//placer les clients 
	poly.placerClients(nbclient1);
	poly.placerClients(nbclient2);
	poly.placerClients(nbclient3);
	poly.placerClients(nbclient4);
	poly.placerClients(nbclient5);

	// commander des plats 
	poly.commanderPlat("Poisson", 1);
	poly.commanderPlat("Poulet", 2);
	poly.commanderPlat("Pizza", 2);
	poly.commanderPlat("Poulet", 4);
	poly.commanderPlat("Muffin", 4);
	poly.commanderPlat("Oeuf", 4);


	//Creation d'une copie du poly restaurant 
	Restaurant poly2(poly);
	poly2.setNom("PolyFood2");

	//Affichage du restaurant poly 
	cout << poly;

	cout << "--------------------------------------------------------------------------------------------------" << endl;


	//liberer les tables et calcule du chiffre d'affaire
	poly.libererTable(1);
	poly.libererTable(2);
	poly.libererTable(3);
	poly.libererTable(4);

	cout << poly;

	cout << "====================================================================================================" << endl;

	// Le restaurant Poly2 ne doit pas encore avoir liberer ses tables
	cout << poly2;

	poly2 = poly; // on ecrase tous les attributs de poly2 avec ceux de poly



	cout << "--------------------------------------------------------------------------------------------------" << endl;
	// Le restaurant Poly2 doit maintenant avoir toutes ses tables lib�r�es
	cout << poly2;

	return 0;
			
}