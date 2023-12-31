/**
 * Model for Simon Game
 * @author Sasha Rybalkina
 * @author Yeon Kim
 * @date October 27, 2023
 */

#include "Model.h"
#include <QTimer>
#include <vector>
#include <iostream>
using std::vector;

/**
 * @brief Model constructor. Sets initial speed and inherits from QObject.
 */
Model::Model(QObject *parent) : QObject{parent} {
    lightSpeed = 1500;
    speedValue = 1;
}

/**
 * @brief Starts the game when the start button is clicked by creating
 * an initial pattern of three
 */
void Model::startClicked(){
    emit disableStart();

    int patternLength = 2;

    // Randomly generates pattern(red/blue)
    while (patternLength > 0)
    {
        pattern.push_back(arc4random() % 2);
        patternLength--;
    }

    nextRound();
}

/**
 * Prepares the game for the next round
 */
void Model::nextRound() {
    index = 0;
    current = 0;

    emit updateProgressBar(0);

    // Add one more color and speed up
    pattern.push_back(arc4random() % 2);
    speedUp();

    QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOn);
    QTimer::singleShot(lightSpeed/speedValue * 1.5, this, &Model::lightOff);
}

/**
 * @brief Speeds up the game every round
 */
void Model::speedUp(){
    if(lightSpeed > 200) {
       lightSpeed -= 200;
    }
}

/**
 * @brief Slot for turning the light on color for a specific color.
 */
void Model::lightOn() {
    if(index < (int)pattern.size()) {
        color = pattern.at(index);
        index++;
        emit flashOn(color);
        QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOn);
    }
}

/**
 * @brief Slot for turning the light off color for a specific color.
 */
void Model::lightOff() {
    int size = (int)pattern.size();
    if(index < size){
        emit flashOff(color);
        QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOff);
    }

    else if(index == size){
        lastButtonFlash();
    }
}

/**
 * @brief Enables the color buttons when the last color of the round flashes.
 */
void Model::lastButtonFlash() {
    emit flashOff(color);
    emit enableColorButtons();
}

/**
 * @brief Checks if the user pressed on blue when they are supposed to. If not,
 * calls the game over method.
 */
void Model::blueClicked() {

    if(pattern.at(current) == 1) {
        current++;
        updateProgress((double)current);

        if(current == (int)pattern.size()) {
            QTimer::singleShot(1000, this, &Model::nextRound);
        }
    }

    else {
        gameOver();
    }
}

/**
 * @brief Checks if the user pressed on red when they are supposed to. If not,
 * calls the game over method.
 */
void Model::redClicked() {

     if(pattern.at(current) == 0) {
        current++;

        updateProgress((double)current);

        if(current == (int)pattern.size()) {
            QTimer::singleShot(1000, this, &Model::nextRound);
        }
    }
    else {
        gameOver();
    }
}

/**
 * @brief Updates the progress bar and displays the current percentage on a seperate
 * label
 * @param progressValue: current percentage of the progress completed
 */
void Model::updateProgress(double progressValue) {
    double progress = progressValue / (double) pattern.size() * 100;
    emit updateProgressBar(progress);
    emit updatePercentage(progress);
}

/**
 * @brief Updates progress bar and clears the pattern list when the player gets a game
 * over
 */
void Model::gameOver(){
    emit updateProgressBar(0);
    pattern.clear();
    lightSpeed = 1500;

    emit gameOverSign();
}

/**
 * @brief Slot for adjusting the speed of the rounds. Gets the value of the horizontal
 * slider and applies it to the logic of the speed.
 * @param value speed
 */
void Model::setSpeedValue(double value)
{
    speedValue = 1 + value / 2;
}
