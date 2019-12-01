;
; Source file: ./test/main.tc
; Target file: main.j
; Thu Nov 14 12:57:08 2019
;

.source ./test/main.tc
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
