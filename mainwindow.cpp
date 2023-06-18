#include <vector>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(size());

    setStyleSheet("background-color: #006400;");

    QString buttonStyle = "background-color: white;";

    playerCards = { ui->player_card1, ui->player_card2, ui->player_card3, ui->player_card4, ui->player_card5, ui->player_card6, ui->player_card7,
                    ui->player_card8, ui->player_card9, ui->player_card10, ui->player_card11, ui->player_card12, ui->player_card13};
    dummyCards = { ui->dummy_card1, ui->dummy_card2, ui->dummy_card3, ui->dummy_card4, ui->dummy_card5, ui->dummy_card6, ui->dummy_card7,
                ui->dummy_card8, ui->dummy_card9, ui->dummy_card10, ui->dummy_card11, ui->dummy_card12, ui->dummy_card13};

    for (QPushButton* button : playerCards) {
        button->setStyleSheet(buttonStyle);
    }

    for (QPushButton* button : dummyCards) {
        button->setStyleSheet(buttonStyle);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

