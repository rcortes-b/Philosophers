# Philosophers

gettimeofday --> Parametros: Una struct timeval la cual tiene como variables el tiempo epoch en segundos y microsegundos. Segundo parametro: NULL. Devuelve 0 if good y 1 if error // En la struct se almacena el valor sirve para ver cuanto ha durado un proceso
pthread_create --> Se utiliza para crear el hilo. Parametros: La variable hilo el cual crear, una struct la cual se puede se le puede pasar el contenido que va a tener el nuevo hilo, la funcion que ejecutara el inicio del hilo y el ultimo sera el puntero de la funcion que iniciara el hilo :::: void *start_routine(void *arg). 0 if good, error number if error
pthread_join --> La funcion espera a que termine el hilo pasado por parametro. Parametros: El hilo al que esperar que termine y un void * el cual puede ser NULL o una variable donde almacenar el exit code del thread. 0 if good 1 if error
pthread_detach --> Detach == Independiente / Individual . El hilo pasado como parametro se ejecutara de forma independiente

// MUTEX

pthread_mutex_init --> Inicia el mutex Parametros: mutex struct y atributos. (as pthread_create attr, creo), is nulleable. 0 if good error num if error.
pthread_mutex_destroy -->  Destruye el mutex Parametros: mutex struct. 0 if good error num if error
pthread_mutex_lock --> Pone un "candado" a los otros hilos de modo que hasta que este no se ejecute, los otros no van a actuar. 0 if good error num if error.
pthread_mutex_unlock --> Quita el "candado" de lock. 0 if good error num if error.

Dining Philo Problem
https://medium.com/science-journal/the-dining-philosophers-problem-fded861c37ed