
#ifndef CLIENT_OCCASIONNEL
#define CLIENT_OCCASIONNEL

#include "Client.h"

class ClientOccasionnel: public Client
{
public:
	//Constructeur
	ClientOccasionnel(string_view nom, string_view prenom, int tailleGroupe);
	//Destructeur
    virtual  ~ClientOccasionnel();
	//Getter
    int getNbPoints() const override;
    double getReduction(const Restaurant & res, double montant, bool estLivraison) const override; 
	//Afficheur
	void afficherClient(ostream & os) const override;
};

#endif
