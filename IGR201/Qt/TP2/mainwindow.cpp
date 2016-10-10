#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zone=ui->widget;

    QSpinBox* spinBox = ui->penSizeSpinBox;
    spinBox->setMinimum(0);
    spinBox->setValue(0);
    spinBox->setSpecialValueText(tr(" Pen Width "));

    QComboBox* comboBox1 = ui->capStyleComboBox;
    comboBox1->addItem("Square Cap");
    comboBox1->addItem("Flat Cap");
    comboBox1->addItem("Round Cap");

    QComboBox* comboBox2 = ui->joinStyleComboBox;
    comboBox2->addItem("Bevel Join");
    comboBox2->addItem("Miter Join");
    comboBox2->addItem("Round Join");

    colorPreview = ui->widget_2;
    colorPreview->setDrawable(0);
    colorPreview->fillDrawZone(Qt::black);

    penJoinStyleActionGroup = new QActionGroup(this);
    penJoinStyleActionGroup->addAction(ui->actionMiter_join);
    penJoinStyleActionGroup->addAction(ui->actionBevel_join);
    penJoinStyleActionGroup->addAction(ui->actionRound_join);
    penJoinStyleActionGroup->setExclusive(true);

    penCapStyleActionGroup = new QActionGroup(this);
    penCapStyleActionGroup->addAction(ui->actionSquare_cap);
    penCapStyleActionGroup->addAction(ui->actionFlat_cap);
    penCapStyleActionGroup->addAction(ui->actionRound_cap);
    penCapStyleActionGroup->setExclusive(true);

    connect(spinBox, SIGNAL(valueChanged(int)), zone, SLOT(setCurrentPenWidth(int)));
    connect(ui->actionPen_size, SIGNAL(triggered(bool)), this, SLOT(openSizeSelectionBox()));

    connect(colorPreview, SIGNAL(drawZoneClicked()), this, SLOT(openColorSelectionDialog()));
    connect(ui->actionPen_color,SIGNAL(triggered(bool)),this,SLOT(openColorSelectionDialog()));

    connect(comboBox1, SIGNAL(currentIndexChanged(int)),zone, SLOT(setCurrentPenCapStyle(int)));
    connect(zone, SIGNAL(penCapStyleChanged(int)), this, SLOT(actualizePenCapStyleUi(int)));
    connect(penCapStyleActionGroup, SIGNAL(triggered(QAction*)),zone,SLOT(setCurrentPenCapStyle(QAction*)));

    connect(comboBox2, SIGNAL(currentIndexChanged(int)), zone, SLOT(setCurrentPenJoinStyle(int)));   
    connect(zone, SIGNAL(penJoinStyleChanged(int)), this, SLOT(actualizePenJoinStyleUi(int)));
    connect(penJoinStyleActionGroup, SIGNAL(triggered(QAction*)), zone, SLOT(setCurrentPenJoinStyle(QAction*)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete penJoinStyleActionGroup;
    delete penCapStyleActionGroup;

}

void MainWindow::openColorSelectionDialog()
{

    QColorDialog *dialog = new QColorDialog(this);
    connect(dialog, SIGNAL(colorSelected(QColor)), zone, SLOT(setCurrentPenColor(QColor)));
    connect(dialog, SIGNAL(colorSelected(QColor)), colorPreview, SLOT(fillDrawZone(QColor)));
    dialog->exec();
    delete dialog;
}

void MainWindow::openSizeSelectionBox()
{

    ui->penSizeSpinBox->clear();
    ui->penSizeSpinBox->setFocus();
}

void MainWindow::actualizePenCapStyleUi(int n)
{

    ui->capStyleComboBox->setCurrentIndex(n);
    switch(n){
    case(0):
        ui->actionSquare_cap->setChecked(true);
        break;
    case(1):
        ui->actionFlat_cap->setChecked(true);
        break;
    case(2):
        ui->actionRound_cap->setChecked(true);
        break;
    }
}

void MainWindow::actualizePenJoinStyleUi(int n)
{

    ui->joinStyleComboBox->setCurrentIndex(n);
    switch(n){
    case(0):
        ui->actionBevel_join->setChecked(true);
        break;
    case(1):
        ui->actionMiter_join->setChecked(true);
        break;
    case(2):
        ui->actionRound_join->setChecked(true);
        break;
    }
}

/*void MainWindow::closeEvent(QCloseEvent *event)
{
     quitFile();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/cal/homes/pourchot/workspace/igr/TP1");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    QString str;
    str=stream.readAll();
    text->setText(str);

}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/cal/homes/pourchot/workspace/igr/TP1");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream in(&file);
    QString str;
    str=text->toPlainText();
    in << str;
}
void MainWindow::quitFile()
{
    QMessageBox msgBox;
    msgBox.setText("ARE YOU SURE YOU WANT TO QUIT ??N??§§!!!");
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Discard);
    int ret = msgBox.exec();
    if (ret==QMessageBox::Ok) this->close();
}
*/
