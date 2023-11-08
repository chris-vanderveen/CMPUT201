#include <stdio.h>
void a_cute_function(int a){
    if (a != 0) {
        a_cute_function(a / 2);
        printf("%c", '0' + a % 2);
    }
}


int main(){
    a_cute_function(10);
    return 0;
}
