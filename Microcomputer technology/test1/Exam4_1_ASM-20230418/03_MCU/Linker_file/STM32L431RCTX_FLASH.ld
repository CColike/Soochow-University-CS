/*======================================================================
**文件名称：STM32L431RCTX_FLASH.ld（链接文件）
**制作单位：SD-Arm(sumcu.suda.edu.cn)
**更新记录：20181201-20200629
**======================================================================*/

ENTRY(Reset_Handler)
/*（1）【变动】相关常数定义*/
/*MCU的Flash每扇区大小与起始地址*/
MCU_SECTORSIZE =2048; 
MCU_FLASH_ADDR_START = 0x8000000;   
/*User程序开始扇区号与结束扇区号*/
GEC_USER_SECTOR_START  =26;       /*【0启动】1/2处，0-0启动，26-从BIOS启动*/
GEC_USER_SECTOR_END =126;   
/*MCU的RAM区起始地址与结束地址*/         
GEC_USER_RAM_START =0x20004000;  
GEC_USER_RAM_END  =0x2000ffff;   
/*堆栈有关初值*/
_estack =  0x2000ffff;	       /*.s文件中有用*/
_Min_Heap_Size  = 0x200 ;      /* 堆最小值，RTOS用*/
_Min_Stack_Size = 0x400 ;	   /* 栈最小值，ROTS用*/
           
/*（2）【固定】MEMORY段定义*/
MEMORY
{
	/*中断向量表*/
	INTVEC(rx) : ORIGIN =MCU_FLASH_ADDR_START + MCU_SECTORSIZE * GEC_USER_SECTOR_START , 
	                   LENGTH = MCU_SECTORSIZE
	/*Flash代码区*/                   
    FLASH (rx) : ORIGIN = MCU_FLASH_ADDR_START + MCU_SECTORSIZE * (GEC_USER_SECTOR_START + 1) , 
                  LENGTH = MCU_SECTORSIZE * (GEC_USER_SECTOR_END - GEC_USER_SECTOR_START )
    /*USER的RAM空间。*/
    RAM  (rwx) : ORIGIN = GEC_USER_RAM_START, 
                  LENGTH = GEC_USER_RAM_END - GEC_USER_RAM_START + 1
}

/*（3）【变动】SECTIONS段定义*/
SECTIONS
{
/* （3.1）【固定】中断向量表 */
  .isr_vector :
  {
    . = ALIGN(8);
    KEEP(*(.isr_vector))
    . = ALIGN(8);
  } >INTVEC
  
  /**********************（3.2）【变动】以下为STM32保留部分***********************/
  
  /* The program code and other data into "FLASH" Rom type memory */
  .text :
  {
    . = ALIGN(8);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(8);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  .rodata :
  {
    . = ALIGN(8);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(8);
  } >FLASH

  .ARM.extab   : { 
  	. = ALIGN(8);
  	*(.ARM.extab* .gnu.linkonce.armextab.*)
  	. = ALIGN(8);
  } >FLASH
  
  .ARM : {
    . = ALIGN(8);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(8);
  } >FLASH

  .preinit_array     :
  {
    . = ALIGN(8);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(8);
  } >FLASH
  
  .init_array :
  {
    . = ALIGN(8);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(8);
  } >FLASH
  
  .fini_array :
  {
    . = ALIGN(8);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(8);
  } >FLASH


  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "RAM" Ram type memory */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
    
  } >RAM AT> FLASH
  
  /* Uninitialized data section into "RAM" Ram type memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
