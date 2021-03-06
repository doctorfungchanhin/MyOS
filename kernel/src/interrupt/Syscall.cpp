#include "Syscall.hpp"
#include  <clib.h>
#include <myos/kernel/Process.hpp>
#include <myos/kernel/Terminals.hpp>
#include <myos/kernel/FAT12.hpp>

extern myos::kernel::Process processes;
extern myos::kernel::Terminals terminal;
extern myos::kernel::Keyboard keyboard;

using myos::kernel::PCB;

namespace myos {
namespace kernel {
namespace Syscall {
/* Parameter     Function
 * 1~4           printSomething
 * 5             print a string
 * 7             create a process (fork())
 * 90            KillProcess(exit())
 * */
void kprintf(char* str);

void windmill() {
    //windwill
    /*
    static int state = 1;
    static char *videomem_windwill = reinterpret_cast<char *>(0xb8000 + 12000 + 2 * (5 * 80 + 20));
    if (state == 5) {
        *(videomem_windwill) = '-';
        state = 1;
    } else {
        if (state == 1)
            *(videomem_windwill) = '|';
        else if (state == 2)
            *(videomem_windwill) = '/';
        else if (state == 3)
            *(videomem_windwill) = '-';
        else if (state == 4)
            *(videomem_windwill) = '\\';
        ++state;
    }
     */

    terminal.set_x_y(3, 20, 5);
    static int state1 = 1;
    char* c = const_cast<char *>(" ");
    if(state1 == 5)
    {
        c[0] = '-';
        state1 = 1;
    }
    else{
        if(state1 == 1)
            c[0] = '|';
        else if(state1 == 2)
            c[0] = '/';
        else if(state1 == 3)
            c[0] = '-';
        else if(state1 == 4)
            c[0] = '\\';
    }
    ++state1;
    terminal.disp_str(3, c, 1);
}

void windmill2() {
    /*static int state2 = 1;
    static char *videomem_windwill2 = reinterpret_cast<char *>(0xb8000 + 12000 + 2 * (10 * 80 + 20));
    if (state2 == 5) {
        *(videomem_windwill2) = '-';
        state2 = 1;
    } else {
        if (state2 == 1)
            *(videomem_windwill2) = '|';
        else if (state2 == 2)
            *(videomem_windwill2) = '/';
        else if (state2 == 3)
            *(videomem_windwill2) = '-';
        else if (state2 == 4)
            *(videomem_windwill2) = '\\';
        ++state2;
    }
     */
    terminal.set_x_y(3, 20, 10);
    static int state2 = 1;
    char* c = const_cast<char *>(" ");
    if(state2 == 5)
    {
        c[0] = '-';
        state2 = 1;
    }
    else{
        if(state2 == 1)
          c[0] = '|';
        else if(state2 == 2)
            c[0] = '/';
        else if(state2 == 3)
            c[0] = '-';
        else if(state2 == 4)
            c[0] = '\\';
    }
    ++state2;
    terminal.disp_str(3, c, 1);
}

//every 100 clock interrupts have a flash
int helloworld_count = 200;

void print_Hello() {
    if (helloworld_count != 100)
        return;
    char *videomem_Hello = reinterpret_cast<char *>(0xb8000 + 2760);
    for (int i = 0; i < 5; ++i) {
        *(videomem_Hello + 60) = ' ';
        videomem_Hello += 2;
    }
    videomem_Hello -= 10;
    char str[6] = "Hello";
    for (int i = 0; i < 5; ++i) {
        *(videomem_Hello) = str[i];
        videomem_Hello += 2;
    }
}

void print_World() {
    --helloworld_count;
    if (helloworld_count)
        return;
    char *videomem_World = reinterpret_cast<char *>(0xb8000 + 2820);
    for (int i = 0; i < 5; ++i) {
        *(videomem_World - 60) = ' ';
        videomem_World += 2;
    }
    videomem_World -= 10;
    char str[6] = "World";
    for (int i = 0; i < 5; ++i) {
        *(videomem_World) = str[i];
        videomem_World += 2;
    }
    helloworld_count = 200;
}

void kill_process(myos::kernel::PCB *progress) {
    //processes.exchange(progress);
    processes.kill(progress);
}


//every 50 clock cycles print a chararter

void print1() {
    static char *str1 = const_cast<char *>("I Love Studying\n");
    terminal.disp_str(1, str1, strlen(str1));
    /*static int index1 = 0;
    static int time_count1 = 0;
    ++time_count1;
    if (time_count1 != 20)
        return;
    if (index1 == 6) {
        index1 = 0;
        videomem1 = reinterpret_cast<char *>(0xb8000 + 2 * (5 * 80 + 17));
        for (int i = 0; i < 6; ++i)
            *(videomem1 + i * 2) = ' ';
    }
    *videomem1 = str1[index1];
    ++index1;
    videomem1 += 2;
    time_count1 = 0;

    static int y1 = 0;
    static int time_count1 = 0;
    ++time_count1;
    if(time_count1 != 20)
        return;
    char *videomem1 = reinterpret_cast<char*>(0xb8000 + 2 * (y1 * 80));
    for(int i = 0; i < strlen(str1); ++i)
    {
        *videomem1 = str1[i];
        videomem1 += 2;
    }

    time_count1 = 0;
    ++y1;
    */
}

void print2() {
    static char *str2 = const_cast<char *>("Operating System!\n");
    terminal.disp_str(2, str2, strlen(str2));
    /*static char y2 = 0;
    char *videomem2 = reinterpret_cast<char *>(0xb8000 + 8000 + 2 * (y2 * 80));
    static int time_count2 = 0;
    ++time_count2;
    if (time_count2 != 20)
        return;
    for(int i = 0; i < strlen(str2); ++i)
    {
        *videomem2 = str2[i];
        videomem2 += 2;
    }
    time_count2 = 0;
    ++y2;
     */
}

void print3() {
    static char *str3 = const_cast<char *>("Operating");
    static char *videomem3 = reinterpret_cast<char *>(0xb8000 + 2 * (17 * 80 + 17));
    static int index3 = 0;
    static int time_count3 = 0;
    ++time_count3;
    if (time_count3 != 20)
        return;
    if (index3 == 9) {
        index3 = 0;
        videomem3 = reinterpret_cast<char *>(0xb8000 + 2 * (17 * 80 + 17));
        for (int i = 0; i < 9; ++i)
            *(videomem3 + i * 2) = ' ';
    }
    *videomem3 = str3[index3];
    ++index3;
    videomem3 += 2;
    time_count3 = 0;
}

void print4() {
    static char *str4 = const_cast<char *>("System");
    static char *videomem4 = reinterpret_cast<char *>(0xb8000 + 2 * (17 * 80 + 60));
    static int index4 = 0;
    static int time_count4 = 0;
    ++time_count4;
    if (time_count4 != 20)
        return;
    if (index4 == 6) {
        index4 = 0;
        videomem4 = reinterpret_cast<char *>(0xb8000 + 2 * (17 * 80 + 60));
        for (int i = 0; i < 6; ++i)
            *(videomem4 + i * 2) = ' ';
    }
    *videomem4 = str4[index4];
    ++index4;
    videomem4 += 2;
    time_count4 = 0;
}

void create_new_process(){
    static unsigned int now_process = 0;
    if (now_process >= 3)
        return;
    now_process++;
    char *name = const_cast<char *>("LETTER0 EXE\0");
    name[6] = static_cast<char>(49 + now_process);
    
    int load = myos::kernel::FAT12::Find_File(name);
    //加载用户程序
    if (load != -1) {
        uintptr_t userCR3 = processes.create(name);
        //myos::kernel::FAT12::FAT12(name, userCR3);
        
        //entry = *(unsigned int *) ((unsigned int *) load + 0x18);
        //processes.create(*(reinterpret_cast<uint32_t *>(load + 0x18)));
        //((void (*)()) entry)();
    } else{
        kprintf(const_cast<char *>("This file is not exist.\n"));
    }
}

void kprintf(char *str) {
    terminal.disp_str(processes.get_running_page(), str, strlen(str));
}

void syscall(PCB *progress) {
    switch (progress->eax) {
        case 1:
            print1();
            break;
        case 2:
            print2();
            break;
        case 3:
            windmill2();
            windmill();
            break;
        case 4:
           break;
        case 5:     //print a string
            kprintf(reinterpret_cast<char*>(progress->ebx));
            break;
        case 6:
            create_new_process();
            break;
//        case 5:
//            kprintf(reinterpret_cast<char *>(progress->ebx));
//            break;
//        case 6:
//             __cpp_create_new_process();
//            break;
        case 90:
            kill_process(progress);
            break;
        default:
            break;
    };
}

}
}
}

