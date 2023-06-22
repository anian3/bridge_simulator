#include <vector>
#include <iostream>
#include <QVBoxLayout>
#include <QTimer>
#include <QKeyEvent>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "hand.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Symulator brydża");
    game = new Game();
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(size());
    setStyleSheet("background-color: #006400;");

    playerCards = { ui->player_card1, ui->player_card2, ui->player_card3, ui->player_card4, ui->player_card5, ui->player_card6, ui->player_card7,
                    ui->player_card8, ui->player_card9, ui->player_card10, ui->player_card11, ui->player_card12, ui->player_card13};
    dummyCards = { ui->dummy_card1, ui->dummy_card2, ui->dummy_card3, ui->dummy_card4, ui->dummy_card5, ui->dummy_card6, ui->dummy_card7,
                ui->dummy_card8, ui->dummy_card9, ui->dummy_card10, ui->dummy_card11, ui->dummy_card12, ui->dummy_card13};

    lhoCards = {ui->l_lho1, ui->l_lho2, ui->l_lho3, ui->l_lho4, ui->l_lho5, ui->l_lho6, ui->l_lho7,
                ui->l_lho8, ui->l_lho9, ui->l_lho10, ui->l_lho11, ui->l_lho12, ui->l_lho13};
    rhoCards = {ui->l_rho1, ui->l_rho2, ui->l_rho3, ui->l_rho4, ui->l_rho5, ui->l_rho6, ui->l_rho7,
                ui->l_rho8, ui->l_rho9, ui->l_rho10, ui->l_rho11, ui->l_rho12, ui->l_rho13};

    setLevelButtons(false);

    hideCardsOnTable();
    updateAllCards(Player_hand);
    updateAllCards(Dummy_hand);

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

    connectCardButtons();
    disableCardButtons(true);
    disableCardButtons(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (Qt::Key_Escape == event->key()){
        close();
        qApp->quit();
    }
    else {
        QMainWindow::keyPressEvent(event);
    }
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

void MainWindow::connectCardButtons()
{
    for (QPushButton* button: playerCards){
        connect(button, &QPushButton::clicked, this, [this]() {this->playerThrowCard(true);}, Qt::DirectConnection);
    }
    for (QPushButton* button: dummyCards){
        connect(button, &QPushButton::clicked, this, [this]() {this->playerThrowCard(false);}, Qt::DirectConnection);
    }
}

void MainWindow::hideCardsOnTable()
{
    ui->l_dummy_table->setVisible(false);


    ui->l_rho_table->setVisible(false);


    ui->l_player_table->setVisible(false);


    ui->l_lho_table->setVisible(false);

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
    QTimer::singleShot(500, this, [this]() {
        opponentPlay(LHO_hand);
    });
}

void MainWindow::updateCardButton(QPushButton* button, const Card& card, int index)
{
    QString cardText;
    int value = card.getValue();
    if (value >= 2 && value <= 10) {
        cardText = QString::number(value);
    } else {
        switch (value) {
        case 11:
            cardText = "J";
            break;
        case 12:
            cardText = "Q";
            break;
        case 13:
            cardText = "K";
            break;
        case 14:
            cardText = "A";
            break;
        default:
            cardText = "";
            break;
        }
    }

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

    QVBoxLayout* layout = new QVBoxLayout(button);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(12); // Set the font size
    font.setBold(true);
    QLabel* textLabel = new QLabel(cardText);
    textLabel->setStyleSheet("border: none; padding: 1;");
    textLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    textLabel->setFont(font);

    QPixmap iconPixmap(iconPath);
    QLabel* iconLabel = new QLabel();
    iconLabel->setStyleSheet("border: none; padding: 0;");
    iconLabel->setPixmap(iconPixmap);
    iconLabel->setScaledContents(true);
    iconLabel->setMaximumSize(35, 35);
    iconLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(textLabel);
    layout->addWidget(iconLabel);
    layout->addStretch();

    button->setProperty("index", QVariant::fromValue(index));
}

void MainWindow::updateAllCards(Player_hands whichPlayer)
{
    QPushButton* button;
    Card card;
    if (whichPlayer == 0){
        for (int i = 0; i < playerCards.size(); i++)
        {
            button = playerCards[i];
            card = game->getCard(whichPlayer, i);
            updateCardButton(button, card, i);
        }
    }
    else if (whichPlayer == 2){
        for (int i = 0; i < dummyCards.size(); i++)
        {
            button = dummyCards[i];
            card = game->getCard(whichPlayer, i);
            updateCardButton(button, card, i);
        }
    }

}

void MainWindow::updateCardProperties(bool isPlayer, int indexRemoved)
{
    std::vector<QPushButton*> buttons;
    if (isPlayer){
        buttons = playerCards;
    }
    else {
        buttons = dummyCards;
    }
    for (int i=indexRemoved; i < buttons.size(); i++){
        buttons[i]->setProperty("index", QVariant::fromValue(i));
    }
}

void MainWindow::updateCardOnTable(Card card, Player_hands whichPlayer)
{
    QLabel *label;
    switch (whichPlayer) {
    case Player_hand:
        label = ui->l_player_table;
        break;
    case LHO_hand:
        label = ui->l_lho_table;
        break;
    case Dummy_hand:
        label = ui->l_dummy_table;
        break;
    case RHO_hand:
        label = ui->l_rho_table;
        break;
    }
    QLayout* existingLayout = label->layout();
    if (existingLayout) {
        QLayoutItem* item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }
    QString cardText;
    int value = card.getValue();
    if (value >= 2 && value <= 10) {
        cardText = QString::number(value);
    } else {
        switch (value) {
        case 11:
            cardText = "J";
            break;
        case 12:
            cardText = "Q";
            break;
        case 13:
            cardText = "K";
            break;
        case 14:
            cardText = "A";
            break;
        default:
            cardText = "";
            break;
        }
    }

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
    QVBoxLayout* layout = new QVBoxLayout(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(12); // Set the font size
    font.setBold(true);
    QLabel* textLabel = new QLabel(cardText);
    textLabel->setStyleSheet("border: none; padding: 1;");
    textLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    textLabel->setFont(font);

    QPixmap iconPixmap(iconPath);
    QLabel* iconLabel = new QLabel();
    iconLabel->setStyleSheet("border: none; padding: 0;");
    iconLabel->setPixmap(iconPixmap);
    iconLabel->setScaledContents(true);
    iconLabel->setMaximumSize(35, 35);
    iconLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(textLabel);
    layout->addWidget(iconLabel);
    layout->addStretch();
    label->setVisible(true);
}

void MainWindow::opponentPlay(Player_hands whichPlayer)
{
    Card card = game->opponentPlay();

    updateCardOnTable(card, whichPlayer);
    if (whichPlayer == LHO_hand){
        QLabel* lastLabel = lhoCards.back();
        lastLabel->hide();
        lhoCards.pop_back();
    }
    else {
        QLabel* lastLabel = rhoCards.back();
        lastLabel->hide();
        rhoCards.pop_back();
    }
    setNextAction(whichPlayer);
}

void MainWindow::playerThrowCard(bool isPlayer)
{
    disableCardButtons(isPlayer);
    QObject* senderObject = QObject::sender();
    if (senderObject == nullptr || !senderObject->isWidgetType()) {
        std::cout << "Error: Invalid sender object" << std::endl;
        return;
    }
    QPushButton* button = qobject_cast<QPushButton*>(senderObject);
    if (button == nullptr) {
        std::cout << "Error: Invalid sender button" << std::endl;
        return;
    }
    QVariant propertyValue = button->property("index");
    int index = propertyValue.toInt();
    if (isPlayer){
        playerCards[index]->setVisible(false);
        playerCards.erase(playerCards.begin() + index);
        Card card = game->playerPlay(index);
        updateCardOnTable(card, Player_hand);
    }
    else {
        dummyCards[index]->setVisible(false);
        dummyCards.erase(dummyCards.begin() + index);
        Card card = game->playerPlay(index);
        updateCardOnTable(card, Dummy_hand);
    }
    updateCardProperties(isPlayer, index);
    Player_hands lastPlayed = isPlayer ? Player_hand : Dummy_hand;
    setNextAction(lastPlayed);
}

void MainWindow::enableAllCardButtons(Player_hands whichPlayer)
{
    if (whichPlayer == Player_hand){
        for (QPushButton *button: playerCards){
            button->setEnabled(true);
        }
    }
    else {
        for (QPushButton *button: dummyCards){
            button->setEnabled(true);
        }
    }
}

void MainWindow::enableCardButtons(Player_hands whichPlayer, Color color)
{
    std::vector<int> indexes = game->getCardIndexesOfColor(whichPlayer, color);
    if (indexes.empty()){
        enableAllCardButtons(whichPlayer);
        return;
    }
    if (whichPlayer == Player_hand){
        for (int index: indexes){
            playerCards[index]->setEnabled(true);
        }
    }
    else {
        for (int index: indexes){
            dummyCards[index]->setEnabled(true);
        }
    }
}

void MainWindow::disableCardButtons(bool isPlayer)
{
    std::vector<QPushButton*> buttons;
    if (isPlayer){
        buttons = playerCards;
    }
    else{
        buttons = dummyCards;
    }
    for (QPushButton *button: buttons){
        button->setEnabled(false);
    }
}



void MainWindow::setNextAction(Player_hands lastPlayed)
{
    if (game->howManyOnTable() == 4){
        QTimer::singleShot(500, this, [this]() {
            hideCardsOnTable();
        Player_hands nowPlays;
        nowPlays = game->endOfRound();
        updateResultLabel();
        if (game->numCardsLeft(Player_hand) == 0){
            updateResultLabelEnd();
            return;
        }
        if (nowPlays == LHO_hand || nowPlays == RHO_hand){
            opponentPlay(nowPlays);
        }
        else if (nowPlays == Player_hand){
            enableAllCardButtons(Player_hand);
        }
        else {
            enableAllCardButtons(Dummy_hand);
        }
        });
    }
    else {
        switch (lastPlayed){

        case Player_hand:
            QTimer::singleShot(200, this, [this]() {
                opponentPlay(LHO_hand);
            });
            break;
        case LHO_hand:
            enableCardButtons(Dummy_hand, game->getRoundColor());
            break;
        case Dummy_hand:
            QTimer::singleShot(200, this, [this]() {
                opponentPlay(RHO_hand);
            });
            break;
        case RHO_hand:
            enableCardButtons(Player_hand, game->getRoundColor());
            break;
        }
    }
}

void MainWindow::updateResultLabel()
{
    ui->l_result->setText("Wziętych: " + QString::number(game->getTakenNum()) + "            Oddanych: " + QString::number(game->getUntakenNum()));
}

void MainWindow::updateResultLabelEnd()
{
    int result = game->getTakenNum() - game->getContractLevel() - 6;
    if (result < 0){
        ui->l_result->setText("Kontrakt nieugrany!  ( " + QString::number(result) + " )");
    }
    else if (result == 0){
        ui->l_result->setText("Kontrakt ugrany!   ( = )");
    }
    else {
        ui->l_result->setText("Kontrakt ugrany!  ( +" + QString::number(result)+ " )");
    }
}






