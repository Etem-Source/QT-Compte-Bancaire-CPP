#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Client.h"
#include <QTimer>
#include <QDebug>

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent, const vector<Client> &clients)
    : QMainWindow(parent), ui(new Ui::MainWindow), clients(clients), dashboard(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Authentication");
    resize(400, 400);

    // Pavé numérique avec génération aléatoire
    QList<int> numbers;
    for (int i = 0; i < 10; ++i)
        numbers.append(i);
    random_shuffle(numbers.begin(), numbers.end(), [](int i) { return QRandomGenerator::global()->bounded(i); });

    for (int i = 0; i < 10; ++i)
    {
        QString text = QString::number(numbers[i]);
        buttons[numbers[i]] = new QPushButton(text, this);
        connect(buttons[numbers[i]], &QPushButton::pressed, this, [this, text]() {
            for (int j = 0; j < 10; ++j)
            {
                if (buttons[j]->text() == text)
                {
                    buttons[j]->setStyleSheet("color: red");
                }
            }
        });
        connect(buttons[numbers[i]], &QPushButton::released, this, [this, text]() {
            for (int j = 0; j < 10; ++j)
            {
                if (buttons[j]->text() == text)
                {
                    buttons[j]->setStyleSheet("");
                }
            }
        });
        connect(buttons[numbers[i]], &QPushButton::clicked, this, &MainWindow::slot_buttonClicked);
    }

    // Layout Pavé numérique
    QGridLayout *layout = new QGridLayout();
    layout->setMargin(6);
    layout->setSpacing(6);
    for (int i = 0; i < 9; ++i)
    {
        layout->addWidget(buttons[numbers[i + 1]], i / 3, i % 3);
    }
    layout->addWidget(buttons[numbers[0]], 3, 1);

    // Champs CIN et Code Secret
    idField = new QLineEdit(this);
    idField->setPlaceholderText("Numéro CIN");
    idField->setMaxLength(9);
    connect(idField, &QLineEdit::textChanged, [this]() {
        passwordField->setEnabled(idField->text().length() == 9);
        messageLabel->clear();
        loginButton->setStyleSheet("");
    });

    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Code Secret");
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setEnabled(false);

    // Case à cocher pour montrer/masquer le code secret
    showPasswordCheckBox = new QCheckBox("Afficher Code Secret", this);
    connect(showPasswordCheckBox, &QCheckBox::toggled, this, &MainWindow::slot_togglePassword);

    // Label pour afficher le message
    messageLabel = new QLabel(this);
    messageLabel->setAlignment(Qt::AlignCenter);

    // Bouton Connexion
    loginButton = new QPushButton("Connexion", this);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::slot_login);

    // Ajouter les widgets au layout
    layout->addWidget(idField, 4, 0, 1, 3);
    layout->addWidget(passwordField, 5, 0, 1, 3);
    layout->addWidget(showPasswordCheckBox, 6, 0, 1, 3);
    layout->addWidget(loginButton, 7, 0, 1, 3);
    layout->addWidget(messageLabel, 8, 0, 1, 3);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

void MainWindow::slot_buttonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        idField->insert(button->text());
    }
}

void MainWindow::slot_togglePassword()
{
    if (showPasswordCheckBox->isChecked())
    {
        passwordField->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        passwordField->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::slot_login()
{
    QString inputCIN = idField->text();
    int inputCodeSecret = passwordField->text().toInt();

    for (const Client &client : clients)
    {
        if (inputCIN == QString::fromStdString(client.getNumcin()) && inputCodeSecret == client.getCodeSecret())
        {
            messageLabel->setText("Connexion réussie!");
            loginButton->setStyleSheet("color: green");
            messageLabel->setStyleSheet("color: green");

            // Délai de 1 seconde avant de montrer le dashboard
            QTimer::singleShot(1000, this, [this, client]()
            {
                dashboard = new Dashboard(nullptr, client);  // Initialise le dashboard avec le client actuel
                dashboard->setOtherClients(clients);  // Passe la liste des autres clients
                dashboard->show();
            });

            return; // Terminer la fonction après une connexion réussie
        }
    }

    // Si la connexion échoue
    essaies--;
    messageLabel->setText(QString("Identifiant ou code secret incorrect! Tentatives restantes : %1").arg(essaies));
    messageLabel->setStyleSheet("color: red");
    loginButton->setStyleSheet("color: red");
    if (essaies == 0)
    {
        close(); // Ferme l'application après 3 tentatives infructueuses
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
