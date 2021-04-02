#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Commande* commande, Filtre* filtre, Menu* menu, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    commande_(commande), filtre_(filtre), menu_(menu)
{
    ui->setupUi(this);
    setUI();
    connecterSignauxAuxSlots();
    mettreAJourPlatsFiltres();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUI(){
    setWindowTitle(WINDOW_TITLE);
    creerWidgets();
    designLayout();
}

void MainWindow::creerWidgets(){
    creerWidgetTypeMenu();
    creerWidgetConditionsAlimentaires();
    creerWidgetPlatsFiltres();
    creerWidgetCommande();
    creerWidgetBoutonsAjouterRetirer();
    creerWidgetPrix();
    creerWidgetCommander();
}

void MainWindow::creerWidgetTypeMenu() {
    widgetTypeMenu_ = new QComboBox(this);
    widgetTypeMenu_->addItem(MATIN);
    widgetTypeMenu_->addItem(MIDI);
    widgetTypeMenu_->addItem(SOIR);
}

void MainWindow::creerWidgetConditionsAlimentaires(){
    widgetPlatsBios_ =  new QCheckBox(BIOLOGIQUE,this);
    widgetPlatsVeges_ = new QCheckBox(VEGETARIEN, this);
}

void MainWindow::creerWidgetPlatsFiltres(){
    widgetPlatsFiltres_ = new QListWidget(this);
    widgetPlatsFiltres_->setSortingEnabled(true);
}

/////////////////////////////////////////////////
///NOM: creerWidgetCommande
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : methode qui cree la liste de la commande
///             et qui l'associe a la fenetre principale
/////////////////////////////////////////////////
void MainWindow::creerWidgetCommande() {
    widgetCommande_= new QListWidget(this);
    widgetCommande_->setSortingEnabled(true);
}

void MainWindow::creerWidgetBoutonsAjouterRetirer() {
    widgetAjouterPlat_ = new QPushButton(this);
    widgetAjouterPlat_->setText(AJOUTER_PLAT);
    widgetRetirerPlat_ = new QPushButton(this);
    widgetRetirerPlat_->setText(RETIRER_PLAT);
}

void MainWindow::creerWidgetPrix() {
    widgetPrix_ = new QLabel(this);
    widgetPrix_->setText(PRIX_STRING + "0" + DOLLAR_SIGN);
}

/////////////////////////////////////////////////
///NOM: creerWidgetCommander
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : methode qui cree le bouton poussoir
///             pour commander et qui l'associe a la
///             fenetre principale
/////////////////////////////////////////////////
void MainWindow::creerWidgetCommander() {
    widgetCommander_ = new QPushButton(this);
    widgetCommander_->setText(COMMANDER);
}


/////////////////////////////////////////////////
///NOM: designLayout
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION : methode qui dispose tous les widgets
///              afin d'obtenir un layout fonctionnel
///              et plaisant visuellement
/////////////////////////////////////////////////
void MainWindow::designLayout() {



	// la ligne
	QFrame* hLine = new QFrame();
	hLine->setFrameShape(QFrame::HLine);

	/*
		menuTypeLayout = menuStyle
		modifyCommandLayout = commandeStyle
		platsLayout = platStyle

		menuLayout  = menuBox
       priceCommanderLayout = commandePrix
	   
	   commandLayout = command
	*/

    QVBoxLayout* menuStyle = new QVBoxLayout(this);
    menuStyle->addWidget(widgetTypeMenu_);
	menuStyle->addWidget(widgetPlatsVeges_);
	menuStyle->addWidget(widgetPlatsBios_);
     QHBoxLayout*  commandeStyle = new QHBoxLayout(this);
	 commandeStyle->addWidget(widgetAjouterPlat_);
	 commandeStyle->addWidget(widgetRetirerPlat_);
     QVBoxLayout*  platStyle = new QVBoxLayout(this);
	 platStyle->addWidget(widgetPlatsFiltres_);
	 platStyle->addLayout(commandeStyle);
     QHBoxLayout* menuBox = new QHBoxLayout(this);
	 menuBox->addLayout(menuStyle);
	 menuBox->addLayout(platStyle);
     QHBoxLayout* commandePrix = new QHBoxLayout(this);
	 commandePrix->addWidget(widgetCommander_);
	 commandePrix->addWidget(widgetPrix_);
     QVBoxLayout* commande = new QVBoxLayout(this);
	 menuStyle ->addWidget(widgetCommande_);
	 menuStyle->addLayout(commandePrix);
     QVBoxLayout* mainBox = new QVBoxLayout(this);
	 mainBox->addLayout(commande);
     mainBox->addLayout(menuBox);
     mainBox->addWidget(hLine);
     QWidget* mainWidget = new QWidget();
     mainWidget->setLayout(mainBox);
     setCentralWidget(mainWidget);

}

/////////////////////////////////////////////////
///NOM: connecterSignauxAuxSlots
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION :Connecte les actions de l'utilisateur
///             sur l'interface aux modifications qui
///             doivent être faites sur le modèle
/////////////////////////////////////////////////
void MainWindow::connecterSignauxAuxSlots() {
    // connecter checkboxes filtre bio et vege
    QObject::connect(widgetPlatsVeges_, SIGNAL(stateChanged(int)),
                     this, SLOT(clicOptionVege()));
    QObject::connect(widgetPlatsBios_, SIGNAL(stateChanged(int)),
                     this, SLOT(clicOptionBio()));

    //connecter menu defilant type plat
    QObject::connect(widgetTypeMenu_, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(choixTypeMenu(QString)));

    //connecter boutons ajouterPlat et retirerPlat
    QObject::connect(widgetAjouterPlat_, SIGNAL(clicked()),
                     this, SLOT(insererPlatsChoisisDansCommande()));

    QObject::connect(widgetRetirerPlat_, SIGNAL(clicked()),
                     this, SLOT(retirerPlatsChoisisDeCommande()));

    //connecter bouton commander
    QObject::connect(widgetCommander_, SIGNAL(clicked()),
                     this, SLOT(commander()));
}
void MainWindow::mettreAJourPlatsFiltres(){
    QStringList plats = filtre_->getNomPlatsFiltres();
    widgetPlatsFiltres_->clear();
    widgetPlatsFiltres_->addItems(plats);
}

void MainWindow::clicOptionBio(){
    filtre_->clicOptionBio();
}

void MainWindow::clicOptionVege(){
    filtre_->clicOptionVege();
}

void MainWindow::choixTypeMenu(QString typeMenu){
    filtre_->choixTypeMenu(qstringToTypeMenu(typeMenu));
}

void MainWindow::mettreAJourPlatsCommande(){
    widgetCommande_->clear();
    foreach (auto nomPlat, commande_->getCommande()) {
        widgetCommande_->addItem(nomPlat);
    }
}

/////////////////////////////////////////////////
///NOM: insererPlatsChoisisDansCommande
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION :ajoute le plat selectionne dans la
///             liste du menu dans la liste comande
/////////////////////////////////////////////////
void MainWindow::insererPlatsChoisisDansCommande() {

    for (auto nomPlat:widgetPlatsFiltres_->selectedItems()) {
            commande_->ajouterPlat(nomPlat->text());
        }
}

/////////////////////////////////////////////////
///NOM: retirerPlatsChoisisDeCommande
///PARAMETRES: aucun
///RETOUR : aucun
///DESCRIPTION :Retire un plat de la liste de
///             commande. Si le plat selectionne
///             n'est pas dans la commande, affiche
///             un message d'erreur.
/////////////////////////////////////////////////
void MainWindow::retirerPlatsChoisisDeCommande() {
    try{
        for (auto nomPlat:widgetPlatsFiltres_->selectedItems()){
                commande_->retirerPlat(nomPlat->text());
        }
    }catch(ErreurPlatIntrouvable erreur){
        message(erreur.what());
    }
}

void MainWindow::mettreAJourPrix() {

    widgetPrix_->setText(PRIX_STRING +
                         QString::number(calculerPrixCommande()) +
                         DOLLAR_SIGN);
}

int MainWindow::calculerPrixCommande(){
    int prix = 0;
    try {
        foreach(auto nomPlatCommande, commande_->getCommande()){
            prix += menu_->getPlat(nomPlatCommande)->getPrix();
        }
    } catch (ErreurPlatIntrouvable erreur) {
        message(erreur.what());
    }
    return prix;
}

void MainWindow::message(QString erreur) {
    QMessageBox mbox;
    mbox.setText(erreur);
    mbox.exec();
}

void MainWindow::commander() {
    try {
        int prix = calculerPrixCommande();
        commande_->viderCommande();
        message(LABEL_COMMANDE_RECUE+ QString::number(prix) + DOLLAR_SIGN);
    } catch (ErreurCommandeVide erreur) {
        message(erreur.what());
    }
}
