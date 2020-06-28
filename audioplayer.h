#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QDir>

// 使用绝对路径可以完成声音输出
static const QString s_curDir = "F:/Qt5.14/TowerDefense-Qt-master/MyTowerDefense/music";


class QMediaPlayer;

enum SoundType
{
    TowerPlaceSound,		// 放塔时的声音
    LifeLoseSound,			// 基地费血时的声音
    BulletSound1,           //敌人被子弹打中的声音
    BulletSound2,
    BulletSound3,
    BulletSound4,
    EnemyDestorySound1,      // 敌人下线声音
    EnemyDestorySound2,
    EnemyDestorySound3,
    EnemyDestorySound4,
    bossEnemyDestorySound,
    luoboCrySound,           //萝卜遭受伤害的声音
};

class AudioPlayer : public QObject
{
public:
    explicit AudioPlayer(QUrl backgroundMusicUrl,QObject *parent = 0);
    void startBGM();
    void stopBGM();
    void playSound(SoundType soundType);
    void playWinSound();
    void playLoseSound();
    QMediaPlayer * getMusic();

private:
    QMediaPlayer *m_backgroundMusic; // 只用来播放背景音乐
    QMediaPlayer *m_winMusic;
    QMediaPlayer *m_loseMusic;
};



#endif // AUDIOPLAYER_H
