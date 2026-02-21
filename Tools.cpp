/********************************************
 * Developer: KAZU
 * Project: KAZU-MOD
 * Telegram: https://t.me/K_4441
 * Purpose: Memory Tools for ESP & Patching
 ********************************************/

#include "Tools.h"
#include <mach/mach.h>
#include <mach-o/dyld.h>

// Global variable for target process (Current Task for iOS)
mach_port_t target_task = mach_task_self();

/**
 * Validates if the memory address is readable
 */
bool Tools::IsPtrValid(void *addr) {
    if (!addr) return false;
    vm_size_t size = 0;
    vm_address_t address = (vm_address_t)addr;
    vm_region_basic_info_data_64_t info;
    mach_msg_type_number_t count = VM_REGION_BASIC_INFO_COUNT_64;
    mach_port_t object_name;
    
    kern_return_t kr = vm_region_64(mach_task_self(), &address, &size, VM_REGION_BASIC_INFO, (char *)&info, &count, &object_name);
    return (kr == KERN_SUCCESS && (info.protection & VM_PROT_READ));
}

/**
 * Standard Memory Read (Used for ESP Data)
 */
bool Tools::Read(void *addr, void *buffer, size_t length) {
    if (!IsPtrValid(addr)) return false;
    return memcpy(buffer, addr, length) != 0;
}

/**
 * Standard Memory Write (Used for Patches)
 */
bool Tools::Write(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    uintptr_t align_addr = (uintptr_t)addr & ~(page_size - 1);
    
    // Change memory protection to Writeable on iOS
    if (mprotect((void *)align_addr, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == 0) {
        memcpy(addr, buffer, length);
        return true;
    }
    return false;
}

/**
 * Get Base Address of the Game Module (Executable)
 */
uintptr_t Tools::GetBaseAddress(const char *name) {
    for (uint32_t i = 0; i < _dyld_image_count(); i++) {
        const char *img_name = _dyld_get_image_name(i);
        if (strstr(img_name, name)) {
            return (uintptr_t)_dyld_get_image_header(i);
        }
    }
    return 0;
}

/**
 * Futuristic Pattern Scanner for iOS
 */
#define INRANGE(x, a, b) (x >= a && x <= b)
#define getBits(x) (INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

uintptr_t Tools::FindPattern(const char *lib, const char *pattern) {
    uintptr_t start = GetBaseAddress(lib);
    if (!start) return 0;

    // Get segment size (simple scan range)
    uintptr_t end = start + 0x8000000; // Scan up to 128MB (Adjustable)

    const unsigned char *pat = reinterpret_cast<const unsigned char *>(pattern);
    uintptr_t firstMatch = 0;

    for (uintptr_t pCur = start; pCur < end; ++pCur) {
        if (!*(uint8_t *)pat) return firstMatch;
        if (*(uint8_t *)pat == '\?' || *(uint8_t *)pCur == getByte(pat)) {
            if (!firstMatch) firstMatch = pCur;
            if (!pat[2]) return firstMatch;
            if (*(uint16_t *)pat == '\?\?' || *(uint8_t *)pat != '\?') pat += 3;
            else pat += 2;
        } else {
            pat = reinterpret_cast<const unsigned char *>(pattern);
            firstMatch = 0;
        }
    }
    return 0;
}
