#ifndef DRAWDLG_H
#define DRAWDLG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include "sinx.h"
#include "ex.h"
#include "nordx.h"
#include <QGridLayout>
#include <QPen>
#include <QStandardItemModel>
#include <QTableView>
#include <QPainterPath>

namespace Ui {
class DrawDlg;
}

class DrawDlg : public QDialog
{
    Q_OBJECT

public:
    explicit DrawDlg(QWidget *parent = 0);
    ~DrawDlg();

    enum Function{Sinx,EX,NorDX,Data};
    void updateLayout(Function function);
    void setupModel();
    void setupView();
    void openFile(QString);


private slots:
    void setFunction(int);
    void slotPath();

    void on_colorBtn_clicked();
    void setWidth(int);
    void setLineStyle(int);

    void on_openBtn_clicked();

    void on_deleteBtn_clicked();

    void on_drawBtn_clicked();
    void slotSinPath();

private:
    void paintEvent(QPaintEvent *);

    Ui::DrawDlg *ui;
    QLabel *functionLabel;
    QComboBox *functionComboBox;
    SinX *sinx;
    DrawDlg::Function function;
    DrawDlg::Function originalFunction;
    Ex *ex;
    NorDx *nordx;
    QGridLayout *layout;
    QDialog *functionInterface;
    QPen pen;
    QStandardItemModel *model;
    QTableView *view;
    QPainterPath datapath;
};

#endif // DRAWDLG_H
