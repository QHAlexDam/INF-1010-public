

#ifndef BOISSON_h
#define BOISSON_h

#include "Taxable.h"
#include <string>
#include <string_view>

using namespace std;
class Boisson : public Taxable
{
public:
	Boisson(string_view nom, double prix);
	virtual void setTaxe();
	virtual double getTaxe() const;
	string_view getNom() const;
	double getPrix() const;
protected:
	string nom_;
	double prix_;
	double taxe_;
};


#endif /* Boisson_h */
