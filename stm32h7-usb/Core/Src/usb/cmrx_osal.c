#include <tusb.h>

osal_semaphore_t osal_semaphore_create(osal_semaphore_def_t* semdef);
bool osal_semaphore_delete(osal_semaphore_t semd_hdl);
bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr);
bool osal_semaphore_wait(osal_semaphore_t sem_hdl, uint32_t msec);
void osal_semaphore_reset(osal_semaphore_t sem_hdl); // TODO removed

osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef);
bool osal_mutex_delete(osal_mutex_t mutex_hdl)
bool osal_mutex_lock (osal_mutex_t sem_hdl, uint32_t msec);
bool osal_mutex_unlock(osal_mutex_t mutex_hdl);

osal_queue_t osal_queue_create(osal_queue_def_t* qdef);
bool osal_queue_delete(osal_queue_t qhdl);
bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec);
bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr);
bool osal_queue_empty(osal_queue_t qhdl);
