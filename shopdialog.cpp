#include "shopdialog.h"
#include "ui_shopdialog.h"

ShopDialog::ShopDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShopDialog)
{
    ui->setupUi(this);
}

ShopDialog::~ShopDialog()
{
    delete ui;
}

void ShopDialog::on_btnBuyHeal_clicked()
{
    emit buyHeal();
}


void ShopDialog::on_btnBuyHint_clicked()
{
    emit buyHint();
}

