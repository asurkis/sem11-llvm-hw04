; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@BUF = dso_local global [2 x [2304 x i32]] zeroinitializer, align 16
@board = dso_local global ptr @BUF, align 8
@board_next = dso_local global ptr getelementptr (i8, ptr @BUF, i64 9216), align 8

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define dso_local i32 @main(i32 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
  store ptr %1, ptr %5, align 8
  call void (...) @simBegin()
  call void @initBoard()
  br label %7

7:                                                ; preds = %10, %2
  %8 = call i32 (...) @simShouldContinue()
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %10, label %14

10:                                               ; preds = %7
  call void @fillNextState()
  %11 = load ptr, ptr @board, align 8
  store ptr %11, ptr %6, align 8
  %12 = load ptr, ptr @board_next, align 8
  store ptr %12, ptr @board, align 8
  %13 = load ptr, ptr %6, align 8
  store ptr %13, ptr @board_next, align 8
  call void (...) @simFlush()
  br label %7, !llvm.loop !6

14:                                               ; preds = %7
  call void (...) @simEnd()
  ret i32 0
}

declare void @simBegin(...) #1

declare i32 @simShouldContinue(...) #1

declare void @simFlush(...) #1

declare void @simEnd(...) #1

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define internal void @initBoard() #0 {
  %1 = load ptr, ptr @board, align 8
  %2 = getelementptr inbounds i32, ptr %1, i64 1
  store i32 1, ptr %2, align 4
  %3 = load ptr, ptr @board, align 8
  %4 = getelementptr inbounds i32, ptr %3, i64 66
  store i32 1, ptr %4, align 4
  %5 = load ptr, ptr @board, align 8
  %6 = getelementptr inbounds i32, ptr %5, i64 128
  store i32 1, ptr %6, align 4
  %7 = load ptr, ptr @board, align 8
  %8 = getelementptr inbounds i32, ptr %7, i64 129
  store i32 1, ptr %8, align 4
  %9 = load ptr, ptr @board, align 8
  %10 = getelementptr inbounds i32, ptr %9, i64 130
  store i32 1, ptr %10, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define internal void @fillNextState() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  br label %6

6:                                                ; preds = %68, %0
  %7 = load i32, ptr %1, align 4
  %8 = icmp slt i32 %7, 36
  br i1 %8, label %9, label %71

9:                                                ; preds = %6
  store i32 0, ptr %2, align 4
  br label %10

10:                                               ; preds = %64, %9
  %11 = load i32, ptr %2, align 4
  %12 = icmp slt i32 %11, 64
  br i1 %12, label %13, label %67

13:                                               ; preds = %10
  %14 = load i32, ptr %1, align 4
  %15 = load i32, ptr %2, align 4
  %16 = call i32 @calcNeighbors(i32 noundef %14, i32 noundef %15)
  store i32 %16, ptr %3, align 4
  %17 = load i32, ptr %1, align 4
  %18 = mul nsw i32 %17, 64
  %19 = load i32, ptr %2, align 4
  %20 = add nsw i32 %18, %19
  store i32 %20, ptr %4, align 4
  %21 = load ptr, ptr @board, align 8
  %22 = load i32, ptr %4, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds i32, ptr %21, i64 %23
  %25 = load i32, ptr %24, align 4
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %27, label %44

27:                                               ; preds = %13
  %28 = load i32, ptr %3, align 4
  %29 = icmp eq i32 %28, 3
  br i1 %29, label %33, label %30

30:                                               ; preds = %27
  %31 = load i32, ptr %3, align 4
  %32 = icmp eq i32 %31, 4
  br label %33

33:                                               ; preds = %30, %27
  %34 = phi i1 [ true, %27 ], [ %32, %30 ]
  %35 = zext i1 %34 to i32
  store i32 %35, ptr %5, align 4
  %36 = load i32, ptr %5, align 4
  %37 = icmp ne i32 %36, 0
  %38 = zext i1 %37 to i64
  %39 = select i1 %37, i32 1, i32 0
  %40 = load ptr, ptr @board_next, align 8
  %41 = load i32, ptr %4, align 4
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds i32, ptr %40, i64 %42
  store i32 %39, ptr %43, align 4
  br label %53

44:                                               ; preds = %13
  %45 = load i32, ptr %3, align 4
  %46 = icmp eq i32 %45, 3
  %47 = zext i1 %46 to i64
  %48 = select i1 %46, i32 1, i32 0
  %49 = load ptr, ptr @board_next, align 8
  %50 = load i32, ptr %4, align 4
  %51 = sext i32 %50 to i64
  %52 = getelementptr inbounds i32, ptr %49, i64 %51
  store i32 %48, ptr %52, align 4
  br label %53

