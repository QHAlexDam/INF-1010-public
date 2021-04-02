

#include "Restaurant.h"

//constructeurs

/////////////////////////////////////////////////
///NOM: Restaurant (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : constructeur par defaut qui cree un restaurant de nom "inconnu", servant un menu du matin
/////////////////////////////////////////////////
Restaurant::Restaurant() :
	nom_(new string("Inconnu")), 
	chiffreAffaire_ (0), 
	momentJournee_(Matin), 
	menuMatin_(new Menu("menu.txt", Matin)),
	menuMidi_(new Menu("menu.txt", Midi)),
	menuSoir_(new Menu("menu.txt", Soir))
{}

/////////////////////////////////////////////////
///NOM: Restaurant (constructeur par parametre)
///PARAMETRES: const string& fichier, const string& nom et typeMenu moment
///RETOUR : aucun
///DESCRIPTION : constructeur par parametre qui cree un restaurant ayant le nom et servant le type de menu passes en parametre
///				le constructeur appelle egalement lireMenu pour lire le fichier contenant les information sur les tables du restaurant
/////////////////////////////////////////////////
Restaurant::Restaurant(const string& fichier, const string& nom, TypeMenu moment) : 
	nom_(new string(nom)),
	chiffreAffaire_(0),
	momentJournee_(moment),
	menuMatin_(new Menu(fichier, Matin)),
	menuMidi_(new Menu(fichier, Midi)),
	menuSoir_(new Menu(fichier, Soir))
{
	lireTable(fichier);
}

/////////////////////////////////////////////////
///NOM: Restaurant (constructeur par copie)
///PARAMETRES: const Restaurant& restaurant
///RETOUR : aucun
///DESCRIPTION : constructeur par defaut qui cree un restaurant de nom "inconnu", servant un menu du matin
/////////////////////////////////////////////////
Restaurant::Restaurant(const Restaurant& restaurant) :
	nom_(new string(*restaurant.nom_)),
	chiffreAffaire_(restaurant.chiffreAffaire_),
	momentJournee_(restaurant.momentJournee_),
	menuMatin_(new Menu(*restaurant.menuMatin_)),
	menuMidi_(new Menu(*restaurant.menuMidi_)),
	menuSoir_(new Menu(*restaurant.menuSoir_)),
	tables_(restaurant.tables_)
{
	for (int i = 0; i < restaurant.tables_.size(); i++) // deep copy
		tables_[i] = new Table(*restaurant.tables_[i]);
}

//destructeur

/////////////////////////////////////////////////
///NOM: Restaurant (destructeur)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : le destructeur detruit les elements contenu dans la memoire dynamique, soit le nom, les menus et les tables
/////////////////////////////////////////////////
Restaurant::~Restaurant() {
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;

	for (int i = 0; i < tables_.size(); i++) // delete des tables, car Table et Restaurant sont en composition
		delete tables_[i];
	tables_.clear();
}


//setter

/////////////////////////////////////////////////
///NOM: setMoment
///PARAMETRES: TypeMenu moment
///RETOUR : aucun
///DESCRIPTION : change le moment de la journee pour le type de menu servi dans le restaurant
/////////////////////////////////////////////////
void Restaurant::setMoment(TypeMenu moment) {
	momentJournee_ = moment;
}

/////////////////////////////////////////////////
///NOM: setNom
///PARAMETRES: string nom
///RETOUR : aucun
///DESCRIPTION : change le nom du restaurant
/////////////////////////////////////////////////
void Restaurant::setNom(string nom) {
	*nom_ = nom;
}

//getters

/////////////////////////////////////////////////
///NOM: getNom
///PARAMETRES: aucun
///RETOUR : nom_
///DESCRIPTION : retourne le nom du restaurant
/////////////////////////////////////////////////
string Restaurant::getNom() const {
	return *nom_;
}

/////////////////////////////////////////////////
///NOM: getMoment
///PARAMETRES: aucun
///RETOUR : momentJournee_
///DESCRIPTION : retourne le moment de la journee
/////////////////////////////////////////////////
TypeMenu Restaurant::getMoment() const {
	return momentJournee_;
}

//autres methodes

/////////////////////////////////////////////////
///NOM: libererTable
///PARAMETRES: int id
///RETOUR : aucun
///DESCRIPTION : libere la table ayant le id passe en parametre en utilisant la methode libererTable de la classe Table
///				La methode calcule egalement le chiffre d'affaire en utilisant la methode getChiffreAffaire de Table
/////////////////////////////////////////////////
void Restaurant::libererTable(int id) {
	for (int i = 0; i < tables_.size(); i++) {
		if (id == tables_[i]->getId()) {
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
		}
	}
}

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& out, const Restaurant& restaurant
///RETOUR : out
///DESCRIPTION : overload de l'operateur << qui affiche les donnees pertinentes au restaurant (le chiffre d'affaire, l'etat des tables et les menus du restaurant)
/////////////////////////////////////////////////
ostream& operator<<(ostream& out, const Restaurant& restaurant) {
	out << "Le restaurant " << restaurant.getNom();
	if (restaurant.chiffreAffaire_ != 0)
		out << " a fait un chiffre d'affaire de : " << restaurant.chiffreAffaire_ << "$" << endl;
	else
		out << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
	out << "-Voici les tables : " << endl;
	for (int i = 0; i < restaurant.tables_.size(); i++) {
		out << "\t";
		out << *restaurant.tables_[i];
		out << endl;
	}
	out << endl;


	out << "-Voici son menu : " << endl;
	out << "Matin : " << endl;
	out << *restaurant.menuMatin_;
	out << "Midi : " << endl;
	out << *restaurant.menuMidi_;
	out << "Soir : " << endl;
	out << *restaurant.menuSoir_;
	return out;
}

