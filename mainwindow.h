#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnMonster1_clicked();
    void on_btnMonster2_clicked();
    void on_btnMonster3_clicked();

    void on_btnShop_clicked();

private:
    Ui::MainWindow *ui;

    int currentLevel;
    int currentHP;
    int gold;

    void fightMonster(int monsterType); // 战斗函数

    int getCorrectMonster();
    int correctMonster;
};

#endif // MAINWINDOW_H