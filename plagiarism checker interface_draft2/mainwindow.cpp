#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <sstream>
#include <QScrollArea>
#include"x_res.h"
#include <QLabel>
#include <QList>
#include <QPair>
#include <QDebug>
#include <QTextEdit>
#include <QScrollArea>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QApplication>
#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QRegularExpression>
#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCursor>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QRegularExpressionMatch>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QFont>
#include <QApplication>
#include <QLabel>
#include <QSyntaxHighlighter>
#include <QRegularExpression>

class MyHighlighter : public QSyntaxHighlighter {
public:
    MyHighlighter(QTextDocument* parent = nullptr) : QSyntaxHighlighter(parent) {
        QTextCharFormat format;
        format.setForeground(QColor(255, 0, 0)); // set text color to red
        QRegularExpression pattern("\\bQt\\b"); // match "Qt" as a whole word
        highlightingRules.append(QPair<QRegularExpression, QTextCharFormat>(pattern, format));
    }

protected:
    void highlightBlock(const QString& text) {
        for (const auto& rule : highlightingRules) {
            QRegularExpressionMatchIterator matchIterator = rule.first.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.second);
            }
        }
    }

private:
    QVector<QPair<QRegularExpression, QTextCharFormat>> highlightingRules;
};




x_res *bu;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        QPixmap bkgnd("C:/Users/Hp/Documents/plagiarism checker interface/graph.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    //ui->setupUi(this);
}
double highlightedWordPercentage(QTextEdit* textEdit, QColor color) {
    QTextCharFormat initialFormat = textEdit->textCursor().charFormat();
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(color);

    QTextDocument* doc = textEdit->document();
    QTextOption option = doc->defaultTextOption();
    option.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    doc->setDefaultTextOption(option);

    QTextCursor highlightCursor(doc);
    highlightCursor.movePosition(QTextCursor::Start);

    int highlightCount = 0;
    int totalCount = 0;
    while (!highlightCursor.atEnd()) {
        highlightCursor = doc->find(highlightCursor.selectedText(), highlightCursor, QTextDocument::FindWholeWords);

        if (!highlightCursor.isNull()) {
            ++totalCount;

            QTextCharFormat format = highlightCursor.charFormat();
            if (format.background() == color) {
                ++highlightCount;
            }
        } else {
            break;
        }
    }

    double percentage = 0.0;
    if (totalCount > 0) {
        percentage = (double)highlightCount / (double)totalCount * 100.0;
    }
    return percentage;
}
MainWindow::~MainWindow()
{
    delete ui;
}
QString file;

void MainWindow::on_pushButton_clicked()
{

        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename1 = file.toStdString();



}


void MainWindow::on_pushButton_2_clicked()
{

        file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*.*)"));
        this->filename2 = file.toStdString();


}

#include <sstream>

#include <sstream>

void output()
{
    std::cout << "cherif" << std::endl;
}
void displayFirsts(const QList<QPair<QString, QString>>& list) {
    for (const auto& pair : list) {
        cout<<pair.first.toStdString();
        cout << "\n";
    }
}
void highlight(const QList<QPair<QString, QString>>& highlightList, QTextEdit *textEdit)
{
    QString labelText = textEdit->toPlainText();


    for (const auto& highlightPair : highlightList)
    {
        const QString& highlightString = highlightPair.first;
        const QString& highlightColor = highlightPair.second;


        QRegularExpression re(highlightString, QRegularExpression::CaseInsensitiveOption);


        QTextCursor cursor(textEdit->document());
        while (!cursor.isNull() && !cursor.atEnd())
        {
            cursor = textEdit->document()->find(re, cursor);
            if (!cursor.isNull()) {
                QTextCharFormat format;
                format.setBackground(QBrush(QColor(highlightColor)));
                cursor.mergeCharFormat(format);
            }
        }
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    brute_force a(filename1,filename2,2);
    if(ui->lineEdit->text().toInt()>0 && ui->lineEdit->text().toInt()<4)
    {
    a=brute_force(filename1,filename2,ui->lineEdit->text().toInt());
    }

    ui->label->setWordWrap(true);

    ui->label->setText("checking every sentence in file 1\n");
  cout<<"sentence check: "<<endl;
    for (int j = 1; j <= a.number_of_phrases_filex(); j++)          // every phrase in filex vector
    {
        vector<logs> plagiarized;
        cout<<"sentence : "<<j <<" of file x check "<<endl;
        for (int i = 1; i <= a.number_of_phrases_filey(); i++)
        {
           cout<<"checking with sentence: "<<i<<" of file y"<<endl;
            vector<char> temp = a.getsentence_filey(i);
            a.trial(temp, a.getsentence_filex(j),i,j,plagiarized);
        }
    }

    ui->label_5->setWordWrap(true);
if(a.filex_authentication())
{
    for(int h=0;h<a.getfilex_vector().size();h++)
    {
        ui->textEdit->setText(ui->textEdit->toPlainText()+ a.getfilex_vector()[h]);
    }
}
else
{
    ui->textEdit->setText("error while opening the file");
}
if(a.filey_authentication())
{
    for(int h=0;h<a.getfiley_vector().size();h++)
    {
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText()+ a.getfiley_vector()[h]);
    }
}
else
{
    ui->textEdit_2->setText("error while opening the file");
}

highlight(a.getnewx(),ui->textEdit);
highlight(a.getnewy(),ui->textEdit_2);
cout<<"X PLAGIARIZED SENDTENCE FINAL"<<endl;
displayFirsts(a.getnewx());
cout<<endl;
cout<<"y PLAGIARIZED SENDTENCE FINAL"<<endl;
displayFirsts(a.getnewy());

ui->label_2->setText(QString::number(highlightedWordPercentage(ui->textEdit,QColor(Qt::yellow)))+ "%");

}










