#include "ButtonsCreator.h"
// Add_button tiene un standar de botones para Qt ahora mismo
//  Si deciden cambiar el estilo es desde aca
QPushButton* ButtonsCreator::create_button(const QString& text, std::function<void()> callback,
                                           const QString& style) {
    QPushButton* button = new QPushButton(text);
    button->setFixedSize(200, 50);
    button->setStyleSheet(style);
    QObject::connect(button, &QPushButton::clicked, std::move(callback));
    return button;
}
void ButtonsCreator::add_button(QVBoxLayout* layout, const QString& text,
                                std::function<void()> callback, const QString& style) {
    QPushButton* button = create_button(text, callback, style);
    layout->addWidget(button, 0, Qt::AlignHCenter);
}
