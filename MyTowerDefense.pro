QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audioplayer.cpp \
    bullet.cpp \
    chooselevelwindow.cpp \
    enemy.cpp \
    gamewindow.cpp \
    gamewindow2.cpp \
    main.cpp \
    mainwindow.cpp \
    mybutton.cpp \
    plistreader.cpp \
    tower.cpp \
    towerposition.cpp \
    utility.cpp \
    waypoint.cpp

HEADERS += \
    audioplayer.h \
    bullet.h \
    chooselevelwindow.h \
    enemy.h \
    gamewindow.h \
    gamewindow2.h \
    mainwindow.h \
    mybutton.h \
    plistreader.h \
    tower.h \
    towericon.h \
    towerposition.h \
    utility.h \
    waypoint.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    music/First Page.mp3 \
    music/Lose.mp3 \
    music/Win.mp3 \
    music/bgmusic2.mp3 \
    music/bossEnemyDie.mp3 \
    music/daojishi.mp3 \
    music/easy.mp3 \
    music/enemy_destroy.wav \
    music/fastEnemyDie.mp3 \
    music/fireBullet.mp3 \
    music/fireEnemyDie.mp3 \
    music/hard.mp3 \
    music/iceBullet.mp3 \
    music/iceEnemyDie.mp3 \
    music/laserBullet.mp3 \
    music/life_lose.mp3 \
    music/mainmusic.mp3 \
    music/mouse.mp3 \
    music/normalBullet.mp3 \
    music/normalEnemyDie.mp3 \
    music/select.mp3 \
    music/tower_place.mp3
