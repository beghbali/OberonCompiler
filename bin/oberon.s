	.file "oberon.s"
oberon1_compiled.:
.section	".rodata"
.TRUE:	.asciz	"TRUE"
.FALSE:	.asciz	"FALSE"
.section	 ".text"
	.global srand
	.type	 srand, #function 
srand:
	!#PROLOGUE# 0
	save	%sp, srand_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to seed
	clr	%l7
	ld	[%fp - 4],%o0	! load: seed
	mov	11,%o1		! %o1=11
	call	.rem,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 8]	! saving to $t0
	ld	[%fp - 8],%l0	! load: $t0
	set	srandseed,%l1	! %l1=srandseed
	st	%l0,[%l1]	! saving to global: srandseed
	srand_space = -112
	ret
	restore
.section	 ".text"
	.global pow
	.type	 pow, #function 
pow:
	!#PROLOGUE# 0
	save	%sp, pow_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to base
	st	%i1,[%fp - 8]	! saving to power
	clr	%l7
	ld	[%fp - 8],%o0	! load: power
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL0
	nop
	mov	1,%l7		! %l7=1
.LL0:
	stb	%l7,[%fp - 13]	! saving to $t1
	clr	%l7
	ldub	[%fp - 13],%l0	! load: $t1
	cmp	%l0,%g2
	bne	.IF1
	nop
	mov	1,%i0		! %i0=1
	ret	
	restore
.IF1:
	ld	[%fp - 8],%o0	! load: power
	mov	2,%o1		! %o1=2
	call	.rem,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 20]	! saving to $t2
	ld	[%fp - 20],%o0	! load: $t2
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL2
	nop
	mov	1,%l7		! %l7=1
.LL2:
	stb	%l7,[%fp - 21]	! saving to $t3
	clr	%l7
	ldub	[%fp - 21],%l0	! load: $t3
	cmp	%l0,%g2
	bne	.IF3
	nop
	ld	[%fp - 8],%o0	! load: power
	mov	2,%o1		! %o1=2
	call	.div,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 28]	! saving to $t4
	ld	[%fp - 4],%o0	! load: base
	ld	[%fp - 28],%o1	! load: $t4
	call	pow,2
	nop
	st	%o0,[%fp - 32]	! saving to pow
	ld	[%fp - 32],%l0	! load: pow
	st	%l0,[%fp - 12]	! saving to temp
	ld	[%fp - 12],%o0	! load: temp
	ld	[%fp - 12],%o1	! load: temp
	call	.mul,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 36]	! saving to $t5
	ld	[%fp - 36],%i0	! load: $t5
	ret	
	restore
	b	.ELSE4
	nop
.IF3:
	ld	[%fp - 8],%o0	! load: power
	mov	1,%o1		! %o1=1
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 40]	! saving to $t6
	ld	[%fp - 4],%o0	! load: base
	ld	[%fp - 40],%o1	! load: $t6
	call	pow,2
	nop
	st	%o0,[%fp - 44]	! saving to pow
	ld	[%fp - 4],%o0	! load: base
	ld	[%fp - 44],%o1	! load: pow
	call	.mul,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 48]	! saving to $t7
	ld	[%fp - 48],%i0	! load: $t7
	ret	
	restore
.ELSE4:
	pow_space = -152
	ret
	restore
.section	 ".text"
	.global rand
	.type	 rand, #function 
rand:
	!#PROLOGUE# 0
	save	%sp, rand_space, %sp
	!#PROLOGUE# 1
	clr	%l7
	set	srandseed,%l0	! %l0=srandseed
	ld	[%l0],%l0	! load value of global: srandseed
	st	%l0,[%fp - 4]	! saving to old
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 8]	! saving to i
.BEGWHILE5:
	ld	[%fp - 8],%o0	! load: i
	mov	32,%o1		! %o1=32
	cmp	%o0,%o1
	bge	.LL6
	nop
	mov	1,%l7		! %l7=1
.LL6:
	stb	%l7,[%fp - 17]	! saving to $t8
	clr	%l7
	ldub	[%fp - 17],%l0	! load: $t8
	cmp	%l0,%g0
	be	.ENDWHILE7
	nop
	mov	57,%o0		! %o0=57
	ld	[%fp - 4],%o1	! load: old
	call	.mul,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 24]	! saving to $t9
	ld	[%fp - 24],%o0	! load: $t9
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 28]	! saving to $t10
	ld	[%fp - 28],%o0	! load: $t10
	mov	7,%o1		! %o1=7
	call	.rem,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 32]	! saving to $t11
	ld	[%fp - 32],%l0	! load: $t11
	st	%l0,[%fp - 12]	! saving to x
	mov	57,%o0		! %o0=57
	ld	[%fp - 12],%o1	! load: x
	call	.mul,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 36]	! saving to $t12
	ld	[%fp - 36],%o0	! load: $t12
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 40]	! saving to $t13
	ld	[%fp - 40],%o0	! load: $t13
	mov	7,%o1		! %o1=7
	call	.rem,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 44]	! saving to $t14
	ld	[%fp - 44],%l0	! load: $t14
	st	%l0,[%fp - 16]	! saving to y
	ld	[%fp - 16],%l0	! load: y
	st	%l0,[%fp - 4]	! saving to old
	ld	[%fp - 8],%o0	! load: i
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 48]	! saving to $t15
	ld	[%fp - 48],%l0	! load: $t15
	st	%l0,[%fp - 8]	! saving to i
	b	.BEGWHILE5
	nop
.ENDWHILE7:
	ld	[%fp - 4],%l0	! load: old
	set	srandseed,%l1	! %l1=srandseed
	st	%l0,[%l1]	! saving to global: srandseed
	ld	[%fp - 4],%i0	! load: old
	ret	
	restore
	rand_space = -152
	ret
	restore
.section	 ".text"
	.global increment
	.type	 increment, #function 
increment:
	!#PROLOGUE# 0
	save	%sp, increment_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to x
	clr	%l7
	ld	[%fp - 4],%o0	! load reference: x
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 8]	! saving to $t16
	ld	[%fp - 8],%l0	! load: $t16
	ld	[%fp - 4],%l1	! load reference: x
	st	%l0,[%l1]	! saving ref param: x
	increment_space = -112
	ret
	restore
.section	 ".text"
	.global getNext
	.type	 getNext, #function 
getNext:
	!#PROLOGUE# 0
	save	%sp, getNext_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 8]	! saving to index
	ld	[%fp - 8],%o0	! load address: index
	call	increment,1
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 12]	! saving to array
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 16]	! saving to index
	ld	[%fp - 16],%o0	! load reference: index
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 20]	! saving to $t17
	mov	4,%o0		! %o0=4
	ld	[%fp - 20],%o1	! load: $t17
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 12],%o0	! load address: array
	add	%o0,%o1,%o2
	st	%o2,[%fp - 24]	! saving to $t18
	ld	[%fp - 24],%i0	! load reference: array
	ld	[%i0],%i0
	ret	
	restore
	getNext_space = -128
	ret
	restore
.section	 ".text"
	.global inRange
	.type	 inRange, #function 
