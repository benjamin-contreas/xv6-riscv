# Informe tarea 2

### Alumno: Benjamin Contreras

### Objetivo: Modificar el programador de procesos en xv6 para implementar un sistema de prioridades.

#### **_El desarrollo de esta tarea fue hecho en un sistema operativo Linux Mint 21.3_**

## 1. Modificar la estructura de proceso (kernel/proc.h)

En la estructura de proceso vamos a agregar los campos necesarios para el priority boost, siendo estos priority y boost. Esto lo realizamos al final del struct proc.

```c
// Per-process state
struct proc {
    // Code ...
    struct inode *cwd;           // Current directory
    char name[16];               // Process name (debugging)
    int priority;                // Process priority
    int boost;                   // Boost value
}
```

## 2. Inicializar los campos creados en kernel/proc.c

En el archivo proc.c vamos a ubicar la funcion encargada de inicializar los procesos, la cual se llama `allocproc()`. En esta funcion agregaremos la inicializacion para los nuevos campos, priority y boost.

```c
allocproc(void)
{
  struct proc *p;

  for(p = proc; p < &proc[NPROC]; p++) {
    acquire(&p->lock);
    if(p->state == UNUSED) {
      goto found;
    } else {
      release(&p->lock);
    }
  }
  return 0;

found:
  p->pid = allocpid();
  p->state = USED;

  // Inicializar los campos priority y boost
  p->priority = 0; // Inicializar en prioridad 0
  p->boost = 1; // Inicializar boost en 1

  // ...
}
```
## 3. Modificar la planificacion de procesos

Vamos ahora a la funcion `scheduler()` , tambien encontrada en proc.c, y añadimos la lógica que permita incrementar la prioridad de los procesos en cada entrada al scheduler
