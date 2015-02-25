#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMediaPlayer>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <stdlib.h>
#include <time.h>
#include <QKeyEvent>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void getMove();
    void checkBoard();
    void checkRackets();
    void playSaund();
    void gameOver(int id);

private:
    Ui::Dialog *ui;
    QPoint direction;
    QLine left;
    QLine right;
    bool lTurn;
    bool rTurn;
    QLabel *score;
    int leftScore;
    int rightScore;
    QRect ball;
    QMediaPlayer player;
    int id;
    bool isOver;

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *pevent);
};

#endif // DIALOG_H
