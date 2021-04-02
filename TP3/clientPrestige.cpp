

#include "ClientPrestige.h"

using namespace std;

/////////////////////////////////////////////////
///NOM: ClientPrestige (constructeur par defaut)
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : Constructeur par defaut de ClientPrestige
/////////////////////////////////////////////////
ClientPrestige::ClientPrestige():ClientRegulier(){
	addresse_ = Zone3;
	statut_ = Prestige;
}

/////////////////////////////////////////////////
///NOM: ClientPrestige (constructeur par parametre)
///PARAMETRES: string nom, string prenom, int tailleGroupe, int bnPoints, AddressCode addresse
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de ClientPrestige
/////////////////////////////////////////////////
ClientPrestige::ClientPrestige(string nom, string prenom, int tailleGroupe, int nbPoints, AddressCode addresse):
	ClientRegulier(nom,prenom,tailleGroupe,nbPoints), addresse_(addresse) {

	
	statut_ = Prestige;
}

//Accesseur 

/////////////////////////////////////////////////
///NOM: getAddressCode
///PARAMETRES: aucun
///RETOUR : addresse_
///DESCRIPTION : retourne l'addresse
/////////////////////////////////////////////////
AddressCode ClientPrestige::getAddresseCode() {
	return addresse_;
}

//Autres Fonctions

/////////////////////////////////////////////////
///NOM: operator<<
///PARAMETRES: ostream& os et const ClientPrestige& client
///RETOUR : out
///DESCRIPTION : oveloader de l'operateur << qui sert a afficher les details du client prestige
/////////////////////////////////////////////////
ostream & operator<<(ostream & os, ClientPrestige client) {
	os << static_cast<ClientRegulier>(client) << ", est dans la " << client.getAddressCodeString() << endl;
	return os;
}

/////////////////////////////////////////////////
///NOM: getAddressCodeString
///PARAMETRES: aucun
///RETOUR : string
///DESCRIPTION : convertit l'addresse en string
/////////////////////////////////////////////////
string ClientPrestige::getAddressCodeString() {
	switch (addresse_) {
	case Zone1: return("Zone1");
		break;
	case Zone2: return("Zone2");
		break;
	case Zone3: return("Zone3");
		break;
	}
}