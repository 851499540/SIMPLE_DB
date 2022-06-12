
#include <stdio.h>
 
int main ()
{

   typedef enum {
     STATEMENT_INSERT,
     STATEMENT_SELECT
   } StatementType;

   typedef struct {
    StatementType type;  //type 是枚举变量， 等价于 enum{ STATEMENT_INSERT,...}type;
   } Statement;

   Statement statement; //statement 是结构体变量，等价于struct {...}statement; (其中含有type变量，可以使用.访问)
   statement.type =STATEMENT_SELECT;
   printf("%d\n",statement.type );

//---------------------------解释，参考enum文件--------------------------
   struct Day
   {
      enum {mon=1, tue, wed, thu, fri, sat, sun } var;
   };
   //struct Day 等价于 int等类型定义参数，day时结构体变量（其中含有枚举便量var）
   struct Day day;
   day.var = wed;
   printf("%d\n", day.var);


//------------------------------结构体指针---------------------------

   struct Day *p1 = &day;////
                           //
                           ////  两者等价
   struct Day *p2 = NULL;  //  
   p2 = &day;            ////

   printf("结构体指针访问变量：%d ,%d\n",(*p1).var,(*p2).var );
   
//------------------------------结构体变量&作为函数输入---------------------------

   
   void f(Statement *statement) {
      statement->type = STATEMENT_INSERT;
      printf("结构体变量&作为函数输入:%d\n",statement->type);
   }
   f(&statement);
   

   return 0;
}