inRange:
	!#PROLOGUE# 0
	save	%sp, inRange_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to low
	st	%i1,[%fp - 8]	! saving to high
	st	%i2,[%fp - 12]	! saving to target
	clr	%l7
	ld	[%fp - 12],%o0	! load: target
	ld	[%fp - 4],%o1	! load: low
	cmp	%o0,%o1
	ble	.LL8
	nop
	mov	1,%l7		! %l7=1
.LL8:
	stb	%l7,[%fp - 13]	! saving to $t19
	clr	%l7
	ldub	[%fp - 13],%o0	! load: $t19
	cmp	%o0,%g0
	be	.NOTAND9
	nop
	ld	[%fp - 12],%o0	! load: target
	ld	[%fp - 8],%o1	! load: high
	cmp	%o0,%o1
	bge	.LL10
	nop
	mov	1,%l7		! %l7=1
.LL10:
	stb	%l7,[%fp - 14]	! saving to $t20
	clr	%l7
	ldub	[%fp - 14],%o0	! load: $t20
	cmp	%o0,%g0
	be	.NOTAND9
	nop
	mov	1,%l7		! %l7=1
.NOTAND9:
	stb	%l7,[%fp - 15]	! saving to $t21
	clr	%l7
	ldub	[%fp - 15],%i0	! load: $t21
	ret	
	restore
	inRange_space = -120
	ret
	restore
.section	 ".text"
	.global swap
	.type	 swap, #function 
swap:
	!#PROLOGUE# 0
	save	%sp, swap_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to a
	st	%i1,[%fp - 8]	! saving to b
	clr	%l7
	ld	[%fp - 4],%l0	! load reference: a
	ld	[%l0],%l0
	st	%l0,[%fp - 12]	! saving to temp
	ld	[%fp - 8],%l0	! load reference: b
	ld	[%l0],%l0
	ld	[%fp - 4],%l1	! load reference: a
	st	%l0,[%l1]	! saving ref param: a
	ld	[%fp - 12],%l0	! load: temp
	ld	[%fp - 8],%l1	! load reference: b
	st	%l0,[%l1]	! saving ref param: b
	swap_space = -112
	ret
	restore
.section	 ".text"
	.global enumerate
	.type	 enumerate, #function 
enumerate:
	!#PROLOGUE# 0
	save	%sp, enumerate_space, %sp
	!#PROLOGUE# 1
	clr	%l7
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 4]	! saving to i
.BEGWHILE11:
	ld	[%fp - 4],%o0	! load: i
	mov	9,%o1		! %o1=9
	cmp	%o0,%o1
	bge	.LL12
	nop
	mov	1,%l7		! %l7=1
.LL12:
	stb	%l7,[%fp - 49]	! saving to $t22
	clr	%l7
	ldub	[%fp - 49],%l0	! load: $t22
	cmp	%l0,%g0
	be	.ENDWHILE13
	nop
	add	%fp,-4,%o0	! load address: i
	call	increment,1
	nop
	ld	[%fp - 4],%o0	! load: i
	mov	1,%o1		! %o1=1
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 56]	! saving to $t23
	mov	4,%o0		! %o0=4
	ld	[%fp - 56],%o1	! load: $t23
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	add	%fp,-44,%o0	! load address: temparr
	add	%o0,%o1,%o2
	st	%o2,[%fp - 60]	! saving to $t24
	ld	[%fp - 4],%l0	! load: i
	ld	[%fp - 60],%l1	! load reference: temparr
	st	%l0,[%l1]	! saving ref param: temparr
	b	.BEGWHILE11
	nop
.ENDWHILE13:
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 4]	! saving to i
.BEGWHILE14:
	ld	[%fp - 4],%o0	! load: i
	mov	3,%o1		! %o1=3
	cmp	%o0,%o1
	bge	.LL15
	nop
	mov	1,%l7		! %l7=1
.LL15:
	stb	%l7,[%fp - 61]	! saving to $t25
	clr	%l7
	ldub	[%fp - 61],%l0	! load: $t25
	cmp	%l0,%g0
	be	.ENDWHILE16
	nop
	add	%fp,-4,%o0	! load address: i
	call	increment,1
	nop
	call	rand,0
	nop
	st	%o0,[%fp - 68]	! saving to rand
	ld	[%fp - 68],%o0	! load: rand
	mov	3,%o1		! %o1=3
	call	.rem,2
	nop
	mov	%o0,%o2		! %o0=%o2
	st	%o2,[%fp - 72]	! saving to $t26
	ld	[%fp - 72],%l0	! load: $t26
	st	%l0,[%fp - 8]	! saving to val
	mov	4,%o0		! %o0=4
	ld	[%fp - 8],%o1	! load: val
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	add	%fp,-44,%o0	! load address: temparr
	add	%o0,%o1,%o2
	st	%o2,[%fp - 76]	! saving to $t27
	mov	8,%o0		! %o0=8
	ld	[%fp - 8],%o1	! load: val
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 80]	! saving to $t28
	mov	4,%o0		! %o0=4
	ld	[%fp - 80],%o1	! load: $t28
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	add	%fp,-44,%o0	! load address: temparr
	add	%o0,%o1,%o2
	st	%o2,[%fp - 84]	! saving to $t29
	ld	[%fp - 76],%o0	! load address: temparr
	ld	[%fp - 84],%o1	! load address: temparr
	call	swap,2
	nop
	b	.BEGWHILE14
	nop
.ENDWHILE16:
	mov	1,%o0		! %o0=1
	mov	44,%o1		! %o1=44
	call	calloc,1
	nop
	st	%o0,[%fp - 48]	! saving to result
	ld	[%fp - 48],%l0	! load: result
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 88]	! saving to array
	ld	[%fp - 88],%o0	! load address: array
	add	%fp,-44,%o1	! load address: temparr
	mov	36,%o2		! %o2=36
	call	memcpy,3
	nop
	ld	[%fp - 48],%l0	! load: result
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 92]	! saving to index
	mov	0,%l0		! %l0=0
	ld	[%fp - 92],%l1	! load reference: index
	st	%l0,[%l1]	! saving ref param: index
	ld	[%fp - 48],%i0	! load: result
	ret	
	restore
	enumerate_space = -192
	ret
	restore
.section	 ".text"
	.global init
	.type	 init, #function 
init:
	!#PROLOGUE# 0
	save	%sp, init_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 28]	! saving to move
	mov	0,%l0		! %l0=0
	ld	[%fp - 28],%l1	! load reference: move
	st	%l0,[%l1]	! saving ref param: move
	mov	7,%o0		! %o0=7
	call	srand,1
	nop
	call	enumerate,0
	nop
	st	%o0,[%fp - 32]	! saving to enumerate
	ld	[%fp - 32],%l0	! load: enumerate
	st	%l0,[%fp - 24]	! saving to enumHndlr
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 8]	! saving to i
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 16]	! saving to k
.BEGWHILE17:
	ld	[%fp - 8],%o0	! load: i
	mov	3,%o1		! %o1=3
	cmp	%o0,%o1
	bge	.LL18
	nop
	mov	1,%l7		! %l7=1
