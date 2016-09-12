#ifndef _H_ELF
#define _H_ELF

#include "sys/multiboot.h"

#define ELF32_ST_TYPE(i) ((i)&0xf)

typedef struct
{
  unsigned int name;
  unsigned int type;
  unsigned int flags;
  unsigned int addr;
  unsigned int offset;
  unsigned int size;
  unsigned int link;
  unsigned int info;
  unsigned int addralign;
  unsigned int entsize;
} __attribute__((packed)) elf_section_header_t;

typedef struct
{
  unsigned int name;
  unsigned int value;
  unsigned int size;
  unsigned char  info;
  unsigned char  other;
  unsigned short shndx;
} __attribute__((packed)) elf_symbol_t;

typedef struct
{
  elf_symbol_t *symtab;
  unsigned int      symtabsz;
  const char   *strtab;
  unsigned int      strtabsz;
} elf_t;

// Takes a multiboot structure and returns an elf structure containing the symbol information.
elf_t elf_from_multiboot (multiboot_t *mb);

// Looks up a symbol by address.
const char *elf_lookup_symbol (unsigned int addr, elf_t *elf);

#endif