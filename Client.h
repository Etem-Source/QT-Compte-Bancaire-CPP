#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include "Compte.h"

using namespace std;

class Client {
private:
    string nom;
    string prenom;
    string numcin;
    int numTel;
    Compte compte;

public:
    Client() : nom(""), prenom(""), numcin(""), numTel(0), compte() {}
    Client(string, string, string, int, Compte);

    string getNom() const;
    string getPrenom() const;
    string getNumcin() const;
    int getNumTel() const;
    int getCodeSecret() const;
    float getSolde() const;
    string getRib() const;

    Compte& getCompteBancaire();

    void afficherClient() const;
    void modifierClient(string, string, string, int);
    void virementCompte(Client &, float);
    void crediterCompte(float);
    void debiterCompte(int, float);
    void consulterCompte() const;
    void commanderChequierCompte();
};

#endif // CLIENT_H