.LL18:
	stb	%l7,[%fp - 33]	! saving to $t30
	clr	%l7
	ldub	[%fp - 33],%l0	! load: $t30
	cmp	%l0,%g0
	be	.ENDWHILE19
	nop
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 12]	! saving to j
.BEGWHILE20:
	ld	[%fp - 12],%o0	! load: j
	mov	3,%o1		! %o1=3
	cmp	%o0,%o1
	bge	.LL21
	nop
	mov	1,%l7		! %l7=1
.LL21:
	stb	%l7,[%fp - 34]	! saving to $t31
	clr	%l7
	ldub	[%fp - 34],%l0	! load: $t31
	cmp	%l0,%g0
	be	.ENDWHILE22
	nop
	ld	[%fp - 24],%o0	! load: enumHndlr
	call	getNext,1
	nop
	st	%o0,[%fp - 40]	! saving to getNext
	ld	[%fp - 40],%l0	! load: getNext
	st	%l0,[%fp - 20]	! saving to val
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 44]	! saving to grid
	mov	12,%o0		! %o0=12
	ld	[%fp - 8],%o1	! load: i
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 44],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 48]	! saving to $t32
	mov	4,%o0		! %o0=4
	ld	[%fp - 12],%o1	! load: j
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 48],%o0	! load address: $t32
	add	%o0,%o1,%o2
	st	%o2,[%fp - 48]	! saving to $t32
	ld	[%fp - 20],%l0	! load: val
	ld	[%fp - 48],%l1	! load reference: grid
	st	%l0,[%l1]	! saving ref param: grid
	ld	[%fp - 20],%o0	! load: val
	mov	9,%o1		! %o1=9
	cmp	%o0,%o1
	bne	.LL23
	nop
	mov	1,%l7		! %l7=1
.LL23:
	stb	%l7,[%fp - 49]	! saving to $t33
	clr	%l7
	ldub	[%fp - 49],%l0	! load: $t33
	cmp	%l0,%g2
	bne	.IF24
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 56]	! saving to indexi
	ld	[%fp - 8],%l0	! load: i
	ld	[%fp - 56],%l1	! load reference: indexi
	st	%l0,[%l1]	! saving ref param: indexi
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 60]	! saving to indexj
	ld	[%fp - 12],%l0	! load: j
	ld	[%fp - 60],%l1	! load reference: indexj
	st	%l0,[%l1]	! saving ref param: indexj
.IF24:
	add	%fp,-12,%o0	! load address: j
	call	increment,1
	nop
	b	.BEGWHILE20
	nop
.ENDWHILE22:
	add	%fp,-8,%o0	! load address: i
	call	increment,1
	nop
	b	.BEGWHILE17
	nop
.ENDWHILE19:
	init_space = -160
	ret
	restore
.section	 ".text"
	.global print
	.type	 print, #function 
print:
	!#PROLOGUE# 0
	save	%sp, print_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 8]	! saving to i
.BEGWHILE25:
	ld	[%fp - 8],%o0	! load: i
	mov	3,%o1		! %o1=3
	cmp	%o0,%o1
	bge	.LL26
	nop
	mov	1,%l7		! %l7=1
.LL26:
	stb	%l7,[%fp - 13]	! saving to $t34
	clr	%l7
	ldub	[%fp - 13],%l0	! load: $t34
	cmp	%l0,%g0
	be	.ENDWHILE27
	nop
	mov	0,%l0		! %l0=0
	st	%l0,[%fp - 12]	! saving to j
.BEGWHILE28:
	ld	[%fp - 12],%o0	! load: j
	mov	3,%o1		! %o1=3
	cmp	%o0,%o1
	bge	.LL29
	nop
	mov	1,%l7		! %l7=1
.LL29:
	stb	%l7,[%fp - 14]	! saving to $t35
	clr	%l7
	ldub	[%fp - 14],%l0	! load: $t35
	cmp	%l0,%g0
	be	.ENDWHILE30
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 20]	! saving to grid
	mov	12,%o0		! %o0=12
	ld	[%fp - 8],%o1	! load: i
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 20],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 24]	! saving to $t36
	mov	4,%o0		! %o0=4
	ld	[%fp - 12],%o1	! load: j
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 24],%o0	! load address: $t36
	add	%o0,%o1,%o2
	st	%o2,[%fp - 24]	! saving to $t36
	ld	[%fp - 24],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	9,%o1		! %o1=9
	cmp	%o0,%o1
	bne	.LL31
	nop
	mov	1,%l7		! %l7=1
.LL31:
	stb	%l7,[%fp - 25]	! saving to $t37
	clr	%l7
	ldub	[%fp - 25],%l0	! load: $t37
	cmp	%l0,%g2
	bne	.IF32
	nop
.section	".rodata"
.LLC0:
	.asciz	"* "
.section	".text"
	set	.LLC0,%o0	! %o0=.LLC0
	call	printf,0
	nop
	b	.ELSE33
	nop
.IF32:
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 32]	! saving to grid
	mov	12,%o0		! %o0=12
	ld	[%fp - 8],%o1	! load: i
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 32],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 36]	! saving to $t38
	mov	4,%o0		! %o0=4
	ld	[%fp - 12],%o1	! load: j
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 36],%o0	! load address: $t38
	add	%o0,%o1,%o2
	st	%o2,[%fp - 36]	! saving to $t38
.section	".rodata"
.LLC1:
	.asciz	"%d "
.section	".text"
	set	.LLC1,%o0	! %o0=.LLC1
	ld	[%fp - 36],%o1	! load reference: grid
	ld	[%o1],%o1
	call	printf,1
	nop
.ELSE33:
	add	%fp,-12,%o0	! load address: j
	call	increment,1
	nop
	b	.BEGWHILE28
	nop
.ENDWHILE30:
.section	".rodata"
.LLC2:
	.asciz	"\n"
.section	".text"
	set	.LLC2,%o0	! %o0=.LLC2
	call	printf,0
	nop
	add	%fp,-8,%o0	! load address: i
	call	increment,1
	nop
	b	.BEGWHILE25
	nop
.ENDWHILE27:
	print_space = -136
	ret
	restore
.section	 ".text"
	.global puzzleComplete
	.type	 puzzleComplete, #function 
puzzleComplete:
	!#PROLOGUE# 0
	save	%sp, puzzleComplete_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 8]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	0,%o1		! %o1=0
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 8],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 12]	! saving to $t39
	mov	4,%o0		! %o0=4
	mov	0,%o1		! %o1=0
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 12],%o0	! load address: $t39
	add	%o0,%o1,%o2
	st	%o2,[%fp - 12]	! saving to $t39
	ld	[%fp - 12],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	cmp	%o0,%o1
	bne	.LL34
	nop
	mov	1,%l7		! %l7=1
.LL34:
	stb	%l7,[%fp - 13]	! saving to $t40
	clr	%l7
	ldub	[%fp - 13],%o0	! load: $t40
	cmp	%o0,%g0
	be	.NOTAND35
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 20]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	0,%o1		! %o1=0
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 20],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 24]	! saving to $t41
	mov	4,%o0		! %o0=4
	mov	1,%o1		! %o1=1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 24],%o0	! load address: $t41
	add	%o0,%o1,%o2
	st	%o2,[%fp - 24]	! saving to $t41
	ld	[%fp - 24],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	2,%o1		! %o1=2
	cmp	%o0,%o1
	bne	.LL36
	nop
	mov	1,%l7		! %l7=1
