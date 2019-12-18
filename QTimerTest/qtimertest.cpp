#include "qtimertest.h"
#include "ui_qtimertest.h"

#include <QDebug>

QTimerTest::QTimerTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTimerTest)
{
    ui->setupUi(this);

    connect(&m_debug_timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
}

QTimerTest::~QTimerTest()
{
    delete ui;
}

void QTimerTest::StartTimer()
{
    if (m_debug_timer.isActive())
    {
        m_debug_timer.stop();

        ui->pushButton->setText("Start Timer");
    }
    else
    {
        m_debug_timer.start(1000);  // 1秒执行一次

        ui->pushButton->setText("Stop Timer");
    }
}

void QTimerTest::OnTimer()
{
    qDebug() << "QTimerTest::OnTimer";
}

void QTimerTest::on_pushButton_clicked()
{
    this->StartTimer();
}
