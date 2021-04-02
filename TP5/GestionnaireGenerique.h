
#pragma once

#include <algorithm>
#include "Foncteur.h"

using namespace  std;

//              T   = pair<string, Plat*> ou Table*; 
//              C   = map<string, Plat*> ou set<Table*>; 


template<typename T, typename C>
class GestionnaireGenerique
{
public:
	C getConteneur() const; 
	void ajouter(T t);
	int getNombreElements() const;

protected:
	C conteneur_;
};

/////////////////////////////////////////////////
///NOM: ajouter
///PARAMETRES: T t
///RETOUR : aucun
///DESCRIPTION : methode qui ajoute un élément, soit un pair<string, Plat*> 
///				ou un Table* au conteneur
/////////////////////////////////////////////////
template<typename T, typename C>
void GestionnaireGenerique<T, C>::ajouter(T t)
{
	conteneur_.insert(t);
}

/////////////////////////////////////////////////
///NOM: getNombreElements
///PARAMETRES: aucun
///RETOUR : int taille du conteneur
///DESCRIPTION : methode qui retourne la taille du conteneur
/////////////////////////////////////////////////
template<typename T, typename C> // car c'est dynamique 
int GestionnaireGenerique<T, C>::getNombreElements() const
{
	return conteneur_.size();
}

/////////////////////////////////////////////////
///NOM: getConteneur
///PARAMETRES: aucun
///RETOUR : C conteneur
///DESCRIPTION : methode qui retourne le conteneur 
/////////////////////////////////////////////////
template<typename T, typename C>
C GestionnaireGenerique<T, C>::getConteneur() const {
	return conteneur_;
}
