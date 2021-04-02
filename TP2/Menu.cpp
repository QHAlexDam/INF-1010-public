
#include "Menu.h"

//constructeurs

/////////////////////////////////////////////////
///NOM: Menu (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut de Menu, initialise le type de menu a matin
/////////////////////////////////////////////////
Menu::Menu() :type_(Matin) {}

/////////////////////////////////////////////////
///NOM: Menu (constructeur par parametre)
///PARAMETRES: String fichier, TypeMenu type
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de Menu, initialise le type de menu au type en parametre et 
///				lit appele lireMenu qui lit le fichier dont le nom est passe en parametre
/////////////////////////////////////////////////
Menu::Menu(string fichier, TypeMenu type): type_(type) {
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
Menu::Menu(const Menu& menu): type_(menu.type_), listePlats_(menu.listePlats_){
	for (int i = 0; i < listePlats_.size(); i++) {
		listePlats_[i] = new Plat(*listePlats_[i]);
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
	for (int i = 0; i < listePlats_.size(); i++) 
	{
		delete listePlats_[i];
	}
	listePlats_.clear();
}

//getters

/////////////////////////////////////////////////
///NOM: getNbPlats
///PARAMETRES: aucun
///RETOUR : listePlats.size() (la quantite de plats dans le menu)
///DESCRIPTION : getter qui retourne la quantite de plats dans le menu
/////////////////////////////////////////////////
int Menu::getNbPlats() const {
	return listePlats_.size();
}

/////////////////////////////////////////////////
///NOM: getListePlats
///PARAMETRES: aucun
///RETOUR : listePlats (un vecteur)
///DESCRIPTION : getter qui retourne la liste complete des plats dans le menu
/////////////////////////////////////////////////
vector<Plat*> Menu::getListePlat() const{
	return listePlats_;
}

/////////////////////////////////////////////////
///NOM: getTyoe
///PARAMETRES: aucun
///RETOUR : type_
///DESCRIPTION : getter qui retourne le type de menu (matin, midi ou soir)
/////////////////////////////////////////////////
TypeMenu Menu::getType() const{
	return type_;
}

//Overload d'operateurs

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& out et const Menu& menu
///RETOUR : out
///DESCRIPTION : oveloader de l'operateur << qui sert a afficher les details du menu, soit les informations sur les
///				plats du menu. Il utilise donc l'operateur << overloader de la classe Plat
/////////////////////////////////////////////////
ostream& operator<<(ostream& out, const Menu& menu) {

	for (int i = 0; i < menu.listePlats_.size(); i++) {
		
		out << *menu.listePlats_[i];

	}
	return out;
}

/////////////////////////////////////////////////
///NOM: operator+=
///PARAMETRES: Plat* plat
///RETOUR : *this
///DESCRIPTION : oveloader de l'operateur += qui ajoute un pointeur de plat passe en parametre a la liste de plats du menu
/////////////////////////////////////////////////
Menu& Menu::operator+=(Plat*  plat) {
	listePlats_.push_back(plat);
	return *this;
}

/////////////////////////////////////////////////
///NOM: operator=
///PARAMETRES: const Menu& menu
///RETOUR : *this
///DESCRIPTION : oveloader de l'operateur = qui ecrase le menu courant (this) avec le menu entre en parametre,
///				tous les attributs du nouveau menu sont transferes
/////////////////////////////////////////////////
Menu& Menu::operator=(const Menu& menu) {
	if (this != &menu) {
		listePlats_ = menu.listePlats_;
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
bool Menu::lireMenu(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (!file) {
		//cout << "ERREUR : le fichier n'a pas pu etre ouvert" << endl;
		return false;
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
		int cout;


		// lecture
		while (!file.eof()) {
			getline(file, ligne);
			//trouver le bon type de menu (section)
			if (ligne == type){
				//commencer a lire -- s'arrete si fin du fichier ou encore si on arrive a une nouvelle section du menu
				getline(file, ligne);
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
						if (ligne[i] == ' ')
							break;
						coutString += ligne[i];
					}

					cout =int( stof(coutString.c_str()));

					listePlats_.push_back(new Plat(nom, prix, cout));
					nom = "";
					prixString = "";
					coutString = "";

					getline(file, ligne);
				}
			}
		}

		file.close();
		return true;
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
		if (listePlats_[i]->getPrix() < minimum.getPrix())
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
	for (int i = 0; i < listePlats_.size(); i++) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i];
	}
	return nullptr;
}
