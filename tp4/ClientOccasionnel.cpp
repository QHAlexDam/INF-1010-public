
#include "ClientOccasionnel.h"
#include "debogageMemoire.hpp"

//Constructeur

/////////////////////////////////////////////////
///NOM: ClientOccasionnel
///PARAMETRES: string_view nom, string_view prenom, int tailleGroupe
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de ClientOccasionnel, utilise le contructeur par parametre de la classe Client
/////////////////////////////////////////////////
ClientOccasionnel::ClientOccasionnel(string_view nom, string_view prenom, int tailleGroupe)
	: Client(nom, prenom, tailleGroupe)
{ 
}

//Destructeur
ClientOccasionnel::~ClientOccasionnel(){}

//Getter

/////////////////////////////////////////////////
///NOM: getNbPoints
///PARAMETRES: aucun
///RETOUR : int nbPoints (0)
///DESCRIPTION : retourne le nb de points, pour un client occasionnel, ce sera toujours 0
/////////////////////////////////////////////////
int ClientOccasionnel::getNbPoints() const
{
 //TODO
	return 0;
}

/////////////////////////////////////////////////
///NOM: getReduction
///PARAMETRES: const Restaurant & res, double montant, bool estLivraison
///RETOUR : double reduction (0.0)
///DESCRIPTION : retourne la reduction, pour un client occasionnel, ce sera toujours 0.0
/////////////////////////////////////////////////
double ClientOccasionnel::getReduction(const Restaurant & res, double montant, bool estLivraison) const
{ // TODO 
	return 0.0;
}

//Afficheur

/////////////////////////////////////////////////
///NOM: afficherClient
///PARAMETRES: ostream & os
///RETOUR : aucun
///DESCRIPTION : Affiche les donnees pertinente d'un client, dans le cas d'un client occasionnel, 
///				on utilise simplement la fonction de la classe de base Client
/////////////////////////////////////////////////
void ClientOccasionnel::afficherClient(ostream & os) const
{
        //TODO

	Client::afficherClient(os);

}

