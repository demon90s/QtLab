#ifndef QMEDIAPLAYERTEST_H
#define QMEDIAPLAYERTEST_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class QMediaPlayerTest;
}

class QMediaPlayerTest : public QMainWindow
{
    Q_OBJECT

private:
    QMediaPlayer m_player;             // 播放器
    QString m_duration;                // 文件播放时长 如同：03:58
    QString m_position;                // 当前播放位置 如同：00:28

public:
    explicit QMediaPlayerTest(QWidget *parent = 0);
    ~QMediaPlayerTest();

private slots:
    // 自定义槽函数
    void OnStateChanged(QMediaPlayer::State state);
    void OnDurationChanged(qint64 duration);
    void OnPositionChanged(qint64 position);
    void OnMediaChanged(QMediaContent media_content);

    void on_pushButtonChooseFile_clicked();
    void on_pushButtonPlay_clicked();
    void on_pushButtonPause_clicked();
    void on_pushButtonStop_clicked();
    void on_horizontalSliderPosition_sliderReleased();

private:
    Ui::QMediaPlayerTest *ui;

    void ChooseFile();
};

#endif // QMEDIAPLAYERTEST_H
