#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    scene = new QGraphicsScene(ui->graphicsView);
    pen.setColor(Qt::black);
    scene->addLine(11,290,380,290,pen);
    scene->addLine(365,300,380,290,pen);
    scene->addLine(365,280,380,290,pen);
    scene->addLine(11,0,21,15,pen);
    scene->addLine(11,0,1,15,pen);
    scene->addLine(11,0,11,290,pen);
    //ui->graphicsView->setScene(scene);

    scene->addLine(1*10,-2*20+350,2*10,-3*20+350,pen);
    scene->addLine(2*10,-3*20+350,3*10,-5*20+350,pen);
    scene->addLine(3*10,-5*20+350,4*10,-6*20+350,pen);
    scene->addLine(4*10,-6*20+350,5*10,-9*20+350,pen);
    scene->addLine(5*10,-9*20+350,6*10,-15*20+350,pen);
    scene->addLine(6*10,-15*20+350,7*10,-23*20+350,pen);
    scene->addLine(7*10,-23*20+350,8*10,-26*20+350,pen);
    scene->addLine(8*10,-26*20+350,9*10,-31*20+350,pen);
    scene->addLine(9*10,-31*20+350,10*10,-47*20+350,pen);
    scene->addLine(10*10,-47*20+350,11*10,-71*20+350,pen);
    scene->addLine(11*10,-71*20+350,12*10,-95*20+350,pen);
    scene->addLine(12*10,-95*20+350,13*10,-96*20+350,pen);
    scene->addLine(13*10,-96*20+350,14*10,-203*20+350,pen);
    scene->addLine(14*10,-203*20+350,15*10,-413*20+350,pen);
    scene->addLine(15*10,-413*20+350,16*10,-617*20+350,pen);
    scene->addLine(16*10,-617*20+350,17*10,-928*20+350,pen);
    scene->addLine(17*10,-928*20+350,18*10,-986*20+350,pen);
    scene->addLine(18*10,-986*20+350,19*10,-1163*20+350,pen);
    scene->addLine(19*10,-1163*20+350,20*10,-1157*20+350,pen);
    scene->addLine(20*10,-1157*20+350,21*10,-1698*20+350,pen);
    scene->addLine(21*10,-1698*20+350,22*10,-3861*20+350,pen);
    scene->addLine(22*10,-3861*20+350,23*10,-3610*20+350,pen);

    //ui->graphicsView->setScene(scene);
}

