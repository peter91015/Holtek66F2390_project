; Generated by holtek-gcc v3.19, Thu Aug 15 10:10:05 2024
; 
; Configuration:
;       with long instruction
;       Multi-ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 16
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.19" "build 20130711"
; Rebuild 718

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [16]
mduwr0 equ [59h]
mduwr1 equ [5ah]
mduwr2 equ [5bh]
mduwr3 equ [5ch]
mduwr4 equ [5dh]
mduwr5 equ [5eh]
mduwrctrl equ [5fh]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
___pf equ [36]
___pd equ [30]
public _LCD_Cmd
#pragma debug scope 2 1
#line 6 "d:\htk\mp3_test\LCD.c"
_LCD_Cmd .section 'code'
_LCD_Cmd proc
    local _LCD_Cmd_2 db 1 dup(?)	; 0,1
	mov ra,a
	mov _LCD_Cmd_2[0],a
#pragma debug variable 8 2 _LCD_Cmd_2+0 "data"
#line 7 "d:\htk\mp3_test\LCD.c"
	mov a,ra
	mov [36],a
#line 8 "d:\htk\mp3_test\LCD.c"
	clr [30].4
#line 9 "d:\htk\mp3_test\LCD.c"
	clr [30].5
#line 10 "d:\htk\mp3_test\LCD.c"
	set [30].6
#line 11 "d:\htk\mp3_test\LCD.c"
	mov a,3
	mov _delay_ms_2[0],a
	clr _delay_ms_2[1]
	fcall _delay_ms
#line 12 "d:\htk\mp3_test\LCD.c"
	clr [30].6
	ret
_LCD_Cmd endp
#line 12 "d:\htk\mp3_test\LCD.c"
#pragma debug scope 1 1
public _LCD_Reset
#pragma debug scope 3 1
#line 15 "d:\htk\mp3_test\LCD.c"
_LCD_Reset .section 'code'
_LCD_Reset proc
#line 16 "d:\htk\mp3_test\LCD.c"
	mov a,56
	fcall _LCD_Cmd
#line 17 "d:\htk\mp3_test\LCD.c"
	mov a,12
	fcall _LCD_Cmd
#line 18 "d:\htk\mp3_test\LCD.c"
	mov a,6
	fcall _LCD_Cmd
#line 19 "d:\htk\mp3_test\LCD.c"
	mov a,1
	fcall _LCD_Cmd
#line 20 "d:\htk\mp3_test\LCD.c"
	mov a,2
	fcall _LCD_Cmd
	ret
_LCD_Reset endp
#line 20 "d:\htk\mp3_test\LCD.c"
#pragma debug scope 1 1
public _LCD_Senddata
#pragma debug scope 4 1
#line 23 "d:\htk\mp3_test\LCD.c"
_LCD_Senddata .section 'code'
_LCD_Senddata proc
    local _LCD_Senddata_2 db 1 dup(?)	; 0,1
	mov ra,a
	mov _LCD_Senddata_2[0],a
#pragma debug variable 8 4 _LCD_Senddata_2+0 "data"
#line 24 "d:\htk\mp3_test\LCD.c"
	mov a,ra
	mov [36],a
#line 25 "d:\htk\mp3_test\LCD.c"
	set [30].4
#line 26 "d:\htk\mp3_test\LCD.c"
	clr [30].5
#line 27 "d:\htk\mp3_test\LCD.c"
	set [30].6
#line 28 "d:\htk\mp3_test\LCD.c"
	mov a,3
	mov _delay_ms_2[0],a
	clr _delay_ms_2[1]
	fcall _delay_ms
#line 29 "d:\htk\mp3_test\LCD.c"
	clr [30].6
	ret
_LCD_Senddata endp
#line 29 "d:\htk\mp3_test\LCD.c"
#pragma debug scope 1 1
public _LCD_Print_Str
#pragma debug scope 5 1
#line 33 "d:\htk\mp3_test\LCD.c"
_LCD_Print_Str .section 'code'
_LCD_Print_Str proc
public _LCD_Print_Str_2
    local _LCD_Print_Str_2 db 2 dup(?)	; 2,0
#pragma debug pointer 42 7 5
#pragma debug variable 42 5 _LCD_Print_Str_2+0 "p"
#line 34 "d:\htk\mp3_test\LCD.c"
	jmp _L5
_L6:
#line 35 "d:\htk\mp3_test\LCD.c"
	inc _LCD_Print_Str_2[0]
	sz z
	inc _LCD_Print_Str_2[1]
	mov a,ra
	fcall _LCD_Senddata
_L5:
#line 34 "d:\htk\mp3_test\LCD.c"
	mov a,_LCD_Print_Str_2[0]
	mov mp,a
	mov a,_LCD_Print_Str_2[1]
	mov sbp,a
	fcall _Crom2Prom
	mov ra,a
	sz ra
	jmp _L6
	ret
_LCD_Print_Str endp
#line 34 "d:\htk\mp3_test\LCD.c"
#pragma debug scope 1 1
#pragma debug struct_begin 43 "__pd_bits"
#pragma debug field 21 8 0 1 "__pd0" ;0,1
#pragma debug field 21 8 0 1 "__pd1" ;1,1
#pragma debug field 21 8 0 1 "__pd2" ;2,1
#pragma debug field 21 8 0 1 "__pd3" ;3,1
#pragma debug field 21 8 0 1 "__pd4" ;4,1
#pragma debug field 21 8 0 1 "__pd5" ;5,1
#pragma debug field 21 8 0 1 "__pd6" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 44 ""
#pragma debug field 2 43 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 44 1 ___pd "__pd" 1
#pragma debug struct_begin 45 "__pf_bits"
#pragma debug field 21 8 0 1 "__pf0" ;0,1
#pragma debug field 21 8 0 1 "__pf1" ;1,1
#pragma debug field 21 8 0 1 "__pf2" ;2,1
#pragma debug field 21 8 0 1 "__pf3" ;3,1
#pragma debug field 21 8 0 1 "__pf4" ;4,1
#pragma debug field 21 8 0 1 "__pf5" ;5,1
#pragma debug field 21 8 0 1 "__pf6" ;6,1
#pragma debug field 21 8 0 1 "__pf7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 46 ""
#pragma debug field 2 45 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 46 1 ___pf "__pf" 1
extern _delay_ms_2:byte
extern _delay_ms:near

; 
; Generated by holtek-gcc v3.19, Thu Aug 15 10:10:05 2024
; Rebuild 718
; end of file
