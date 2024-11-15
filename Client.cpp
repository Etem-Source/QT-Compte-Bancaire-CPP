#include <iostream>

using namespace std;

#include "Client.h"

Client::Client(string c_nom, string c_prenom, string c_numcin, int c_numTel, Compte c_compte)
    : nom(c_nom), prenom(c_prenom), numcin(c_numcin), numTel(c_numTel), compte(c_compte) {}

string Client::getNom() const
{
    return nom;
}

string Client::getPrenom() const
{
    return prenom;
}

string Client::getNumcin() const
{
    return numcin;
}

int Client::getNumTel() const
{
    return numTel;
}

int Client::getCodeSecret() const
{
    return compte.getCodeSecret();
}

float Client::getSolde() const
{
    return compte.getSolde();
}

string Client::getRib() const
{
    return compte.getRib();
}

void Client::afficherClient() const {
    cout << "Nom: " << nom << endl;
    cout << "Prenom: " << prenom << endl;
    cout << "NumCIN: " << numcin << endl;
    cout << "Numero Tel: +33 " << numTel << endl;
    cout << "/Y\\ --> Informations du client affichées avec succès !" << endl;
}

void Client::modifierClient(string mod_nom, string mod_prenom, string mod_numcin, int mod_num) {
    nom = mod_nom;
    prenom = mod_prenom;
    numcin = mod_numcin;
    numTel = mod_num;
    cout << "/Y\\ --> Client modifié avec succès !" << endl;
}

void Client::virementCompte(Client &destinataire, float montant) {
    compte.virementCompte(destinataire.compte, montant);
}

void Client::crediterCompte(float montant) {
    compte.crediterCompte(montant);
}

void Client::debiterCompte(int code_secret, float montant) {
    compte.debiterCompte(code_secret, montant);
}

void Client::consulterCompte() const {
    compte.consulterCompte();
}

void Client::commanderChequierCompte() {
    compte.commanderChequierCompte();
}


Compte& Client::getCompteBancaire() {
    return compte;  // Retourne une référence vers le compte bancaire du client
}
