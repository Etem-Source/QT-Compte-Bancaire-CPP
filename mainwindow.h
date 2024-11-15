#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
using namespace std;

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QRandomGenerator>
#include <vector>
#include "Client.h"
#include "Dashboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const vector<Client> &clients = {});
    ~MainWindow();

    void setOtherClients(const vector<Client> &clients); // Définir les autres clients pour les virements

private slots:
    void slot_buttonClicked();
    void slot_togglePassword();
    void slot_login();

private:
    Ui::MainWindow *ui;
    QPushButton *buttons[10];
    QGridLayout *Grille_boutons;
    QLabel *label;
    QLineEdit *idField;
    QLineEdit *passwordField;
    QCheckBox *showPasswordCheckBox;
    QPushButton *loginButton;
    QLabel *messageLabel;
    int essaies = 3;
    vector<Client> clients;
    Dashboard *dashboard;
};

#endif // MAINWINDOW_H
