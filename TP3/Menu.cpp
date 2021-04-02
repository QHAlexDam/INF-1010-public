

#include "Menu.h"

//constructeurs 

/////////////////////////////////////////////////
///NOM: Menu (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut de Menu, initialise le type de menu a matin
/////////////////////////////////////////////////
Menu::Menu() {
	type_ = Matin; 
}

/////////////////////////////////////////////////
///NOM: Menu (constructeur par parametre)
///PARAMETRES: String fichier, TypeMenu type
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de Menu, initialise le type de menu au type en parametre et 
///				lit appele lireMenu qui lit le fichier dont le nom est passe en parametre
/////////////////////////////////////////////////
Menu::Menu(string fichier, TypeMenu type) {
	type_ = type; 

	//lecture du fichier -- creation du menu
	lireMenu(fichier); 
}

/////////////////////////////////////////////////
///NOM: Menu (constructeur par copie)
///PARAMETRES: Const
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de Menu, initialise le type de menu au type en parametre et 
///				lit appele lireMenu qui lit le fichier dont le nom est passe en parametre
/////////////////////////////////////////////////
Menu::Menu(const Menu & menu): type_(menu.type_)
{
	///TODO 
	///Modifier
	if (this != &menu) {
		for (unsigned i = 0; i < menu.listePlats_.size(); ++i)
		{
			switch (menu.listePlats_[i]->getType()) {
			case Regulier: listePlats_.push_back(new Plat(*menu.listePlats_[i]));
				break;
			case Bio:
				listePlats_.push_back(new PlatBio (menu.listePlats_[i]->getNom(), menu.listePlats_[i]->getPrix(), menu.listePlats_[i]->getCout(), static_cast<PlatBio*>(menu.listePlats_[i])->getEcoTaxe()));
				break;
			default: break;
			}

		}
	}
}

//destructeur

/////////////////////////////////////////////////
///NOM: Menu (Destructeur)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : efface la memoire, ici menu et plat ont une relation de composition, alors il faut deleter les plats
/////////////////////////////////////////////////
Menu::~Menu() {
	for (unsigned int i = 0; i < listePlats_.size(); i++) {
		delete listePlats_[i];
	}
}

//getters

/////////////////////////////////////////////////
///NOM: getListePlats
///PARAMETRES: aucun
///RETOUR : listePlats (un vecteur)
///DESCRIPTION : getter qui retourne la liste complete des plats dans le menu
/////////////////////////////////////////////////
vector<Plat*> Menu::getListePlats() const
{
	return listePlats_;
}

//autres methodes 

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& out et const Menu& menu
///RETOUR : out
///DESCRIPTION : oveloader de l'operateur << qui sert a afficher les details du menu, soit les informations sur les
///				plats du menu. Il utilise donc l'operateur << overloader de la classe Plat
/////////////////////////////////////////////////
ostream& operator<<(ostream& os, const Menu& menu)
{
	for (unsigned i = 0; i < menu.listePlats_.size(); ++i) {
		
		if (menu.listePlats_[i]->getType() == Regulier)
			os << "\n\t" << *menu.listePlats_[i];
		else if (menu.listePlats_[i]->getType() == Bio)
			os << "\n\t" << *static_cast<PlatBio*>(menu.listePlats_[i]);
	}

	return os;
}

/////////////////////////////////////////////////
///NOM: operator+=
///PARAMETRES: Plat* plat
///RETOUR : *this
///DESCRIPTION : oveloader de l'operateur += qui ajoute un pointeur de plat 
/////////////////////////////////////////////////
Menu& Menu::operator+=(const Plat& plat) {
	
	listePlats_.push_back(new Plat(plat));
	return *this;
}

/////////////////////////////////////////////////
///NOM: operator+=
///PARAMETRES: PlatBio* plat
///RETOUR : *this
///DESCRIPTION : oveloader de l'operateur += qui ajoute un pointeur de platbio 
/////////////////////////////////////////////////
Menu & Menu::operator+=(const PlatBio & plat)
{
	listePlats_.push_back(new PlatBio(plat.getNom(), plat.getPrix(), plat.getCout(), plat.getEcoTaxe()));
	return *this;
}

