;
; Source file: ../test/cg.tc
; Target file: cg.j
; Sun Dec  1 19:35:33 2019
;

.source ../test/cg.tc
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
	iload_1
	iconst_0
	if_icmpge _label0
	iconst_1
	goto _label1
_label0:
	iconst_0
_label1:
	iload_1
	iconst_0
	if_icmple _label2
	iconst_1
	goto _label3
_label2:
	iconst_0
_label3:
	aload_2
	iconst_1
	invokevirtual java/io/PrintStream/println(I)V
	aload_2
	iconst_0
	invokevirtual java/io/PrintStream/println(I)V
	iload_1
	iconst_3
	iconst_4
	iadd
	ineg
	istore_1
	iload_1
	bipush 7
	if_icmpeq _label4
	iconst_1
	goto _label5
_label4:
	iconst_0
_label5:
	aload_2
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	aload_2
	iload_1
	iconst_1
	iadd
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
