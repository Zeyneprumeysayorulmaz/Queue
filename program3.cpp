/*
Her bir dizi elemaný kendi iþlem sürelerini tutmaktadýr.
Kuyrukta tanýmlanan no deðiþkeni dizinin indexlerine ulaþmakta kullanýlmaktadýr.
clearQueue() fonksiyonundan sonra dizi varsayýlan deðerlerine döndürülmüþ ve tekrar kullanýma hazýr hale gelmiþtir.
MAX sabiti dizinin boyutunu belirlemekle beraber arzulara baðlý daha uzun veya daha kýsa kuyruklar oluþturulabilinir.
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

#define MAX 5

/* Kuyruk yapýsýnýn düðüm yapýsý */
typedef struct node{
    int array[MAX];
}Node;

/* Kuyruk yapýsý */
typedef struct queue{
    int head; /* Kuyruðun ilk elemanýnýn numarasýný tutan deðiþken */
    int last;
    int processTimeSum; /* Kuyrukta geçirilen toplam iþlem süresi */
    int no; /* Kuyruk üzerinde dolaþmamýzý saðlayan deðiþken */
}Queue;

int randProcessTime(void);
Node* newNode(void);
Queue* newQueue(void);
bool emptyQueue(Queue*);
void addNodeToQueue(Queue* queue,Node* node);
int popNodeFromQueue(Queue* queue,Node* node);
void clearQueue(Queue* queue,Node* node);
void averageOfProcessTime(Queue* queue);

int main(void){
    int select;
    int n;
    Queue* newQueuex=newQueue();
    Node* newNodex=newNode();
    printf("Welcome to Bank");
    while(1){
        printf("\n\n1: Add \"n\" customer\n2: The time the customers spend on the queue\n3: Average process time\n\nPlease select your process: ");
        scanf("%d",&select);
        printf("\n\n");
        switch(select){
            case 1:
                printf("How many customer in the queue?\nChoose: ");
                scanf("%d",&n);
                while(n>0){
                    for(int i=0;i<600000000;i++); /* Bu satýr randomize sayinin üretilebilmesi için zaman geçiriyor */
                    addNodeToQueue(newQueuex,newNodex);
                    n--;
                }
                break;
            case 2:
                clearQueue(newQueuex,newNodex);
                break;
            case 3:
                averageOfProcessTime(newQueuex);
                break;
            default :
                printf("Wrong choose!\n");
                break;
        }
    }
    return 0;
}

/* Rastgele iþlem süresini hesaplayan fonksiyon */
int randProcessTime(void){
    srand(time(NULL));
    int x=rand()%270+30;
    return x;
}

/* Dugum oluþturma fonksiyonu */
Node* newNode(void){
    Node* newNode=(Node*)malloc(sizeof(Node));
    int n=0;
    while(n<MAX){ /* Dizideki elemanlara varsayýlan 0 deðeri atandý */
        newNode->array[n]=0;
        n++;
    }
    return newNode;
}

/* Kuyruk yapýsý oluþturma fonksiyonu */
Queue* newQueue(void){
    Queue* newQueue=(Queue*)malloc(sizeof(Queue));
    newQueue->head=-1;
    newQueue->last=-1;
    newQueue->processTimeSum=0;
    newQueue->no=-1;
    return newQueue;
}

/* Kuyruðun boþ olup olmadýðýný kontrol eden fonksiyon */
bool emptyQueue(Queue* queue){
    if(!(queue->head>=-1 && queue->head<5))
    return true;
    else
    return false;
}

/* Kuyruk yapýsýna yeni bir düðüm ekleme fonksiyonu */
void addNodeToQueue(Queue* queue,Node* node){
    queue->no++;
    if(queue->no==MAX){ /* Kuyruðun full olma durumu */
        printf("Queue is full, the transaction has not been approved!\n");
        queue->no--;
        return;
    }
    if(queue->no==0){
        queue->head=queue->no;
    }
    queue->last=queue->no;
    node->array[queue->no]=randProcessTime();
    if(queue->no==0){ /* Kuyruða eklenen ilk elemana özel süreç */
        queue->processTimeSum+=node->array[queue->no];
        return;
    }
    queue->processTimeSum+=node->array[queue->no];
    node->array[queue->no]=queue->processTimeSum;
}

/* Kuyruktan eleman çýkarma ve çýkarýlan elemanýn iþlem süresini döndüren fonksiyon */
int popNodeFromQueue(Queue* queue,Node* node){
    if(emptyQueue(queue)){ /* Eðer kuyruk boþsa iþlem yapýlmadan -1 döner */
        printf("Queue is empty!\n");
        return -1;
    }
    int data=node->array[queue->head];
    queue->head++;
    return data;
}

/* Kuyruðu boþaltan ve her bir müþterinin kuyrukta harcadýklarý süreyi gösteren fonksiyon */
void clearQueue(Queue* queue,Node* node){
    int temp;
    while(!(queue->head==MAX+1)){
        temp=popNodeFromQueue(queue,node);
        if(temp==-1){ /* Dönen deðer -1 ise kuyruk boþaltýlmýþtýr fonksiyondan çýkýlacaktýr */
            queue->head=-1;
            queue->last=-1;
            queue->no=-1;
            queue->processTimeSum=0;
            return;
        }
        printf("The time the %d. customer spent in the queue: %d second.\n",queue->head,temp);
    }
}

/* Kuyrukta geçirilen ortalama iþlem süresini gösteren fonskiyon */
void averageOfProcessTime(Queue* queue){
    if(emptyQueue(queue)){
        printf("Queue is empty!\n\n");
        return;
    }
    int average=queue->processTimeSum/queue->no;
    printf("Avarege process time in the queue: %d second.\n",average);
}
