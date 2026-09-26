#include "extract.h"
#include "extract_tab.h"

extract_init() {
  extract_tab[0] = extract0;
}
int (*extract_tab[])(unsigned char*, unsigned char*, int) = {
    extract0,
    rextract0,
    extract1,
    rextract1,
    extract2,
    rextract2,
    extract3,
    rextract3,
    extract4,
    rextract4,
    extract5,
    rextract5,
    extract6,
    rextract6,
    extract7,
    rextract7,
    extract_all,
    rextract_all
    };
