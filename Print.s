; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 
decCnt EQU 0
fixCnt EQU 0 
star   EQU 42
dot    EQU 46
counter EQU 0
string EQU 0x20007000
    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix
	


    AREA    |.text|, CODE, READONLY, ALIGN=2
	preserve8
    THUMB


;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
		PUSH{LR,R4,R5}
		;create local variable
			SUB SP, #4 ; allocating space 
			MOV R5, SP	; R5 is the frame pointer
			 
			MOV R1, #0	;storing the local variable counter on the stack
			STR R1, [R5]
			
			;Make this a local variable
			MOV R2, #10 ;R2= 10= DIVISOR
			
			CMP R0, #0
			BNE ODloop
			ADD R0, #0x30
			BL ST7735_OutChar
			B done
			
ODloop
			UDIV R1, R0, R2 ; R1= (N+R)/10,R/10=0
			MUL R1, R1, R2 ; R1= N/10*10
			SUB R1, R0, R1 ; 	R1= N- (R1= N/10*10) OR N%10
			PUSH {R1} 
			UDIV R0,R0,R2 ; N = N/10
			CMP R0,#0
			BEQ ODout
			B ODloop
			
		
ODout		
			CMP SP, R5
			BEQ done		; stack is empty if SP == R5
			POP{R0}
			ADD R0,#0x30
			BL ST7735_OutChar
			B ODout
			
done		ADD SP, #4

			POP{LR,R4, R5}
			
			BX LR
			
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11

LCD_OutFix	
	PUSH {R12,LR,R4,R5}
	
	MOV R12, R0 ; 
	
	LDR R1,=star
	MOV R4,#5
 	;MAKING THE STRING "*.***"
		LDR R2,=string
putstr  
		STRB R1,[R2]	;storing character 
		ADD R2,R2,#1	
		CMP R4,#5
		BNE next
		LDR R1,=dot
		SUBS R4,#1
		B putstr
next	LDR R1,=star
		SUBS R4,#1
		BNE putstr
		MOV R4,#0
		STRB R4,[R2]	;writing null at the end of string 
		
	SUB SP, #4 ; allocating space 
	MOV R1, #30
	STR R1, [SP, #fixCnt]
		
	MOV R3, #9999
	CMP R0, R3
	BLS skip
	
	;outputs default

	LDR R0,=string
	BL ST7735_OutString
	B exit

;isolates the highest digit 	
skip 
	MOV R3, #1000
	UDIV R1, R12, R3 ; R1= N/1000	
;outputs 
	ADD R1,#0x30	;adding ASCII offset
	MOV R0, R1
	BL ST7735_OutChar
		
;outputs decimal
	LDR R0,=dot
	BL ST7735_OutChar
	
	MOV R3, #1000
	UDIV R1, R12, R3 ; R1= N/1000
;isolate hundreds place
	MUL R1, R1, R3 ; R1= N/1000*1000
	SUB R12, R12, R1 ; 	R12= N- (N/1000*1000) OR N%1000
	
	MOV R3, #100
	UDIV R1, R12, R3 ; R1= R12/100
;outputs 
	ADD R1,#0x30	;adding ASCII offset
	MOV R0, R1
	BL ST7735_OutChar

	MOV R3, #100
	UDIV R1, R12, R3 ; R1= R12/100
;isolate tens place
	MUL R1, R1, R3 ; R1= N/100*100
	SUB R12, R12, R1 ; 	R15= N- (N/100*100) OR N%100
	
	MOV R3, #10
	UDIV R1, R12, R3 ; R1= R12/10
;outputs 
	ADD R1,#0x30	;adding ASCII offset
	MOV R0, R1
	BL ST7735_OutChar

	MOV R3, #10
	UDIV R1, R12, R3 ; R1= R12/10
;isolates ones place
	MUL R1, R1, R3 ; R1= N/10*10
	SUB R12, R12, R1 ; 	R15= N- (N/10*10) OR N%10
;outputs 
	ADD R12,#0x30	;adding ASCII offset
	MOV R0, R12
	BL ST7735_OutChar
	
exit		ADD	SP, #4
			POP {R12,LR,R4,R5}
     BX   LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file