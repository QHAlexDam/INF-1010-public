
#include "ClientPrestige.h"
#include "Restaurant.h"
#include "debogageMemoire.hpp"

//Constructeur

ClientPrestige::ClientPrestige()
{
	adresse_ = ZoneHabitation::Zone3;
}

/////////////////////////////////////////////////
///NOM: ClientPrestige
///PARAMETRES: string_view nom, string_view prenom, int tailleGroupe, int nbPoints, ZoneHabitation adresse
///RETOUR : aucun
///DESCRIPTION : constructeur par parametre qui utilise le constructeur par parametre de ClientRegulier, en plus de setter une addresse
/////////////////////////////////////////////////
ClientPrestige::ClientPrestige(string_view nom, string_view prenom, int tailleGroupe, int nbPoints, ZoneHabitation adresse)
	: ClientRegulier(nom, prenom , tailleGroupe, nbPoints), adresse_(adresse)
{
   //ok
}

//Getter

ZoneHabitation ClientPrestige::getAdresseCode() const
{
	return adresse_;
}

string ClientPrestige::getAdressCodeString() const
{
	string zone;
	switch (adresse_)
	{
	case ZoneHabitation::Zone1:
		zone = "Zone 1";
		break;
	case  ZoneHabitation::Zone2:
		zone = " Zone 2";
		break;
	case  ZoneHabitation::Zone3:
		zone = "Zone 3";
		break;

	default:
		zone = "erreur zone";
		break;
	}
	return zone;
}

/////////////////////////////////////////////////
///NOM: getReduction
///PARAMETRES: const Restaurant & res, double montant , bool estLivraison
///RETOUR : reduction
///DESCRIPTION : methode qui retourne la reduction (combinaison de la reduction du statut et la reduction de livraison s'il a lieu
/////////////////////////////////////////////////
double ClientPrestige :: getReduction(const Restaurant & res, double montant , bool estLivraison) const
{   //ok
	double reduction = 0.0;
	if (nbPoints_ >= SEUIL_DEBUT_REDUCTION) {
		reduction = ((-montant)*TAUX_REDUC_PRESTIGE);
	}
	if (estLivraison) {
		if (nbPoints_ < SEUIL_LIVRAISON_GRATUITE) {
			reduction -= res.getFraisLivraison(adresse_);
		}
	}
	return reduction;
}

//Afficheur

/////////////////////////////////////////////////
///NOM: afficherClient
///PARAMETRES: ostream & os
///RETOUR : aucun
///DESCRIPTION : methode qui affiche les donnees pertinentes, en utilisant l'afficheur de ClientRegulier, en plus d'afficher l'adresse
/////////////////////////////////////////////////
void ClientPrestige::afficherClient(ostream & os) const
{
	// ok
	ClientRegulier::afficherClient(os);
	os << "Habite dans la: " << getAdressCodeString() << endl;

}
