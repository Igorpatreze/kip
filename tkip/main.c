#include "tkip.h"
#include "stdio.h"

int main(void) {
    int i;
    for(i=0;i<16;i++)
    {
        k_clear();
        k_color(k_info_colors()[i]);
        k_write(i+2,2,"#");
        k_sleep(300);
    }

    int cont = 0;
    char e = 'a';
    char c ;
    while(1)
    {
//        c = k_peek();
//        if(c){
//            e = c;
//            cont=0;
//        }
        e = k_wait();
        cont++;
        k_clear();
        k_write(0,cont,"%d",e);
        k_sleep(500);
    }
    k_wait();
    return 0;
}
