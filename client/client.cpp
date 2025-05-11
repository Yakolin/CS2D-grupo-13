#include  "client.h"


int Client::run(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Counter Strike");
    mainWindow.resize(500, 500);

    QWidget *centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);

    
    QVBoxLayout *h_table = new QVBoxLayout(centralWidget);

    QPushButton *button_crear = new QPushButton("Crear Partida", &mainWindow);
    QPushButton *button_unirse = new QPushButton("Unirse a Partida", &mainWindow);


    h_table->addWidget(button_crear);
    h_table->addWidget(button_unirse);

    QObject::connect(button_crear, &QPushButton::clicked, [&]() {
        QMessageBox::information(&mainWindow, "Mensaje", "se creó una partida");
    });
    QObject::connect(button_unirse, &QPushButton::clicked, [&]() {
        QMessageBox::information(&mainWindow, "Mensaje", "se unió a una partida");
    });

    mainWindow.show();
    return app.exec();

}