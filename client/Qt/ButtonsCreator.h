#ifndef BUTTONS_CREATOR_H_
#define BUTTONS_CREATOR_H_
#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QFont>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QStackedWidget>
#include <QString>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>
#include <iostream>

#define DEFAULT_STYLE                                                          \
  "QPushButton { background-color: transparent; color:rgb(255, 255, 255); font-size:     \
  16px; font-weight: bold; }"

#define LOBBY_STYLE                                                            \
  "QPushButton { background-color: rgb(36, 36, 36); color: rgb(255, 255, 255); font-size: 14px;      \
   font-weight: bold;border-radius: 25px;padding: 8px 16px; border: 2px solid rgb(0, 132, 255);}"

#define ITEM_STYLE                                                             \
  "QPushButton { background-color: rgba(0, 0, 0, 0.35); color: rgb(255, 255, 255); font-size: 14px;      \
    padding: 2px 10px; border: 1px solid rgb(0, 132, 255);}"
#define LOBBY_LABEL_STYLE                                                      \
  "QLabel { color: rgb(255, 255, 255); font-size: 14px; font-weight: bold;    \
    background-color: rgb(18, 18, 18); padding: 4px 8px; border-radius: 10px; }"
#define LOBBY_LABEL_STYLE2                                                     \
  "QLabel { color: rgb(255, 255, 255); font-size: 14px; font-weight: bold;    \
    background-color: rgba(18, 18, 18, 0); padding: 4px 8px; border: 1px solid rgb(0, 204, 255); border-radius: 10px;}"

#define LOBBY_COMBO_STYLE                                                      \
  "QComboBox { color: rgb(255, 255, 255); font-size: 14px; font-weight: bold;    \
    background-color: rgba(18, 18, 18, 0.69); padding: 4px 8px; border: 1px solid rgb(0, 140, 175); border-radius: 10px;}"

#define LOBBY_IMAGES                                                           \
  R"(QLabel {border: 1px solid rgba(0, 238, 255, 0.14);border-radius: 50px;padding: 4px; background-color:rgba(68, 0, 255, 0.2);})"
class ButtonsCreator {
public:
  ButtonsCreator() = default;
  ~ButtonsCreator() = default;
  QPushButton *create_button(const QString &text,
                             std::function<void()> callback,
                             const QString &style = DEFAULT_STYLE);
  void add_button(QVBoxLayout *layout, const QString &text,
                  std::function<void()> callback,
                  const QString &style = DEFAULT_STYLE);
};
#endif // BUTTONS_CREATOR_H_