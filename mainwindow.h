#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QBitArray>
#include <QByteArray>
#include <string>
#include <iostream>
#include <ctime>
#include <random>
#include <QTime>
#include <QGraphicsScene>

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString hash(QByteArray text);

    quint32 calculateRoundOne(quint32 O1, quint32 O2, quint32 O3, quint32 O4, int k, int s);
    quint32 calculateRoundTwo(quint32 O1, quint32 O2, quint32 O3, quint32 O4, int k, int s);
    quint32 calculateRoundThree(quint32 O1, quint32 O2, quint32 O3, quint32 O4, int k, int s);

    quint32 functionF(quint32 f1, quint32 f2, quint32 f3);
    quint32 functionG(quint32 g1, quint32 g2, quint32 g3);
    quint32 functionH(quint32 h1, quint32 h2, quint32 h3);

    quint32 leftShift(quint32 a, int s);

private slots:
    void on_hashButton_clicked();

    void on_changeBitPushButton_clicked();

    void on_findColPushButton_clicked();

    void on_findProtPushButton_clicked();

private:
    Ui::MainWindow *ui;

        QString abc[2];
        int kk=0;

    quint32 A, B, C, D, AA, BB, CC, DD;
    quint32 *X;

    int textLength, bitLength;

    QBitArray textBitArray;

    int lengthInt,modForInt;

    QBitArray newTextBitArray;

    quint32 degree;

    int count;

    QByteArray text;

    QString hashString;

    string textAfterChange;

    int textBitLength;
    int numberOfBlocks;

    QStringList hashes;
    QStringList strings;

    int L,k=128;
    int N;

    QString stringForProt;

    QGraphicsScene *scene;
    QPen pen;
};

#endif // MAINWINDOW_H
