// Header file for Model
// @author Sasha Rybalkina
// @author Yeon Kim
// @date Oct 27,2023

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <vector>
#include <iostream>
using std::vector;

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

private:
    // vector to store the color pattern list
    vector<int> pattern;
    // tracks index of the color pattern list
    int index;
    // 0 is red, 1 is blue
    int color;
    // current index of the color pattern list
    int current;
    // color button flashing speed
    int lightSpeed;
    // user-adjustable flashing speed
    double speedValue;

public slots:
    // start button clicked
    void startClicked();
    // prepares next round
    void nextRound();
    // speeds up the game
    void speedUp();
    // updates the progress bar
    void updateProgress(double progressValue);
    // when game over
    void gameOver();
    // sets game speed to what user wanted
    void setSpeedValue(double value);

    // flash color on
    void lightOn();
    // flash color off
    void lightOff();
    // when last color is flashed
    void lastButtonFlash();

    // check user guess when red clicked
    void redClicked();
    // check user guess when blue clicked
    void blueClicked();


signals:
    // enable user clicking on color buttons
    void enableColorButtons();
    // enable user clicking on start buttons
    void enableStartButton();
    // disable user clicking on color buttons
    void disableStart();

    // when game is over
    void gameOverSign();

    // updates progress bar
    void updateProgressBar(int percentage);
    // updates the percentage label
    void updatePercentage(int percentage);

    // turn the light on for the color
    void flashOn(int colorCode);
    // turn the light off for the color
    void flashOff(int colorCode);
};

#endif // MODEL_H
