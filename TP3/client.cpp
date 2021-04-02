

#include"Client.h"

using namespace std;

//Constructeurs

/////////////////////////////////////////////////
///NOM: Client (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut 
/////////////////////////////////////////////////
Client::Client() :
nom_("inconnu"), prenom_ ("inconnu"), statut_ (Occasionnel){
}

/////////////////////////////////////////////////
///NOM: Client (constructeur par parametre)
///PARAMETRES: String nom, string prenom, int tailleGroupe
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre 
/////////////////////////////////////////////////
Client::Client(string nom, string prenom, int tailleGroupe):
	nom_(nom), prenom_(prenom), tailleGroupe_(tailleGroupe), statut_(Occasionnel) {
}

//Destructeur
/////////////////////////////////////////////////
///NOM: Menu (Destructeur)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : efface la memoire, ici, rien ne depend de Client, alors le destructeur est vide
/////////////////////////////////////////////////
Client::~Client() {

}

// Accesseurs
/////////////////////////////////////////////////
///NOM: getStatut
///PARAMETRES: aucun
///RETOUR : statut_
///DESCRIPTION : getter qui retourne le statut du client
/////////////////////////////////////////////////
StatutClient Client::getStatut() const{
	return statut_;
}

/////////////////////////////////////////////////
///NOM: getTailleGroupe
///PARAMETRES: aucun
///RETOUR : tailleGroupe_
///DESCRIPTION : getter qui retourne la taille gu groupe client
/////////////////////////////////////////////////
int Client::getTailleGroupe() const{
	return tailleGroupe_;
}

/////////////////////////////////////////////////
///NOM: getNom
///PARAMETRES: aucun
///RETOUR : nom_
///DESCRIPTION : getter qui retourne le nom du client
/////////////////////////////////////////////////
string Client::getNom() const{
	return nom_;
}

/////////////////////////////////////////////////
///NOM: getPrenom
///PARAMETRES: aucun
///RETOUR : prenom_
///DESCRIPTION : getter qui retourne le prenom du client
/////////////////////////////////////////////////
string Client::getPrenom() const{
	return prenom_;
}

//Autes méthodes

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os et const Client& client
///RETOUR : os
///DESCRIPTION : oveloader de l'operateur << qui sert a afficher les details du client
/////////////////////////////////////////////////
ostream & operator<<(ostream & os, const Client& client) {
	os << "\t-" << client.prenom_ << " " << client.nom_ << " statut: " << client.convertirStatutString();
	if (client.statut_ == Occasionnel)
		os << endl;
	return os;
}

/////////////////////////////////////////////////
///NOM: convertirStatutString
///PARAMETRES: aucun
///RETOUR : string
///DESCRIPTION : convertit le statut en string
/////////////////////////////////////////////////
string Client::convertirStatutString() const {
	switch (statut_) {
		case Occasionnel: return("Occasionnel");
			break;
		case Fidele: return("Fidele");
			break;
		case Prestige: return("Prestige");
			break;
		default:
			return ("erreur");
	}
}