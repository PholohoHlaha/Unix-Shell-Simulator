!********************************************************************
!Copyright 2010-2015 K.C. Wang, <kwang@eecs.wsu.edu>
!This program is free software: you can redistribute it and/or modify
!it under the terms of the GNU General Public License as published by
!the Free Software Foundation, either version 3 of the License, or
!(at your option) any later version.

!This program is distributed in the hope that it will be useful,
!but WITHOUT ANY WARRANTY; without even the implied warranty of
!MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!GNU General Public License for more details.

!You should have received a copy of the GNU General Public License
!along with this program.  If not, see <http://www.gnu.org/licenses/>.
!********************************************************************/

        OSSEG  = 0x1000
	
       .globl _main,_running,_scheduler,_proc,_procSize  ! IMPORT
       .globl _tswitch,_getc,_putc ! EXPORT
       
               mov  ax,#OSSEG    ! set ES to 0x1000
        mov  es,ax
        xor  bx,bx          ! clear BX = 0
        
        !---------------------------------------------------
        !  read boot BLOCK to [0x1000,0]     
        !---------------------------------------------------
        xor  dx,dx          ! drive 0, head 0
        xor  cx,cx          ! cyl 0    sector 0        
        incb cl             ! cyl 0, sector 1
        mov  ax, #0x0202    ! READ 1 block
        int  0x13
	
        jmpi   start,OSSEG

start:	mov  ax,cs
	mov  ds,ax
	mov  ss,ax

        mov  sp,#_proc
	add  sp,_procSize

	call _main
idle:	 jmp  idle

_getc:

        xor   ah, ah           ; clear ah
        int   0x16             ; call BIOS to get a char in AX

        ret                ; remove 4 bytes from the stack

;----------------------------------------------
; void putc(char c, char page, char color) function: print a char
;----------------------------------------------
_putc:
        push  bp
        mov   bp, sp

        mov   al, 4[bp]       ; get the char into al
        mov   ah,#14         ; ah = 0x0E (teletype output)
        movb   bl,#0x0D        ! bL = cyan color 

        int   0x10             ; call BIOS to display the char

        pop   bp
        ret    
	
_tswitch:
SAVE:	
	push ax
	push bx
	push cx
	push dx
	push bp
	push si
	push di
	pushf
	mov  bx,_running
	mov  2[bx],sp

FIND:	call _scheduler

RESUME:
	mov  bx,_running
	mov  sp,2[bx]
	popf
	pop  di
	pop  si
	pop  bp
	pop  dx
	pop  cx
	pop  bx
	pop  ax

	ret
