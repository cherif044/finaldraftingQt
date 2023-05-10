#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <sstream>
#include <QScrollArea>
#include"x_res.h""
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

    // Loop through each string to highlight
    for (const auto& highlightPair : highlightList)
    {
        const QString& highlightString = highlightPair.first;
        const QString& highlightColor = highlightPair.second;

        // Create a regular expression to find the substring to highlight
        QRegularExpression re(highlightString, QRegularExpression::CaseInsensitiveOption);

        // Loop through all instances of the substring and apply a background color to the selected text
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
    brute_force a(filename1,filename2);







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


            //if (tempI.size() > 0)
           // {
           //     ui->label->setText(ui->label->text()+QString("sentence: ") + QString::fromStdString(std::to_string(j)) + '\n');

           //     for (int z = 0; z < tempI.size(); z++)
           //     {
           //         ui->label->setText(ui->label->text()+QString("the phrase : (") + QString::fromStdString(tempI[z].text) +
            //                           QString(") is similar to a phrase in sentence: ") + QString::number(i) +
            //                           QString(" of the second file") + QString(" this phrase starts from word number: ") +
            //                           QString::number(tempI[z].index_x) + QString(" of the first file sentence and starts from the word: ") +
            //                           QString::number(tempI[z].index_y) + QString(" of the second file sentence") + QChar('\n'));
//
            //    }

           // }

        }
     a.push_storage(plagiarized);
    }

    ui->label_5->setWordWrap(true);

    for(int h=0;h<a.getfilex_vector().size();h++)
    {

        ui->label_5->setText(ui->label_5->text()+ a.getfilex_vector()[h]);

                 ui->textEdit->setText(ui->textEdit->toPlainText()+ a.getfilex_vector()[h]);
    }




    for(int h=0; h < a.getfiley_vector().size(); h++) {
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText() + a.getfiley_vector()[h]);
    }







    for(int i = 0; i < a.getstorage().size(); i++)
    {
        cout << "sentence: " << i+1 << " has plagiarism phrases: " << a.getstorage().at(i).size() << endl;





        for(int j = 0; j < a.getstorage().at(i).size(); j++)
        {
            QString highlight = QString::fromStdString(a.getstorage().at(i).at(j).textx);
        QString labelText = ui->label_5->text();
            // Check if the highlight string is found in the label text
            if (ui->label_5->text().contains(highlight, Qt::CaseInsensitive)) {
                cout << "Match found: " << highlight.toStdString() << endl;
            }

            // Replace all instances of the substring with HTML formatting to highlight them
            QRegularExpression re(highlight);

            labelText.replace(re, "<span style='background-color: yellow'>" + highlight + "</span>");
            ui->label_5->setText(labelText);
        }




    }



highlight(a.getnewx(),ui->textEdit);
highlight(a.getnewy(),ui->textEdit_2);
cout<<"X PLAGIARIZED SENDTENCE FINAL"<<endl;
displayFirsts(a.getnewx());
cout<<endl;
cout<<"y PLAGIARIZED SENDTENCE FINAL"<<endl;
displayFirsts(a.getnewy());


}





   /* for(int i=1;i<=a.number_of_phrases_filex();i++)
    {


            for(int j=0;j<a.getstorage().at(i).size();j++)
            {
                for(int k=0;k<a.getstorage().at(i).at(j).size();k++)
                {
                if(a.getstorage().at(i).at(j).at(k).index_x!=-999)
                {
                int startIndex=a.get_filex_sentences_index()[i-1]+a.getstorage().at(i).at(j).at(k).index_x;
                int endIndex=startIndex+a.getstorage().at(i).at(j).at(k).text.length();

                QString labelText = ui->label_5->text(); // get the text of label_2 widget


                // apply highlighting with span element and yellow background color to the specified section of text
                QString highlightedText = "<span style='background-color: yellow'>" + labelText.mid(startIndex, endIndex - startIndex + 1) + "</span>";

                // combine the rest of the label text with the highlighted text
                QString finalText = labelText.left(startIndex) + highlightedText + labelText.right(labelText.length() - endIndex - 1);

                ui->label_5->setTextFormat(Qt::RichText); // set the text format of the widget to RichText
                ui->label_5->setText(finalText); // set the final text as the text of label_2 widget
                }
                }

            }

    }*/










