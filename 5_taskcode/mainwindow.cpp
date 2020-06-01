#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    processes.resize(10);
    QStringList m_TableHeader;
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(1);
    m_TableHeader<<"progress";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->setColumnWidth(0,295);
    for(int i=0;i<10;i++)
    {
        processes[i]=0;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update(int n, int i)
{
    reinterpret_cast<QProgressBar*> (ui->tableWidget->cellWidget(n,0))->setValue(i);
}
void MainWindow::deleteLater(int n)
{
    ui->tableWidget->removeCellWidget(n,0);
    QThread *thread=processes[n]->first;
    thread->exit();
    delete processes[n]->second;
    processes[n]=0;
    if(!thread->isFinished())
    {

       thread->wait();
    }
    delete thread;
}
void MainWindow::on_pushButton_clicked()
{
    for (int i=0;i<10;i++)
    {
        if(processes[i]==0)
        {
            QProgressBar* tmp=new QProgressBar();
            tmp->setValue(0);
            ui->tableWidget->setCellWidget(i,0,tmp);
            QThread *thread=new QThread();
            LongProcess *process=new LongProcess(i);
            process->moveToThread(thread);
            connect(process, SIGNAL(send(int,int)), this, SLOT(update(int,int)));
            connect(thread, SIGNAL(started()), process, SLOT(doWork()));
            connect(process,SIGNAL(finished(int)),this,SLOT(deleteLater(int)));
            processes[i]=new TPair(thread,process);
            thread->start();
            break;
        }
    }
}