.LL36:
	stb	%l7,[%fp - 25]	! saving to $t42
	clr	%l7
	ldub	[%fp - 25],%o0	! load: $t42
	cmp	%o0,%g0
	be	.NOTAND35
	nop
	mov	1,%l7		! %l7=1
.NOTAND35:
	stb	%l7,[%fp - 26]	! saving to $t43
	clr	%l7
	ldub	[%fp - 26],%o0	! load: $t43
	cmp	%o0,%g0
	be	.NOTAND37
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 32]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	0,%o1		! %o1=0
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 32],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 36]	! saving to $t44
	mov	4,%o0		! %o0=4
	mov	2,%o1		! %o1=2
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 36],%o0	! load address: $t44
	add	%o0,%o1,%o2
	st	%o2,[%fp - 36]	! saving to $t44
	ld	[%fp - 36],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	3,%o1		! %o1=3
	cmp	%o0,%o1
	bne	.LL38
	nop
	mov	1,%l7		! %l7=1
.LL38:
	stb	%l7,[%fp - 37]	! saving to $t45
	clr	%l7
	ldub	[%fp - 37],%o0	! load: $t45
	cmp	%o0,%g0
	be	.NOTAND37
	nop
	mov	1,%l7		! %l7=1
.NOTAND37:
	stb	%l7,[%fp - 38]	! saving to $t46
	clr	%l7
	ldub	[%fp - 38],%o0	! load: $t46
	cmp	%o0,%g0
	be	.NOTAND39
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 44]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	1,%o1		! %o1=1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 44],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 48]	! saving to $t47
	mov	4,%o0		! %o0=4
	mov	0,%o1		! %o1=0
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 48],%o0	! load address: $t47
	add	%o0,%o1,%o2
	st	%o2,[%fp - 48]	! saving to $t47
	ld	[%fp - 48],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	4,%o1		! %o1=4
	cmp	%o0,%o1
	bne	.LL40
	nop
	mov	1,%l7		! %l7=1
.LL40:
	stb	%l7,[%fp - 49]	! saving to $t48
	clr	%l7
	ldub	[%fp - 49],%o0	! load: $t48
	cmp	%o0,%g0
	be	.NOTAND39
	nop
	mov	1,%l7		! %l7=1
.NOTAND39:
	stb	%l7,[%fp - 50]	! saving to $t49
	clr	%l7
	ldub	[%fp - 50],%o0	! load: $t49
	cmp	%o0,%g0
	be	.NOTAND41
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 56]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	1,%o1		! %o1=1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 56],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 60]	! saving to $t50
	mov	4,%o0		! %o0=4
	mov	1,%o1		! %o1=1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 60],%o0	! load address: $t50
	add	%o0,%o1,%o2
	st	%o2,[%fp - 60]	! saving to $t50
	ld	[%fp - 60],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	9,%o1		! %o1=9
	cmp	%o0,%o1
	bne	.LL42
	nop
	mov	1,%l7		! %l7=1
.LL42:
	stb	%l7,[%fp - 61]	! saving to $t51
	clr	%l7
	ldub	[%fp - 61],%o0	! load: $t51
	cmp	%o0,%g0
	be	.NOTAND41
	nop
	mov	1,%l7		! %l7=1
.NOTAND41:
	stb	%l7,[%fp - 62]	! saving to $t52
	clr	%l7
	ldub	[%fp - 62],%o0	! load: $t52
	cmp	%o0,%g0
	be	.NOTAND43
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 68]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	1,%o1		! %o1=1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 68],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 72]	! saving to $t53
	mov	4,%o0		! %o0=4
	mov	2,%o1		! %o1=2
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 72],%o0	! load address: $t53
	add	%o0,%o1,%o2
	st	%o2,[%fp - 72]	! saving to $t53
	ld	[%fp - 72],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	5,%o1		! %o1=5
	cmp	%o0,%o1
	bne	.LL44
	nop
	mov	1,%l7		! %l7=1
.LL44:
	stb	%l7,[%fp - 73]	! saving to $t54
	clr	%l7
	ldub	[%fp - 73],%o0	! load: $t54
	cmp	%o0,%g0
	be	.NOTAND43
	nop
	mov	1,%l7		! %l7=1
.NOTAND43:
	stb	%l7,[%fp - 74]	! saving to $t55
	clr	%l7
	ldub	[%fp - 74],%o0	! load: $t55
	cmp	%o0,%g0
	be	.NOTAND45
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 80]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	2,%o1		! %o1=2
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 80],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 84]	! saving to $t56
	mov	4,%o0		! %o0=4
	mov	0,%o1		! %o1=0
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 84],%o0	! load address: $t56
	add	%o0,%o1,%o2
	st	%o2,[%fp - 84]	! saving to $t56
	ld	[%fp - 84],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	6,%o1		! %o1=6
	cmp	%o0,%o1
	bne	.LL46
	nop
	mov	1,%l7		! %l7=1
.LL46:
	stb	%l7,[%fp - 85]	! saving to $t57
	clr	%l7
	ldub	[%fp - 85],%o0	! load: $t57
	cmp	%o0,%g0
	be	.NOTAND45
	nop
	mov	1,%l7		! %l7=1
.NOTAND45:
	stb	%l7,[%fp - 86]	! saving to $t58
	clr	%l7
	ldub	[%fp - 86],%o0	! load: $t58
	cmp	%o0,%g0
	be	.NOTAND47
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 92]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	2,%o1		! %o1=2
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 92],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 96]	! saving to $t59
	mov	4,%o0		! %o0=4
	mov	1,%o1		! %o1=1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 96],%o0	! load address: $t59
	add	%o0,%o1,%o2
	st	%o2,[%fp - 96]	! saving to $t59
	ld	[%fp - 96],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	7,%o1		! %o1=7
	cmp	%o0,%o1
	bne	.LL48
	nop
	mov	1,%l7		! %l7=1
.LL48:
	stb	%l7,[%fp - 97]	! saving to $t60
	clr	%l7
	ldub	[%fp - 97],%o0	! load: $t60
	cmp	%o0,%g0
	be	.NOTAND47
	nop
	mov	1,%l7		! %l7=1
.NOTAND47:
	stb	%l7,[%fp - 98]	! saving to $t61
	clr	%l7
	ldub	[%fp - 98],%o0	! load: $t61
	cmp	%o0,%g0
	be	.NOTAND49
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 104]	! saving to grid
	mov	12,%o0		! %o0=12
	mov	2,%o1		! %o1=2
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 104],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 108]	! saving to $t62
	mov	4,%o0		! %o0=4
	mov	2,%o1		! %o1=2
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 108],%o0	! load address: $t62
	add	%o0,%o1,%o2
	st	%o2,[%fp - 108]	! saving to $t62
	ld	[%fp - 108],%o0	! load reference: grid
	ld	[%o0],%o0
	mov	8,%o1		! %o1=8
	cmp	%o0,%o1
	bne	.LL50
	nop
	mov	1,%l7		! %l7=1
.LL50:
	stb	%l7,[%fp - 109]	! saving to $t63
	clr	%l7
	ldub	[%fp - 109],%o0	! load: $t63
	cmp	%o0,%g0
	be	.NOTAND49
	nop
	mov	1,%l7		! %l7=1
