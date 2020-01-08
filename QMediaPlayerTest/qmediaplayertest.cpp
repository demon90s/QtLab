#include "qmediaplayertest.h"
#include "ui_qmediaplayertest.h"

#include <QDir>
#include <QFileDialog>

QMediaPlayerTest::QMediaPlayerTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QMediaPlayerTest)
{
    ui->setupUi(this);

    m_position = "00:00";

    connect(&m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(OnStateChanged(QMediaPlayer::State)));
    connect(&m_player, SIGNAL(durationChanged(qint64)), this, SLOT(OnDurationChanged(qint64)));
    connect(&m_player, SIGNAL(positionChanged(qint64)), this, SLOT(OnPositionChanged(qint64)));
    connect(&m_player, SIGNAL(mediaChanged(QMediaContent)), this, SLOT(OnMediaChanged(QMediaContent)));
}

QMediaPlayerTest::~QMediaPlayerTest()
{
    delete ui;
}

void QMediaPlayerTest::on_pushButtonChooseFile_clicked()
{
    this->ChooseFile();
}

void QMediaPlayerTest::ChooseFile()
{
    QString cur_path = QDir::homePath();
    QString dlg_title = "choose music file";
    QString filter = "music(*.mp3 *.wav *.wma);;mp3(*.mp3);;wav(*.wav);;wma(*.wma);;all(*.*)";
    QString file_path = QFileDialog::getOpenFileName(this, dlg_title, cur_path, filter);
    if (file_path.size() == 0)
    {
        return;
    }

    QFileInfo file_info(file_path);
    ui->labelFileName->setText(file_info.fileName());

    QMediaContent media_content(QUrl::fromLocalFile(file_path));
    m_player.setMedia(media_content);
}

void QMediaPlayerTest::on_pushButtonPlay_clicked()
{
    m_player.play();
}

void QMediaPlayerTest::on_pushButtonPause_clicked()
{
    m_player.pause();
}

void QMediaPlayerTest::on_pushButtonStop_clicked()
{
    m_player.stop();
}

void QMediaPlayerTest::OnStateChanged(QMediaPlayer::State state)
{
    qDebug() << "OnStateChanged ->" + QString::number(state);
}

void QMediaPlayerTest::OnDurationChanged(qint64 duration)
{
    //qDebug() << "OnDurationChanged";

    // 文件时长变化，duration 是毫秒
    int sec = duration / 1000;
    int min = sec / 60;
    sec %= 60;

    char buffer[1024];
    sprintf(buffer, "%02d:%02d", min, sec);
    m_duration = buffer;

    ui->labelDuration->setText(m_position + "/" + m_duration);

    ui->horizontalSliderPosition->setMaximum(duration);
}

void QMediaPlayerTest::OnPositionChanged(qint64 position)
{
    // 文件播放位置变化 position 是毫秒

    if (ui->horizontalSliderPosition->isSliderDown())
    {
        // 正处于手动调整状态，不处理
        return;
    }

    int sec = position / 1000;
    int min = sec / 60;
    sec %= 60;

    char buffer[1024];
    sprintf(buffer, "%02d:%02d", min, sec);
    m_position = buffer;

    ui->labelDuration->setText(m_position + "/" + m_duration);

    ui->horizontalSliderPosition->setSliderPosition(position);
}

void QMediaPlayerTest::OnMediaChanged(QMediaContent)
{
    m_player.stop();
}

void QMediaPlayerTest::on_horizontalSliderPosition_sliderReleased()
{
    // 这里 value 已经被预设成了时间
    m_player.setPosition(ui->horizontalSliderPosition->value());
}
