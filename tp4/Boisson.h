
#ifndef BOISSON_h
#define BOISSON_h
#include "Taxable.h"
#include <string>
#include <string_view>
using namespace std;

const double TAXE = 0.12;

class Boisson : public Taxable 
{
 public:
    Boisson (string_view nom, double prix);
	virtual ~Boisson();
    string_view getNom() const;
    double getPrix () const;
    void setTaxe() override;
	double getTaxe() const override;
protected:
    string nom_;
    double prix_;
    double taxe_;
};


#endif /* Boisson_h */
