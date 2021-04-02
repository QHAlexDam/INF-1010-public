

#include "Client.h"
#include "debogageMemoire.hpp"
//Constructeur

Client::Client()
{ tableOccupee_ = nullptr;
}

Client::Client( string_view nom, string_view prenom, int tailleGroupe) :
	nom_(nom), prenom_(prenom), tailleGroupe_(tailleGroupe)
{
    tableOccupee_ = nullptr;
}

//Destructeur

Client::~Client() {}

//Getter

int Client::getTailleGroupe() const
{
	return tailleGroupe_;
}

string Client::getNom() const
{
	return nom_;
}

string Client::getPrenom() const
{
	return prenom_;
}

Table * Client::getTable() const
{
	return tableOccupee_;
}

//Setter

void Client:: setTable(Table * ta)
{ tableOccupee_ = ta;}


//Afficheur

/////////////////////////////////////////////////
///NOM: afficherClient
///PARAMETRES: ostream& os
///RETOUR : aucun
///DESCRIPTION : Methode qui affiche les donnees pertinentes d'un client et sa table s'il a lieu
/////////////////////////////////////////////////
void Client::afficherClient(ostream & os) const
{ 
	os << prenom_ << " " << nom_;
	if (tableOccupee_ != nullptr) {
		os << " a une place au resto." << endl;
		os << tableOccupee_;
	}
	else{
		os << "n'a pas une place au resto" << endl;
	}
}

