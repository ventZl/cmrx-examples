#pragma once

#include <cmrx/ipc/mutex.h>
#include <cmrx/ipc/notify.h>
#include <cmrx/ipc/rpc.h>
#include <cmrx/ipc/isr.h>
#include <../../cmrx/include/extra/queue_server/queue.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t * semaphore;
} osal_semaphore_def_t;

typedef uint32_t * osal_semaphore_t;

typedef futex_t osal_mutex_def_t;
typedef futex_t * osal_mutex_t;

typedef struct {
    struct Queue queue;
    uint8_t depth;
    uint8_t size;
} osal_queue_def_t;

#define OSAL_QUEUE_DEF(_int_set, _name, _depth, _type)    \
osal_queue_def_t _name = {                              \
    .depth = _depth,                            \
    .size = sizeof(_type) \
}

typedef struct Queue * osal_queue_t;

extern unsigned char defer_buffer[32];
extern volatile osal_queue_t defer_queue;
extern volatile bool defer_busy;


TU_ATTR_ALWAYS_INLINE static inline osal_semaphore_t osal_semaphore_create(osal_semaphore_def_t* semdef)
{
    return semdef->semaphore;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_delete(osal_semaphore_t sem_hdl)
{
    (void) sem_hdl;
    return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr)
{
    if (!in_isr)
    {
        notify_object(sem_hdl);
        return true;
    }
    else
    {
        isr_notify_object(sem_hdl);
        return true;
    }
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_wait(osal_semaphore_t sem_hdl, uint32_t msec)
{
    (void) msec;
    wait_for_object(sem_hdl, 0);
    return true;
}

//void osal_semaphore_reset(osal_semaphore_t sem_hdl); // TODO removed

TU_ATTR_ALWAYS_INLINE static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef)
{
    int rv = futex_init(mdef);
    return rv == 0 ? mdef : NULL;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_delete(osal_mutex_t mutex_hdl)
{
    return futex_destroy(mutex_hdl) == 0;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_lock (osal_mutex_t mutex_hdl, uint32_t msec)
{
    (void) msec;
    return futex_lock(mutex_hdl) == 0;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl)
{
    return futex_unlock(mutex_hdl) == 0;
}

TU_ATTR_ALWAYS_INLINE static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef)
{
    (void) qdef;
    bool rv = queue_init(&qdef->queue, qdef->depth, qdef->size);
    if (rv)
    {
        return &qdef->queue;
    }
    return NULL;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_delete(osal_queue_t qhdl)
{
    (void) qhdl;
//    rpc_call(qhdl, destroy);
    return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec)
{
    (void) msec;
    return queue_receive(qhdl, (uint8_t *) data);
}


TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr)
{
    bool rv = queue_send(qhdl, (const uint8_t *) data);

    if (!rv)
    {
        return false;
    }

    if (!in_isr)
    {
        notify_object(qhdl);
    } else {
        isr_notify_object(qhdl);
    }

    return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_empty(osal_queue_t qhdl)
{
    return queue_empty(qhdl);
}
