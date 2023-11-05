; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@BUF = dso_local global [2 x [2304 x i32]] zeroinitializer, align 16
@board = dso_local local_unnamed_addr global ptr @BUF, align 8
@board_next = dso_local local_unnamed_addr global ptr getelementptr inbounds ([2 x [2304 x i32]], ptr @BUF, i64 0, i64 1, i64 0), align 8

; Function Attrs: nounwind sspstrong uwtable
define dso_local i32 @main(i32 noundef %0, ptr nocapture noundef readnone %1) local_unnamed_addr #0 {
  tail call void (...) @simBegin() #2
  %3 = load ptr, ptr @board, align 8, !tbaa !5
  %4 = getelementptr inbounds i32, ptr %3, i64 1
  store i32 1, ptr %4, align 4, !tbaa !9
  %5 = getelementptr inbounds i32, ptr %3, i64 66
  store i32 1, ptr %5, align 4, !tbaa !9
  %6 = getelementptr inbounds i32, ptr %3, i64 128
  store i32 1, ptr %6, align 4, !tbaa !9
  %7 = getelementptr inbounds i32, ptr %3, i64 129
  store i32 1, ptr %7, align 4, !tbaa !9
  %8 = getelementptr inbounds i32, ptr %3, i64 130
  store i32 1, ptr %8, align 4, !tbaa !9
  %9 = tail call i32 (...) @simShouldContinue() #2
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %128, label %11

11:                                               ; preds = %2, %23
  %12 = phi i1 [ %24, %23 ], [ true, %2 ]
  %13 = phi i32 [ %25, %23 ], [ 0, %2 ]
  %14 = add nsw i32 %13, -1
  %15 = icmp ult i32 %14, 36
  %16 = shl nuw nsw i32 %14, 6
  %17 = shl i32 %13, 6
  %18 = icmp ult i32 %13, 35
  %19 = add nuw nsw i32 %17, 64
  br label %26

20:                                               ; preds = %107
  %21 = add nuw nsw i32 %13, 1
  %22 = icmp eq i32 %21, 36
  br i1 %22, label %123, label %23

23:                                               ; preds = %20, %123
  %24 = phi i1 [ %18, %20 ], [ true, %123 ]
  %25 = phi i32 [ %21, %20 ], [ 0, %123 ]
  br label %11, !llvm.loop !11

26:                                               ; preds = %107, %11
  %27 = phi i32 [ 0, %11 ], [ %59, %107 ]
  %28 = load ptr, ptr @board, align 8
  %29 = add nsw i32 %27, -1
  %30 = icmp ult i32 %29, 64
  %31 = select i1 %15, i1 %30, i1 false
  br i1 %31, label %32, label %37

32:                                               ; preds = %26
  %33 = add nuw nsw i32 %29, %16
  %34 = zext i32 %33 to i64
  %35 = getelementptr inbounds i32, ptr %28, i64 %34
  %36 = load i32, ptr %35, align 4, !tbaa !9
  br label %41

37:                                               ; preds = %26
  br i1 %15, label %41, label %38

38:                                               ; preds = %37
  %39 = add nuw nsw i32 %27, 1
  %40 = icmp ne i32 %27, 63
  br label %57

41:                                               ; preds = %37, %32
  %42 = phi i32 [ %36, %32 ], [ 0, %37 ]
  %43 = or i32 %27, %16
  %44 = zext i32 %43 to i64
  %45 = getelementptr inbounds i32, ptr %28, i64 %44
  %46 = load i32, ptr %45, align 4, !tbaa !9
  %47 = add nsw i32 %46, %42
  %48 = add nuw nsw i32 %27, 1
  %49 = icmp ne i32 %27, 63
  %50 = select i1 %15, i1 %49, i1 false
  br i1 %50, label %51, label %57

51:                                               ; preds = %41
  %52 = add nuw nsw i32 %48, %16
  %53 = zext i32 %52 to i64
  %54 = getelementptr inbounds i32, ptr %28, i64 %53
  %55 = load i32, ptr %54, align 4, !tbaa !9
  %56 = add nsw i32 %55, %47
  br label %57

57:                                               ; preds = %51, %41, %38
  %58 = phi i1 [ true, %51 ], [ %49, %41 ], [ %40, %38 ]
  %59 = phi i32 [ %48, %51 ], [ %48, %41 ], [ %39, %38 ]
  %60 = phi i32 [ %56, %51 ], [ %47, %41 ], [ 0, %38 ]
  %61 = select i1 %12, i1 %30, i1 false
  br i1 %61, label %62, label %68

62:                                               ; preds = %57
  %63 = add nuw nsw i32 %29, %17
  %64 = zext i32 %63 to i64
  %65 = getelementptr inbounds i32, ptr %28, i64 %64
  %66 = load i32, ptr %65, align 4, !tbaa !9
  %67 = add nsw i32 %66, %60
  br label %69

