#include "mainwindow.h"
#include "Menu.h"
#include "Filtre.h"
#include "Commande.h"
#include <QString>
#include <QApplication>
#include "erreurfichierintrouvable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString chemin = // INSERER CHEMIN ABSOLU VERS polyFood.txt
    try {
        Menu menu = Menu(chemin+FICHIER_POLYFOOD);
        Filtre filtre(&menu);
        Commande commande;
        MainWindow mainGui(&commande, &filtre, &menu);



        //Connecter les mises a jour de la vue en fonction du modele (plats filtres + plats commande + prix)
        // mettre a jour les affichages des listes et du prix lorsque ces derniers sont modifies


		QObject::connect(&filtre, SIGNAL(choixFiltrageModifie()), &mainGui, SLOT(mettreAJourPlatsFiltres()));

		QObject::connect(&commande, SIGNAL(commandeModifie()), &mainGui, SLOT(mettreAJourPlatsCommande()));

		QObject::connect(&commande, SIGNAL(commandeModifie()), &mainGui, SLOT(mettreAJourPrix()));



        mainGui.show();
        return a.exec();

    } catch (ErreurFichierIntrouvable erreur) {
        QMessageBox mbox;
        mbox.setText(erreur.what());
        mbox.show();
        return a.exec();
    }

}
