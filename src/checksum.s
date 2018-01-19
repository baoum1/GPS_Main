/**********************************************************
@file		checksum.s
@version	1.0
@date		14.01.2018
@author		L. Heller
@brief		source file checksum
**********************************************************/

.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.global Kontrollsumme
.global GetSegment_Length
 
    .data                   @ section data (initialized data)
/************************************************************************
* Constants
************************************************************************/

    .text                   @ section text (executable code)
    .align
/************************************************************************
* Code
************************************************************************/
/**
 Ueberprueft die GPS Daten anhand der Kontrollsumme
 Zwischen den Zeichen '$' und '*' befinden sich die Daten, die mit EXOR verglichen werden.
 Die zwei Zahlen nach dem '*' sind im HEX Format und muessen aneinandergereiht dem EXOR Wert entsprechen.
 */

Kontrollsumme:
 	PUSH	{r4, lr}
 	MOV		r1, r0

// Erstes '$' zeichen wird gesucht
loop1:
 	LDRB	r2, [r1], #1
 	CMP		r2, #0
 	BEQ		wrong
 	CMP 	r2, #'$'
 	BEQ		data
 	B		loop1

 data:
 	LDRB	r2, [r1], #1
 	cmp		r2, #0
 	BEQ		wrong
 	CMP		r2, #'$'
 	BEQ		wrong
 	MOV		r3, r2

// Die Daten zwichen '$' und '*' werden mit XOR verknuepft
 loop2:
 	LDRB	r2, [r1], #1
 	CMP		r2, #0
 	BEQ		wrong
 	CMP		r2, #'$'
 	BEQ		wrong
 	CMP		r2, #'*'
 	BEQ		compare
 	EOR		r3, r2
 	B		loop2


// Die Zahlen der Kontrollsumme werden ins richtige Format gebracht
// und mit dem Ergebnis der XOR Operationen verglichen
 compare:
	LDRB	r2, [r1], #1
	SUB		r2, #48
	LSL		r2, r2, #4
	LDRB	r4, [r1], #1
	SUB		r4, #48
	ADD		r2, r4
	CMP		r2, r3
	BEQ		correct

 wrong:
 	MOV		r0, #0			// GPS String ist nicht korrekt uebermittelt worden
 	B		ende

correct:
	MOV		r0,	#1			// Rueckgabewert: 1 wenn korrekt, 0 wenn fehlerhaft

 ende:
 	POP		{r4, pc}



//Segmentlaenge berechnen
GetSegment_Length:
 	PUSH	{lr}
 	MOV		r1, r0
 	MOV		r0,	#0			// Rueckgabewert: Segmentlaenge

// Erstes '$' zeichen wird gesucht
loop3:
 	LDRB	r2, [r1], #1
 	CMP 	r2, #'$'
 	BEQ		loop4
 	B		loop3

// Die Daten zwichen '$' und '*' werden gezaehlt
 loop4:
 	LDRB	r2, [r1], #1
 	CMP		r2, #'*'
 	BEQ		ende2
 	ADD		r0, #1
 	B		loop4

 ende2:
 	POP		{pc}


