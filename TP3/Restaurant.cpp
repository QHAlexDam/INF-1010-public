
#include "Restaurant.h"

//constructeurs 

/////////////////////////////////////////////////
///NOM: Restaurant (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : constructeur par defaut qui cree un restaurant de nom "inconnu", servant un menu du matin
/////////////////////////////////////////////////
Restaurant::Restaurant() {
	nom_ = new string("Inconnu"); 

	chiffreAffaire_ = 0; 
	
	momentJournee_ = Matin; 

	menuMatin_ = new Menu("menu.txt", Matin);
	menuMidi_ = new Menu("menu.txt", Midi);
	menuSoir_ = new Menu("menu.txt",  Soir);

}

/////////////////////////////////////////////////
///NOM: Restaurant (constructeur par parametre)
///PARAMETRES: const string& fichier, const string& nom et typeMenu moment
///RETOUR : aucun
///DESCRIPTION : constructeur par parametre qui cree un restaurant ayant le nom et servant le type de menu passes en parametre
///				le constructeur appelle egalement lireMenu pour lire le fichier contenant les information sur les tables du restaurant
/////////////////////////////////////////////////
Restaurant::Restaurant(const string& fichier,  const string& nom, TypeMenu moment) {
	nom_ = new string(nom); 

	chiffreAffaire_ = 0; 

	momentJournee_ = moment; 

	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier,  Midi);
	menuSoir_ = new Menu(fichier,  Soir);

	lireTable(fichier); 
	lireAdresses(fichier);
}

