#ifndef __H_MULTIBOOT
#define __H_MULTIBOOT

typedef struct
{
  unsigned int flags;
  unsigned int mem_lower;
  unsigned int mem_upper;
  unsigned int boot_device;
  unsigned int cmdline;
  unsigned int mods_count;
  unsigned int mods_addr;
  unsigned int num;
  unsigned int size;
  unsigned int addr;
  unsigned int shndx;
  unsigned int mmap_length;
  unsigned int mmap_addr;
  unsigned int drives_length;
  unsigned int drives_addr;
  unsigned int config_table;
  unsigned int boot_loader_name;
  unsigned int apm_table;
  unsigned int vbe_control_info;
  unsigned int vbe_mode_info;
  unsigned int vbe_mode;
  unsigned int vbe_interface_seg;
  unsigned int vbe_interface_off;
  unsigned int vbe_interface_len;
} __attribute__((packed)) multiboot_t;

#endif