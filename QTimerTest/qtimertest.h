#ifndef QTIMERTEST_H
#define QTIMERTEST_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class QTimerTest;
}

class QTimerTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTimerTest(QWidget *parent = 0);
    ~QTimerTest();

private:
    void StartTimer();
    private slots: void OnTimer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QTimerTest *ui;

    QTimer m_debug_timer;
};

#endif // QTIMERTEST_H
