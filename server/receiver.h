#ifndef RECEIVER_H
#define RECEIVER_H

class Receiver : public Thread
{
private:
public:
    Receiver(Socket &socket);
    ~Receiver() = default;
    void run() override;
};
#endif // !RECEIVER_H