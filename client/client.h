#ifndef CLIENT_H
#define CLIENT_H
#include "controller.h"
#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Client {
public:
    int run( int argc , char *argv[]);
};

#endif // CLIENT_H