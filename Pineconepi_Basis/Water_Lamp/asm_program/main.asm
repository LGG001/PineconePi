;Define correlation register
P1M0	DATA	094H
P1M1	DATA	093H

P5M0	DATA 	0CAH
P5M1	DATA	0C9H
	
P5 		DATA	0C8H
LED_EN	EQU		P5.5



;Program start address 0x0000
		ORG		0000H
		LJMP	MAIN	;Jump to main program
		
		
		ORG		0100H	;Main start address 0x0100
MAIN:
		MOV		SP,#3FH		
		
		;Initializes the P5 and P3 port modes
		MOV		P1M0,#0FFH
		MOV		P1M1,#00H
		MOV		P5M0,#0FFH
		MOV		P5M1,#00H
		CLR		LED_EN		;Enable LED control
		MOV		A,#0FEH		;A = 0B1111 1110
		
		LOOP:
				MOV 	P1,A	;Assign A tp P1
				LCALL	DELAY	;Delay
				RL		A		;A <<= 1
				AJMP	LOOP	;Cycle show
		;Delay subroutine
		DELAY:
				MOV 	R3,#40
				D1:
						MOV		R4,#80
				D2:
						MOV		R5,#250	
				DJNZ	R5,$
				DJNZ	R4,D2
				DJNZ	R3,D1
				RET
		
		END



