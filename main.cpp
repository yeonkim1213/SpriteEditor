/**
 * Main setup
 * @author Sasha Rybalkina - @crazyrussian123456
 * @author Yeon Kim - @yeonkim1213
 * @date October 27, 2023
 *
 * [Short description of the creative element]
 * Our Simon Game has a feature of "speed slider".
 * Slider allows the user to adjust the speed of the game by sliding the button.
 * The user can adjust the speed in 11 different modes.
 * Both beginners and experts can enjoy our Simon Game!
 */

#include "mainwindow.h"
#include <QApplication>
#include "Model.h"

/**
 * @brief main Starting point of Simon Game
 * @param argc Number of command-line arguments
 * @param argv Char array of command-line arguments
 * @return exit status
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    MainWindow w(model);
    w.show();
    return a.exec();
}
