#include <vector>
#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "hand.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(size());

    setStyleSheet("background-color: #006400;");

    playerCards = { ui->player_card1, ui->player_card2, ui->player_card3, ui->player_card4, ui->player_card5, ui->player_card6, ui->player_card7,
                    ui->player_card8, ui->player_card9, ui->player_card10, ui->player_card11, ui->player_card12, ui->player_card13};
    dummyCards = { ui->dummy_card1, ui->dummy_card2, ui->dummy_card3, ui->dummy_card4, ui->dummy_card5, ui->dummy_card6, ui->dummy_card7,
                ui->dummy_card8, ui->dummy_card9, ui->dummy_card10, ui->dummy_card11, ui->dummy_card12, ui->dummy_card13};

    setLevelButtons(false);
    connect(ui->pb_pik, &QPushButton::clicked, [this]() {this->trumpPressed(0);});
    connect(ui->pb_kier, &QPushButton::clicked, [this]() {this->trumpPressed(1);});
    connect(ui->pb_karo, &QPushButton::clicked, [this]() {this->trumpPressed(2);});
    connect(ui->pb_trefl, &QPushButton::clicked, [this]() {this->trumpPressed(3);});
    connect(ui->pb_bezatu, &QPushButton::clicked, [this]() {this->trumpPressed(4);});

    connect(ui->pb_level1, &QPushButton::clicked, [this]() {this->contractLevelPressed(1);});
    connect(ui->pb_level2, &QPushButton::clicked, [this]() {this->contractLevelPressed(2);});
    connect(ui->pb_level3, &QPushButton::clicked, [this]() {this->contractLevelPressed(3);});
    connect(ui->pb_level4, &QPushButton::clicked, [this]() {this->contractLevelPressed(4);});
    connect(ui->pb_level5, &QPushButton::clicked, [this]() {this->contractLevelPressed(5);});
    connect(ui->pb_level6, &QPushButton::clicked, [this]() {this->contractLevelPressed(6);});
    connect(ui->pb_level7, &QPushButton::clicked, [this]() {this->contractLevelPressed(7);});
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::setLevelButtons(bool active)
{
    ui->pb_level1->setEnabled(active);
    ui->pb_level1->setVisible(active);
    ui->pb_level2->setEnabled(active);
    ui->pb_level2->setVisible(active);
    ui->pb_level3->setEnabled(active);
    ui->pb_level3->setVisible(active);
    ui->pb_level4->setEnabled(active);
    ui->pb_level4->setVisible(active);
    ui->pb_level5->setEnabled(active);
    ui->pb_level5->setVisible(active);
    ui->pb_level6->setEnabled(active);
    ui->pb_level6->setVisible(active);
    ui->pb_level7->setEnabled(active);
    ui->pb_level7->setVisible(active);
}

void MainWindow::setColorButtons(bool active)
{
    ui->pb_pik->setEnabled(active);
    ui->pb_pik->setVisible(active);
    ui->pb_kier->setEnabled(active);
    ui->pb_kier->setVisible(active);
    ui->pb_karo->setEnabled(active);
    ui->pb_karo->setVisible(active);
    ui->pb_trefl->setEnabled(active);
    ui->pb_trefl->setVisible(active);
    ui->pb_bezatu->setEnabled(active);
    ui->pb_bezatu->setVisible(active);
}

void MainWindow::trumpPressed(int which)
{
    bool isTrumpGame = true;
    Color trump = SPADES;
    if (which == 1) trump = HEARTS;
    else if (which == 2) trump = DIAMONDS;
    else if (which == 3) trump = CLUBS;
    else if (which == 4) isTrumpGame = false;
    game->color_chosen(isTrumpGame, trump);

    ui->l_contract->setText("Wybierz poziom:");
    setColorButtons(false);
    setLevelButtons(true);

}

void MainWindow::contractLevelPressed(int level)
{
    game->contractLevel_chosen(level);
    setLevelButtons(false);
    QString trump;
    if (!(game->isTrump())) {trump = "Bez atu";}
    else {
        switch(game->getTrump()){
        case SPADES:
            trump = "Pik";
            break;
        case HEARTS:
            trump = "Kier";
            break;
        case CLUBS:
            trump = "Trefl";
            break;
        case DIAMONDS:
            trump = "Karo";
            break;
        }
    }
    ui->l_contract->setText(QString::number(level) + " " + trump);
}

void MainWindow::updateCardButton(QPushButton* button, const Card& card, int* index)
{
    button->setText(QString::number(card.getValue()));

    QString iconPath;
    switch (card.getColor())
    {
    case SPADES:
        iconPath = ":/icons/spades.png";
        break;
    case HEARTS:
        iconPath = ":/icons/hearts.png";
        break;
    case CLUBS:
        iconPath = ":/icons/clubs.png";
        break;
    case DIAMONDS:
        iconPath = ":/icons/diamonds.png";
        break;
    default:
        iconPath = "";
        break;
    }
    QIcon icon(iconPath);
    button->setIcon(icon);
    button->setIconSize(QSize(40, 40));
}

