#include "drawdlg.h"
#include "ui_drawdlg.h"
#include <QSplitter>
#include <QLabel>
#include <QGridLayout>
#include <QFont>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QColorDialog>
#include <QPixmap>
#include <QFileDialog>
#include <QTextStream>

DrawDlg::DrawDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawDlg)
{
    ui->setupUi(this);

    setWindowTitle(tr("嘻哈绘图"));
    setFixedSize(800,600);

    originalFunction=DrawDlg::Sinx;

    sinx=new SinX(this);
    connect(sinx,SIGNAL(updatePaint()),this,SLOT(slotPath()));
    functionInterface=sinx;

    QFont font;
    font.setPointSize(9);
    font.setBold(true);
    functionLabel=new QLabel(tr("函数类型"),this);
    functionLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    functionLabel->setFont(font);
    functionComboBox=new QComboBox(this);
    functionComboBox->setFont(font);
    functionComboBox->addItem(tr("正弦函数"),DrawDlg::Sinx);
    functionComboBox->addItem(tr("指数函数"),DrawDlg::EX);
    functionComboBox->addItem(tr("正态分布函数"),DrawDlg::NorDX);

    connect(functionComboBox,SIGNAL(activated(int)),this,SLOT(setFunction(int)));

    layout=new QGridLayout;
    layout->addWidget(functionLabel,2,0);
    layout->addWidget(functionComboBox,2,1);

    layout->addWidget(sinx,5,0,10,2);

    ui->functionTab->setLayout(layout);

    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);

    QPixmap pix(20,20);
    pix.fill(Qt::red);
    ui->colorBtn->setIcon(QIcon(pix));

    ui->widthSpinBox->setRange(1,8);
    connect(ui->widthSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setWidth(int)));

    ui->styleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    ui->styleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    ui->styleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    ui->styleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
    ui->styleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotDotLine));
    connect(ui->styleComboBox,SIGNAL(activated(int)),this,SLOT(setLineStyle(int)));

    setupModel();
    setupView();

    setWhatsThis(tr("这是一个Qt实现的绘图软件"));

}

DrawDlg::~DrawDlg()
{
    delete ui;
}

void DrawDlg::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //绘制坐标轴
    QPen axisPen;
    axisPen.setColor(Qt::black);
    axisPen.setWidth(1);
    painter.setPen(axisPen);
    painter.drawLine(10,10,10,520);
    painter.drawLine(10,10,575,10);
    painter.drawLine(10,520,575,520);
    painter.drawLine(575,10,575,520);
    painter.drawLine(10,260,575,260);
    painter.drawLine(287,10,287,520);

    QPoint original(287,260);
    painter.drawLine(575,260,570,263);
    painter.drawLine(575,260,570,257);

    painter.drawLine(287,10,290,15);
    painter.drawLine(287,10,284,15);

    painter.drawText(original.x()+10,original.y()+15,tr("O"));
    painter.drawText(565,280,tr("X"));
    painter.drawText(297,30,tr("Y"));

    painter.setPen(pen);
    //图形绘制
    switch (originalFunction)
    {
        case Sinx:
        {
            painter.drawPath(sinx->getPath());//初始化时，path还没有被赋值，所以没有绘图
            break;
        }
        case EX:
        {
            painter.drawPath(ex->getPath());
            break;
        }
        case NorDX:
        {
            painter.drawPath(nordx->getPath());
            break;
        }
        case Data:
        {
            painter.drawPath(datapath);
            break;
        }
        default:
            break;
    }
}

void DrawDlg::updateLayout(Function function)
{

    if(originalFunction==function)return;

    switch (function)//更改布局
    {
        case Sinx:
        {
            layout->removeWidget(functionInterface);
            functionInterface->close();
            delete functionInterface;
            sinx=new SinX(this);
            connect(sinx,SIGNAL(updatePaint()),this,SLOT(slotSinPath()));
            layout->addWidget(sinx,5,0,10,2);
            functionInterface=sinx;
            break;
        }
        case EX:
        {
            layout->removeWidget(functionInterface);
            functionInterface->close();
            delete functionInterface;
            ex=new Ex(this);
            connect(ex,SIGNAL(updatePaint()),this,SLOT(slotPath()));
            layout->addWidget(ex,5,0,10,2);
            functionInterface=ex;
            break;
        }
        case NorDX:
        {
            layout->removeWidget(functionInterface);
            functionInterface->close();
            delete functionInterface;
            nordx=new NorDx(this);
            connect(nordx,SIGNAL(updatePaint()),this,SLOT(slotPath()));
            layout->addWidget(nordx,5,0,10,2);
            functionInterface=nordx;
            break;
        }
        default:
            break;
    }
    originalFunction=function;
    //同时更改函数,但不会立即更新函数，等参数设置完毕，点击确定时，相应函数控件发送信号更新
}