QString MainWindow::hash(QByteArray text)
{
    textLength=text.length();
    textBitLength=textLength*8;
    textBitArray.resize(textBitLength);
    for(int i=0; i<textLength; ++i)
        for(int b=0; b<8; ++b)
            textBitArray.setBit((i*8+7-b), text.at(i)&(1<<b));

    textBitLength=textLength*8;

    textBitArray.resize(textBitArray.size()+1);
    textBitArray.setBit(textBitArray.size()-1,true);
    while(textBitArray.size()%512!=448)
        textBitArray.resize(textBitArray.size()+1);
    textBitArray.resize(textBitArray.size()+64);
    numberOfBlocks=textBitArray.size()/512;
    lengthInt=textBitLength;
    newTextBitArray.resize(numberOfBlocks*512);
    for(int i=numberOfBlocks*512-33;i>=numberOfBlocks*512-64;i--)
    {
        modForInt=lengthInt%2;
        lengthInt=lengthInt/2;
            if(modForInt==1)
                newTextBitArray.setBit(i,true);
            else
                newTextBitArray.setBit(i,false);
    }
    for(int i=numberOfBlocks*512-1;i>=numberOfBlocks*512-32;i--)
    {
        modForInt=lengthInt%2;
        lengthInt=lengthInt/2;
            if(modForInt==1)
                newTextBitArray.setBit(i,true);
            else
                newTextBitArray.setBit(i,false);
    }
    int m=0;
    while(m<numberOfBlocks*512-64)
    {
        for(int b=0;b<8;b++)
        {
            newTextBitArray.setBit(m+b,textBitArray.at(m+b+24));
            newTextBitArray.setBit(m+b+8,textBitArray.at(m+b+16));
            newTextBitArray.setBit(m+b+16,textBitArray.at(m+b+8));
            newTextBitArray.setBit(m+b+24,textBitArray.at(m+b));
        }
        m=m+32;
    }

    A = 0x67452301;
    B = 0xefcdab89;
    C = 0x98badcfe;
    D = 0x10325476;

    int f=0;
    for (int i = 0;i<numberOfBlocks;i++)
    {
       X=new quint32[16];
       for (count = 0;count<16;count++)
       {
           X[count]=0;
           for(int k=0;k<32;k++)
           {
               if(newTextBitArray.at(count*32+k+f))
               {
                   degree=1;
                   for(int p=0;p<31-k;p++)
                       degree=degree*2;
                    X[count]=X[count]+degree;
               }
           }
       }
       AA = A;
       BB = B;
       CC = C;
       DD = D;

       A=calculateRoundOne(A,B,C,D,0,3);
       D=calculateRoundOne(D,A,B,C,1,7);
       C=calculateRoundOne(C,D,A,B,2,11);
       B=calculateRoundOne(B,C,D,A,3,19);

       A=calculateRoundOne(A,B,C,D,4,3);
       D=calculateRoundOne(D,A,B,C,5,7);
       C=calculateRoundOne(C,D,A,B,6,11);
       B=calculateRoundOne(B,C,D,A,7,19);

       A=calculateRoundOne(A,B,C,D,8,3);
       D=calculateRoundOne(D,A,B,C,9,7);
       C=calculateRoundOne(C,D,A,B,10,11);
       B=calculateRoundOne(B,C,D,A,11,19);

       A=calculateRoundOne(A,B,C,D,12,3);
       D=calculateRoundOne(D,A,B,C,13,7);
       C=calculateRoundOne(C,D,A,B,14,11);
       B=calculateRoundOne(B,C,D,A,15,19);

       A=calculateRoundTwo(A,B,C,D,0,3);
       D=calculateRoundTwo(D,A,B,C,4,5);
       C=calculateRoundTwo(C,D,A,B,8,9);
       B=calculateRoundTwo(B,C,D,A,12,13);

       A=calculateRoundTwo(A,B,C,D,1,3);
       D=calculateRoundTwo(D,A,B,C,5,5);
       C=calculateRoundTwo(C,D,A,B,9,9);
       B=calculateRoundTwo(B,C,D,A,13,13);

       A=calculateRoundTwo(A,B,C,D,2,3);
       D=calculateRoundTwo(D,A,B,C,6,5);
       C=calculateRoundTwo(C,D,A,B,10,9);
       B=calculateRoundTwo(B,C,D,A,14,13);

       A=calculateRoundTwo(A,B,C,D,3,3);
       D=calculateRoundTwo(D,A,B,C,7,5);
       C=calculateRoundTwo(C,D,A,B,11,9);
       B=calculateRoundTwo(B,C,D,A,15,13);

       A=calculateRoundThree(A,B,C,D,0,3);
       D=calculateRoundThree(D,A,B,C,8,9);
       C=calculateRoundThree(C,D,A,B,4,11);
       B=calculateRoundThree(B,C,D,A,12,15);

       A=calculateRoundThree(A,B,C,D,2,3);
       D=calculateRoundThree(D,A,B,C,10,9);
       C=calculateRoundThree(C,D,A,B,6,11);
       B=calculateRoundThree(B,C,D,A,14,15);

       A=calculateRoundThree(A,B,C,D,1,3);
       D=calculateRoundThree(D,A,B,C,9,9);
       C=calculateRoundThree(C,D,A,B,5,11);
       B=calculateRoundThree(B,C,D,A,13,15);

       A=calculateRoundThree(A,B,C,D,3,3);
       D=calculateRoundThree(D,A,B,C,11,9);
       C=calculateRoundThree(C,D,A,B,7,11);
       B=calculateRoundThree(B,C,D,A,15,15);

       A = A + AA;
       B = B + BB;
       C = C + CC;
       D = D + DD;

       f=f+512;
    }
    int sd[k];
    quint32 divForM=A;
    quint32 modForM;
    int i=0;
    quint32 ss[4];
    ss[0]=A;
    ss[1]=B;
    ss[2]=C;
    ss[3]=D;
    divForM=ss[0];
    while(i<k)
    {
        while(divForM>=2 && i<k)
        {
            modForM=divForM%2;
            divForM=divForM/2;
            sd[i]=modForM;
            i++;
        }
        sd[i]=divForM;
        if(k>32)
        {
            while((i+1)%32!=0)
            {
                i++;
                sd[i]=0;
            }
        }
        i++;
        divForM=ss[i/32];
    }
    int x=0;
    hashString="";
    int h;
    if(k<128)
        h=4;
    else
        h=16;
    for(int i=0;i<h;i++)
    {
        x=0;
        for(int b=0;b<8;b++)
        {
            if(sd[i*8+b]==1)
            {
                degree=1;
                for(int j=0;j<b;j++)
                    degree=degree*2;
                x=x+degree;
            }
        }
        if(QString::number(x).setNum(x,16).size()<2)
            hashString=hashString+"0"+QString::number(x).setNum(x,16);
        else
            hashString=hashString+QString::number(x).setNum(x,16);
    }
    return hashString;
}
quint32 MainWindow::calculateRoundOne(quint32 O1, quint32 O2, quint32 O3, quint32 O4, int k, int s)
{
    //a = (a + F(b, c, d) + X[k]) <<< s.
    return leftShift((O1 + functionF(O2,O3,O4)+ X[k]), s);
}