/////////////////////////////////////////////////
///NOM: Restaurant (constructeur par copie)
///PARAMETRES: const Restaurant& restaurant
///RETOUR : aucun
///DESCRIPTION : constructeur par defaut qui cree un restaurant de nom "inconnu", servant un menu du matin
/////////////////////////////////////////////////
Restaurant::Restaurant(const Restaurant & restau) : nom_(new string(*restau.nom_)),
chiffreAffaire_(restau.chiffreAffaire_),
momentJournee_(restau.momentJournee_),
menuMatin_(new Menu(*restau.menuMatin_)),
menuMidi_(new Menu(*restau.menuMidi_)),
menuSoir_(new Menu(*restau.menuSoir_))
{
	tables_.clear();
	for (unsigned i = 0; i < restau.tables_.size(); ++i)
		tables_.push_back(new Table(*restau.tables_[i]));
	for (unsigned i = 0; i < NB_ZONES_LIVR; i++) 
		fraisTransport_[i] = restau.fraisTransport_[i];


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
	for (unsigned i = 0; i < tables_.size(); ++i)
		delete tables_[i];

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
void Restaurant::setNom(const string & nom)
{
	nom_ = new string(nom);
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

/////////////////////////////////////////////////
///NOM: getFraisTransport
///PARAMETRES: int index
///RETOUR : fraisTransport_[index]
///DESCRIPTION : retourne le frais de transport selon la zonage indique par index
/////////////////////////////////////////////////
double Restaurant::getFraisTransports(int index) const
{
	return fraisTransport_[index];
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

	for (unsigned i = 0; i < tables_.size(); ++i) {
		if (id == tables_[i]->getId() && tables_[i]->estOccupee()) {
			chiffreAffaire_ += tables_[i]->getChiffreAffaire() +
				calculerReduction(tables_[i]->getCliengtPrincipal(), tables_[i]->getChiffreAffaire(), i == INDEX_TABLE_LIVRAISON);
		
			tables_[i]->libererTable(); 
			break;
		}
	}
}

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os, const Restaurant& restaurant
///RETOUR : os
///DESCRIPTION : overload de l'operateur << qui affiche les donnees pertinentes au restaurant (le chiffre d'affaire, l'etat des tables et les menus du restaurant)
/////////////////////////////////////////////////
ostream& operator<<(ostream& os, const Restaurant& restau)
{
	os << "Le restaurant " << *restau.nom_;
	if (restau.chiffreAffaire_ != 0)
		os << " a fait un chiffre d'affaire de : " << restau.chiffreAffaire_ << "$" << endl;
	else
		os << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;

	os << "-Voici les tables : " << endl;

	for (unsigned i = 0; i < restau.tables_.size(); i++) {
		os  << *restau.tables_[i] << endl;
	}
	os << endl;


	os << "-Voici son menu : " << endl;
	os << "Matin : " << endl
		<<*restau.menuMatin_<<endl << "Le plat le moins cher est : " << *restau.menuMatin_->trouverPlatMoinsCher() << endl;

	os << "Midi : " << endl
		<< *restau.menuMidi_<<endl << "Le plat le moins cher est : " << *restau.menuMidi_->trouverPlatMoinsCher() << endl;
	os << "Soir : " << endl
		<< *restau.menuSoir_<<endl << "Le plat le moins cher est : " << *restau.menuSoir_->trouverPlatMoinsCher() <<endl;

	return os;
}

/////////////////////////////////////////////////
///NOM: commanderPlat
///PARAMETRES: const string& nom, int idTable,TypePlat type, int nbIngredients
///RETOUR : aucun
///DESCRIPTION : Methode qui commande un plat, soit qui cherche dans le menu pour trouver un plat par son nom et 
///				l'ajoute a la commande de la table ayant le id en parametre
/////////////////////////////////////////////////
void Restaurant::commanderPlat(const string& nom, int idTable,TypePlat type, int nbIngredients) {
	Plat* plat = nullptr;

	int index;
	for (unsigned i = 0; i < tables_.size(); i++) {
		if (idTable == tables_[i]->getId()) {
			index = i;
			switch (momentJournee_) {
			case Matin:
				plat = menuMatin_->trouverPlat(nom);
				break;
			case Midi:
				plat = menuMidi_->trouverPlat(nom);
				break;
			case Soir:
				plat = menuSoir_->trouverPlat(nom);
				break;
			}
			break;
		}
	}
	if (plat == nullptr || !tables_[index]->estOccupee()) {

		cout << "Erreur : table vide ou plat introuvable" << endl << endl;
	}
	else {
		if (type == Custom) { 
			PlatCustom* platCustom = new PlatCustom(plat->getNom(), plat->getPrix(), plat->getCout(), nbIngredients);
			tables_[index]->commander(platCustom);
		}
		else
			tables_[index]->commander(plat);
	}
}

/////////////////////////////////////////////////
///NOM: operator<
///PARAMETRES: const Restaurant& restaurant1, const Restaurant& restaurant2
///RETOUR : bool (true/false)
///DESCRIPTION : overload de l'operateur < qui compare le chiffre d'affaire entre 2 restaurant, retourne vrai si 
///				le premier restaurant a fait moins de profit que le 2e rentre en parametre
/////////////////////////////////////////////////
bool Restaurant::operator<(const Restaurant & restau) const 
{
	return this->chiffreAffaire_ < restau.chiffreAffaire_;
}

/////////////////////////////////////////////////
///NOM: operator=
///PARAMETRES: const Restaurant& restaurant
///RETOUR : *this
///DESCRIPTION : overload de l'operateur = qui ecrase le restaurant courrant (this) avec les attributs du restaurant entre en parametre
/////////////////////////////////////////////////
Restaurant & Restaurant::operator=(const Restaurant & restau)
{
	if (this != &restau)
	{
		chiffreAffaire_ = restau.chiffreAffaire_;
		momentJournee_ = restau.momentJournee_;
		menuMatin_ = new Menu(*restau.menuMatin_);
		menuMidi_ = new Menu(*restau.menuMidi_);
		menuSoir_ = new Menu(*restau.menuSoir_);
		for (unsigned i = 0; i < tables_.size(); ++i)
			delete tables_[i];

		tables_.clear();
		for (unsigned i = 0; i < restau.tables_.size(); ++i)
			tables_.push_back(new Table(*restau.tables_[i]));
		for (unsigned i = 0; i < NB_ZONES_LIVR; i++)
			fraisTransport_[i] = restau.getFraisTransports(i);

	}

	return *this;
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
		while ( !file.eof()) {
			getline(file, ligne); 
			if (ligne == "-TABLES") {
					getline(file, ligne); 
				do {
					for (unsigned i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i; 
							break; 
						}
						idString += ligne[i]; 
					}

					id = stoi(idString); 

					nbPersonnesString = ligne.substr(curseur + 1); 
					nbPersonnes = stoi(nbPersonnesString); 

					*this+= new Table(id, nbPersonnes); 
					nbPersonnesString = ""; 
					idString = ""; 					
					getline(file, ligne);

				} while (ligne[0] != '-' && !file.eof());
			}
		}
		file.close(); 
	}
}

/////////////////////////////////////////////////
///NOM: operator+=
///PARAMETRES: Table* table
///RETOUR : *this
///DESCRIPTION : overload de l'operateur += permet d'ajouter un pointeur de table aux tables du restaurant
/////////////////////////////////////////////////
Restaurant& Restaurant::operator+=(Table* table) {
	tables_.push_back(new Table(*table)); 
	return *this;
}

