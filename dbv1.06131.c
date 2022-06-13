/*
1.支持插入一行并打印所有行的功能
  insert 1 cstack foo@bar.com
2.尚未写入硬盘
3.单编码表
  column 	type
  id 	integer
  username 	varchar(32)
  email 	varchar(255)
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义输入缓存的结构体
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

//--------------定义枚举-------------
//1.元命令(.为前缀的)
typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

//2.执行语句结果判断(成功还是失败)
typedef enum { 
  PREPARE_SUCCESS, 
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

//3.执行具体语句判断(select还是insert)
typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

//储存具体执行语句的结构体
typedef struct {
  StatementType type;
} Statement;

//输入缓存指针通过函数返回
InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

//命令行在新行重复打印db>
void print_prompt() { printf("db > "); }

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

//元命令执行函数
MetaCommandResult do_meta_command(InputBuffer* inputer_buffer){
  if (strcmp(inputer_buffer->buffer, ".exit")==0){
    close_input_buffer(inputer_buffer);
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

//sql动作判断执行函数
PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement ){
  if (strncmp(input_buffer->buffer, "insert", 6) ==0){
    statement->type =STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }
  if (strcmp(input_buffer->buffer, "select") == 0){
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

//sql语句执行函数
void execute_statement(Statement* statement) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      printf("This is where we would do an insert.\n");
      break;
    case (STATEMENT_SELECT): {
      printf("This is where we would do a select.\n");
      break;
    }
  }
}


//主函数
int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);
    //元命令单独处理，对数据库的操作(退出数据库)
    if (input_buffer->buffer[0] == '.'){
      switch (do_meta_command(input_buffer)) {
        case(META_COMMAND_SUCCESS):
          continue;
        case(META_COMMAND_UNRECOGNIZED_COMMAND):
          printf("Unrecognized command '%s'\n", input_buffer->buffer);
          continue;
      }
    }
    //确定sql语句是枚举中的哪一选项(sql语句处理)；对数据的操作(增删改查)
    //1.先赋予枚举变量
    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at start of '%s' \n",input_buffer->buffer);
        continue;
    }
    //2.具体执行
    execute_statement(&statement);
    printf("Executed.\n");
  }
}
