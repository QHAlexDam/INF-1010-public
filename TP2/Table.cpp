

#include "Table.h"

//constructeurs

/////////////////////////////////////////////////
///NOM: Table (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut qui initialise le id a -1, le nb de places a 1 et le nb de clients a 0
/////////////////////////////////////////////////
Table::Table() : id_(-1), nbPlaces_(1), nbClientsATable_(0){
}

/////////////////////////////////////////////////
///NOM: Table (constructeur par parametre)
///PARAMETRES: int id et int nbPlaces
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre qui initialise le id et le nb de places aux valeurs passes en parametre,
///				et le nb de clients a 0
/////////////////////////////////////////////////
Table::Table(int id, int nbPlaces) : id_(id), nbPlaces_(nbPlaces), nbClientsATable_(0) {
}

//destructeur

/////////////////////////////////////////////////
///NOM: Table (destructeur)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : efface le contenu de la commande (vecteur de pointeur), les plats ne sont pas effaces, puisqu'ils sont en aggregation avec la table
/////////////////////////////////////////////////
Table::~Table() {
	commande_.clear();
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
///NOM: getnbClientsATable
///PARAMETRES: aucun
///RETOUR : nbClientsATable_
///DESCRIPTION : Retourne le nombre de clients a la table
/////////////////////////////////////////////////
int Table::getnbClientATable() const
{
	return nbClientsATable_;
}

/////////////////////////////////////////////////
///NOM: estPleine
///PARAMETRES: aucun
///RETOUR : bool (vrai/faux)
///DESCRIPTION : Retourne vrai ou faux, dependamment si la table est occupee completement ou non
/////////////////////////////////////////////////
bool Table::estPleine() const {
	return nbPlaces_==0;
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
///NOM: libererTable
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : libere la table (enleve les clients, reset le nb de places libres et efface la liste de commande
/////////////////////////////////////////////////
void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	commande_.clear(); // Pas besoin de delete les Plats, car Plat et Table sont en agregation
}

/////////////////////////////////////////////////
///NOM: PlacerClient
///PARAMETRES: int NbClients
///RETOUR : aucun
///DESCRIPTION : Place les clients a table (le nb de places libres diminue consequamment)
/////////////////////////////////////////////////
void Table::placerClient(int nbClients) {
	nbClientsATable_ = nbClients;
	nbPlaces_ -= nbClients;
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
	for (int i = 0; i < commande_.size(); i++) {
		chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
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
ostream& operator<<(ostream& out, const Table& table) {
	out << "La table numero " << table.getId();
	if (table.nbClientsATable_>0) {
		out << " est occupee. ";
		if (table.commande_.size() != 0) {
			out << "Voici la commande passee par les clients : " << endl;
			for (int i = 0; i < table.commande_.size(); i++) {
				out << "\t";
				out << *table.commande_[i];
			}
		}
		else
			cout << "Mais ils n'ont rien conmmande pour l'instant. " << endl;
	}
	else {
		cout << " est libre. " << endl;
	}
	return out;
}


