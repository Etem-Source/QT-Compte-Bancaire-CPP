#include <iostream>

using namespace std;

#include "Compte.h"

int Compte::nextId = 0;

Compte::Compte() : solde(0), codeSecret(0), rib(""), chequier(0) {
    idUnique = nextId++;
}

Compte::Compte(float c_solde, int c_codeSecret, string c_rib) : solde(c_solde), codeSecret(c_codeSecret), rib(c_rib), chequier(0) {
    idUnique = nextId++;
}

float Compte::getSolde() const {
    return solde;
}

string Compte::getRib() const {
    return rib;
}

void Compte::crediterCompte(float montant) {
    solde += montant;
    cout << "/Y\\ --> Compte " << idUnique << " crédité de " << montant << " euros avec succès !" << endl;
}

void Compte::debiterCompte(int code_secret, float montant) {
    if (solde >= -50 && solde - montant >= -50) {
        if (code_secret == codeSecret) {
            solde -= montant;
            cout << "/Y\\ --> Compte " << idUnique << " débité de " << montant << " euros avec succès !" << endl;
        } else {
            cout << "/!\\ --> Mauvais code secret pour débiter du compte " << idUnique << ": " << montant << " euros !" << endl;
        }
    } else {
        cout << "/!\\ --> Solde insuffisant pour débiter du compte " << idUnique << " : " << montant << " euros !" << endl;
    }
}

void Compte::virementCompte(Compte &compteDest, float montant) {
    if (montant <= 0) {
        cout << "/!\\ --> Le montant doit être positif pour un virement !" << endl;
    } else {
        if (solde >= -50 && solde - montant >= -50) {
            solde -= montant;
            compteDest.crediterCompte(montant);
            cout << "/Y\\ --> Virement de " << montant << " euros effectué avec succès !" << endl;
        } else {
            cout << "/!\\ --> Solde insuffisant pour effectuer le virement de " << montant << " euros !" << endl;
        }
    }
}

void Compte::consulterCompte() const {
    cout << "ID Unique: " << idUnique << endl;
    cout << "Solde: " << solde << " euros" << endl;
    cout << "Code Secret: " << codeSecret << endl;
    cout << "RIB: " << rib << endl;
    cout << "/Y\\ --> Compte " << idUnique << " consulté avec succès !" << endl;
}

void Compte::commanderChequierCompte() {
    if (chequier == 0) {
        cout << "/Y\\ --> Compte " << idUnique << " chèque commandé avec succès !" << endl;
        chequier = 1;
    } else {
        cout << "/!\\ --> Le compte " << idUnique << " possède déjà un chèque !" << endl;
    }
}