.NOTAND49:
	stb	%l7,[%fp - 110]	! saving to $t64
	clr	%l7
	ldub	[%fp - 110],%l0	! load: $t64
	cmp	%l0,%g2
	bne	.IF51
	nop
	mov	1,%i0		! %i0=1
	ret	
	restore
.IF51:
	mov	0,%i0		! %i0=0
	ret	
	restore
	puzzleComplete_space = -216
	ret
	restore
.section	 ".text"
	.global prompt
	.type	 prompt, #function 
prompt:
	!#PROLOGUE# 0
	save	%sp, prompt_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
.section	".rodata"
.LLC3:
	.asciz	"Enter Move(<=4,^8,v5,=>6) or 0 to Exit: "
.section	".text"
	set	.LLC3,%o0	! %o0=.LLC3
	call	printf,0
	nop
	prompt_space = -104
	ret
	restore
.section	 ".text"
	.global validateMove
	.type	 validateMove, #function 
validateMove:
	!#PROLOGUE# 0
	save	%sp, validateMove_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 8]	! saving to move
	ld	[%fp - 8],%o0	! load reference: move
	ld	[%o0],%o0
	mov	8,%o1		! %o1=8
	cmp	%o0,%o1
	bne	.LL52
	nop
	mov	1,%l7		! %l7=1
.LL52:
	stb	%l7,[%fp - 9]	! saving to $t65
	clr	%l7
	ldub	[%fp - 9],%o0	! load: $t65
	cmp	%o0,%g2
	be	.OR53
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 16]	! saving to move
	ld	[%fp - 16],%o0	! load reference: move
	ld	[%o0],%o0
	mov	4,%o1		! %o1=4
	cmp	%o0,%o1
	bne	.LL54
	nop
	mov	1,%l7		! %l7=1
.LL54:
	stb	%l7,[%fp - 17]	! saving to $t66
	clr	%l7
	ldub	[%fp - 17],%o0	! load: $t66
	cmp	%o0,%g2
	bne	.NOTOR55
	nop
.OR53:
	mov	1,%l7		! %l7=1
.NOTOR55:
	stb	%l7,[%fp - 18]	! saving to $t67
	clr	%l7
	ldub	[%fp - 18],%o0	! load: $t67
	cmp	%o0,%g0
	be	.NOTAND56
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 24]	! saving to indexi
	ld	[%fp - 24],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL57
	nop
	mov	1,%l7		! %l7=1
.LL57:
	stb	%l7,[%fp - 25]	! saving to $t68
	clr	%l7
	ldub	[%fp - 25],%o0	! load: $t68
	cmp	%o0,%g0
	be	.NOTAND56
	nop
	mov	1,%l7		! %l7=1
.NOTAND56:
	stb	%l7,[%fp - 26]	! saving to $t69
	clr	%l7
	ldub	[%fp - 26],%o0	! load: $t69
	cmp	%o0,%g0
	be	.NOTAND58
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 32]	! saving to indexj
	ld	[%fp - 32],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL59
	nop
	mov	1,%l7		! %l7=1
.LL59:
	stb	%l7,[%fp - 33]	! saving to $t70
	clr	%l7
	ldub	[%fp - 33],%o0	! load: $t70
	cmp	%o0,%g0
	be	.NOTAND58
	nop
	mov	1,%l7		! %l7=1
.NOTAND58:
	stb	%l7,[%fp - 34]	! saving to $t71
	clr	%l7
	ldub	[%fp - 34],%l0	! load: $t71
	cmp	%l0,%g2
	bne	.IF60
	nop
	mov	0,%i0		! %i0=0
	ret	
	restore
	b	.ELSE61
	nop
.IF60:
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 40]	! saving to move
	ld	[%fp - 40],%o0	! load reference: move
	ld	[%o0],%o0
	mov	8,%o1		! %o1=8
	cmp	%o0,%o1
	bne	.LL62
	nop
	mov	1,%l7		! %l7=1
.LL62:
	stb	%l7,[%fp - 41]	! saving to $t72
	clr	%l7
	ldub	[%fp - 41],%o0	! load: $t72
	cmp	%o0,%g2
	be	.OR63
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 48]	! saving to move
	ld	[%fp - 48],%o0	! load reference: move
	ld	[%o0],%o0
	mov	6,%o1		! %o1=6
	cmp	%o0,%o1
	bne	.LL64
	nop
	mov	1,%l7		! %l7=1
.LL64:
	stb	%l7,[%fp - 49]	! saving to $t73
	clr	%l7
	ldub	[%fp - 49],%o0	! load: $t73
	cmp	%o0,%g2
	bne	.NOTOR65
	nop
.OR63:
	mov	1,%l7		! %l7=1
.NOTOR65:
	stb	%l7,[%fp - 50]	! saving to $t74
	clr	%l7
	ldub	[%fp - 50],%o0	! load: $t74
	cmp	%o0,%g0
	be	.NOTAND66
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 56]	! saving to indexi
	ld	[%fp - 56],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL67
	nop
	mov	1,%l7		! %l7=1
.LL67:
	stb	%l7,[%fp - 57]	! saving to $t75
	clr	%l7
	ldub	[%fp - 57],%o0	! load: $t75
	cmp	%o0,%g0
	be	.NOTAND66
	nop
	mov	1,%l7		! %l7=1
.NOTAND66:
	stb	%l7,[%fp - 58]	! saving to $t76
	clr	%l7
	ldub	[%fp - 58],%o0	! load: $t76
	cmp	%o0,%g0
	be	.NOTAND68
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 64]	! saving to indexj
	ld	[%fp - 64],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	2,%o1		! %o1=2
	cmp	%o0,%o1
	bne	.LL69
	nop
	mov	1,%l7		! %l7=1
.LL69:
	stb	%l7,[%fp - 65]	! saving to $t77
	clr	%l7
	ldub	[%fp - 65],%o0	! load: $t77
	cmp	%o0,%g0
	be	.NOTAND68
	nop
	mov	1,%l7		! %l7=1
.NOTAND68:
	stb	%l7,[%fp - 66]	! saving to $t78
	clr	%l7
	ldub	[%fp - 66],%l0	! load: $t78
	cmp	%l0,%g2
	bne	.IF70
	nop
	mov	0,%i0		! %i0=0
	ret	
	restore
	b	.ELSE71
	nop
.IF70:
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 72]	! saving to move
	ld	[%fp - 72],%o0	! load reference: move
	ld	[%o0],%o0
	mov	5,%o1		! %o1=5
	cmp	%o0,%o1
	bne	.LL72
	nop
	mov	1,%l7		! %l7=1
.LL72:
	stb	%l7,[%fp - 73]	! saving to $t79
	clr	%l7
	ldub	[%fp - 73],%o0	! load: $t79
	cmp	%o0,%g2
	be	.OR73
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 80]	! saving to move
	ld	[%fp - 80],%o0	! load reference: move
	ld	[%o0],%o0
	mov	4,%o1		! %o1=4
	cmp	%o0,%o1
	bne	.LL74
	nop
	mov	1,%l7		! %l7=1
