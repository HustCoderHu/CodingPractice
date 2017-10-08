#include <iostream>

using namespace std;

class Receiver {
public:
    Receiver() = default;
    ~Receiver() = default;
    void action(const char *str) {
        cout << str << endl;
    }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void exec() = 0;
};

class ConcreteCmd : public Command {
public:
    ConcreteCmd(Receiver *recver, const char *str)
        : mReceiver(recver), cmdStr(str) { }
    ~ConcreteCmd() = default;

    void exec() override {
        cout << "cmd exec" << endl;
        mReceiver->action(cmdStr.c_str());
    }
private:
    Receiver *mReceiver;
    string cmdStr;
};

class Invoker {
public:
    Invoker() = default;
    Invoker(Command *cmd) : mCmd(cmd) { }
    ~Invoker() = default;

    void calling(Command *cmd) {
        cout << "Invoker call" << endl;
        if (nullptr != cmd)
            cmd->exec();
    }
    void call() {
        cout << "Invoker call" << endl;
        if (nullptr != mCmd)
            mCmd->exec();
    }
private:
    Command *mCmd;
};

int main(int argc, char *argv[])
{
    Receiver recver;
    ConcreteCmd tvOn(&recver, "turn tv on");
    ConcreteCmd tvOff(&recver, "turn tv off");

    Invoker controller;
    controller.calling(&tvOn);
    cout << endl;
    controller.calling(&tvOff);

    return 0;
}

// blog.csdn.net/yanbober/article/details/45500113
// design-patterns.readthedocs.io/zh_CN/latest/behavioral_patterns/command.html