/////////////////////////////////////////////////
///NOM: operator<
///PARAMETRES: const Restaurant& restaurant1, const Restaurant& restaurant2
///RETOUR : bool (true/false)
///DESCRIPTION : overload de l'operateur < qui compare le chiffre d'affaire entre 2 restaurant, retourne vrai si 
///				le premier restaurant a fait moins de profit que le 2e rentre en parametre
/////////////////////////////////////////////////
bool operator<(const Restaurant& restaurant1, const Restaurant& restaurant2) { 
	if (restaurant1.chiffreAffaire_ < restaurant2.chiffreAffaire_)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////
///NOM: operator+=
///PARAMETRES: Table* table
///RETOUR : *this
///DESCRIPTION : overload de l'operateur += permet d'ajouter un pointeur de table aux tables du restaurant
/////////////////////////////////////////////////
Restaurant& Restaurant::operator+=(Table* table) {
	tables_.push_back(table);
	return *this;
}

/////////////////////////////////////////////////
///NOM: operator=
///PARAMETRES: const Restaurant& restaurant
///RETOUR : *this
///DESCRIPTION : overload de l'operateur = qui ecrase le restaurant courrant (this) avec les attributs du restaurant entre en parametre
/////////////////////////////////////////////////
Restaurant& Restaurant::operator=(const Restaurant& restaurant) {
	if (this != &restaurant) {
		*nom_ = *restaurant.nom_;
		chiffreAffaire_ = restaurant.chiffreAffaire_;
		momentJournee_ = restaurant.momentJournee_;
		menuMatin_ = new Menu(*restaurant.menuMatin_);
		menuMidi_ = new Menu(*restaurant.menuMidi_);
		menuSoir_ = new Menu(*restaurant.menuSoir_);
		tables_ = restaurant.tables_;
		for (int i = 0; i < restaurant.tables_.size(); i++) // deep copy
			tables_[i] = new Table(*restaurant.tables_[i]);
	}
	return *this;
		
}

/////////////////////////////////////////////////
///NOM: commanderPlat
///PARAMETRES: const string& nom, int idTable
///RETOUR : aucun
///DESCRIPTION : Methode qui commande un plat, soit qui cherche dans le menu pour trouver un plat par son nom et 
///				l'ajoute a la commande de la table ayant le id en parametre
/////////////////////////////////////////////////
void Restaurant::commanderPlat(const string& nom, int idTable) {
	Plat* plat = nullptr;
	int index;
	for (int i = 0; i < tables_.size(); i++) {
		if (idTable == tables_[i]->getId()) {
			index = i;
			switch (momentJournee_) {
			case Matin :
				plat = menuMatin_->trouverPlat(nom);
				break;
			case Midi :
				plat = menuMidi_->trouverPlat(nom);
				break;
			case Soir :
				plat = menuSoir_->trouverPlat(nom);
				break;
			}
		}
	}
	if (plat != nullptr && tables_[index]->estOccupee()) {
		tables_[index]->commander(plat);
	}
	else cout << "Erreur : table non occupee ou plat introuvable" << endl;
}

/////////////////////////////////////////////////
///NOM: LireTable
///PARAMETRES: const string& fichier
///RETOUR : aucun
///DESCRIPTION : Methode qui lit un fichier dont le nom est en parametre et qui en tire les informations sur les tables du restaurant
///				elle ajoute ensuite les tables contenues dans le fichier au restaurant
/////////////////////////////////////////////////
void Restaurant::lireTable(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (file) {
		string ligne;

		string idString;
		int id;

		string nbPersonnesString;
		int nbPersonnes;

		int curseur;
		while (!file.eof()) {
			getline(file, ligne);
			if (ligne == "-TABLES") {
				while (!file.eof()) {
					getline(file, ligne);
					for (int i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						idString += ligne[i];
					}

					id = stoi(idString);

					nbPersonnesString = ligne.substr(curseur + 1);
					nbPersonnes = stoi(nbPersonnesString);

					tables_.push_back(new Table(id, nbPersonnes));

					nbPersonnesString = "";
					idString = "";
				}
			}
		}
		file.close();
	}
}

/////////////////////////////////////////////////
///NOM: PlacerClient
///PARAMETRES: int nbClients
///RETOUR : aucun
///DESCRIPTION : Methode qui place les clients de facon "intelligente", c'est a dire que les clients seront places a une 
///				table ayant le moins de nombre de place possible.
///				ex. un groupe de 4 personne serait placee a une table de 5 places versus une autre de 10 si les 2 sont libres
/////////////////////////////////////////////////
void Restaurant::placerClients(int nbClients) {
	int indexTable = -1;
	int minimum = 100;


	for (int i = 0; i < tables_.size(); i++) {
		if (tables_[i]->getNbPlaces() >= nbClients && !tables_[i]->estOccupee() && tables_[i]->getNbPlaces() < minimum) {
			indexTable = i;
			minimum = tables_[i]->getNbPlaces();
		}
	}
	if (indexTable == -1) {
		cout << "Erreur : il n'y a plus/pas de table disponible pour le client. " << endl;
	}else
	tables_[indexTable]->placerClient(nbClients);
}
