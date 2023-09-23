#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_PHILOSOPHERS 200

typedef enum e_state
{
    THINKING,
    EATING,
    SLEEPING,
    DEAD
} t_state;

typedef struct s_philo
{
    int id;
    t_state state;
    pthread_t thread;
    int eat_count;
    long last_meal;
} t_philo;

typedef struct s_table
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_eat;
    struct timeval start_time;
    pthread_mutex_t *forks;
    t_philo *philos;
} t_table;

long get_timestamp(t_table *table) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec - table->start_time.tv_sec) * 1000 + (current_time.tv_usec - table->start_time.tv_usec) / 1000;
}

void take_forks(t_table *table, int philosopher_id) {
    pthread_mutex_lock(&table->forks[philosopher_id]);
    pthread_mutex_lock(&table->forks[(philosopher_id + 1) % table->num_philos]);

    printf("%ld %d has taken a fork\n", get_timestamp(table), philosopher_id + 1);
    printf("%ld %d has taken a fork\n", get_timestamp(table), philosopher_id + 1);
}

void put_forks(t_table *table, int philosopher_id) {
    pthread_mutex_unlock(&table->forks[philosopher_id]);
    pthread_mutex_unlock(&table->forks[(philosopher_id + 1) % table->num_philos]);
}

void eat(t_table *table, int philosopher_id) {
    printf("%ld %d is eating\n", get_timestamp(table), philosopher_id + 1);
    usleep(table->time_to_eat * 1000);
}

void sleep_philosopher(t_table *table, int philosopher_id) {
    printf("%ld %d is sleeping\n", get_timestamp(table), philosopher_id + 1);
    usleep(table->time_to_sleep * 1000);
}

void think(t_table *table, int philosopher_id) {
    printf("%ld %d is thinking\n", get_timestamp(table), philosopher_id + 1);
}

void *philosopher_thread(void *arg) {
    t_table *table = (t_table *)arg;
    int philosopher_id = table->philos[table->num_eat].id; // Corrected philosopher_id assignment
    int meals_eaten = 0;

    while (table->num_eat == 0 || meals_eaten < table->num_eat) {
        philosopher_id = table->philos[table->num_eat].id; // Updated philosopher_id inside the loop
        think(table, philosopher_id);
        take_forks(table, philosopher_id);
        eat(table, philosopher_id);
        put_forks(table, philosopher_id);
        sleep_philosopher(table, philosopher_id);
        meals_eaten++;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    t_table table;
    table.start_time.tv_sec = 0;
    table.start_time.tv_usec = 0;

    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    table.num_philos = atoi(argv[1]);
    table.time_to_die = atoi(argv[2]);
    table.time_to_eat = atoi(argv[3]);
    table.time_to_sleep = atoi(argv[4]);

    if (argc == 6) {
        table.num_eat = atoi(argv[5]);
    } else {
        table.num_eat = 0;
    }

    if (table.num_philos <= 1 || table.num_philos > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers. Please use a value between 2 and %d.\n", MAX_PHILOSOPHERS);
        return 1;
    }

    gettimeofday(&table.start_time, NULL);

    table.forks = (pthread_mutex_t *)malloc(table.num_philos * sizeof(pthread_mutex_t));
    table.philos = (t_philo *)malloc(table.num_philos * sizeof(t_philo));

    for (int i = 0; i < table.num_philos; i++) {
        pthread_mutex_init(&table.forks[i], NULL);
        table.philos[i].id = i;
        pthread_create(&table.philos[i].thread, NULL, philosopher_thread, &table);
    }

    for (int i = 0; i < table.num_philos; i++) {
        pthread_join(table.philos[i].thread, NULL);
        pthread_mutex_destroy(&table.forks[i]);
    }

    free(table.forks);
    free(table.philos);

    return 0;
}
