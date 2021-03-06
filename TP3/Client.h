
#ifndef CLIENT
#define CLIENT

#include <string>
#include <iostream>

using namespace std;

enum StatutClient { Occasionnel,Fidele,Prestige };

class Client{
public:
	Client();
	Client(string nom,string prenom,int tailleGroupe);
	~Client();

// Accesseurs
	StatutClient getStatut() const;
	int getTailleGroupe() const;
	string getNom() const;
	string getPrenom() const;
	
//Autes m?thodes

	friend ostream & operator<<(ostream & os, const Client& client);

private:
	string convertirStatutString() const;

protected:
	string nom_;
	string prenom_;
	int tailleGroupe_;
	StatutClient statut_;
};

#endif

