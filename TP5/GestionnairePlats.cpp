

#include "gestionnairePlats.h"
#include "LectureFichierEnSections.h"
#include "PlatBio.h"
#include "PlatVege.h"
#include "PlatBioVege.h"
#include "Plat.h"

/////////////////////////////////////////////////
///NOM: GestionnairePlats
///PARAMETRES: const string& nomFichier, TypeMenu type
///RETOUR :aucun
///DESCRIPTION : Constructeur par parametre de GestionnairePlat qui 
///				lit le fichier et assigne le type de menu.
/////////////////////////////////////////////////
GestionnairePlats::GestionnairePlats(const string& nomFichier, TypeMenu type) {
	lirePlats(nomFichier, type);
	type_ = type;
}

/////////////////////////////////////////////////
///NOM: GestionnairePlats
///PARAMETRES: GestionnairePlats * gestionnaire
///RETOUR :aucun
///DESCRIPTION : constructeur par copie qui contruit un nouveau gestionnaire identique a celui passe en parametre
/////////////////////////////////////////////////
GestionnairePlats::GestionnairePlats(GestionnairePlats * gestionnaire)
{
	if (this != gestionnaire) {
		conteneur_ = gestionnaire->getConteneur();
		type_ = gestionnaire->getType();
	}


}

/////////////////////////////////////////////////
///NOM: getType
///PARAMETRES: aucun
///RETOUR : TypeMenu type
///DESCRIPTION : methode qui retourne le type de menu
/////////////////////////////////////////////////
TypeMenu GestionnairePlats::getType() const {
	return type_;
}

/////////////////////////////////////////////////
///NOM: trouverPlatMoinsCher
///PARAMETRES: aucun
///RETOUR : Plat* plat moins cher
///DESCRIPTION : Methode qui parourt le conteneur et utilise le foncteur 
///				FoncteurPlatMoinsCher pour trouver le plat dont le prix est le moindre
/////////////////////////////////////////////////
Plat* GestionnairePlats::trouverPlatMoinsCher() const {
	
	return (min_element(conteneur_.begin(), conteneur_.end(), FoncteurPlatMoinsCher()))->second;
}

/////////////////////////////////////////////////
///NOM: trouverPlatPlusCher
///PARAMETRES: aucun
///RETOUR : Plat* plat le plus cher
///DESCRIPTION : Methode qui trouve le plat le plus cher, cette fois-ci,
///				en utilisant une fonction lamda
/////////////////////////////////////////////////
Plat * GestionnairePlats::trouverPlatPlusCher() const
{
	//return max_element(conteneur_.begin(), conteneur_.end(), FoncteurPlatMoinsCher())->second; ca marche mais sans fonction lamda 
	auto it = max_element(conteneur_.begin(), conteneur_.end(), [](const pair<string, Plat*> plat1, const pair<string, Plat*> plat2) -> bool {return plat1.second->getPrix() < plat2.second->getPrix(); });
	return it->second;
	

}

/////////////////////////////////////////////////
///NOM: getPlatsEntre
///PARAMETRES: double borneInf, double borneSup
///RETOUR : vecteur de pair<string,Plat*>
///DESCRIPTION : Methode qui trouve et retourne les plats a l'interieur d'un interval, 
///				avec le foncteur FoncteurIntervalle
/////////////////////////////////////////////////
vector<pair<string, Plat*>> GestionnairePlats::getPlatsEntre(double borneInf, double borneSup) const
{
	
	vector<pair<string, Plat*>> listePlats;
	copy_if(conteneur_.begin(), conteneur_.end(),back_inserter(listePlats) , FoncteurIntervalle(borneInf, borneSup));
	return listePlats;
	
}


void GestionnairePlats::lirePlats(const string& nomFichier, TypeMenu type)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type)]);
	while (!fichier.estFinSection()) {
		ajouter(lirePlatDe(fichier));
	}
}

pair<string, Plat*> GestionnairePlats::lirePlatDe(LectureFichierEnSections& fichier)
{
	auto lectureLigne = fichier.lecteurDeLigne();
	Plat* plat;
	string nom, typeStr;
	TypePlat type;
	double prix, coutDeRevient;
	lectureLigne >> nom >> typeStr >> prix >> coutDeRevient;
	type = TypePlat(stoi(typeStr));
	double ecotaxe, vitamines, proteines, mineraux;
	switch (type) {
	case TypePlat::Bio:
		lectureLigne >> ecotaxe;
		plat = new PlatBio{ nom, prix, coutDeRevient, ecotaxe };
		break;
	case TypePlat::BioVege:
		lectureLigne >> ecotaxe >> vitamines >> proteines >> mineraux;
		plat = new PlatBioVege(nom, prix, coutDeRevient, ecotaxe, vitamines, proteines, mineraux);
		break;
	case TypePlat::Vege:
		lectureLigne >> vitamines >> proteines >> mineraux;
		plat = new PlatVege(nom, prix, coutDeRevient, vitamines, proteines, mineraux);
		break;
	default:
		plat = new Plat{ nom, prix, coutDeRevient };
	}
	return pair<string, Plat*>(plat->getNom(), plat);
}


/////////////////////////////////////////////////
///NOM: trouverPlat
///PARAMETRES: const string & nom
///RETOUR :Plat* plat
///DESCRIPTION : methode qui trouve un plat dans le conteneur par son nom, 
///				retourne un nullptr si il trouve rien
/////////////////////////////////////////////////
Plat * GestionnairePlats::trouverPlat(const string & nom) const
{
	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		if (it->second->getNom() == nom) {
			return it->second;
		}
	}
	return nullptr;
}



/////////////////////////////////////////////////
///NOM: ~GestionnairePlats
///PARAMETRES: aucun	
///RETOUR : aucun
///DESCRIPTION : Destructeur, doit delete les plats qui se trouvent dans les pair, car c'est une composition
/////////////////////////////////////////////////
GestionnairePlats::~GestionnairePlats()
{
	/*for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		delete it->second;
	}*/
	for_each(conteneur_.begin(), conteneur_.end(), [&](pair<string, Plat*> m) {delete m.second; });
	conteneur_.clear();
}

/////////////////////////////////////////////////
///NOM: allouerPlat
///PARAMETRES: Plat * plat
///RETOUR : Plat* plat clone
///DESCRIPTION : methode qui retourne une copie d'un plat passe en parametre, 
///				utilise la metode clone de Plat
/////////////////////////////////////////////////
Plat * GestionnairePlats::allouerPlat(Plat * plat)
{
	return plat->clone();
}

/////////////////////////////////////////////////
///NOM: afficherPlats
///PARAMETRES: ostream& os
///RETOUR : aucun
///DESCRIPTION : methode qui affiche les plats du conteneur
/////////////////////////////////////////////////
void GestionnairePlats::afficherPlats(ostream& os) const{

	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
		it->second->afficherPlat(os);
	}
}

