#include "../../common/tm_api.h"

/* associative array */
void assoc_init(const int hashpower_init);
TX_SAFE item *assoc_find(const char *key, const size_t nkey, const uint32_t hv);
TX_SAFE int assoc_insert(item *item, const uint32_t hv);
TX_SAFE void assoc_delete(const char *key, const size_t nkey,
                          const uint32_t hv);
void do_assoc_move_next_bucket(void);
int start_assoc_maintenance_thread(void);
void stop_assoc_maintenance_thread(void);
extern unsigned int hashpower;
