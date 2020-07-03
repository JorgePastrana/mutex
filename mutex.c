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
int mutex_lock(MUTEX *mp){ 
if(mp->lock == 0){
mp->lock=1;
mp->owner = running;
}else{
enqueue(&(mp->queue),running);
tswitch();
}
}// implement mutex locking operation }
int mutex_unlock(MUTEX *mp){
if(mp->lock==0||(mp->lock ==1 && running != mp->owner)){
return -1;
}
if(mp->queue == 0){
mp->lock=0;
mp->owner = 0;
}
else{
PROC *p = dequeue(mp->queue);
mp->owner = p;
enqueue (&readyQueue,p);

}
}// implement mutex unlocking operation }