//print_info
//static char info[40] = "16337062FENGZHENXUAN16337067GUANPEIDONG";
//static int info_x = 0;
//static int info_y = 0;
//static int index = 0;
//static int info_count = 40;
/*
 * 1 right down
 * 2 right up
 * 3 left down
 * 4 left up

static int info_state = 1;
void print_info() {
//    --info_count;
//    if (info_count)
//        return;
    char *videomem_info = reinterpret_cast<char *>(0xb8000 + 2 * (80 * (info_y + 1) + info_x + 40));
    *(videomem_info) = info[index++];
    if (index == 40)
        index = 0;
    if (info_state == 1) {
        ++info_x;
        ++info_y;
        if (info_x == 37 && info_y == 11)
            info_state = 4;
        else if (info_y == 11)
            info_state = 2;
        else if (info_x == 37)
            info_state = 3;
    } else if (info_state == 2) {
        ++info_x;
        --info_y;
        if (info_x == 37 && info_y == 0)
            info_state = 3;
        else if (info_x == 37)
            info_state = 4;
        else if (info_y == 0)
            info_state = 1;
    } else if (info_state == 3) {
        --info_x;
        ++info_y;
        if (info_x == 0 && info_y == 11)
            info_state = 2;
        else if (info_x == 0)
            info_state = 1;
        else if (info_y == 11)
            info_state = 4;
    } else if (info_state == 4) {
        --info_x;
        --info_y;
        if (info_x == 0 && info_y == 0)
            info_state = 1;
        else if (info_x == 0)
            info_state = 2;
        else if (info_y == 0)
            info_state = 3;
    }
    info_count = 40;
}
*/
//void kprintf(char* str)
//{
//    terminal.disp_str(processes.get_running(), str, strlen(str));
//}
//void __cpp_create_new_process() {
//    static unsigned int now_process = 0;
//    if (now_process >= 3)
//        return;
//    char *userName = const_cast<char *>("LETTER0 EXE\0");
//    userName[6] = static_cast<char>(49 + now_process);
//    uintptr_t load = reinterpret_cast<uintptr_t>
//    (myos::kernel::FAT12::FAT12(userName));
//    unsigned int entry;
//    //加载用户程序
//    if (load > 0) {
//        //entry = *(unsigned int *) ((unsigned int *) load + 0x18);
//        processes.create(*(reinterpret_cast<uint32_t *>(load + 0x18)));
//        //((void (*)()) entry)();
//    }
//    now_process++;
//    keyboard.clean();
//}