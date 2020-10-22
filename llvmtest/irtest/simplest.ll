
define i32 @test(){
  ret i32 10
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