.LL74:
	stb	%l7,[%fp - 81]	! saving to $t80
	clr	%l7
	ldub	[%fp - 81],%o0	! load: $t80
	cmp	%o0,%g2
	bne	.NOTOR75
	nop
.OR73:
	mov	1,%l7		! %l7=1
.NOTOR75:
	stb	%l7,[%fp - 82]	! saving to $t81
	clr	%l7
	ldub	[%fp - 82],%o0	! load: $t81
	cmp	%o0,%g0
	be	.NOTAND76
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 88]	! saving to indexi
	ld	[%fp - 88],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	2,%o1		! %o1=2
	cmp	%o0,%o1
	bne	.LL77
	nop
	mov	1,%l7		! %l7=1
.LL77:
	stb	%l7,[%fp - 89]	! saving to $t82
	clr	%l7
	ldub	[%fp - 89],%o0	! load: $t82
	cmp	%o0,%g0
	be	.NOTAND76
	nop
	mov	1,%l7		! %l7=1
.NOTAND76:
	stb	%l7,[%fp - 90]	! saving to $t83
	clr	%l7
	ldub	[%fp - 90],%o0	! load: $t83
	cmp	%o0,%g0
	be	.NOTAND78
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 96]	! saving to indexj
	ld	[%fp - 96],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL79
	nop
	mov	1,%l7		! %l7=1
.LL79:
	stb	%l7,[%fp - 97]	! saving to $t84
	clr	%l7
	ldub	[%fp - 97],%o0	! load: $t84
	cmp	%o0,%g0
	be	.NOTAND78
	nop
	mov	1,%l7		! %l7=1
.NOTAND78:
	stb	%l7,[%fp - 98]	! saving to $t85
	clr	%l7
	ldub	[%fp - 98],%l0	! load: $t85
	cmp	%l0,%g2
	bne	.IF80
	nop
	mov	0,%i0		! %i0=0
	ret	
	restore
	b	.ELSE81
	nop
.IF80:
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 104]	! saving to move
	ld	[%fp - 104],%o0	! load reference: move
	ld	[%o0],%o0
	mov	5,%o1		! %o1=5
	cmp	%o0,%o1
	bne	.LL82
	nop
	mov	1,%l7		! %l7=1
.LL82:
	stb	%l7,[%fp - 105]	! saving to $t86
	clr	%l7
	ldub	[%fp - 105],%o0	! load: $t86
	cmp	%o0,%g2
	be	.OR83
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 112]	! saving to move
	ld	[%fp - 112],%o0	! load reference: move
	ld	[%o0],%o0
	mov	6,%o1		! %o1=6
	cmp	%o0,%o1
	bne	.LL84
	nop
	mov	1,%l7		! %l7=1
.LL84:
	stb	%l7,[%fp - 113]	! saving to $t87
	clr	%l7
	ldub	[%fp - 113],%o0	! load: $t87
	cmp	%o0,%g2
	bne	.NOTOR85
	nop
.OR83:
	mov	1,%l7		! %l7=1
.NOTOR85:
	stb	%l7,[%fp - 114]	! saving to $t88
	clr	%l7
	ldub	[%fp - 114],%o0	! load: $t88
	cmp	%o0,%g0
	be	.NOTAND86
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 120]	! saving to indexi
	ld	[%fp - 120],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	2,%o1		! %o1=2
	cmp	%o0,%o1
	bne	.LL87
	nop
	mov	1,%l7		! %l7=1
.LL87:
	stb	%l7,[%fp - 121]	! saving to $t89
	clr	%l7
	ldub	[%fp - 121],%o0	! load: $t89
	cmp	%o0,%g0
	be	.NOTAND86
	nop
	mov	1,%l7		! %l7=1
.NOTAND86:
	stb	%l7,[%fp - 122]	! saving to $t90
	clr	%l7
	ldub	[%fp - 122],%o0	! load: $t90
	cmp	%o0,%g0
	be	.NOTAND88
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 128]	! saving to indexj
	ld	[%fp - 128],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	2,%o1		! %o1=2
	cmp	%o0,%o1
	bne	.LL89
	nop
	mov	1,%l7		! %l7=1
.LL89:
	stb	%l7,[%fp - 129]	! saving to $t91
	clr	%l7
	ldub	[%fp - 129],%o0	! load: $t91
	cmp	%o0,%g0
	be	.NOTAND88
	nop
	mov	1,%l7		! %l7=1
.NOTAND88:
	stb	%l7,[%fp - 130]	! saving to $t92
	clr	%l7
	ldub	[%fp - 130],%l0	! load: $t92
	cmp	%l0,%g2
	bne	.IF90
	nop
	mov	0,%i0		! %i0=0
	ret	
	restore
.IF90:
.ELSE81:
.ELSE71:
.ELSE61:
	mov	1,%i0		! %i0=1
	ret	
	restore
	validateMove_space = -232
	ret
	restore
.section	 ".text"
	.global getMove
	.type	 getMove, #function 
getMove:
	!#PROLOGUE# 0
	save	%sp, getMove_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
.BEGWHILE91:
	mov	1,%l0		! %l0=1
	cmp	%l0,%g0
	be	.ENDWHILE92
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 8]	! saving to move
.section	".rodata"
.LLC4:
	.asciz	"%d"
.section	".text"
	set	.LLC4,%o0	! %o0=.LLC4
	ld	[%fp - 8],%o1	! load address: move
	call	scanf,1
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 12]	! saving to move
	ld	[%fp - 12],%o0	! load reference: move
	ld	[%o0],%o0
	mov	8,%o1		! %o1=8
	cmp	%o0,%o1
	bne	.LL93
	nop
	mov	1,%l7		! %l7=1
.LL93:
	stb	%l7,[%fp - 13]	! saving to $t93
	clr	%l7
	ldub	[%fp - 13],%o0	! load: $t93
	cmp	%o0,%g2
	be	.OR94
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 20]	! saving to move
	ld	[%fp - 20],%o0	! load reference: move
	ld	[%o0],%o0
	mov	5,%o1		! %o1=5
	cmp	%o0,%o1
	bne	.LL95
	nop
	mov	1,%l7		! %l7=1
.LL95:
	stb	%l7,[%fp - 21]	! saving to $t94
	clr	%l7
	ldub	[%fp - 21],%o0	! load: $t94
	cmp	%o0,%g2
	bne	.NOTOR96
	nop
.OR94:
	mov	1,%l7		! %l7=1
.NOTOR96:
	stb	%l7,[%fp - 22]	! saving to $t95
	clr	%l7
	ldub	[%fp - 22],%o0	! load: $t95
	cmp	%o0,%g2
	be	.OR97
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 28]	! saving to move
	ld	[%fp - 28],%o0	! load reference: move
	ld	[%o0],%o0
	mov	4,%o1		! %o1=4
	cmp	%o0,%o1
	bne	.LL98
	nop
	mov	1,%l7		! %l7=1
.LL98:
	stb	%l7,[%fp - 29]	! saving to $t96
	clr	%l7
	ldub	[%fp - 29],%o0	! load: $t96
	cmp	%o0,%g2
	bne	.NOTOR99
	nop
.OR97:
	mov	1,%l7		! %l7=1
