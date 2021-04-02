

#include "Table.h"

//constructeurs

/////////////////////////////////////////////////
///NOM: Table (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut qui initialise le id a -1, le nb de places a 1 et le nb de clients a 0
/////////////////////////////////////////////////
Table::Table() {
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

/////////////////////////////////////////////////
///NOM: Table (constructeur par parametre)
///PARAMETRES: int id et int nbPlaces
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre qui initialise le id et le nb de places aux valeurs passes en parametre,
///				et le nb de clients a 0
/////////////////////////////////////////////////
Table::Table(int id, int nbPlaces) {
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}

//getters

/////////////////////////////////////////////////
///NOM: getID
///PARAMETRES: aucun
///RETOUR : id_
///DESCRIPTION : Retourne le id de la table
/////////////////////////////////////////////////
int Table::getId() const {
	return id_;
}

/////////////////////////////////////////////////
///NOM: getNbPlaces
///PARAMETRES: aucun
///RETOUR : nbPlaces_
///DESCRIPTION : Retourne le nb de places de la table
/////////////////////////////////////////////////
int Table::getNbPlaces() const {
	return nbPlaces_;
}

/////////////////////////////////////////////////
///NOM: estOccupee
///PARAMETRES: aucun
///RETOUR : bool (vrai/faux)
///DESCRIPTION : Retourne vrai ou faux, dependamment si la table a au moins 1 client ou non
/////////////////////////////////////////////////
bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

/////////////////////////////////////////////////
///NOM: estPleine
///PARAMETRES: aucun
///RETOUR : bool (vrai/faux)
///DESCRIPTION : Retourne vrai ou faux, dependamment si la table est occupee completement ou non
/////////////////////////////////////////////////
bool Table::estPleine() const {
	return nbPlaces_ == 0;
}

/////////////////////////////////////////////////
///NOM: getnbClientsATable
///PARAMETRES: aucun
///RETOUR : nbClientsATable_
///DESCRIPTION : Retourne le nombre de clients a la table
/////////////////////////////////////////////////
int Table::getNbClientsATable() const
{
	return nbClientsATable_;
}
vector<Plat*> Table::getCommande() const
{
	return commande_;
}

/////////////////////////////////////////////////
///NOM: getClientPrincipal
///PARAMETRES: aucun
///RETOUR : clientPrincipal
///DESCRIPTION : retourne le client principal, qui represente la table pour le paiement
/////////////////////////////////////////////////
Client * Table::getCliengtPrincipal() const
{
	return clientPrincipal_;
}


//setters

/////////////////////////////////////////////////
///NOM: setId
///PARAMETRES: int id
///RETOUR : aucun
///DESCRIPTION : Change le id de la table
/////////////////////////////////////////////////
void Table::setId(int id) {
	id_ = id;
}

/////////////////////////////////////////////////
///NOM: setClientPrincipal
///PARAMETRES: aucun
///RETOUR : clientPrincipal
///DESCRIPTION : change le client principal
/////////////////////////////////////////////////
void Table::setClientPrincipal(Client * clientPrincipal)
{
	clientPrincipal_ = clientPrincipal;
}

/////////////////////////////////////////////////
///NOM: libererTable
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : libere la table (enleve les clients, reset le nb de places libres et efface la liste de commande
/////////////////////////////////////////////////
void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	commande_.clear();
	clientPrincipal_ = nullptr;
}

/////////////////////////////////////////////////
///NOM: PlacerClient
///PARAMETRES: int NbClients
///RETOUR : aucun
///DESCRIPTION : Place les clients a table (le nb de places libres diminue consequamment)
/////////////////////////////////////////////////
void Table::placerClients(int nbClient) {
	nbPlaces_ -= nbClient;
	nbClientsATable_ = nbClient;
}

//autres methodes

/////////////////////////////////////////////////
///NOM: commander
///PARAMETRES: Plat* plat
///RETOUR : aucun
///DESCRIPTION : ajoute un pointeur du plat a commander dans la liste de commande
/////////////////////////////////////////////////
void Table::commander(Plat* plat) {
	commande_.push_back(plat);
}

/////////////////////////////////////////////////
///NOM: getChiffreAffaire
///PARAMETRES: aucun
///RETOUR : chiffre 
///DESCRIPTION : calcule le chiffre d'affaire (prix-couts) de chaque plats commandes de la table
/////////////////////////////////////////////////
double Table::getChiffreAffaire() const {
	double chiffre = 0;
	
	for (unsigned i = 0; i < commande_.size(); ++i) {
			switch (commande_[i]->getType())
			{
			case Regulier:
				chiffre += commande_[i]->getPrix() - commande_[i]->getCout();
				break;
			case Bio:
				
				chiffre += (commande_[i]->getPrix() - commande_[i]->getCout()+ static_cast<PlatBio*> (commande_[i])->getEcoTaxe());
				break;
			case Custom:
				chiffre += (commande_[i]->getPrix() - commande_[i]->getCout() + static_cast<PlatCustom*>(commande_[i])->getSupplement());
				break;
			}
		
	}
	return chiffre;
}

//affichage

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& out, const Table& table
///RETOUR : out
///DESCRIPTION : overloader de l'operateur <<, qui affiche les donnees pertienentes a une table, soit si elle est occupee et les commandes
/////////////////////////////////////////////////
ostream& operator<<(ostream& os, const Table& table)
{
	os << "La table numero " << table.id_;
	if (table.estOccupee())
	{
		os << " est occupee. ";
		os << "le client principale est: " << endl;
		switch (table.getCliengtPrincipal()->getStatut()) {
		case Occasionnel:
			os << "\n" << *table.getCliengtPrincipal() << endl;
			break;
		case Fidele:
			os << "\n" << *static_cast<ClientRegulier*>(table.getCliengtPrincipal()) << endl;
			break;
		case Prestige:
			os << "\n" << *static_cast<ClientPrestige*>(table.getCliengtPrincipal()) << endl;
			break;
		}
		
		if (!table.commande_.empty())
		{
			os << "Voici la commande passee par les clients : " << endl;
			for (unsigned i = 0; i < table.commande_.size(); ++i)
			{
				os << "\t"; 
				switch (table.commande_[i]->getType())
				{
				case Regulier:
					os << *table.commande_[i];
					break;
				case Bio:
					os << *static_cast<PlatBio*> (table.commande_[i]);
					break;
				case Custom:
					os << *static_cast<PlatCustom*> (table.commande_[i]);
				default:
					break;
				}
				
			}
		}
		else
			os << "Mais ils n'ont rien commande pour l'instant. " << endl;
	}
	else
		os << " est vide. " << endl;

	return os;
}
