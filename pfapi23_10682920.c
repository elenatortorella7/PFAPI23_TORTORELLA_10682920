
// Created by Utente on 24/08/2023.
//
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100



//struttura nodo dell'albero

typedef struct tStation {
    int distance;       // Distanza dalla partenza dell'autostrada chiave
    int numCars;        // Num di macchine disponibili
    int autonomies[512];    //  array di autonomie
    int maxAutonomy;         //autonomia massima
    struct tStation *left; // puntatore a figlio sin
    struct tStation *right;   // punt a ramo destro

} tStation;




//ricerca di una stazione( se la stazione esiste torna il puntatore alla stazione, altrimenti NULL)

tStation *searchStation(tStation *root, int distance) {

    if (root == NULL || root->distance == distance) {
        return root;
    }

    if (distance < root->distance) {
        return searchStation(root->left, distance);
    }

    return searchStation(root->right, distance);
}




//funzione che cerca l'autonomia e ne ritorna il puntatore a intero

int* searchCar(int *autonomies,int numCars,int autonomy){
    for (int i = 0; i < numCars; i++) {
        if (autonomies[i] == autonomy) {
            return &autonomies[i];
        }
    }
    return NULL;

}

// creazione della Stazione

tStation *createStation(int distance, int numCars, const int autonomy[]) {

    tStation *newStation = (tStation *)malloc(sizeof(tStation));
    newStation->distance = distance;
    newStation->numCars = numCars;
    newStation->maxAutonomy=0;

    //setta il massimo
    if(numCars!=0) {
       // newStation->autonomies = NULL;
       // newStation->autonomies = (int *) malloc(sizeof(int) * numCars);
        for (int i = 0; i < numCars; i++) {
            newStation->autonomies[i] = autonomy[i];
            if(newStation->autonomies[i]>newStation->maxAutonomy){
                newStation->maxAutonomy=newStation->autonomies[i];
            }
        }


    }
    newStation->left = newStation->right = NULL;
    return newStation;

}

//inserimento della Stazione nell'autostrada

tStation *insert(tStation *root, int distance, int numCars, int aut[]) {
    if (root == NULL) {
        return createStation(distance, numCars, aut); // Crea e restituisci un nuovo nodo
    }

    if (distance < root->distance) {
        root->left = insert(root->left, distance, numCars, aut);
    } else if (distance > root->distance) {
        root->right = insert(root->right, distance, numCars, aut);
    }

    return root;
}

//funzione ausiliaria trova successore

