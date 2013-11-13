#include "kip.h"

int main(){
    k_open(800, 600, "Janela");
    pen_setd(8);
    pen_fd(100);
    k_sleep(2000);
    return 0;
}
