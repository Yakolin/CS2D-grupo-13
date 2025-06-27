#ifndef STACK_NAVIGATOR_H_
#define STACK_NAVIGATOR_H_

#include <QWidget>


class StackNavigator {
public:
    virtual void add_widget(QWidget* page) = 0;
    virtual void go_to(QWidget* destine) = 0;
    virtual void back() = 0;
    virtual ~StackNavigator() {}
};
#endif
