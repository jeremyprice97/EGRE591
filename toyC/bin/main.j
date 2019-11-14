;
; Source file: C:/Users/gelbe/1Drive/OneDrive/Documents/VCU Class Documents/B-graduate/9-Fall 2019/EGRE591 - compiler construction/compiler_project/compilers/toyC/test/main.tc
; Target file: main.j
; Wed Nov 13 18:29:04 2019
;

.source C:/Users/gelbe/1Drive/OneDrive/Documents/VCU Class Documents/B-graduate/9-Fall 2019/EGRE591 - compiler construction/compiler_project/compilers/toyC/test/main.tc
.class public main
.super java/lang/Object

.method public <init>()V
	.limit stack 1
	.limit locals 1
	aload_0
	invokespecial java/lang/Object/<init>()V
	return
.end method

.method public static main([Ljava/lang/String;)V
	.limit stack 10
	.limit locals 10
	iload_1
	iconst_0
	istore_1
	iload_2
	iconst_2
	istore_2
	iload_1
	iload_2
	iconst_1
	iadd
	istore_1
	return
.end method
