.data
numdigits dq ?
numelements dq ?
currentdigit dq ?

.code
mysort proc
	;r8 = iterator
	;rcx = pointer to array
	;rdx = size of the array

	xor r8, r8
	xor r9, r9

	mov rax, rcx
	inc r8
FindBiggest:
	;mov current index into r9b
	mov r9b, [rcx + r8]

	;get the address of the current index
	mov r10, rcx
	add r10, r8

	;if the current index is greater that what rax is pointing to then set rax to the current index
	cmp [rax], r9b
	cmovb rax, r10 

	;increment the index counter
	inc r8
	;check to see if through the whole list
	cmp r8, rdx
	jne FindBiggest

	;decrement the length of the list and save dereferenced rax
	dec rdx
	mov r10b, [rax]

	;swap the last element in the list with the element at rax
	mov [rcx + rdx], r10b
	mov [rax], r9b

	;set rax back to the begining and reset the iterator
	mov rax, rcx
	xor r8, r8

	;if the whole list has been gone though then exit
	cmp rdx, 1
	jne FindBiggest
	ret

mysort endp

bubblesort proc
	; If there is only one item in the array then return because it is already sorted
	cmp rdx, 1
	jle Finish


	; set r8 and r9 as the iterating variables
	mov r8, 0
	mov r9, 1
	; r10 is used as a check to see if anything changed.
	mov r10, 1

	; clear rax, and r11
	xor rax, rax
	xor r11, r11
LoopHead:

	; compare the index of r8, and r9
	mov al, [rcx + r9]
	mov r11b, [rcx + r8]
	cmp r11, rax

	; if they are in the correct order skip to continue
	jle cont

	; swap the indexes of r8, and r9
	mov [rcx + r9], r11b
	mov [rcx + r8], al

	; set r10 to zero because there were things changed.
	mov r10, 0
cont:
	; increment the iterating varibles
	inc r8
	inc r9

	; check to see if the whole list has been gone through
	cmp r9, rdx
	jne LoopHead

	; check to see if nothing changed meaning sorting is finished
	cmp r10, 1
	mov r10, 1
	je Finish

	; if sorting isnt finished reset the iterators and start from the begining
	mov r8, 0
	mov r9, 1
	jmp LoopHead

Finish:
ret
bubblesort endp

bucketsort proc
	;take 2 parameters out of 1
	mov r10, r9
	and r9d, r9d
	shr r10, 32
	
	cmp r9, 1
	jle Finish

	mov numelements, r9
	mov numdigits, r10

	;move array pointers
	mov r11, rcx ;input
	mov r12, rdx ;output
	
	;used for counting
	mov r15, 8
	mul r15


	;clear counters
	mov r10, 0
	mov r9, 0
	;clear rax, rcx, and rdx for division/multiplication
	xor rax, rax
	xor rdx, rdx
	xor rcx, rcx
	

	mov currentdigit, 1
CountSetup:
	;rcx = currentdigit * 10, r12 = currentdigit
	mov rcx, currentdigit
	mov r13, currentdigit
	mov rax, 10
	mul cl
	mov cx, ax
	xor rax, rax

CountLoop:
	;get the value of the current element
	;mod 10*placevalue
	xor rdx, rdx
	mov al, [r11 + r9]
	div cx
	;divide by placevalue
	mov ax, dx
	xor rdx, rdx
	div r13w

	xor rdx, rdx
	mul r15

	add qword ptr [r8 + rax], 1
	inc r9

	cmp r9, numelements
	jne CountLoop

	;set iterators
	mov rax, 8
	mov rdx, 0
Prefixsum:
	;add each element of the counting array with the one before it
	mov r14, [r8 + rdx]

	add [r8 + rax], r14

	add rax, 8
	add rdx, 8
	cmp rax, 80
	jne Prefixsum

	xor r10, r10
ReconstructArray:
	xor rax, rax
	dec r9
	;get the value of the current element, rax = value
	;mod 10*placevalue
	xor rdx, rdx
	mov al, [r11 + r9]
	div cx
	;divide by placevalue
	mov ax, dx
	xor dx, dx
	div r13w

	xor rdx, rdx
	mul r15

	mov r10, [r8 + rax]
	dec r10
	mov [r8 + rax], r10

	mov al, [r11 + r9]

	mov [r12 + r10], al
	
	cmp r9, 0
	jnz ReconstructArray

	dec numdigits
	cmp numdigits, 0
	jz Finish

	mov rax, 0
ResetCount:
	;clears the counter
	mov [r8 + r9], rax

	add r9, 8
	cmp r9, 80
	jne ResetCount


	xor r9, r9
MoveArray:
	;move input array to output array
	mov al, [r12 + r9]
	mov [r11 + r9], al

	inc r9
	cmp r9, numelements
	jne MoveArray

	xor r9, r9
	mov currentdigit, rcx
	jmp CountSetup


Finish:
	ret
bucketsort endp

lshift32timesandcombine proc
	shl rcx, 32
	or rcx, rdx
	mov [r8], rcx
	ret
lshift32timesandcombine endp



end

