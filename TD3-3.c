#include <stdio.h>
#include <pthread.h>  // Bibliothèque pour gérer les threads POSIX
#include <semaphore.h>  // Bibliothèque pour les sémaphores POSIX
#include <unistd.h>  // Bibliothèque pour les fonctions système (ex : sleep)

// Déclaration d'un sémaphore global
sem_t mutex;

// Fonction exécutée par chaque thread
void *multi_thread(void *arg) {
    // Attente du sémaphore - bloque l'exécution jusqu'à ce que le sémaphore soit disponible
    sem_wait(&mutex);
    
    // Code exécuté dans chaque thread : ici, affichage d'un message avec l'identifiant du thread
    printf("Hello world from thread %ld\n", (long)arg);
    
    // Libération du sémaphore - permet à un autre thread d'acquérir le sémaphore
    sem_post(&mutex);
    
    return NULL;  // Retour de la fonction, le thread se termine ici
}

int main() {
    // Initialisation du sémaphore :
    // &mutex : adresse du sémaphore,
    // 0 : indique qu'il est partagé entre threads (pas entre processus),
    // 1 : valeur initiale du sémaphore, ici 1, ce qui signifie qu'un seul thread peut accéder à la ressource à la fois.
    printf("Coucou Louis");
    sem_init(&mutex, 0, 1);
    
    pthread_t threads[5];  // Tableau de threads pour stocker les identifiants des 5 threads
    
    // Création de 5 threads
    for (long i = 0; i < 5; i++) {
        // pthread_create() crée un thread :
        // &threads[i] : l'identifiant du thread,
        // NULL : paramètres par défaut pour l'attribut du thread,
        // multi_thread : fonction à exécuter dans chaque thread,
        // (void*)i : passer l'identifiant du thread (i) comme argument à la fonction
        pthread_create(&threads[i], NULL, multi_thread, (void*)i);
    }
    
    // Attente de la fin de chaque thread :
    // pthread_join() bloque le programme principal jusqu'à ce que chaque thread termine
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Détruire le sémaphore - libère les ressources associées au sémaphore
    sem_destroy(&mutex);
    
    return 0;  // Fin du programme principal

    // Fichier modifié
}