void DrawDlg::setFunction(int index)
{
    function=DrawDlg::Function(functionComboBox->itemData(index,Qt::UserRole).toInt());
    updateLayout(function);
}

void DrawDlg::slotPath()
{
    update();//收到函数控件后开始更新
}

void DrawDlg::slotSinPath()
{
    originalFunction=Sinx;
    update();
}

void DrawDlg::on_colorBtn_clicked()//设置颜色
{
    QColor color=QColorDialog::getColor(Qt::blue,this);
    if(!color.isValid())return;//当用户取消时，返回的是无效值
    pen.setColor(color);
    QPixmap pixmap(20,20);
    pixmap.fill(color);
    ui->colorBtn->setIcon(QIcon(pixmap));
    update();

}

void DrawDlg::setWidth(int width)//设置线宽
{
    pen.setWidth(width);
    update();
}

void DrawDlg::setLineStyle(int value)//设置线型
{
    pen.setStyle(Qt::PenStyle(ui->styleComboBox->itemData(value,Qt::UserRole).toInt()));
    update();
}

void DrawDlg::setupModel()
{
    model=new QStandardItemModel(10,2,this);
    model->setHeaderData(0,Qt::Horizontal,tr("X"));
    model->setHeaderData(1,Qt::Horizontal,tr("Y"));
}

void DrawDlg::setupView()
{
    view=new QTableView;
    view->setModel(model);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    view->setSelectionModel(selectionModel);
    connect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            view,SLOT(selectionChanged(QItemSelection,QItemSelection)));
    ui->verticalLayout->addWidget(view);
}

void DrawDlg::on_openBtn_clicked()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,tr("打开"),".","TXT文件 (*.txt)");
    if(!filename.isEmpty())
        openFile(filename);
}

void DrawDlg::openFile(QString filename)
{
    if(!filename.isEmpty())
    {
        QFile file(filename);
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream stream(&file);
            QString line;

            model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());

            int row=0;
            do
            {
                line=stream.readLine();
                if(!line.isEmpty())
                {
                    model->insertRows(row,1,QModelIndex());
                    QStringList pieces=line.split(",",QString::SkipEmptyParts);
                    model->setData(model->index(row,0,QModelIndex()),pieces.value(0));
                    model->setData(model->index(row,1,QModelIndex()),pieces.value(1));
                    row++;
                }

            }while (!line.isEmpty());
        }
    }
}

void DrawDlg::on_deleteBtn_clicked()
{
    model->removeRows(0,model->rowCount(QModelIndex()));
    int row=0;
    for(;row<10;++row)
    {
        model->insertRows(row,1,QModelIndex());
        model->setData(model->index(row,0,QModelIndex()),"");
        model->setData(model->index(row,1,QModelIndex()),"");
    }
}

void DrawDlg::on_drawBtn_clicked()
{
    originalFunction=Data;
    QModelIndex indexx=model->index(0,0,QModelIndex());
    QModelIndex indexy=model->index(0,1,QModelIndex());
    double x=model->data(indexx).toDouble();
    double y=model->data(indexy).toDouble();
    int row=1;
    QPoint original(287,260);
    for(;row<model->rowCount(QModelIndex());++row)
    {
        datapath.moveTo(original.x()+x,original.y()-y);
        QModelIndex indexx=model->index(row,0,QModelIndex());
        QModelIndex indexy=model->index(row,1,QModelIndex());
        x=model->data(indexx).toDouble();
        y=model->data(indexy).toDouble();
        datapath.lineTo(original.x()+x,original.y()-y);
    }
    update();
}
