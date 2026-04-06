#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shopdialog.h"
#include <QString>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(nullptr));
    correctMonster=getCorrectMonster();

    // 初始化玩家状态
    currentLevel = 1;
    currentHP = 100;
    gold = 0;

    // 初始化 Label
    ui->labelLevel->setText(QString("第%1层").arg(currentLevel));
    ui->labelHP->setText(QString("当前血量: %1").arg(currentHP));
    ui->labelGold->setText(QString("金币：%1").arg(gold));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 点击怪物按钮1
void MainWindow::on_btnMonster1_clicked() {
    fightMonster(1);
}

// 点击怪物按钮2
void MainWindow::on_btnMonster2_clicked() {
    fightMonster(2);
}

// 点击怪物按钮3
void MainWindow::on_btnMonster3_clicked() {
    fightMonster(3);
}

// 战斗逻辑
void MainWindow::fightMonster(int monsterType) {
    if(monsterType==1)ui->btnMonster1->setEnabled(false);
    else if(monsterType==2)ui->btnMonster2->setEnabled(false);
    else ui->btnMonster3->setEnabled(false);
    int damage = 0;

    switch(monsterType) {
    case 1: damage = 5; break; // 小怪掉血
    case 2: damage = 10; break; // 大怪掉血
    case 3: damage = 15; break; // 精英怪掉血
    }

    currentHP -= damage;
    if(currentHP < 0) currentHP = 0;

    // 更新血量 Label
    ui->labelHP->setText(QString("当前血量: %1").arg(currentHP));

    // 选对怪物升层
    QString monsterName;

    if(monsterType==1)monsterName="小怪";
    else if(monsterType==2)monsterName="大怪";
    else monsterName="精英怪";
    int reward=0;
    int r = rand()%100;

    if(monsterType==1)
    {
        if(r < 60) reward = 10;
        else if(r < 90) reward = 20;
        else reward = 50;
    }
    else if(monsterType==2)
    {
        if(r < 50) reward = 20;
        else if(r < 80) reward = 40;
        else reward = 80;
    }
    else
    {
        if(r < 40) reward = 50;
        else if(r < 75) reward = 80;
        else reward = 150;
    }

    gold+=reward;

    ui->labelGold->setText(QString("金币：%1").arg(gold));

    if(monsterType == correctMonster) {
        currentLevel++;
        ui->labelLevel->setText(QString("第%1层").arg(currentLevel));

        QMessageBox::information(this,"结果",QString("你选择了【%1】，选对了！\n获得金币：%2").arg(monsterName).arg(reward));
        correctMonster=getCorrectMonster();

        ui->btnMonster1->setEnabled(true);
        ui->btnMonster2->setEnabled(true);
        ui->btnMonster3->setEnabled(true);
    }
    else
    {
        QMessageBox::information(this,"结果",QString("你选择了【%1】，选错了！\n获得金币：%2").arg(monsterName).arg(reward));
    }

    // 死亡判断
    if(currentHP == 0) {
        QMessageBox::information(this, "Game Over", "你挂了！");
    }
}

int MainWindow::getCorrectMonster()
{
    int r=rand()%100;

    if(r<15)return 1;
    else if(r<40)return 2;
    else return 3;
}
void MainWindow::on_btnShop_clicked()
{
    ShopDialog dialog(this);
    //  回血
    connect(&dialog, &ShopDialog::buyHeal, this, [=]() {
        if(gold >= 50)
        {
            gold -= 50;
            currentHP += 30;

            ui->labelGold->setText(QString("金币：%1").arg(gold));
            ui->labelHP->setText(QString("当前血量: %1").arg(currentHP));

            QMessageBox::information(this, "商店", "回血成功！");
        }
        else
        {
            QMessageBox::information(this, "商店", "金币不足！");
        }
    });

    //  提示
    connect(&dialog, &ShopDialog::buyHint, this, [=]() {
        if(gold >= 30)
        {
            gold -= 30;
            ui->labelGold->setText(QString("金币：%1").arg(gold));

            QString hint;
            if(correctMonster == 1) hint = "小怪";
            else if(correctMonster == 2) hint = "大怪";
            else hint = "精英怪";

            QMessageBox::information(this, "提示",QString("正确的是：%1").arg(hint));
        }
        else
        {
            QMessageBox::information(this, "商店", "金币不足！");
        }
    });
    dialog.exec();
}