/////////////////////////////////////////////////
///NOM: PlacerClient
///PARAMETRES: int nbClients
///RETOUR : aucun
///DESCRIPTION : Methode qui place les clients de facon "intelligente", c'est a dire que les clients seront places a une 
///				table ayant le moins de nombre de place possible.
///				ex. un groupe de 4 personne serait placee a une table de 5 places versus une autre de 10 si les 2 sont libres
/////////////////////////////////////////////////
void Restaurant::placerClients(Client* client) {
	int indexTable = -1;
	int minimum = 100;

	for (unsigned i = 0; i < tables_.size(); i++) {
		if (tables_[i]->getNbPlaces() >= client->getTailleGroupe() && !tables_[i]->estOccupee() && tables_[i]->getNbPlaces() < minimum && i != INDEX_TABLE_LIVRAISON) {
			indexTable = i;
			minimum = tables_[i]->getNbPlaces();
		}
	}
	if (indexTable == -1) {
		cout << "Erreur : il n'y a plus/pas de table disponible pour les clients. " << endl;
	}
	else {
		tables_[indexTable]->placerClients(client->getTailleGroupe());
		tables_[indexTable]->setClientPrincipal(client);
	}
}

/////////////////////////////////////////////////
///NOM: livrerClient
///PARAMETRES: Client * client, vector<string> commande
///RETOUR : aucun
///DESCRIPTION : methode qui livre une commande a un client si celui ci a les prerequis
/////////////////////////////////////////////////
void Restaurant::livrerClient(Client * client, vector<string> commande)
{
	if (client->getStatut() == Prestige)
	{
		cout <<endl << "Livraison en cours ..." << endl;
		if (!tables_[INDEX_TABLE_LIVRAISON]->estOccupee()) {
			tables_[INDEX_TABLE_LIVRAISON]->setClientPrincipal(client);
			tables_[INDEX_TABLE_LIVRAISON]->placerClients(client->getTailleGroupe());
		}

		for (unsigned int i = 0; i < commande.size(); i++) {
			commanderPlat(commande[i], tables_[INDEX_TABLE_LIVRAISON]->getId());
		}

		cout << "Livraison: " << endl;
		cout << *tables_[INDEX_TABLE_LIVRAISON] << endl;
		libererTable(tables_[INDEX_TABLE_LIVRAISON]->getId());
	}
	else
		cout << "Le client "<< client->getNom() << " n'a pas le droit aux livraisons";
}

/////////////////////////////////////////////////
///NOM: calculerReduction
///PARAMETRES: Client * client, double montant, bool livraison
///RETOUR : reduction
///DESCRIPTION : methode qui calcule les reductions selon le type de client et les points accumules
/////////////////////////////////////////////////
double Restaurant::calculerReduction(Client * client, double montant, bool livraison)
{
	double reduction = 0.0;
	switch (client->getStatut()) {
		case Fidele:
			if (static_cast<ClientRegulier*>(client)->getNbPoints() >= SEUIL_DEBUT_REDUCTION)
				reduction -= montant * TAUX_REDUC_REGULIER;
			break;
		case Prestige:
			reduction -= montant * TAUX_REDUC_PRESTIGE;
			if (livraison) {
				ClientPrestige* clientPrestige = static_cast<ClientPrestige*>(client);
				if (clientPrestige->getNbPoints() < SEUIL_LIVRAISON_GRATUITE)
					reduction += getFraisTransports(clientPrestige->getAddresseCode());
			}
			break;
	}
	return reduction;
}

/////////////////////////////////////////////////
///NOM: LireAddresses
///PARAMETRES: const string& fichier
///RETOUR : aucun
///DESCRIPTION : Methode qui lit un fichier pour en retirer le prix de livraison par zonage
/////////////////////////////////////////////////
void Restaurant::lireAdresses(const string & fichier)
{
	ifstream file(fichier, ios::in);

		if (file) {
			string ligne;

			string addresseCodeStr;
			int addressCode;

			string fraisStrg;
			double frais;

			int curseur;
			while (!file.eof()) {
				getline(file, ligne);
				if (ligne == "-ADDRESSES") {
					while (!file.eof()) {
						getline(file, ligne);
						for (unsigned i = 0; i < ligne.size(); i++) {
							if (ligne[i] == ' ') {
								curseur = i;
								break;
							}
							addresseCodeStr += ligne[i];
							addressCode = stoi(addresseCodeStr);

						}


						fraisStrg = ligne.substr(curseur + 1);
						frais = stod(fraisStrg);
						fraisTransport_[addressCode] = frais;

						addresseCodeStr = "";
						fraisStrg = "";



					}

					
				}
			}
			file.close();
		}
	}