quint32 MainWindow::calculateRoundTwo(quint32 O1, quint32 O2, quint32 O3, quint32 O4, int k, int s)
{
    //a = (a + G(b,c,d) + X[k] + 5A827999) <<< s.
    return leftShift((O1 + functionG(O2, O3, O4) + X[k]+ 0x5A827999), s);
}

quint32 MainWindow::calculateRoundThree(quint32 O1, quint32 O2, quint32 O3, quint32 O4, int k, int s)
{
    //a = (a + H(b,c,d) + X[k] + 6ED9EBA1) <<< s.
    return leftShift((O1 + functionH(O2, O3, O4) + X[k] + 0x6ED9EBA1), s);
}

quint32 MainWindow::functionF(quint32 f1, quint32 f2, quint32 f3)
{
    return ((f1 & f2)|(((~f1)&f3)));
}

quint32 MainWindow::functionG(quint32 f1, quint32 f2, quint32 f3)
{
    //qDebug()<<"s"<<(f1&f2)<<(f1&f3)<<(f2&f3);
    return ((f1 & f2) | (f1 & f3) | (f2 & f3));
}

quint32 MainWindow::functionH(quint32 f1, quint32 f2, quint32 f3)
{
    return (f1^f2^f3);
}

quint32 MainWindow::leftShift(quint32 a, int s)
{
    return ((a << s) | (a >> (32 - s)));
}

void MainWindow::on_hashButton_clicked()
{
    k=128;
    text=ui->textEdit->toPlainText().toUtf8();
    hash(text);
    ui->hashEdit->clear();
    ui->hashEdit->document()->setPlainText(hash(text));
}

void MainWindow::on_changeBitPushButton_clicked()
{
    textAfterChange=ui->textEdit->toPlainText().toStdString();
    textAfterChange[textLength-1]=int(textAfterChange[textLength-1])+1;
    ui->textAfterChangeEdit->document()->setPlainText(QString::fromStdString(textAfterChange));
    text=QString::fromStdString(textAfterChange).toUtf8();
    ui->hashAfterChangeEdit->clear();
    ui->hashAfterChangeEdit->document()->setPlainText(hash(text));
}

void MainWindow::on_findColPushButton_clicked()
{
    L=ui->LSpinBox->value();
    k=ui->kSpinBox->value();

    bool t=true;

    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = L;
    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
     }
     strings.push_back(randomString);

     hashes.push_back(hash(randomString.toUtf8()));

    int u,w;
    while(t)
    {
       randomString="";
       for(int i=0; i<randomStringLength; ++i)
       {
           int index = qrand() % possibleCharacters.length();
           QChar nextChar = possibleCharacters.at(index);
           randomString.append(nextChar);
        }
        strings.push_back(randomString);
        qDebug()<<strings.last();

        hashes.push_back(hash(randomString.toUtf8()));
        qDebug()<<hashes.last();

        N=0;
        for(int j=0;j<hashes.size();j++)
        {
            for(int i=0;i<hashes.size();i++)
            {
                if(hashes.at(j)==hashes.at(i) && j!=i)
                {
                    u=j;
                    w=i;
                    t=false;
                    break;
                }
            }
            N++;
        }
        if(!t)
            break;
    }

    ui->colEdit1->setPlainText(strings.at(u));
    ui->colEdit2->setPlainText(strings.at(w));
    ui->Nlabel->setText(QString::number(N));
    ui->sameHashEdit->setPlainText(hashes.at(u));

    hashes.clear();
    strings.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findProtPushButton_clicked()
{
    k=ui->k2SpinBox->value();
    stringForProt=ui->textForProtEdit->document()->toPlainText();

    strings.push_back(stringForProt);

    hashes.push_back(hash(stringForProt.toUtf8()));

    QString randomString;
    int randomStringLength=stringForProt.length();
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    bool t=true;
    int w;
    while(t)
    {
       randomString="";
       for(int i=0; i<randomStringLength; ++i)
       {
           int index = qrand() % possibleCharacters.length();
           QChar nextChar = possibleCharacters.at(index);
           randomString.append(nextChar);
        }
        strings.push_back(randomString);
        qDebug()<<strings.last();

        hashes.push_back(hash(randomString.toUtf8()));
        qDebug()<<hashes.last();

        N=0;
        for(int i=1;i<hashes.size();i++)
        {
            if(hashes.at(i)==hashes.at(0))
            {
                w=i;
                t=false;
                N++;
                break;
            }
            N++;
        }
        if(!t)
            break;
    }

    ui->protEdit->setPlainText(strings.at(w));
    ui->N2label->setText(QString::number(N));

    hashes.clear();
    strings.clear();
}