.NOTOR99:
	stb	%l7,[%fp - 30]	! saving to $t97
	clr	%l7
	ldub	[%fp - 30],%o0	! load: $t97
	cmp	%o0,%g2
	be	.OR100
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 36]	! saving to move
	ld	[%fp - 36],%o0	! load reference: move
	ld	[%o0],%o0
	mov	6,%o1		! %o1=6
	cmp	%o0,%o1
	bne	.LL101
	nop
	mov	1,%l7		! %l7=1
.LL101:
	stb	%l7,[%fp - 37]	! saving to $t98
	clr	%l7
	ldub	[%fp - 37],%o0	! load: $t98
	cmp	%o0,%g2
	bne	.NOTOR102
	nop
.OR100:
	mov	1,%l7		! %l7=1
.NOTOR102:
	stb	%l7,[%fp - 38]	! saving to $t99
	clr	%l7
	ldub	[%fp - 38],%l0	! load: $t99
	cmp	%l0,%g2
	bne	.IF103
	nop
	ld	[%fp - 4],%o0	! load: this
	call	validateMove,1
	nop
	stb	%o0,[%fp - 39]	! saving to validateMove
	ldub	[%fp - 39],%l0	! load: validateMove
	cmp	%l0,%g2
	bne	.IF104
	nop
	ret	
	restore
	b	.ELSE105
	nop
.IF104:
.section	".rodata"
.LLC5:
	.asciz	"Bad Move!\n"
.section	".text"
	set	.LLC5,%o0	! %o0=.LLC5
	call	printf,0
	nop
.ELSE105:
	b	.ELSE106
	nop
.IF103:
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 44]	! saving to move
	ld	[%fp - 44],%o0	! load reference: move
	ld	[%o0],%o0
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL107
	nop
	mov	1,%l7		! %l7=1
.LL107:
	stb	%l7,[%fp - 45]	! saving to $t100
	clr	%l7
	ldub	[%fp - 45],%l0	! load: $t100
	cmp	%l0,%g2
	bne	.IF108
	nop
	b	.ENDWHILE92
	nop
.IF108:
.ELSE106:
	ld	[%fp - 4],%o0	! load: this
	call	prompt,1
	nop
	b	.BEGWHILE91
	nop
.ENDWHILE92:
	getMove_space = -152
	ret
	restore
.section	 ".text"
	.global assertMove
	.type	 assertMove, #function 
assertMove:
	!#PROLOGUE# 0
	save	%sp, assertMove_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to this
	clr	%l7
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 8]	! saving to move
	ld	[%fp - 8],%o0	! load reference: move
	ld	[%o0],%o0
	mov	8,%o1		! %o1=8
	cmp	%o0,%o1
	bne	.LL109
	nop
	mov	1,%l7		! %l7=1
.LL109:
	stb	%l7,[%fp - 9]	! saving to $t101
	clr	%l7
	ldub	[%fp - 9],%l0	! load: $t101
	cmp	%l0,%g2
	bne	.IF110
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 16]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 20]	! saving to indexi
	mov	12,%o0		! %o0=12
	ld	[%fp - 20],%o1	! load reference: indexi
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 16],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 24]	! saving to $t102
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 28]	! saving to indexj
	mov	4,%o0		! %o0=4
	ld	[%fp - 28],%o1	! load reference: indexj
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 24],%o0	! load address: $t102
	add	%o0,%o1,%o2
	st	%o2,[%fp - 24]	! saving to $t102
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 32]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 36]	! saving to indexi
	ld	[%fp - 36],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 40]	! saving to $t103
	mov	12,%o0		! %o0=12
	ld	[%fp - 40],%o1	! load: $t103
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 32],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 44]	! saving to $t104
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 48]	! saving to indexj
	mov	4,%o0		! %o0=4
	ld	[%fp - 48],%o1	! load reference: indexj
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 44],%o0	! load address: $t104
	add	%o0,%o1,%o2
	st	%o2,[%fp - 44]	! saving to $t104
	ld	[%fp - 24],%o0	! load address: grid
	ld	[%fp - 44],%o1	! load address: grid
	call	swap,2
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 52]	! saving to indexi
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 56]	! saving to indexi
	ld	[%fp - 56],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 60]	! saving to $t105
	ld	[%fp - 60],%l0	! load: $t105
	ld	[%fp - 52],%l1	! load reference: indexi
	st	%l0,[%l1]	! saving ref param: indexi
	b	.ELSE111
	nop
.IF110:
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 64]	! saving to move
	ld	[%fp - 64],%o0	! load reference: move
	ld	[%o0],%o0
	mov	5,%o1		! %o1=5
	cmp	%o0,%o1
	bne	.LL112
	nop
	mov	1,%l7		! %l7=1
.LL112:
	stb	%l7,[%fp - 65]	! saving to $t106
	clr	%l7
	ldub	[%fp - 65],%l0	! load: $t106
	cmp	%l0,%g2
	bne	.IF113
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 72]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 76]	! saving to indexi
	mov	12,%o0		! %o0=12
	ld	[%fp - 76],%o1	! load reference: indexi
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 72],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 80]	! saving to $t107
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 84]	! saving to indexj
	mov	4,%o0		! %o0=4
	ld	[%fp - 84],%o1	! load reference: indexj
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 80],%o0	! load address: $t107
	add	%o0,%o1,%o2
	st	%o2,[%fp - 80]	! saving to $t107
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 88]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 92]	! saving to indexi
	ld	[%fp - 92],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 96]	! saving to $t108
	mov	12,%o0		! %o0=12
	ld	[%fp - 96],%o1	! load: $t108
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 88],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 100]	! saving to $t109
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 104]	! saving to indexj
	mov	4,%o0		! %o0=4
	ld	[%fp - 104],%o1	! load reference: indexj
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 100],%o0	! load address: $t109
	add	%o0,%o1,%o2
	st	%o2,[%fp - 100]	! saving to $t109
	ld	[%fp - 80],%o0	! load address: grid
	ld	[%fp - 100],%o1	! load address: grid
	call	swap,2
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 108]	! saving to indexi
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 112]	! saving to indexi
	ld	[%fp - 112],%o0	! load reference: indexi
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 116]	! saving to $t110
	ld	[%fp - 116],%l0	! load: $t110
	ld	[%fp - 108],%l1	! load reference: indexi
	st	%l0,[%l1]	! saving ref param: indexi
	b	.ELSE114
	nop
.IF113:
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 120]	! saving to move
	ld	[%fp - 120],%o0	! load reference: move
	ld	[%o0],%o0
	mov	4,%o1		! %o1=4
	cmp	%o0,%o1
	bne	.LL115
	nop
	mov	1,%l7		! %l7=1
