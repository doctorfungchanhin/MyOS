#include <myos/kernel/IDT.hpp>

extern "C" void cpu_initialize();
extern "C" void callinterrupt();

void showA()
{
    char *video = reinterpret_cast<char*>(0xb8000);
    *(video) = 'A';
}


extern "C" int main() {
    //cpu_initialize();
    IDT idt;
    idt.AddInterrupt(32, 0, callinterrupt);

    //char *video = reinterpret_cast<char *>(0xb8000);
    //*(video) = 'A';

    return 0;
}
