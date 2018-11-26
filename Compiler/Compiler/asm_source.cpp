#define _CRT_SECURE_NO_WARNINGS
#define USINT unsigned short int
#include <stdio.h>
void cast(USINT& _a) {
__asm {
push eax
push ecx
mov eax, _a
mov ecx, [eax]
cmp ecx, 0
je end_cast
mov ecx, 1
mov [eax], ecx
end_cast:
pop ecx
pop eax
}}
char __format[4] = "%hu";
USINT _a = 0;
USINT _b = 0;
USINT _c = 0;
USINT _d = 0;
USINT _temp = 0;
int main() {
__asm {
push eax
push ebx
push offset _a
push offset __format
call scanf
add esp, 8
push offset _a
call cast
add esp, 4
push offset _b
push offset __format
call scanf
add esp, 8
push offset _b
call cast
add esp, 4
push offset _c
push offset __format
call scanf
add esp, 8
push offset _c
call cast
add esp, 4
push offset _d
push offset __format
call scanf
add esp, 8
push offset _d
call cast
add esp, 4
xor eax, eax
mov ax, [_a]
push eax
xor eax, eax
mov ax, [_b]
push eax
pop eax
pop ebx
or eax, ebx
push eax
pop eax
mov [_temp], ax
xor eax, eax
mov ax, [_temp]
push eax
xor eax, eax
mov ax, [_c]
push eax
pop eax
pop ebx
or eax, ebx
push eax
pop eax
mov [_temp], ax
xor eax, eax
mov ax, [_temp]
push eax
xor eax, eax
mov ax, [_d]
push eax
pop eax
pop ebx
or eax, ebx
push eax
pop eax
mov [_temp], ax
xor eax, eax
mov ax, [_temp]
push eax
pop eax
cmp eax, 1
jne else0
push _d
push offset __format
call printf
add esp, 6
push _c
push offset __format
call printf
add esp, 6
push _b
push offset __format
call printf
add esp, 6
push _a
push offset __format
call printf
add esp, 6
jmp end_if0
else0:
xor eax, eax
mov ax, [_a]
push eax
pop eax
xor eax, 1
push eax
pop eax
mov [_a], ax
xor eax, eax
mov ax, [_b]
push eax
pop eax
xor eax, 1
push eax
pop eax
mov [_b], ax
xor eax, eax
mov ax, [_c]
push eax
pop eax
xor eax, 1
push eax
pop eax
mov [_c], ax
xor eax, eax
mov ax, [_d]
push eax
pop eax
xor eax, 1
push eax
pop eax
mov [_d], ax
push _d
push offset __format
call printf
add esp, 6
push _c
push offset __format
call printf
add esp, 6
push _b
push offset __format
call printf
add esp, 6
push _a
push offset __format
call printf
add esp, 6
end_if0:
push _temp
push offset __format
call printf
add esp, 6
pop ebx
pop eax
}
return 0;
}