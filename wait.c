int tsleep(int event);
int twakeup(int event);
int texit(int status);
int join(int pid, int *status);
int tsleep(int event)//La misma función que se utiliza en las partes pasadas
{
  running->event=event;
  running->status = SLEEP;
  enqueue(&sleepList,running);
  tswitch();
}
int twakeup(int event)//La misma función que se utiliza en las partes pasadas
{
  PROC **LS = &sleepList;
  PROC *p = *LS;
  while(p)
     {
      PROC *q = p->next;
      printf("Depertar = %d\n", p->pid);
      if(p->event == event){
      	*LS=(*LS)->next;
	p->status=READY;
	enqueue(&readyQueue,p);
      }
      p=q;
     }
}

int join(int targetPID,int *status){
	while(1){
		int taskwithtargetpid=0;
		PROC *p,*h; 
		for (int i=0; i<NPROC; i++){ 
		p = &proc[i]; 
		 if(p->pid == targetPID && (p->status == ZOMBIE || p->status == READY || p->status == SLEEP)){
			taskwithtargetpid=1;
			h=p;
		}
		} //Busca que haya un proceso disponible para unirse con el target pid
		
		if(!taskwithtargetpid)
			{
			printf("NOTHREAD Error, no hay un hilo disponible con el PID: %d\n",targetPID);
			return NOTHREAD;//No hay proceso disponible con ese pid en readyqueue	
			}
		if(h->joinPid==running->pid){//Corrobora que no se genere un Deadlock con el target pid
			printf("DEADLOCK error\n");
			return DEADLOCK;//Deadlock 
		}
		running->joinPid = targetPID;
		running->joinPtr = h;
		if(h->status==ZOMBIE){
			*status = h->exitStatus;
			h->status=FREE;
			enqueue(&freeList,h);
			printf("Operación exitosa La tarea: %d se unio a la tarea: %d\n", running->pid, targetPID);
			return h->pid;		
		}
		printf("Operación exitosa La tarea: %d se unio a la tarea: %d\n", running->pid, targetPID);
		tsleep(targetPID);
	}

}

int texit(int value) { //La misma función que se utiliza en las partes pasadas, unicamente se modifica la busqueda de padres-familiares por los joinPid
	printf("task %d in texit value=%d\n", running->pid, running->pid);
		
	PROC **LS = &sleepList;
  	PROC *p = *LS;
	int tasktojoin=0;
  	while(p)
     	{
      		PROC *q = p->next;
      		if(p->joinPid == running->pid){
      			tasktojoin=1;
      		}
      		p=q;
     	}
	if(!tasktojoin){
		running->status = FREE;
		running->priority = 0;
		enqueue(&freeList, running); 
		printList("freeList", freeList);
	}
	else{
	 	running->status=ZOMBIE;
		twakeup(running->pid);
	}
	running->exitStatus=value;
	tswitch(); 
}
