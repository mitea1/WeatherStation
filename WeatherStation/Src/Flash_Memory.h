/*
 * Flash.h
 *
 *  Created on: Apr 3, 2016
 *      Author: Simon
 */
/*----- Header-Files -------------------------------------------------------*/
#include <stm32l1xx.h>				/* Processor STM32F407IG				*/
#include "stm32l1xx_hal_rcc.h"

#define MAN_FAM_DEN_VAL 0x25       // Used for Chip Identity (see datasheet)
#define PAGE_COUNT 4096            // Number of pages in the chip
#define BYTES_PER_PAGE 264         // Bytes per page of the chip
#define MAP_BYTES 1920             // Bytes required to make 'node' usage (map) -> (((PAGE_COUNT - PAGE_PER_SECTOR) * BYTES_PER_PAGE) / NODE_SIZE_PARENT) / 8bits
#define MAP_PAGES 8                // Pages required to hold 'node' usage (map) -> CEILING(MAP_BYTES / BYTES_PER_PAGE)
#define NODE_PARENT_PER_PAGE 4     // Number of parent nodes per page -> BYTES_PER_PAGE / NODE_SIZE_PARENT
#define NODE_CHILD_MAX_NODE 2	   // Last valid child node block (due to size of child = size of parent * 2)
#define NODE_PER_PAGE 2            // Number of nodes per page
#define BLOCK_COUNT 512            // Number of blocks in the chip
#define SECTOR_START 1             // The first whole sector number in the chip
#define SECTOR_END 15               // The last whole sector number in the chip
#define PAGE_PER_SECTOR 256        // Number of pages per sector in the chip

#define SECTOR_ERASE_0_SHT_AMT 12  // The shift amount used for a sector zero part erase (see comments below)
#define SECTOR_ERASE_N_SHT_AMT 17  // The shift amount used for a sector erase (see comments below)
#define BLOCK_ERASE_SHT_AMT 12     // The shift amount used for a block erase (see comments below)
#define PAGE_ERASE_SHT_AMT 9       // The shift amount used for a page erase (see comments below)
#define WRITE_SHT_AMT 9            // The shift amount used for a write operation (see comments below)
#define READ_OFFSET_SHT_AMT 9      // The shift amount used for a read operation (see comments below)

// sector erase -> 264size -> OP: 0x7C -> 0a/0b -> 3 address bytes -> 3 D/C, 9 Sector Address (PA11-PA3), 12 D/C -> PA3=0 -> 0a, PA3=1 -> 0b
// sector erase -> 264size -> OP: 0x7C -> 1/15 -> 3 address bytes -> 3 D/C, 4 Sector Address Bits, 17 D/C
// sector 0a -> 8 pages, sector 0b -> 248 pages, sector 1/15 -> 256 pages
// block erase -> 264size -> OP: 0x50 -> 3 address bytes -> 3 D/C, 9 Block Num, 12 D/C -> 512 Blocks
// page erase -> 264size -> OP: 0x81 -> 3 address bytes -> 3 D/C, 12 Page Num, 9 D/C -> 4096 Pages

// Write_p1 -> 264size -> MMP to Buffer T -> OP: 0x53 -> 3 address bytes -> 3 D/C, 12 Page Address, 9 D/C
// write_p2 -> 264size -> MMP PROG T Buffer -> OP: 0x82 -> 3 address bytes -> 3 D/C, 12 Page Address, 9 Buffer Address

// Read -> 528size -> Low Freq Read -> 0P: 0x03 -> 3 address bytes -> 12 Page Address, 9 Offset, 3 D/C ?

// Common for all flash chips
#define FLASH_MANUF_ID                0x1F
#define FLASH_OPCODE_SECTOR_ERASE     0x7C  // Opcode to perform a sector erase
#define FLASH_OPCODE_BLOCK_ERASE      0x50  // Opcode to perform a block erase
#define FLASH_OPCODE_PAGE_ERASE       0x81  // Opcode to perform a page erase
#define FLASH_OPCODE_READ_STAT_REG    0xD7  // Opcode to perform a read of the status register
#define FLASH_OPCODE_MAINP_TO_BUF     0x53  // Opcode to perform a Main Memory Page to Buffer Transfer
#define FLASH_OPCODE_MMP_PROG_TBUF    0x82  // Opcode to perform a Main Memory Page Program Through Buffer
#define FLASH_OPCODE_LOWF_READ        0x03  // Opcode to perform a Continuous Array Read (Low Frequency)
#define FLASH_OPCODE_BUF_WRITE        0x84  // Opcode to write into buffer
#define FLASH_OPCODE_BUF_TO_PAGE      0x83  // Opcode to write buffer to given page
#define FLASH_OPCODE_READ_DEV_INFO    0x9F  // Opcode to perform a Manufacturer and Device ID Read
#define FLASH_READY_BITMASK           0x80  // Bitmask used to determine if the chip is ready (poll status register). Used with FLASH_OPCODE_READ_STAT_REG.
#define FLASH_SECTOR_ZER0_A_PAGES     8
#define FLASH_SECTOR_ZERO_A_CODE      0
#define FLASH_SECTOR_ZERO_B_CODE      1

// Flash Page Mappings
#define FLASH_PAGE_MAPPING_NODE_META_DATA  0  // Reserving two (2) pages for node management meta data
#define FLASH_PAGE_MAPPING_NODE_MAP_START  2  // Reserving two (2) pages for node management meta data
#define FLASH_PAGE_MAPPING_NODE_MAP_END    (FLASH_PAGE_MAPPING_NODE_MAP_START + MAP_PAGES)  // Last page used for node mapping
#define FLASH_PAGE_MAPPING_GFX_START       (FLASH_PAGE_MAPPING_NODE_MAP_END + 1)  // Start GFX Mapping
#define FLASH_PAGE_MAPPING_GFX_END         (PAGE_PER_SECTOR) // End GFX Mapping
#define FLASH_PAGE_MAPPING_GFX_SIZE        (FLASH_PAGE_MAPPING_GFX_END - FLASH_PAGE_MAPPING_GFX_START)


#define FLASH_SIZE          ((uint32_t)PAGE_COUNT * (uint32_t)BYTES_PER_PAGE)

extern void writeToFlash(uint16_t *data, uint8_t size);
extern void readFromFlash(uint16_t *pValue, uint8_t size);
void waitForFlash(void);
