/**
 * @mainpage
 * @author sharikac, keenanbu
 * @brief This is a C++ program with a Qt-based interface which can visualise 3D
wireframe models
 * @version 0.1
 * @date 2024-01-20
 * @warning This program is an educational project for School 21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <QApplication>
#include <QScreen>

#include "view/mainwindow.h"

/// @brief Program entry point
/// @param argc
/// @param argv
/// @return
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow w;

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int screenHeight = screenGeometry.height();
  int screenWidth = screenGeometry.width();
  // Get window size
  int windowWidth = w.width();
  int windowHeight = w.height();
  // Calculate coordinates to center the window
  int x = (screenWidth - windowWidth) / 2;
  int y = (screenHeight - windowHeight) / 2;
  w.move(x, y);
  w.setWindowIcon(QIcon(":logo/logo.png"));
  w.show();
  return a.exec();
}