.LL115:
	stb	%l7,[%fp - 121]	! saving to $t111
	clr	%l7
	ldub	[%fp - 121],%l0	! load: $t111
	cmp	%l0,%g2
	bne	.IF116
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 128]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 132]	! saving to indexi
	mov	12,%o0		! %o0=12
	ld	[%fp - 132],%o1	! load reference: indexi
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 128],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 136]	! saving to $t112
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 140]	! saving to indexj
	mov	4,%o0		! %o0=4
	ld	[%fp - 140],%o1	! load reference: indexj
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 136],%o0	! load address: $t112
	add	%o0,%o1,%o2
	st	%o2,[%fp - 136]	! saving to $t112
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 144]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 148]	! saving to indexi
	mov	12,%o0		! %o0=12
	ld	[%fp - 148],%o1	! load reference: indexi
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 144],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 152]	! saving to $t113
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 156]	! saving to indexj
	ld	[%fp - 156],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 160]	! saving to $t114
	mov	4,%o0		! %o0=4
	ld	[%fp - 160],%o1	! load: $t114
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 152],%o0	! load address: $t113
	add	%o0,%o1,%o2
	st	%o2,[%fp - 152]	! saving to $t113
	ld	[%fp - 136],%o0	! load address: grid
	ld	[%fp - 152],%o1	! load address: grid
	call	swap,2
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 164]	! saving to indexj
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 168]	! saving to indexj
	ld	[%fp - 168],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	sub	%o0,%o1,%o2
	st	%o2,[%fp - 172]	! saving to $t115
	ld	[%fp - 172],%l0	! load: $t115
	ld	[%fp - 164],%l1	! load reference: indexj
	st	%l0,[%l1]	! saving ref param: indexj
	b	.ELSE117
	nop
.IF116:
	ld	[%fp - 4],%l0	! load: this
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 176]	! saving to move
	ld	[%fp - 176],%o0	! load reference: move
	ld	[%o0],%o0
	mov	6,%o1		! %o1=6
	cmp	%o0,%o1
	bne	.LL118
	nop
	mov	1,%l7		! %l7=1
.LL118:
	stb	%l7,[%fp - 177]	! saving to $t116
	clr	%l7
	ldub	[%fp - 177],%l0	! load: $t116
	cmp	%l0,%g2
	bne	.IF119
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 184]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 188]	! saving to indexi
	mov	12,%o0		! %o0=12
	ld	[%fp - 188],%o1	! load reference: indexi
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 184],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 192]	! saving to $t117
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 196]	! saving to indexj
	mov	4,%o0		! %o0=4
	ld	[%fp - 196],%o1	! load reference: indexj
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 192],%o0	! load address: $t117
	add	%o0,%o1,%o2
	st	%o2,[%fp - 192]	! saving to $t117
	ld	[%fp - 4],%l0	! load: this
	mov	0,%l1		! %l1=0
	add	%l0,%l1,%l0
	st	%l0,[%fp - 200]	! saving to grid
	ld	[%fp - 4],%l0	! load: this
	mov	40,%l1		! %l1=40
	add	%l0,%l1,%l0
	st	%l0,[%fp - 204]	! saving to indexi
	mov	12,%o0		! %o0=12
	ld	[%fp - 204],%o1	! load reference: indexi
	ld	[%o1],%o1
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 200],%o0	! load address: grid
	add	%o0,%o1,%o2
	st	%o2,[%fp - 208]	! saving to $t118
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 212]	! saving to indexj
	ld	[%fp - 212],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 216]	! saving to $t119
	mov	4,%o0		! %o0=4
	ld	[%fp - 216],%o1	! load: $t119
	call	.mul,2
	nop
	mov	%o0,%o1		! %o0=%o1
	ld	[%fp - 208],%o0	! load address: $t118
	add	%o0,%o1,%o2
	st	%o2,[%fp - 208]	! saving to $t118
	ld	[%fp - 192],%o0	! load address: grid
	ld	[%fp - 208],%o1	! load address: grid
	call	swap,2
	nop
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 220]	! saving to indexj
	ld	[%fp - 4],%l0	! load: this
	mov	44,%l1		! %l1=44
	add	%l0,%l1,%l0
	st	%l0,[%fp - 224]	! saving to indexj
	ld	[%fp - 224],%o0	! load reference: indexj
	ld	[%o0],%o0
	mov	1,%o1		! %o1=1
	add	%o0,%o1,%o2
	st	%o2,[%fp - 228]	! saving to $t120
	ld	[%fp - 228],%l0	! load: $t120
	ld	[%fp - 220],%l1	! load reference: indexj
	st	%l0,[%l1]	! saving ref param: indexj
.IF119:
.ELSE117:
.ELSE114:
.ELSE111:
	assertMove_space = -328
	ret
	restore
.section	 ".text"
	.global run
	.type	 run, #function 
run:
	!#PROLOGUE# 0
	save	%sp, run_space, %sp
	!#PROLOGUE# 1
	st	%i0,[%fp - 4]	! saving to puzzle
	clr	%l7
.BEGWHILE120:
	ld	[%fp - 4],%o0	! load: puzzle
	call	puzzleComplete,1
	nop
	stb	%o0,[%fp - 5]	! saving to puzzleComplete
	ldub	[%fp - 5],%l0	! load: puzzleComplete
	xor	%l0,%g2,%l0	! negating
	stb	%l0,[%fp - 6]	! saving to $t121
	ldub	[%fp - 6],%l0	! load: $t121
	cmp	%l0,%g0
	be	.ENDWHILE121
	nop
	ld	[%fp - 4],%o0	! load: puzzle
	call	prompt,1
	nop
	ld	[%fp - 4],%o0	! load: puzzle
	call	getMove,1
	nop
	ld	[%fp - 4],%l0	! load: puzzle
	mov	48,%l1		! %l1=48
	add	%l0,%l1,%l0
	st	%l0,[%fp - 12]	! saving to move
	ld	[%fp - 12],%o0	! load reference: move
	ld	[%o0],%o0
	mov	0,%o1		! %o1=0
	cmp	%o0,%o1
	bne	.LL122
	nop
	mov	1,%l7		! %l7=1
.LL122:
	stb	%l7,[%fp - 13]	! saving to $t122
	clr	%l7
	ldub	[%fp - 13],%l0	! load: $t122
	cmp	%l0,%g2
	bne	.IF123
	nop
	ret	
	restore
.IF123:
	ld	[%fp - 4],%o0	! load: puzzle
	call	assertMove,1
	nop
	ld	[%fp - 4],%o0	! load: puzzle
	call	print,1
	nop
	b	.BEGWHILE120
	nop
.ENDWHILE121:
	run_space = -120
	ret
	restore
.section	 ".text"
	.global main
	.type	 main, #function 
main:
	!#PROLOGUE# 0
	save	%sp, main_space, %sp
	!#PROLOGUE# 1
	mov	1,%g2		! %g2=1
	clr	%l7
	mov	1,%o0		! %o0=1
	mov	52,%o1		! %o1=52
	call	calloc,1
	nop
	set	puzzle,%l0	! %l0=puzzle
	st	%o0,[%l0]	! saving to global: puzzle
	set	puzzle,%o0	! %o0=puzzle
	ld	[%o0],%o0	! load value of global: puzzle
	call	init,1
	nop
	set	puzzle,%o0	! %o0=puzzle
	ld	[%o0],%o0	! load value of global: puzzle
	call	print,1
	nop
	set	puzzle,%o0	! %o0=puzzle
	ld	[%o0],%o0	! load value of global: puzzle
	call	run,1
	nop
	main_space = -104
	ret
	restore
	.common	puzzle,4,52
	.common	srandseed,4,4
	.ident	"Oberon Copyright 2002, Bashir Eghbali"
