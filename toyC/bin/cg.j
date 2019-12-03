;
; Source file: /mnt/c/school/fall19/egre591/proj/jasmin-2.4/cg.tc
; Target file: cg.j
; Tue Dec  3 14:38:41 2019
;

.source /mnt/c/school/fall19/egre591/proj/jasmin-2.4/cg.tc
.class public cg
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
	getstatic java/lang/System/out Ljava/io/PrintStream;
	astore 4
	iconst_2
	istore_2
	iconst_3
	istore_2
	iload_2
	istore_3
	iload_3
	istore_1
	aload 4
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	aload 4
	iload_2
	invokevirtual java/io/PrintStream/println(I)V
	aload 4
	iload_3
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
