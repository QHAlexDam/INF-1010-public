
#ifndef CLIENT_PRESTIGE
#define CLIENT_PRESTIGE

#include "ClientRegulier.h"
//using namespace std;

enum AddressCode{Zone1,Zone2,Zone3};
class ClientPrestige : public ClientRegulier
{
public:
	ClientPrestige();
	ClientPrestige(string nom, string prenom, int tailleGroupe, int nbPoints,AddressCode addresse);

	//Accesseur 
	AddressCode getAddresseCode();

	//Autres Fonctions??
	friend ostream & operator<<(ostream & os, ClientPrestige client);
	string getAddressCodeString();



private: 
	AddressCode addresse_;

};

#endif;

