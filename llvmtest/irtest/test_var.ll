define i32 @test() #0 {
entry:
  ;声明变量，在栈中分配空间
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  ;为变量赋值
  store i32 0, i32* %retval, align 4
  store i32 10, i32* %a, align 4
  store i32 11, i32* %b, align 4
  ;读取变量的值(%a为指针类型，load后%0变为值类型)
  %0 = load i32, i32* %a, align 4
  %1 = load i32, i32* %b, align 4
  ;加法运算
  %add = add nsw i32 %0, %1
  ret i32 %add
}






;;============================;;
; main function just for test  ;
;;============================;;
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() #0{
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @test()
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %2)
  ret i32 0
  }
  
declare i32 @printf(i8*, ...) #1