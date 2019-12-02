;
; Source file: /mnt/c/school/fall19/egre591/proj/jasmin-2.4/cg.tc
; Target file: cg.j
; Sun Dec  1 23:43:26 2019
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
	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore_3
	getstatic java/lang/System/out Ljava/io/PrintStream;
	astore_2
	aload_2
	ldc "Please enter a value for x: "
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	aload_3
	invokevirtual java/util/Scanner/nextInt()I
	istore_1
	return
.end method
