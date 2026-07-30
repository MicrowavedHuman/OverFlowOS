#include <kernel/pmm.h>

static uint8_t *bitmap;

static size_t total_pages;
static size_t free_pages;

static void bitmap_set(size_t bit)
{
    bitmap[byte] |= (1 << offset);
}
static void bitmap_clear(size_t bit)
{
    bitmap[byte] &= ~(1 << offset);
}
static bool bitmap_test(size_t bit)
{
    return ((bitmap[byte] & (1 << offset)) != 0);
}

void pmm_init(memory_map_t *map)
{

}

void *pmm_alloc_page(void)
{

}

void pmm_free_page(void *page)
{

}

size_t pmm_total_pages(void)
{

}

size_t pmm_free_pages(void)
{

}