68:                                               ; preds = %57
  br i1 %12, label %69, label %83

69:                                               ; preds = %68, %62
  %70 = phi i32 [ %67, %62 ], [ %60, %68 ]
  %71 = or i32 %27, %17
  %72 = zext i32 %71 to i64
  %73 = getelementptr inbounds i32, ptr %28, i64 %72
  %74 = load i32, ptr %73, align 4, !tbaa !9
  %75 = add nsw i32 %74, %70
  %76 = select i1 %12, i1 %58, i1 false
  br i1 %76, label %77, label %83

77:                                               ; preds = %69
  %78 = add nuw nsw i32 %59, %17
  %79 = zext i32 %78 to i64
  %80 = getelementptr inbounds i32, ptr %28, i64 %79
  %81 = load i32, ptr %80, align 4, !tbaa !9
  %82 = add nsw i32 %81, %75
  br label %83

83:                                               ; preds = %77, %69, %68
  %84 = phi i32 [ %82, %77 ], [ %75, %69 ], [ %60, %68 ]
  %85 = select i1 %18, i1 %30, i1 false
  br i1 %85, label %86, label %92

86:                                               ; preds = %83
  %87 = add nuw nsw i32 %29, %19
  %88 = zext i32 %87 to i64
  %89 = getelementptr inbounds i32, ptr %28, i64 %88
  %90 = load i32, ptr %89, align 4, !tbaa !9
  %91 = add nsw i32 %90, %84
  br label %93

92:                                               ; preds = %83
  br i1 %18, label %93, label %107

93:                                               ; preds = %92, %86
  %94 = phi i32 [ %91, %86 ], [ %84, %92 ]
  %95 = or i32 %27, %19
  %96 = zext i32 %95 to i64
  %97 = getelementptr inbounds i32, ptr %28, i64 %96
  %98 = load i32, ptr %97, align 4, !tbaa !9
  %99 = add nsw i32 %98, %94
  %100 = select i1 %18, i1 %58, i1 false
  br i1 %100, label %101, label %107

101:                                              ; preds = %93
  %102 = add nuw nsw i32 %59, %19
  %103 = zext i32 %102 to i64
  %104 = getelementptr inbounds i32, ptr %28, i64 %103
  %105 = load i32, ptr %104, align 4, !tbaa !9
  %106 = add nsw i32 %105, %99
  br label %107

107:                                              ; preds = %101, %93, %92
  %108 = phi i32 [ %106, %101 ], [ %99, %93 ], [ %84, %92 ]
  %109 = or i32 %27, %17
  %110 = zext i32 %109 to i64
  %111 = getelementptr inbounds i32, ptr %28, i64 %110
  %112 = load i32, ptr %111, align 4, !tbaa !9
  %113 = icmp eq i32 %112, 0
  %114 = icmp eq i32 %108, 3
  %115 = add i32 %108, -3
  %116 = icmp ult i32 %115, 2
  %117 = select i1 %113, i1 %114, i1 %116
  %118 = zext i1 %117 to i32
  %119 = load ptr, ptr @board_next, align 8, !tbaa !5
  %120 = getelementptr inbounds i32, ptr %119, i64 %110
  store i32 %118, ptr %120, align 4, !tbaa !9
  %121 = select i1 %117, i32 0, i32 16777215
  tail call void @simSetPixel(i32 noundef %27, i32 noundef %13, i32 noundef %121) #2
  %122 = icmp ult i32 %59, 64
  br i1 %122, label %26, label %20, !llvm.loop !13

123:                                              ; preds = %20
  %124 = load ptr, ptr @board, align 8, !tbaa !5
  %125 = load ptr, ptr @board_next, align 8, !tbaa !5
  store ptr %125, ptr @board, align 8, !tbaa !5
  store ptr %124, ptr @board_next, align 8, !tbaa !5
  tail call void (...) @simFlush() #2
  %126 = tail call i32 (...) @simShouldContinue() #2
  %127 = icmp eq i32 %126, 0
  br i1 %127, label %128, label %23

128:                                              ; preds = %123, %2
  tail call void (...) @simEnd() #2
  ret i32 0
}

declare void @simBegin(...) local_unnamed_addr #1

declare i32 @simShouldContinue(...) local_unnamed_addr #1

declare void @simFlush(...) local_unnamed_addr #1

declare void @simEnd(...) local_unnamed_addr #1

declare void @simSetPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

attributes #0 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 16.0.6"}
!5 = !{!6, !6, i64 0}
!6 = !{!"any pointer", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = !{!10, !10, i64 0}
!10 = !{!"int", !7, i64 0}
!11 = distinct !{!11, !12}
!12 = !{!"llvm.loop.mustprogress"}
!13 = distinct !{!13, !12}