tStation *findMin(tStation *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

//funzione ausiliaria per eliminare la stazione dall'autostrada

tStation *deleteStation(tStation *root, int key) {
    if (root == NULL) {
        return root;
    }

    // Ricerca del nodo da eliminare
    if (key < root->distance) {
        root->left = deleteStation(root->left, key);
    } else if (key > root->distance) {
        root->right = deleteStation(root->right, key);
    } else {
        // Il nodo con la chiave è stato trovato, gestione dei casi di eliminazione
        if (root->left == NULL) {
            tStation *temp = root->right;
            free(root);
            return temp;  // Restituisce il nuovo nodo radice (può essere NULL se l'albero aveva un solo nodo)
        } else if (root->right == NULL) {
            tStation *temp = root->left;
            free(root);
            return temp;  // Restituisce il nuovo nodo radice
        } else {
            // Il nodo ha due figli, troviamo il successore in ordine
            tStation *temp = findMin(root->right);

            // Copia i dati del successore nel nodo corrente
            root->distance = temp->distance;
            root->numCars = temp->numCars;
            root->maxAutonomy = temp->maxAutonomy;
            memcpy(root->autonomies, temp->autonomies, sizeof(root->autonomies));
            // Elimina il successore dalla sottostruttura destra
            root->right = deleteStation(root->right, temp->distance);
        }
    }
    return root;  // Restituisce il nodo radice aggiornato
}

































/*tStation *deleteStation(tStation *root, int distance) {
    if (root == NULL) {
        return root;
    }

    if (distance < root->distance) {
        root->left = deleteStation(root->left, distance);
    } else if (distance > root->distance) {
        root->right = deleteStation(root->right, distance);
    } else {
        // Il nodo con la chiave è stato trovato
        if (root->left == NULL) {
            tStation *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            tStation *temp = root->left;
            free(root);
            return temp;
        }

        // Se il nodo ha due figli, trova il successore
        tStation *temp = findMin(root->right);
        root->distance = temp->distance;
        root->numCars = temp->numCars;

        memcpy(root->autonomies, temp->autonomies, sizeof(root->autonomies));

        // Elimina il successore dalla sottostruttura destra
        root->right = deleteStation(root->right, temp->distance);
    }
    return root; // Restituisci la radice aggiornata
}
*/
//aggiungi stazione


tStation *addStn(tStation* root, int distance,int numCars,int aut[]) {

if(root==NULL){

    root = createStation(distance, numCars, aut);
    insert(root, root->distance,numCars,aut);
    printf("aggiunta\n");
     return root;                             //chiama insert, che se la radice è nullla crea


}else if(searchStation(root,distance)==NULL) {

        tStation *newStation = NULL;
        newStation = createStation(distance, numCars, aut);
        insert(root, newStation->distance,numCars,aut);
        printf("aggiunta\n");
    }
    else printf("non aggiunta\n");
    return root;
}


// demolisci stazione (successivamente incorporare delete in questa funzione)

void demStn(tStation* root,int distance){

    if(searchStation(root,distance)==NULL){
        printf("non demolita\n");
    } else {
        root = deleteStation(root, distance);
        printf("demolita\n");
    }

}



//funzione aggiungi macchina

void addCar(tStation *root, int distance,int aut) {

    tStation * station = searchStation(root,distance);

    if (station==NULL) {
        printf("non aggiunta\n");
        return;
    }

    else if(station->numCars<512){
        station->numCars++;
      //  station->autonomies = realloc(station->autonomies, sizeof(int) * station->numCars);
           station->autonomies[station->numCars - 1] = aut;
            if(aut>station->maxAutonomy) {
                station->maxAutonomy = aut;
            }
            printf("aggiunta\n");


        }else{printf("non aggiunta\n");}
    }


//funzione rottama auto

void scrCar(tStation *root, int distance, int aut) {
    tStation *station = searchStation(root, distance);
    if (station == NULL) {
        printf("non rottamata\n");
        return;
    } else {
        int *srcCar = searchCar(station->autonomies, station->numCars, aut);

        if (srcCar == NULL) {
            printf("non rottamata\n");
            return;
        } else {
            int index = srcCar - station->autonomies;

            // Sposta gli elementi successivi a sinistra per riempire il vuoto
                for (int j = index; j < station->numCars ; j++) {
                    station->autonomies[j] = station->autonomies[j + 1];
                }
                station->numCars--;

                //find max
                station->maxAutonomy = station->autonomies[0];
                for (int i = 1; i < station->numCars; i++) {

                    if (station->autonomies[i] > station->maxAutonomy) {
                        station->maxAutonomy = station->autonomies[i];
                    }
                }
            printf("rottamata\n");

            }
        }
    }


//funzione che controlla la raggiungibilità

bool reachable(tStation *root, int src,int dst) {

    tStation *srcStation = searchStation(root, src);
    tStation *dstStation = searchStation(root, dst);

    if (srcStation == NULL || dstStation == NULL) {
        return false;
    } else {

        // int numCars = srcStation->numCars;
        int effDist = abs(dst - src);
        //int *autonomies = srcStation->autonomies;
        if (srcStation->maxAutonomy >= effDist) {

            return true;
        }


        return false;
    }
}

// ricerca altri nodi raggiungibili e riempe l'array di int per il confronto

void searchAndFill(struct tStation *root, struct tStation *currNode, int lastStop, int dst, int reachableArray[],int* i) {
    if (currNode == NULL) {
        return;
    }

    // Controlla se il nodo corrente soddisfa la condizione  lastStop è la penultima fermata
    if ((currNode->distance < lastStop) && reachable(currNode, currNode->distance,dst) ){
        reachableArray[*i] = currNode->distance;
        (*i)++;
    }

    // Visita il sottoalbero sinistro e destro
    searchAndFill(root,currNode->left,lastStop,dst, reachableArray, i);
    searchAndFill(root,currNode->right, lastStop,dst, reachableArray, i);
}

// ricerca percorso migliore avanti
//all'inizio c'era root

struct tStation* findNextStop(struct tStation *currNode, struct tStation* nextNodeMin,tStation* destNode,int start) {

    if (currNode != NULL) {
        if ((currNode->distance >= start) && (currNode->distance < destNode->distance) && (currNode->maxAutonomy>=(destNode->distance - currNode->distance))
            && (nextNodeMin == NULL || currNode->distance < nextNodeMin->distance)) {
            nextNodeMin = currNode;
        }

        if (currNode->distance >= start) {
            nextNodeMin = findNextStop(currNode->left, nextNodeMin, destNode,start );
        }

        if (currNode->distance < destNode->distance) {
            nextNodeMin = findNextStop(currNode->right, nextNodeMin, destNode,start);
        }
    }

    return nextNodeMin;
}



struct tStation* findNextStopReverse(struct tStation *currNode, struct tStation* nextNodeMax, tStation* destNode,int start) {
    // è grande start è grande dst è piccola

    if (currNode != NULL) {

        if ((currNode->distance <= start) && (currNode->distance > destNode->distance) && (currNode->maxAutonomy>=(currNode->distance-destNode->distance))
            && (nextNodeMax == NULL|| currNode->distance > nextNodeMax->distance)) {
            nextNodeMax = currNode;
            //  printf("%d ",nextNodeMax->distance);
        }
        if(currNode->distance>destNode->distance) {
            nextNodeMax = findNextStopReverse(currNode->left, nextNodeMax, destNode, start);
        }

        if(currNode->distance<=start){

        nextNodeMax = findNextStopReverse( currNode->right, nextNodeMax, destNode,start);
        }
    }

    return nextNodeMax;
}





//riempi array percorso
    void fillPath(int* route, int index, int station) {
    route[index] =station;
    }

    void fillPathStation(tStation*route[],int index,tStation *station){
    route[index]=station;
}




struct tStation* findPredecessor(struct tStation* root, int valMagg) {
    struct tStation* predecessor = NULL;

    while (root != NULL) {
        if (valMagg > root->distance) {
            predecessor = root; // Il nodo corrente potrebbe essere il predecessore
            root = root->right; // Continua la ricerca nel sottoalbero destro
        } else if (valMagg < root->distance) {
            root = root->left; // Continua la ricerca nel sottoalbero sinistro
        } else {
            // Il nodo con la chiave è stato trovato
            if (root->left != NULL) {
                // Se esiste un sottoalbero sinistro, il predecessore sarà il massimo
                // valore nel sottoalbero sinistro.
                struct tStation* temp = root->left;
                while (temp->right != NULL) {
                    temp = temp->right;
                }
                predecessor = temp;
            }
            break;
        }
    }

    return predecessor;
}




struct tStation* findSuccessor(struct tStation* root, int minValue) {
    struct tStation* successor = NULL;

    while (root != NULL) {
        if (minValue < root->distance) {
            successor = root;
            root = root->left;
        } else if (minValue > root->distance) {
            root = root->right;
        } else {
            // Il nodo con la chiave è stato trovato
            if (root->right != NULL) {
                // Se esiste un sottoalbero destro, il successore sarà il minimo
                // valore nel sottoalbero destro.
                root = root->right;
                while (root->left != NULL) {
                    root = root->left;
                }
                successor = root;
            }
            break;
        }
    }

    return successor;
}



// pianifica percorso    if(reachable(root, node->distance,minValue)&& reachable(root,prevStation,node->distance))

void plnRoute(tStation *root, int startDist, int endDist) {

    tStation *startStation = searchStation(root, startDist);
    tStation *endStation = searchStation(root, endDist);


    int max;//forse dopo porre=0
    max = abs(endDist - startDist);
    int index = 0;
    int found = 1;

    if(startStation->numCars==0){
        printf("nessun percorso\n");
        return;
    }
    if (startStation == NULL || endStation == NULL) {
        printf("nessun percorso\n");
        return;
    } else if (startStation == endStation) {
        printf("%d\n", startDist);
        return;

    } else {

        if (startDist < endDist) {
            int stationStop = endDist;


            int *route = (int *) malloc(max * sizeof(int));
            struct tStation *stop = endStation;


            while (stop->distance >= startDist) {
                stop = findNextStop( root, NULL,stop, startDist);
                if (stop == NULL) {
                    printf("nessun percorso\n");
                    found = 0;
                    break;         // se non trovo nodi stampo nessun percorso ed esco

                }
                if (stop->distance == startDist) {
                    stationStop = stop->distance;                    //la fermata è uguale al nodo di ritorno
                    fillPath(route, index, stationStop);            //riempo l'array
                    break;
                }
                stationStop = stop->distance;                    //la fermata è uguale al nodo di ritorno
                fillPath(route, index, stationStop);            //riempo l'array
                index = index + 1;

            }

            if (found == 1) {

                for (int i = index; i >= 0; i--) {
                    printf("%d ", route[i]);
                }
                printf("%d\n", endDist);
            }

            free(route);

        } else {

            //ALGO 1

           // int stationStop = endDist;
            tStation **route= (struct tStation**)malloc(MAX*sizeof(struct tStation*));
            //route[0]=endStation;  CAMBIO commentato questo
            index=0;   // CAMBIO DA 1 A 0

            struct tStation *stop = endStation;


            while (stop->distance >=endDist) {
                stop = findNextStopReverse(root, NULL, stop,startDist);//va sistemata  questa f
                if (stop == NULL) {
                    printf("nessun percorso\n");
                    found = 0;
                    break;         // se non trovo nodi stampo nessun percorso ed esco
                }
                if (stop->distance == startDist) {
                    fillPathStation(route, index, startStation);            //riempo l'array
                    break;
                }
             //   stationStop = stop->distance;
                fillPathStation(route, index, stop);            //riempo l'array
                index = index + 1;
            }

            if (found == 1) {

                int steps= index+1;

             struct  tStation *imprRoute[steps+1];  //prima ero solo steps

             // fillo imprRoute dopo i risultati di algoritmo 1

             for(int j=steps;j>0;j--){

                 imprRoute[j]=route[j-1];
             }

                imprRoute[0]=endStation;    //vicina
             //   free(route);

              /* for(int k= steps;k>0;k--){
                   printf("%d ",imprRoute[k]->distance);
               }
               printf("%d\n",imprRoute[0]->distance);  */




                tStation *stationToEval = findPredecessor(root,  route[index]->distance);
                tStation *currentStation = imprRoute[steps];
                tStation *nextStop = imprRoute[0];


                int newIndex = steps-1;

                while (currentStation != nextStop) {

                    int distMax = 0;

                    while (stationToEval != nextStop) {
                                         //prima cond è reachable
                        if (currentStation->maxAutonomy>=(currentStation->distance - stationToEval->distance)
                            && ((stationToEval->maxAutonomy + currentStation->distance - stationToEval->distance) >
                                distMax)) {

                            distMax = stationToEval->maxAutonomy + currentStation->distance - stationToEval->distance;
                            imprRoute[newIndex] = stationToEval;

                        }
                        stationToEval = findPredecessor(root,stationToEval->distance);
                    }

                    currentStation = imprRoute[newIndex];
                    stationToEval = findPredecessor(root,currentStation->distance);
                    newIndex--;

                    if(newIndex==0){
                    imprRoute[0]=nextStop;
                        break;
                    }

                }

                // ALGO 3

                tStation *betweenStation = findSuccessor(root,imprRoute[0]->distance);

                for (int k = 0; k<=(steps-2); k++) {

                   // betweenStation = findSuccessor(root, imprRoute[k]->distance);
                    while (betweenStation->distance < imprRoute[k +1]->distance) {
                           //la prima condizione è la raggiungibilità
                        if (betweenStation->maxAutonomy>=(betweenStation->distance - imprRoute[k+2]->distance) &&
                            imprRoute[k+2]->maxAutonomy>= (imprRoute[k+2]->distance-betweenStation->distance)) {
                            imprRoute[k + 1] = betweenStation;
                            break;
                        }
                        betweenStation = findSuccessor(root, betweenStation->distance);
                    }
                }


                for(int k= steps;k>0;k--){
                    printf("%d ",imprRoute[k]->distance);
                }
                printf("%d\n",imprRoute[0]->distance);


              //PRINT

          /*    printf("%d ",startDist);
                for (int i = index; i>0; i--) {

                    printf("%d ", route[i]->distance);
                }
                printf("%d\n",route[0]->distance);  */
            }

          //  free(route);
        }

    }
}


    int main() {

        tStation *root = NULL;                                           //createStation(0, 0, NULL);
        // root = createStation(0, 0, NULL);

        char riga[10000];
        while (fgets(riga, sizeof(riga), stdin) != NULL) {
            char cmd[30];
            int par[520];
            int numPar = 0;



            //lettura comandi e parametri

            if (sscanf(riga, "%s", cmd) == 1) {
                char *token = strtok(riga + strlen(cmd) + 1, " \t\n"); // Ignora il comando e leggi il resto

                while (token != NULL && numPar < 520) {
                    if (sscanf(token, "%d", &par[numPar]) == 1) {
                        numPar++;
                    }
                    token = strtok(NULL, " \t\n");
                }



                //Esegui operazioni basate sul comando
                if (strcmp(cmd, "aggiungi-stazione") == 0) {

                    int aut[512]; // Supponiamo che l'array di autonomie abbia al massimo 512
                    for (int i = 0; i < par[1]; i++) {
                        aut[i] = par[i + 2];
                    }
                    if(root==NULL){
                        root=addStn(root, par[0], par[1], aut);
                    }else {
                        addStn(root, par[0], par[1], aut);
                    }


                } else if (strcmp(cmd, "demolisci-stazione") == 0) {
                    demStn(root, par[0]);

                } else if (strcmp(cmd, "pianifica-percorso") == 0) {
                    plnRoute(root, par[0], par[1]);

                } else if (strcmp(cmd, "rottama-auto") == 0) {
                    scrCar(root, par[0], par[1]);
                } else if (strcmp(cmd, "aggiungi-auto") == 0) {
                    addCar(root, par[0], par[1]);
                } else if (strcmp(cmd, "quit") == 0) {
                    exit(0);
                } else {
                    printf("Comando sconosciuto: %s\n", cmd);
                }
            }
        }


        return 0;


    }

