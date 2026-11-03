	.build_version macos, 26, 0	sdk_version 26, 5
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__Z6squarei                     ; -- Begin function _Z6squarei
	.p2align	2
__Z6squarei:                            ; @_Z6squarei
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #12]
	mul	w0, w8, w9
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__Z14sum_of_squaresii           ; -- Begin function _Z14sum_of_squaresii
	.p2align	2
__Z14sum_of_squaresii:                  ; @_Z14sum_of_squaresii
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-4]
	str	w1, [sp, #8]
	ldur	w0, [x29, #-4]
	bl	__Z6squarei
	str	w0, [sp, #4]                    ; 4-byte Folded Spill
	ldr	w0, [sp, #8]
	bl	__Z6squarei
	mov	x8, x0
	ldr	w0, [sp, #4]                    ; 4-byte Folded Reload
	add	w0, w0, w8
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	__Z12bump_counterv              ; -- Begin function _Z12bump_counterv
	.p2align	2
__Z12bump_counterv:                     ; @_Z12bump_counterv
	.cfi_startproc
; %bb.0:
	adrp	x9, _global_counter@PAGE
	ldr	w8, [x9, _global_counter@PAGEOFF]
	add	w8, w8, #1
	str	w8, [x9, _global_counter@PAGEOFF]
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #0                          ; =0x0
	stur	w8, [x29, #-12]                 ; 4-byte Folded Spill
	stur	wzr, [x29, #-4]
	mov	w0, #3                          ; =0x3
	mov	w1, #4                          ; =0x4
	bl	__Z14sum_of_squaresii
	stur	w0, [x29, #-8]
	bl	__Z12bump_counterv
	ldur	w8, [x29, #-8]
	mov	x10, x8
	adrp	x8, _global_counter@PAGE
	ldr	w8, [x8, _global_counter@PAGEOFF]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x10, [x9]
	str	x8, [x9, #8]
	mov	x8, #42                         ; =0x2a
	str	x8, [x9, #16]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldur	w0, [x29, #-12]                 ; 4-byte Folded Reload
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_global_counter                 ; @global_counter
.zerofill __DATA,__common,_global_counter,4,2
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Result: %d, Counter: %d, Magic: %d\n"

.subsections_via_symbols
