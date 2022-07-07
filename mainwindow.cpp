#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setVisible(1);
    ui->tableWidget->verticalHeader()->setVisible(1);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(addChar()));
    connect(ui->pushButtonBspace, SIGNAL(clicked()), this, SLOT(deleteLast()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addChar(){
    PoopChar *newChar = new PoopChar;
    newChar->setFamily(this->font().family());
    text.append(newChar);
    int index = ui->tableWidget->rowCount();
    newChar->position = index;
    ui->tableWidget->insertRow(index);
    ui->tableWidget->setRowHeight(index, 48);
    //columns: char, font, size, italic, bold, preview

    QComboBox *charEdit = new QComboBox;        //char edit column
    unsigned char c;
    for(c = '!'; c <= '~'; c++){
        charEdit->addItem(QString(QChar(c)));
    }
    charEdit->addItem("[space]");
    charEdit->addItem("[newline]");
    charEdit->setCurrentText("a");
    ui->tableWidget->setCellWidget(index, 0, charEdit);
    connect(charEdit, SIGNAL(currentTextChanged(QString)), newChar, SLOT(setChar(QString)));

    QComboBox *fontPicker = new QFontComboBox;  //font picker column
    fontPicker->setCurrentText(this->font().family());
    ui->tableWidget->setCellWidget(index, 1, fontPicker);
    connect(fontPicker, SIGNAL(currentTextChanged(QString)), newChar, SLOT(setFamily(QString)));

    QSpinBox *sizeEdit = new QSpinBox;          //size spinbox column
    sizeEdit->setRange(6, 72);
    sizeEdit->setValue(newChar->font.pointSize());
    ui->tableWidget->setCellWidget(index, 2, sizeEdit);
    //connect sizeEdit->valueChanged() to setSize
    connect(sizeEdit, SIGNAL(valueChanged(int)), newChar, SLOT(setSize(int)));

    QCheckBox *italicCheck = new QCheckBox;     //italic checkbox column
    italicCheck->setChecked(false);
    ui->tableWidget->setCellWidget(index, 3, italicCheck);
    connect(italicCheck, SIGNAL(clicked(bool)), newChar, SLOT(setItalic(bool)));

    QCheckBox *boldCheck = new QCheckBox;       //bold checkbox column
    boldCheck->setChecked(false);
    ui->tableWidget->setCellWidget(index, 4, boldCheck);
    connect(boldCheck, SIGNAL(clicked(bool)), newChar, SLOT(setBold(bool)));

    QTextEdit *preview = new QTextEdit;         //preview
    preview->setReadOnly(1);
    previewList.append(preview);
    preview->setFont(newChar->font);
    preview->setText("a");
    ui->tableWidget->setCellWidget(index, 5, preview);
    connect(newChar, SIGNAL(fontChanged(QString)), preview, SLOT(setFontFamily(QString)));
    connect(newChar, SIGNAL(italicChanged(bool)), preview, SLOT(setFontItalic(bool)));
    connect(newChar, SIGNAL(charChanged(QString)), preview, SLOT(setText(QString)));
    connect(newChar, SIGNAL(sizeChanged(qreal)), preview, SLOT(setFontPointSize(qreal)));
    connect(newChar, SIGNAL(boldChanged(int)), preview, SLOT(setFontWeight(int)));

    connect(preview, SIGNAL(textChanged()), this, SLOT(updateText()));
    updateText();
}

void MainWindow::updateText(){
    ui->textBrowser->clear();
    int i;
    for(i = 0; i < previewList.size(); i++){
        ui->textBrowser->insertHtml(previewList[i]->toHtml());  //the preview isn't just a preview, it stores the html
    }
}

void MainWindow::deleteLast(){
    if(ui->tableWidget->rowCount()){
        int i, rows = ui->tableWidget->rowCount();
        for(i = 0; i < 6; i++){
            ui->tableWidget->cellWidget(rows-1, i)->~QWidget();
        }
        ui->tableWidget->removeRow(rows-1);
        previewList.removeLast();
        updateText();
    }
}

void MainWindow::clear(){
    while(ui->tableWidget->rowCount()){
        deleteLast();
    }
}
