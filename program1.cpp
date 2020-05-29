#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

/* Kuyruk yapýsýnýn düðüm yapýsý */
typedef struct node{
    int no; /* Müþteri numarasý */
    int processTime; /* Müþterinin iþlem süresini tutan deðiþken */
    struct node* next; /* Kendinden sonra sýraya gelen müþteriyi gösteren pointer */
}Node;

/* Kuyruk yapýsý */
typedef struct queue{
    Node* head;
    Node* last; /* Kuyruðun baþýný ve sonunu gösteren pointerlar */
    int processTimeSum; /* Kuyrukta müþterilerin harcadýðý toplam iþlem süresi */
    int no; /* Genel müþteri numarasý */
}Queue;

int randProcessTime(void);
Node* newNode(void);
Queue* newQueue(void);
bool emptyQueue(Queue*);
void addNodeToQueue(Node*,Queue*);
Node* popNodeFromQueue(Queue*);
void clearQueue(Queue*);
void averageOfProcessTime(Queue*);

int main(void){
    int select;
    int n;
    Queue* newQueuex=newQueue();
    Node* newNodex;
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
                    newNodex=newNode();
                    for(int i=0;i<600000000;i++); /* Bu satýr randomize sayinin üretilebilmesi için zaman geçiriyor */
                    addNodeToQueue(newNodex,newQueuex);
                    n--;
                }
                break;
            case 2:
                clearQueue(newQueuex);
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
    newNode->no=0;
    newNode->processTime=0;
    newNode->next=NULL;
    return newNode;
}

/* Kuyruk yapýsý oluþturma fonksiyonu */
Queue* newQueue(void){
    Queue* newQueue=(Queue*)malloc(sizeof(Queue));
    newQueue->head=NULL;
    newQueue->last=NULL;
    newQueue->no=0;
    newQueue->processTimeSum=0;
    return newQueue;
}

/* Kuyruðun boþ olup olmadýðýný kontrol eden fonksiyon */
bool emptyQueue(Queue* queue){
    if(queue->head==NULL)
        return true;
    else
        return false;
}

/* Kuyruk yapýsýna yeni bir düðüm ekleme fonksiyonu */
void addNodeToQueue(Node* newNode,Queue* queue){
    queue->no+=1; /* Genel müþteri numarasýnýn bir artttýrýlmasý */
    if(emptyQueue(queue)){
        queue->head=newNode; /* Eðer kuyruk boþ ise kuyruðun baþýna yeni elemanýn adresinin atanmasý */
    }
    else{
        queue->last->next=newNode; /* Kuyruðun son müþterisinden sonra gelecek müþterinin adresinin atanmasý */
    }
    queue->last=newNode; /* Kuyruðun sonuna son gelen müþteri atanmasý */
    newNode->no=queue->no; /* Müþteri numarasýnýn atanmasý */
    newNode->processTime=randProcessTime(); /* Müþterinin iþlem süresi hesaplanmasý */
    if(queue->no==1){
        queue->processTimeSum+=newNode->processTime;
        return;
    }
    queue->processTimeSum+=newNode->processTime; /* Toplam kuyrukta geçirilen vaktin hesaplanmasý */
    newNode->processTime=queue->processTimeSum; /* Yeni müþterinin iþlem süresi dahil kuyrukta geçirdiði sürenin hesaplanmasý */
}

/* Kuyruktan eleman çýkarma ve çýkarýlan elemaný döndüren fonksiyon */
Node* popNodeFromQueue(Queue* queue){
    Node* returnNode;
    if(emptyQueue(queue)){ /* Eðer kuyruk boþsa iþlem yapýlmadan null döner */
        printf("Queue is empty!\n");
        return NULL;
    }
    returnNode=queue->head;
    queue->head=queue->head->next; /* Listenin baþýna kuyrukta iþi biten müþterinden sonra gelen müþterinin atanmasý */
    return returnNode;
}

/* Kuyruðu boþaltan ve her bir müþterinin kuyrukta harcadýklarý süreyi gösteren fonksiyon */
void clearQueue(Queue* queue){
    if(emptyQueue(queue)){
        printf("Queue is empty already!\n\n");
        return;
    }
    Node* temp;
    while(!emptyQueue(queue)){
        temp=popNodeFromQueue(queue);
        printf("The time the %d. customer spent in the queue: %d second.\n",temp->no,temp->processTime);
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
