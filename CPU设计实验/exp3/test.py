from pwn import *
context.arch = 'mips'


'''
/*
__init()
{
    
    main();
    while(1);
}

int main()
{
        BYTE mem[0x100];
        int i = 0;
        while(i != 0x100)
        {
                mem[i] = i;
                i = i + 1;
        }
        return 0;
}

RAM: 4K 

stack_frame:
    sp---->+0x0         byte buff[0x100]
    
    
    
           +0x100       uint32_t i
           +0x104       fp
           +0x108       ra
*/
'''

code = '''
__init: 
    addu  $sp,$zero,$zero
    addiu $sp, 0x1000 - 0x100       /*256的栈空间*/
    /* jal __main */
    beq $zero,$zero,__main
    __pause:
        beq $zero,$zero,__pause
    
__main:
    addiu $sp,- (0x4 + 0x100 + 0x8)
    
    sw $fp, 0x104($sp)
    sw $ra, 0x108($sp)
    
    addu $fp,$zero,$sp
    
    /* i = 0 */
    sw $zero, 0x100($sp)            
    
    /**/
_loop:
    lw $v0,0x100($sp)
    addiu $v1,$zero,0x100
    beq $v0,$v1,_loop_end
    
    /* mem[off] = i*/
    lw $v0,0x100($sp)  
    addu $v1,$v0,$sp
    sb $v0,0x0($v1)
    
    /*i++*/
    lw $v0,0x100($sp)
    addiu $v0,$v0,1
    sw $v0,0x100($sp)

    beq $zero,$zero,_loop
_loop_end:
  
    lw $fp,0x104($sp)
    lw $ra,0x108($sp)
    
    addiu $sp,0x100 + 0x4 + 0x8
    jr $ra

'''


code = '''
beq $zero,$zero,test
nop
nop
test:
nop

'''

code = asm(code)



for i in range(len(code) // 4):
    print("mem[%d] = " % i + hex(u32(code[i * 4 : i * 4 + 4])).replace("0x","32'h") + ";")