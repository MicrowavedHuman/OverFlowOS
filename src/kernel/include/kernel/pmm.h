#ifndef _KERNEL_PMM_H
#define _KERNEL_PMM_H

#define PAGE_SIZE 4096

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void pmm_init(memory_map_t *map);

void *pmm_alloc_page(void);

void pmm_free_page(void *page);

size_t pmm_total_pages(void);

size_t pmm_free_pages(void);

#endif
