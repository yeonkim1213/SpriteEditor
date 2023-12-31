// Header file for Main Window (View)
// @author Sasha Rybalkina
// @author Yeon Kim
// @date Oct 27,2023

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    MainWindow(Model &model, QWidget *parent = nullptr);
    // Deconstructor
    ~MainWindow();

public slots:
    // flash of a color button in on state
    void flashColorOn(int colorCode);
    // flash of a color button in off state
    void flashColorOff(int colorCode);
    // sends speed value of the speed slider
    void sendValue();
    // sets progress percentage
    void setPercentage(int progress);

signals:
    // speed slider value
    void sliderValue(double speed);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
