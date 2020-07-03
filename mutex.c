typedef struct mutex{
int lock; // mutex lock state: 0 for unlocked, 1 for locked
PROC *owner; // pointer to owner of mutex; may also use PID
PROC *queue; // FIFO queue of BLOCKED waiting PROCs
}MUTEX;
MUTEX *mutex_create() // create a mutex and initialize it
{
MUTEX *mp = (MUTEX *)malloc(sizeof(MUTEX));
mp->lock = mp->owner = mp->queue = 0;
return mp;
}
void mutex_destroy(MUTEX *mp){ free(mp); }
int mutex_lock(MUTEX *mp){ // implement mutex locking operation }
int mutex_unlock(MUTEX *mp){// implement mutex unlocking operation }