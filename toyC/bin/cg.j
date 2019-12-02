;
; Source file: /mnt/c/school/fall19/egre591/proj/jasmin-2.4/cg.tc
; Target file: cg.j
; Mon Dec  2 12:20:25 2019
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
	astore 4
	getstatic java/lang/System/out Ljava/io/PrintStream;
	astore_3
	aload_3
	ldc "\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	aload_3
	ldc "Please enter a value for x: "
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	aload 4
	invokevirtual java/util/Scanner/nextInt()I
	istore_1
	iconst_0
	istore_2
_label0:
	iload_1
	iconst_0
	if_icmpeq _label2
	iconst_1
	goto _label3
_label2:
	iconst_0
_label3:
	iconst_0
	if_icmpeq _label1
	iload_1
	iconst_1
	isub
	istore_1
	iconst_2
	istore_2
	goto _label0
_label1:
	aload_3
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
