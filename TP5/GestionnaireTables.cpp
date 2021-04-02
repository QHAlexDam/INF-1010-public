

#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"


void GestionnaireTables::lireTables(const string& nomFichier)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection("-TABLES");
	while (!fichier.estFinSection()) {
		int id, nbPlaces;
		fichier >> id >> nbPlaces;
		ajouter(new Table(id, nbPlaces));
	}
}

GestionnaireTables::~GestionnaireTables()
{

	for_each(conteneur_.begin(), conteneur_.end(), [](Table* m) {delete m; });
	conteneur_.clear();
}

/////////////////////////////////////////////////
///NOM: getTable
///PARAMETRES: int id
///RETOUR : Table* table
///DESCRIPTION : retourne le pointeur vers la table avec le id entre en parametre
/////////////////////////////////////////////////
Table* GestionnaireTables::getTable(int id) const {
	
	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		if ((*it)->getId() == id) {
			return *it;
		}
	}

	return nullptr;		
}

/////////////////////////////////////////////////
///NOM: getMeilleureTable
///PARAMETRES: int tailleGroupe
///RETOUR :Table* table
///DESCRIPTION : methode qui trouve la plus petite table disponible possible 
///				pour la taille de groupe entre en parametre
/////////////////////////////////////////////////
Table * GestionnaireTables::getMeilleureTable(int tailleGroupe) const
{

	Table* meilleurTable = nullptr;
	int minPlace = 0;
	bool premiereTable = true;
	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		if (tailleGroupe <= (*it)->getNbPlaces() && !((*it)->estOccupee()) && (*it)->getId() != ID_TABLE_LIVRAISON && premiereTable) {
			meilleurTable = *it;
			minPlace = meilleurTable->getNbPlaces();
			premiereTable = false;
		}
		if (tailleGroupe <= (*it)->getNbPlaces() && !((*it)->estOccupee()) && (*it)->getId() != ID_TABLE_LIVRAISON && !premiereTable && (*it)->getNbPlaces() < minPlace) {
			meilleurTable = *it;

		}
	}
	return meilleurTable;
}

/////////////////////////////////////////////////
///NOM: afficherTables
///PARAMETRES: ostream & os
///RETOUR : aucun
///DESCRIPTION : mehtode d'affichage qui utilise la surcharge de l'operateur << de table 
///				pour afficher les information des tables
/////////////////////////////////////////////////
void GestionnaireTables::afficherTables(ostream & os) const
{
	
	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		os << *(*it) << endl;
	}
}