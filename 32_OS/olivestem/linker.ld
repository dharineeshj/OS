ENTRY(start)
SECTIONS
{
    . = 1M;    /* GRUB loads kernels at 1MB */

    .text :
    {
        *(.text)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}