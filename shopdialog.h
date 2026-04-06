#ifndef SHOPDIALOG_H
#define SHOPDIALOG_H

#include <QDialog>

namespace Ui {
class ShopDialog;
}

class ShopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopDialog(QWidget *parent = nullptr);
    ~ShopDialog();
signals:
    void buyHeal();
    void buyHint();
private slots:
    void on_btnBuyHeal_clicked();

    void on_btnBuyHint_clicked();

private:
    Ui::ShopDialog *ui;
};

#endif // SHOPDIALOG_H
