#include "includes/parsing.h"


int main(int ac , char **av)
{

    if(ac == 2){
        printf("%s\n", split2(av[1])[0]);
        printf("%s\n", split2(av[1])[1]);
    }
    return 0;
}