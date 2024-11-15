#include "mainwindow.h"
#include "Client.h"
#include "Compte.h"
#include <QApplication>
#include <vector>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Création de trois comptes bancaires
    Compte compte1(50, 1234, "FR751000100010001"); // Solde + CodeSecret + RIB
    Compte compte2(50, 5678, "FR751000100010002"); // "
    Compte compte3(50, 9876, "FR751000100010003"); // "

    // Création de trois clients avec leurs comptes respectifs
    Client C1("S", "Etem", "123456789", 701020304, compte1); // Nom + Prénom + CIN + Num + CompteBancaire
    Client C2("G", "Corentin", "234567890", 601020305, compte2); // "
    Client C3("P", "Luka", "345678901", 501020306, compte3); // "

    // Stocker les clients dans un vecteur
    vector<Client> clients = {C1, C2, C3};

    MainWindow w(nullptr, clients); // Passer la liste des clients à la fenêtre principale
    w.show();

    return a.exec();
}
