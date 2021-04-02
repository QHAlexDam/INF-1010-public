

#include"ClientRegulier.h"

using namespace std;

/////////////////////////////////////////////////
///NOM: ClientRegulier (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut de CientRegulier
/////////////////////////////////////////////////
ClientRegulier::ClientRegulier() :Client() {
	nbPoints_ = 0;
	statut_ = Fidele;
}

/////////////////////////////////////////////////
///NOM: ClientRegulier (constructeur par parametre)
///PARAMETRES:string nom, string prenom, int tailleGroupe, int nbPoints
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de ClientRegulier
/////////////////////////////////////////////////
ClientRegulier::ClientRegulier(string nom, string prenom, int tailleGroupe, int nbPoints): 
	Client(nom,prenom,tailleGroupe), nbPoints_ (nbPoints){
	statut_ = Fidele;
}


//Accesseurs

/////////////////////////////////////////////////
///NOM: getNbPoints 
///PARAMETRES: aucun
///RETOUR : nbPoints_
///DESCRIPTION : retourne le nombre de points
/////////////////////////////////////////////////
int ClientRegulier::getNbPoints() const {
	return nbPoints_;
}

//Autres Méthodes

/////////////////////////////////////////////////
///NOM: augmenterNbPoints
///PARAMETRES: int bonus
///RETOUR : aucun
///DESCRIPTION : augmente le nombre de points par bonus
/////////////////////////////////////////////////
void ClientRegulier::augmenterNbPoints(int bonus) {
	nbPoints_ += bonus;
}

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os et const ClientRegulier& client
///RETOUR : out
///DESCRIPTION : oveloader de l'operateur << qui sert a afficher les details du client regulier
/////////////////////////////////////////////////
ostream & operator<<(ostream & os, const ClientRegulier& client) {



	os << static_cast<Client>(client) << " Possede " << client.nbPoints_ << " points";
	
	if (client.getStatut() == Fidele)
		os << endl;

	return os;
}
