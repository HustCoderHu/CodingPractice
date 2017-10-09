#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    return 0;
}

// shared_ptr
void testSharedPtr(void)
{
    auto p3 = make_shared<int>(42);
    auto p4 = make_shared<string>(10, '9');
    auto p5 = make_shared<int>();
}
