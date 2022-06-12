#include <stdio.h>
 
int main () {

    enum DAY {a,b,c}day;
    //枚举名称定义枚举变量   var等价于day
    enum DAY var = c;
    printf("%d\n",var);

    //直接使用枚举变量
    day = a;
    printf("%d\n",day);


    return 0;


}