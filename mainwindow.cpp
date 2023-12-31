/**
 * View for Simon Game
 * @author Sasha Rybalkina
 * @author Yeon Kim
 * @date October 27, 2023
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Model.h"
#include <QTimer>

/**
 * @brief MainWindow::MainWindow Constructor
 * @param model Reference of model
 * @param parent Parent widget
 */
MainWindow::MainWindow(Model& model, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Set the colors of all the buttons
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(250,100,100);}"
                                         "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,250);}"
                                         "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->startButton->setStyleSheet(QString("QPushButton {background-color: rgb(250,215,100);}"
                                          "QPushButton:pressed {background-color: rgb(250,215,150);}"));

    // Connect the buttons with specific slots in the Model class.
    connect(ui -> startButton, &QPushButton::clicked, &model, &Model::startClicked);
    connect(ui -> blueButton, &QPushButton::clicked, &model, &Model::blueClicked);
    connect(ui -> redButton, &QPushButton::clicked, &model,&Model::redClicked);

    // Sets the speed of the game with a horizontal slider
    connect(ui -> speedSlider, &QSlider::sliderReleased, this, &MainWindow::sendValue);
    connect(this, &MainWindow::sliderValue, &model, &Model::setSpeedValue);

    // Disable blue and red buttons by default
    ui -> blueButton -> setEnabled(false);
    ui -> redButton -> setEnabled(false);

    // Set the range of speed the rounds can have
    ui -> speedSlider -> setRange(0, 10);

    // Enables the start button before the start of every game.
    connect(&model, &Model::enableStartButton, this,
            [this]() {
                ui -> startButton -> setEnabled(true);
            });

    // Enables the color buttons once the start button is clicked.
    connect(&model, &Model::enableColorButtons, this,
            [this]() {
                ui -> blueButton -> setEnabled(true);
                ui -> redButton -> setEnabled(true);

            });

    // Disables the start button once the game begins
    connect(&model, &Model::disableStart, this,
            [this]() {
                ui -> startButton -> setEnabled(false);
                ui -> blueButton -> setEnabled(false);
                ui -> redButton -> setEnabled(false);
                ui->gameOverLabel->setText("");
            });

    // Game over
    connect(&model, &Model::gameOverSign, this,
            [this]() {
                ui->startButton->setDisabled(false);
                ui->blueButton->setDisabled(true);
                ui->redButton->setDisabled(true);
                ui->gameOverLabel->setText("Game Over");
                ui->percentage->setText("0%");
            });

    // Controls the flashing of the red and blue buttons
    connect(&model, &Model::flashOn, this, &MainWindow::flashColorOn);
    connect(&model, &Model::flashOff, this, &MainWindow::flashColorOff);

    // Update progress bar and percentage display
    connect(&model, &Model::updateProgressBar, ui->progressBar, &QProgressBar::setValue);
    connect(&model, &Model::updatePercentage, this, &MainWindow::setPercentage);
}

/**
 * @brief Destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Send value of the speed slider
 */
void MainWindow::sendValue()
{
    emit sliderValue(ui -> speedSlider -> value());
}

/**
 * @brief Update progress percentage display
 * @param progress: Current progress percentage
 */
void MainWindow::setPercentage(int progress)
{
    QString percent = QString::number(progress) + "%";
    ui -> percentage->setText(percent);
    if (ui -> percentage -> text() == "100%")
    {
        QTimer::singleShot(1000, this, [=] () {
            ui -> percentage->setText(QString::number(0) + "%");
        });
    }
}

/**
 * @brief Lights up a specific color button
 * @param colorCode: 0 for Red or 1 for Blue
 */
void MainWindow::flashColorOn(int colorCode) {
    // Red
    if(colorCode == 0) {
        ui -> redButton -> setStyleSheet(QString("QPushButton {background-color: rgb(255,150,150);}"
                                                 "QPushButton:pressed {background-color: rgb(250,100,100);}"));
    }
    // Blue
    else {
        ui -> blueButton -> setStyleSheet(QString("QPushButton {background-color: rgb(150,150,225);}"
                                                  "QPushButton:pressed {background-color: rgb(100,100,250);}"));
    }
}

/**
 * @brief Lights off a specific color button
 * @param colorCode: 0 for Red or 1 for Blue
 */
void MainWindow::flashColorOff(int colorCode) {
    // Red
    if(colorCode == 0) {
        ui -> redButton -> setStyleSheet(QString("QPushButton {background-color: rgb(250,100,100);}"
                                             "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    }
    // Blue
    else {
        ui -> blueButton -> setStyleSheet(QString("QPushButton {background-color: rgb(100,100,250);}"
                                                  "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    }
}