/////////////////////////////////////////////////
///NOM: operator=
///PARAMETRES: const Menu& menu
///RETOUR : *this
///DESCRIPTION : oveloader de l'operateur = qui ecrase le menu courant (this) avec le menu entre en parametre,
///				tous les attributs du nouveau menu sont transferes
/////////////////////////////////////////////////
Menu & Menu::operator=(const Menu & menu)
{
	///TODO
	/// A Modifier
	if (this != &menu)
	{
		this->type_ = menu.type_;
		listePlats_.clear();
		for (unsigned i = 0; i < menu.listePlats_.size(); ++i)
		{
			switch (menu.listePlats_[i]->getType()) {
			case Regulier: listePlats_.push_back(new Plat(*menu.listePlats_[i]));
				break;
			case Bio: listePlats_.push_back(new PlatBio(menu.listePlats_[i]->getNom(), menu.listePlats_[i]->getPrix(), menu.listePlats_[i]->getCout(), static_cast<PlatBio*> (menu.listePlats_[i])->getEcoTaxe()));
				break;
			case Custom:
				listePlats_.push_back(new PlatCustom(menu.listePlats_[i]->getNom(), menu.listePlats_[i]->getPrix(), menu.listePlats_[i]->getCout(), static_cast<PlatCustom*> (menu.listePlats_[i])->getNbIngredients()));

				//PlatCustom::PlatCustom(string nom, double prix, double cout, int nbIngredients)
			default: break;
			}

		}
	}
	return *this;
}

/////////////////////////////////////////////////
///NOM: lireMenu
///PARAMETRES: string fichier
///RETOUR : bool (true/false)
///DESCRIPTION : Methode qui ouvre un fichier texte et qui lit les informations pertinentes a menu (type de menu, nom du plat, prix et cout)
///				Ensuite, la methode cree un nouveau plat pour chaque plat lu dans le fichier et ajoute un pointeur vers ce dernier dans la liste de plat du menu
/////////////////////////////////////////////////
void Menu::lireMenu(const string& fichier) {
	ifstream file(fichier, ios::in); 

	if (!file) {
		cout << "ERREUR : le fichier n'a pas pu etre ouvert" << endl; 
	}
	else {
		string type; 
		switch (type_) {
		case Matin :
			type = "-MATIN"; 
			break; 
		case Midi : 
			type = "-MIDI";
			break;
		case Soir : 
			type = "-SOIR"; 
			break;
		}
		string ligne; 

		string nom; 
		
		string prixString;
		double prix; 

		string coutString; 
		double cout;

		string typeString;
		int typePlat;

		string ecotaxeString;
		double ecoTaxe;


		// lecture
		while (!file.eof()) {
			std::getline(file, ligne); 
			//trouver le bon type de menu (section)
			if (ligne == type){ 
				//commencer a lire -- s'arrete si fin du fichier ou encore si on arrive a une nouvelle section du menu 
				std::getline(file, ligne);
				int curseur; 
				while (ligne[0] != '-' && !file.eof()) {
					//trouver le nom 
					for (int i = 0; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						nom += ligne[i]; 
					}

					//trouver le type 
					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						typeString += ligne[i];

					}

					typePlat = stoi(typeString);

					//trouver le prix 

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i; 
							break; 
						}
						prixString += ligne[i]; 
						
					}
					//passer le prixString en double --- indice dans l'enonce 
					prix = stof(prixString.c_str()); 

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							if (typePlat == Bio)
								curseur = i;
							break;

						}

						coutString += ligne[i]; 
					}

					cout = stod(coutString.c_str()); 

					//lire le taux si plat bio

					if (typePlat == TypePlat::Bio) {

						for (int i = curseur + 1; i < int(ligne.size()); i++) {
							if (ligne[i] == ' ')
								break;
							ecotaxeString += ligne[i];
						}
						ecoTaxe = stod(ecotaxeString);
						*this += PlatBio(nom, prix, cout, ecoTaxe);
					}
					else {
						*this += Plat(nom, prix, cout);
					}

					nom = ""; 
					prixString = ""; 
					coutString = ""; 
					typeString = "";
					ecotaxeString ="";

					std::getline(file, ligne);
				}
			}
		}

		file.close(); 
	}
}

/////////////////////////////////////////////////
///NOM: trouverPlatMoinsCher
///PARAMETRES: aucun
///RETOUR : listePlats[found] (un pointeur vers un plat)
///DESCRIPTION : Methode qui cherche le plat le moins cher dans le menu et retourne le pointeur vers ce plat
/////////////////////////////////////////////////
Plat * Menu::trouverPlatMoinsCher() const
{
	Plat minimum(*listePlats_[0]);
	int found = -1;

	for (unsigned i = 0; i < listePlats_.size(); ++i)
	{
		if (*listePlats_[i] < minimum)
		{
			minimum = *listePlats_[i];
			found = i;
		}
	}
	return listePlats_[found];
}

/////////////////////////////////////////////////
///NOM: trouverPlat
///PARAMETRES: const string& nom
///RETOUR : listePlat_[i] ou nullptr (pointeur vers le plat si trouve)
///DESCRIPTION : Methode qui cherche un plat dans le menu par son nom, retourne un pointeur vers le plat si trouve, nullptr sinon
/////////////////////////////////////////////////
Plat* Menu::trouverPlat(const string& nom) const {
	for (int i = 0; i < listePlats_.size(); ++i) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i]; 
	}
	return nullptr; 
}