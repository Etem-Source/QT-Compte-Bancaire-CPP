#ifndef COMPTE_H
#define COMPTE_H

#include <iostream>
#include <string>

using namespace std;

class Compte {
private:
    static int nextId;
    int idUnique;
    float solde;
    int codeSecret;
    string rib;
    int chequier;

public:
    Compte();
    Compte(float, int, string);

    float getSolde() const;
    int getCodeSecret() const { return codeSecret; }
    string getRib() const;

    void crediterCompte(float);
    void debiterCompte(int, float);
    void virementCompte(Compte &, float);
    void consulterCompte() const;
    void commanderChequierCompte();
};

#endif // COMPTE_H
