#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "Client.h"
#include <vector>

#include <iostream>

using namespace std;

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr, const Client &client = Client());
    ~Dashboard();

    void setOtherClients(const vector<Client> &clients); // Définir les autres clients pour les virements


private slots:
    void viewAccountDetails();  // Afficher les détails du compte
    void credit();              // Effectuer un crédit
    void transfer();            // Effectuer un virement
    void debit();               // Effectuer un débit
    void checkbook();           // Commander un chéquier

private:
    QLabel *welcomeLabel;
    QLabel *balanceLabel;
    QPushButton *creditButton;
    QPushButton *transferButton;
    QPushButton *debitButton;
    QPushButton *checkbookButton;
    QPushButton *viewAccountButton;
    QPushButton *logoutButton;

    Client currentClient;
    bool checkbookOrdered = false;
    vector<Client> otherClients;
};

#endif // DASHBOARD_H