53:                                               ; preds = %44, %33
  %54 = load i32, ptr %2, align 4
  %55 = load i32, ptr %1, align 4
  %56 = load ptr, ptr @board_next, align 8
  %57 = load i32, ptr %4, align 4
  %58 = sext i32 %57 to i64
  %59 = getelementptr inbounds i32, ptr %56, i64 %58
  %60 = load i32, ptr %59, align 4
  %61 = icmp ne i32 %60, 0
  %62 = zext i1 %61 to i64
  %63 = select i1 %61, i32 0, i32 16777215
  call void @simSetPixel(i32 noundef %54, i32 noundef %55, i32 noundef %63)
  br label %64

64:                                               ; preds = %53
  %65 = load i32, ptr %2, align 4
  %66 = add nsw i32 %65, 1
  store i32 %66, ptr %2, align 4
  br label %10, !llvm.loop !8

67:                                               ; preds = %10
  br label %68

68:                                               ; preds = %67
  %69 = load i32, ptr %1, align 4
  %70 = add nsw i32 %69, 1
  store i32 %70, ptr %1, align 4
  br label %6, !llvm.loop !9

71:                                               ; preds = %6
  ret void
}

; Function Attrs: noinline nounwind optnone sspstrong uwtable
define internal i32 @calcNeighbors(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  store i32 0, ptr %5, align 4
  store i32 -1, ptr %6, align 4
  br label %12

12:                                               ; preds = %63, %2
  %13 = load i32, ptr %6, align 4
  %14 = icmp sle i32 %13, 1
  br i1 %14, label %15, label %66

15:                                               ; preds = %12
  store i32 -1, ptr %7, align 4
  br label %16

16:                                               ; preds = %59, %15
  %17 = load i32, ptr %7, align 4
  %18 = icmp sle i32 %17, 1
  br i1 %18, label %19, label %62

19:                                               ; preds = %16
  %20 = load i32, ptr %3, align 4
  %21 = load i32, ptr %6, align 4
  %22 = add nsw i32 %20, %21
  store i32 %22, ptr %8, align 4
  %23 = load i32, ptr %4, align 4
  %24 = load i32, ptr %7, align 4
  %25 = add nsw i32 %23, %24
  store i32 %25, ptr %9, align 4
  %26 = load i32, ptr %8, align 4
  %27 = icmp sle i32 0, %26
  br i1 %27, label %28, label %31

28:                                               ; preds = %19
  %29 = load i32, ptr %8, align 4
  %30 = icmp slt i32 %29, 36
  br label %31

31:                                               ; preds = %28, %19
  %32 = phi i1 [ false, %19 ], [ %30, %28 ]
  %33 = zext i1 %32 to i32
  store i32 %33, ptr %10, align 4
  %34 = load i32, ptr %9, align 4
  %35 = icmp sle i32 0, %34
  br i1 %35, label %36, label %39

36:                                               ; preds = %31
  %37 = load i32, ptr %9, align 4
  %38 = icmp slt i32 %37, 64
  br label %39

39:                                               ; preds = %36, %31
  %40 = phi i1 [ false, %31 ], [ %38, %36 ]
  %41 = zext i1 %40 to i32
  store i32 %41, ptr %11, align 4
  %42 = load i32, ptr %10, align 4
  %43 = icmp ne i32 %42, 0
  br i1 %43, label %44, label %58

44:                                               ; preds = %39
  %45 = load i32, ptr %11, align 4
  %46 = icmp ne i32 %45, 0
  br i1 %46, label %47, label %58

47:                                               ; preds = %44
  %48 = load ptr, ptr @board, align 8
  %49 = load i32, ptr %8, align 4
  %50 = mul nsw i32 %49, 64
  %51 = load i32, ptr %9, align 4
  %52 = add nsw i32 %50, %51
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds i32, ptr %48, i64 %53
  %55 = load i32, ptr %54, align 4
  %56 = load i32, ptr %5, align 4
  %57 = add nsw i32 %56, %55
  store i32 %57, ptr %5, align 4
  br label %58

58:                                               ; preds = %47, %44, %39
  br label %59

59:                                               ; preds = %58
  %60 = load i32, ptr %7, align 4
  %61 = add nsw i32 %60, 1
  store i32 %61, ptr %7, align 4
  br label %16, !llvm.loop !10

62:                                               ; preds = %16
  br label %63

63:                                               ; preds = %62
  %64 = load i32, ptr %6, align 4
  %65 = add nsw i32 %64, 1
  store i32 %65, ptr %6, align 4
  br label %12, !llvm.loop !11

66:                                               ; preds = %12
  %67 = load i32, ptr %5, align 4
  ret i32 %67
}

declare void @simSetPixel(i32 noundef, i32 noundef, i32 noundef) #1

attributes #0 = { noinline nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 16.0.6"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
