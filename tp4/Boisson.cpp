

#include "Boisson.h"
#include"Taxable.h"
#include "debogageMemoire.hpp"

//Constructeur

/////////////////////////////////////////////////
///NOM: Boisson
///PARAMETRES: String_view nom, double prix
///RETOUR : aucun
///DESCRIPTION : Constructeur par parametre de Boisson, initialise le nom et le prix a des 
///				valeurs entrees en parametre et la taxe a la valeur de constante de 0.12
/////////////////////////////////////////////////
Boisson::Boisson(string_view nom, double prix) : Taxable(),nom_(nom), prix_(prix)
{
	taxe_ = TAXE; // valeur constante definie dans Boisson.h
}

//Destructeur
Boisson::~Boisson(){}

//Getter

	string_view Boisson::getNom() const
	{
		return nom_;
	}

	double Boisson::getPrix()  const
    {
		return prix_;
	}

	double Boisson::getTaxe() const
	{
		return taxe_ ;
	}

//Setter

	void Boisson::setTaxe()
	{
		prix_ += getTaxe();
	}

