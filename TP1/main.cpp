
#include "Restaurant.h"
#include <string>

using namespace std;

int main() {


	//creation du restaurant - avec le fichier donne - le nom : PolyFood - moment de la journee : soir. 
	string nom = "PolyFood", nomFichier = "polyFood.txt";
	Restaurant resto(nomFichier, nom, Soir);
	resto.afficher();

	cout << "______________________________________________________________" << endl;

	// Creer les clients (Entiers)
	//const int NBCLIENTS = 5;
	//int clients[NBCLIENTS] = { 1, 5, 15, 3, 2 };
	int clients1 = 1;
	int	clients2 = 5;
	int	clients3 = 15;
	int clients4 = 3;
	int clients5 = 2;

	//placer les clients
	resto.placerClients(clients1);
	resto.placerClients(clients2);
	resto.placerClients(clients3);
	resto.placerClients(clients4);
	resto.placerClients(clients5);
	/*for (int i = 0; i < NBCLIENTS; i++)
	{
		resto.placerClients(clients[i]);
	}*/

	// commander des plats
	//const int NBPLATS = 5;
	//string nomPlat[NBPLATS] = { "Poisson", "Poulet", "Pizza", "Muffin", "Oeuf" };
	string commande1 = "Poisson";
	string commande2 = "Poulet";
	string commande3 = "Pizza";
	string commande4 = "Poulet";
	string commande5 = "Muffin";
	string commande6 = "Oeuf";
	
	//Poisson - Table 1
	resto.commanderPlat(commande1, 1);
	//Poulet - Table 2
	resto.commanderPlat(commande2, 2);
	//Pizza - Table 2
	resto.commanderPlat(commande3, 2);
	//Poulet - Table 4
	resto.commanderPlat(commande4, 4);
	//Muffin - Table 4
	resto.commanderPlat(commande5, 4);
	//Oeuf - Table 4
	resto.commanderPlat(commande6, 4);

	//afficher le restaurant
	resto.afficher();

	cout << "______________________________________________________________" << endl;

	//liberer les tables 
	for (int i = 0; i < 4; i++)
	{
		resto.libererTable(i+1);
	}

	//afficher le restaurant 
	resto.afficher();

	
	return 0;
	
	
	
	
	/*
	Plat plat("bla", 25.5, 10.4);
	cout << plat.getNom() << " " << plat.getPrix() << " " << plat.getCout() << endl;
	plat.setNom("mop");
	plat.setPrix(55.5);
	cout << plat.getNom() << " " << plat.getPrix() << endl;
	plat.afficher();

	cout << endl;

	//test Menu
	string nomFichier = "polyFood.txt";
	Menu menu(nomFichier, Matin);

	cout << menu.getCapcite() << " " << menu.getNbPlats() << " " << endl;
	cout << "le nombre de plat est ";
	cout << menu.getNbPlats() << endl;
	string nomPLat = "Oeuf";
	cout << menu.trouverPlat(nomPLat)->getNom() << endl;

	Plat plat2("chakhchoukha", 10.0, 5.5);
	menu.ajouterPlat(plat2);
	cout << menu.getNbPlats() << endl;

	cout << "-voici son menu" << endl;
	menu.afficher();

	cout << "-------Table------ " << endl;

	Table table(12, 23);

	table.libererTable();
	cout << boolalpha << table.estOccupee() << endl;

	table.placerClient();

	table.commander(&plat2);
	table.commander(&plat);

	cout << table.getChiffreAffaire() << endl;

	table.afficher();

	cout << endl;
	cout << "-----------Restaurant____________" << endl;

	string nomResto = "Mcdonalds'";
	Restaurant resto(nomFichier, nomResto, Matin);

	cout << "NOM DU RESTO: " << resto.getNom();
	string nomPlat = "Oeuf";
	resto.commanderPlat(nomPlat, 1);
	resto.afficher();



	cout << "-------------------------------------------------" << endl;

	cout << " i am in the main";
*/

}