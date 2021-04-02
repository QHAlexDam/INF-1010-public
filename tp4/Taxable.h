

#ifndef TAXABLE_H
#define TAXABLE_H
class Taxable
{
public:
	virtual ~Taxable() {} // un destructeur virtuel est implemente pour pouvoir effacer la listeTaxable cree dans le main
    virtual void setTaxe () = 0;
    virtual double getTaxe()const = 0;
};

#endif /* Taxable_h */
