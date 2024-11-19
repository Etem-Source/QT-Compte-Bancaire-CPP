#include "Dashboard.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>

Dashboard::Dashboard(QWidget *parent, const Client &client)
    : QWidget(parent), currentClient(client)
{
    resize(400, 400);
    setWindowTitle("Dashboard");

    // Bienvenue
    QString welcomeText = QString("Bienvenue %1 %2 !")
                              .arg(QString::fromStdString(currentClient.getPrenom()))
                              .arg(QString::fromStdString(currentClient.getNom()));
    welcomeLabel = new QLabel(welcomeText, this);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    // Solde
    QString balanceText = QString("Votre solde est de : %1 €").arg(currentClient.getSolde());
    balanceLabel = new QLabel(balanceText, this);
    balanceLabel->setAlignment(Qt::AlignCenter);

    // Boutons
    creditButton = new QPushButton("Crédit", this);
    transferButton = new QPushButton("Virement", this);
    debitButton = new QPushButton("Débit", this);
    checkbookButton = new QPushButton("Commander Chéquier", this);
    viewAccountButton = new QPushButton("Consulter mon compte", this);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(welcomeLabel);
    layout->addWidget(balanceLabel);
    layout->addWidget(creditButton);
    layout->addWidget(transferButton);
    layout->addWidget(debitButton);
    layout->addWidget(checkbookButton);
    layout->addWidget(viewAccountButton);

    setLayout(layout);

    // Connexions des boutons aux slots
    connect(creditButton, &QPushButton::clicked, this, &Dashboard::credit);
    connect(transferButton, &QPushButton::clicked, this, &Dashboard::transfer);
    connect(debitButton, &QPushButton::clicked, this, &Dashboard::debit);
    connect(checkbookButton, &QPushButton::clicked, this, &Dashboard::checkbook);
    connect(viewAccountButton, &QPushButton::clicked, this, &Dashboard::viewAccountDetails);
}

void Dashboard::viewAccountDetails()
{
    QString accountDetails = QString(
        "> Informations du client :\n\n"
        "CIN : %1\n"
        "Nom : %2\n"
        "Prénom : %3\n"
        "Téléphone : +33 %4\n\n"
        "> Informations du compte :\n\n"
        "Solde : %5 €\n"
        "RIB : %6\n"
        "Code Secret : %7")
                                 .arg(QString::fromStdString(currentClient.getNumcin()))
                                 .arg(QString::fromStdString(currentClient.getNom()))
                                 .arg(QString::fromStdString(currentClient.getPrenom()))
                                 .arg(currentClient.getNumTel())
                                 .arg(currentClient.getSolde())
                                 .arg(QString::fromStdString(currentClient.getRib()))
                                 .arg(currentClient.getCodeSecret());

    QMessageBox::information(this, "Détails du compte", accountDetails);

}

void Dashboard::credit()
{
    bool ok;
    double amount = QInputDialog::getDouble(this, "Crédit", "Entrez le montant à créditer :", 0, 0, 9999, 2, &ok);
    if (ok && amount > 0)
    {
        currentClient.crediterCompte(amount);
        balanceLabel->setText(QString("Votre solde est de : %1 €").arg(currentClient.getSolde()));
        QMessageBox::information(this, "Crédit", QString("Vous avez crédité %1 € avec succès !").arg(amount));
    }
}

void Dashboard::debit()
{
    bool ok;
    int enteredCode = QInputDialog::getInt(this, "Code secret", "Entrez votre code secret :", 0, 0, 9999, 1, &ok);

    if (ok && enteredCode == currentClient.getCodeSecret())
    {
        double amount = QInputDialog::getDouble(this, "Débit", "Entrez le montant à débiter :", 0, 0, 5000, 2, &ok);
        if (ok && amount > 0)
        {
            if(currentClient.getSolde() - amount >= -50)
            {
                currentClient.debiterCompte(enteredCode, amount);
                balanceLabel->setText(QString("Votre solde est de : %1 €").arg(currentClient.getSolde()));
                QMessageBox::information(this, "Débit", QString("Vous avez débité %1 € avec succès !").arg(amount));

            }
            else
            {
               QMessageBox::information(this, "Débit", QString("Vous n'avez pas l'argent nécessaire."));
            }

        }
        else if (ok)
        {
            QMessageBox::warning(this, "Débit", "Montant invalide ou insuffisant !");
        }
    }
    else if (ok)
    {
        QMessageBox::warning(this, "Code secret", "Code secret incorrect !");
    }
}

void Dashboard::transfer()
{
    // Demander l'ID du destinataire (1, 2, 3...)
    bool ok;
    int clientID = QInputDialog::getInt(this, "Virement", "Entrez l'ID du destinataire (1, 2, 3):", 1, 1, 3, 1, &ok);

    if (ok)
    {
        // Vérifier que l'ID est valide
        if (clientID < 1 || clientID > otherClients.size())
        {
            QMessageBox::warning(this, "Virement", "ID du destinataire invalide !");
            return;
        }


        int destClientIndex = clientID - 1;
        Client &destClient = otherClients[destClientIndex];

        // Demander le montant du virement
        double amount = QInputDialog::getDouble(this, "Virement", "Entrez le montant à transférer :", 0, 0, currentClient.getSolde(), 2, &ok);

        if (ok && amount > 0 && amount <= currentClient.getSolde())
        {
            // Effectuer le virement entre les comptes
           // destClient.getCompteBancaire().crediterCompte(amount);
            currentClient.getCompteBancaire().virementCompte(destClient.getCompteBancaire(), amount);

            // Màj l'affichage du solde
            balanceLabel->setText(QString("Votre solde est de : %1 € \n Le solde de CorentinG est de : %2 €")
            .arg(currentClient.getSolde())
            .arg(destClient.getSolde()));

            // Afficher confirmation
            QMessageBox::information(this, "Virement", QString("Vous avez transféré %1 € à : %2 %3 (ID : %4)")
            .arg(amount)
            .arg(QString::fromStdString(destClient.getPrenom()))
            .arg(QString::fromStdString(destClient.getNom()))
            .arg(clientID));
        }
        else if (ok)
        {
            QMessageBox::warning(this, "Virement", "Montant invalide ou insuffisant !");
        }
    }
}



void Dashboard::checkbook()
{
    if (checkbookOrdered)
    {
        QMessageBox::information(this, "Commande de chéquier", "Chéquier déjà commandé !");
    }
    else
    {
        checkbookOrdered = true;
        QMessageBox::information(this, "Commande de chéquier", "Chéquier commandé !");
    }
}

void Dashboard::setOtherClients(const std::vector<Client> &clients)
{
    otherClients = clients;
}

Dashboard::~Dashboard()
{
}
