#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    startTimer(50);
    setWindowTitle("Ping-pong");
    setGeometry(200, 200, 300, 200);

    srand(time(NULL));
    int randX = rand() % 5 + 2;
    int randY = rand() % 5 + 2;

    direction.setX(randX);
    direction.setY(randY);

    ball.setX(0);
    ball.setY(this->height()/2);

    left.setP1(QPoint(1, this->height()/2 - 20));
    left.setP2(QPoint(1, this->height()/2 + 20));

    right.setP1(QPoint(this->width() - 1, this->height()/2 - 20));
    right.setP2(QPoint(this->width() - 1, this->height()/2 + 20));

    score = new QLabel(this);
    leftScore = 0;
    rightScore = 0;

    score->setGeometry(this->width() / 2 - 45, 7, 90, 25);
    score->setText(QString("<b><h2><font color=#33FF00>Счет: %1:%2</font></h2></b>").arg(leftScore).arg(rightScore));

    QSize size(10, 10);
    ball.setSize(size);

    player.setMedia(QUrl::fromLocalFile("C:/Users/Olga/Desktop/2.mp3"));
    player.setVolume(80);
    playSaund();

    this->setStyleSheet("background-color: black");

    isOver = false;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::getMove()
{
    ball.setX(ball.x() + direction.x());
    ball.setY(ball.y() + direction.y());
    QSize size(10, 10);
    ball.setSize(size);
}

void Dialog::checkBoard()
{
    srand(time(NULL));
    int randX = rand() % 5 + 2;

    if (ball.right() > this->width() - 1) {
        if (ball.bottom() < right.p1().y() || ball.top() > right.p2().y()) {
            leftScore += 1;
            direction.setX(-abs(direction.x()));
        } else {
            direction.setX(-randX);
            playSaund();
        }
    } else if (ball.bottom() > this->height() - 1) {
        direction.setY(-abs(direction.y()));
    } else if (ball.x() < 1) {
        if (ball.bottom() < left.p1().y() || ball.top() > left.p2().y()) {
            rightScore += 1;
            direction.setX(abs(direction.x()));
        } else {
            direction.setX(randX);
            playSaund();
        }
    } else if (ball.top() < 0) {
        direction.setY(abs(direction.y()));
    }
}

void Dialog::checkRackets()
{
    if (left.p1().y() < 0) {
        left.setP1(QPoint(1, 0));
        left.setP2(QPoint(1, 40));
    } else if (left.p2().y() > this->height()) {
        left.setP1(QPoint(1, this->height() - 40));
        left.setP2(QPoint(1, this->height()));
    }
}

void Dialog::playSaund()
{
    player.play();
}

void Dialog::gameOver(int id)
{
    killTimer(id);
    isOver = true;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!isOver) {
        QPen pen(Qt::yellow);
        QBrush brush(Qt::yellow);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawEllipse(ball);

        QPen line(Qt::green);
        line.setWidth(4);
        painter.setPen(line);
        painter.drawLine(this->width()/2, 0, this->width()/2, this->height());
        painter.drawLine(left);
        painter.drawLine(right);

        score->setText(QString("<b><h2><font color=#33FF00>Счет: %1:%2</font></h2></b>").arg(leftScore).arg(rightScore));

        right.setP1(QPoint(this->width() - 1, right.y1()));
        right.setP2(QPoint(this->width() - 1, right.y2()));

        score->setGeometry(this->width() / 2 - 45, 7, 90, 25);
    } else {
        QPen line(Qt::green);
        line.setWidth(4);
        painter.setPen(line);
        score->setText(QString("<b><h2><p align=\"center\"><font color=#33FF00>Игра окончена!<br><br> Счет: %1:%2</font></p></h2></b>").arg(leftScore).arg(rightScore));
        score->setGeometry(this->width() / 2 - 150, this->height() / 2 - 30, 300, 60);
    }
    this->update();
}

void Dialog::timerEvent(QTimerEvent *event)
{
    if (leftScore == 2 || rightScore == 2)
        gameOver(event->timerId());
    getMove();
    checkBoard();
}

void Dialog::keyPressEvent(QKeyEvent *pevent)
{
    if (pevent->key() == Qt::Key_Left) {
        lTurn = true;
        rTurn = false;
    } else if (pevent->key() == Qt::Key_Right) {
        lTurn = false;
        rTurn = true;
    } else if (pevent->key() == Qt::Key_Up) {
        if (lTurn) {
            if (left.p1().y() <= 0)
                return;
            left.setP1(left.p1() + QPoint(0, -10));
            left.setP2(left.p2() + QPoint(0, -10));
        } else {
            if (right.p1().y() <= 0)
                return;
            right.setP1(right.p1() + QPoint(0, -10));
            right.setP2(right.p2() + QPoint(0, -10));
        }
    } else if (pevent->key() == Qt::Key_Down) {
        if (rTurn) {
            if (right.p2().y() >= this->height())
                return;
            right.setP1(right.p1() + QPoint(0, 10));
            right.setP2(right.p2() + QPoint(0, 10));
        } else {
            if (left.p2().y() >= this->height())
                return;
            left.setP1(left.p1() + QPoint(0, 10));
            left.setP2(left.p2() + QPoint(0, 10));
        }
    }
}

