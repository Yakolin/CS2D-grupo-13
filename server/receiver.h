#ifndef RECEIVER_H
#define RECEIVER_H

class Receiver : public Thread
{
private:
public:
    void run() override;
};
#endif // !RECEIVER_H