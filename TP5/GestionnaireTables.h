
#pragma once

#include "Table.h"
#include "Foncteur.h"
#include "GestionnaireGenerique.h"

#include <set>


class GestionnaireTables :public  GestionnaireGenerique< Table*, set<Table*> >
{
public:
	GestionnaireTables() = default;
	~GestionnaireTables();
	Table* getTable(int id) const; 
	Table* getMeilleureTable(int tailleGroupe) const;
	void lireTables(const string& nomFichier);
	void afficherTables(ostream& os) const; 
};