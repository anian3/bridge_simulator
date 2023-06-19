#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QPushButton>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void contractLevelPressed(int level);
    void trumpPressed(int which);

private:
    Ui::MainWindow *ui;
    std::vector<QPushButton*> playerCards;
    std::vector<QPushButton*> dummyCards;
    Game *game;

    //methods:
    void setLevelButtons(bool active);
    void setColorButtons(bool active);
    void updateCardButton(QPushButton* button, const Card& card, int* index);
};
#endif // MAINWINDOW_H
