#include "./headers/msg.h"
//#include "../klog.c"
#define TRUE 1
#define FALSE 0

static msg_t msgTable[MAXMESSAGES];
LIST_HEAD(msgFree_h);

void initMsgs() {
    for(int i=0;i<MAXMESSAGES;i++){
        //Scorro msgTable e aggiungo ogni elemento in coda a msgFree
        list_add_tail(&(msgTable[i].m_list), &msgFree_h);
        msgTable[i].m_payload = 0;
    }
}

void freeMsg(msg_t *m) {
    //inserisco la list_head puntata da m in coda alla msgFree
    list_add_tail(&(m->m_list), &msgFree_h);
}

msg_t *allocMsg() {

    //variabile ausiliaria usata per ritornare l'elemento della lista che viene eliminato
    msg_t *tmp;

    if(list_empty(&msgFree_h))
        return NULL;

    else{
        tmp = container_of((&msgFree_h)->next, msg_t, m_list);
        list_del((&msgFree_h)->next);

        tmp->m_sender = NULL;
        tmp->m_payload = 0;
        INIT_LIST_HEAD(&(tmp->m_list));

        /*
        //scorro la msgTable e metto tutti i payload = 0
        for(int i=0;i<MAXMESSAGES;i++){
            msgTable[i].m_payload = 0;
        }*/
        return tmp;
    }
}

void mkEmptyMessageQ(struct list_head *head) {
    INIT_LIST_HEAD(head);
}

int emptyMessageQ(struct list_head *head) {
    return list_empty(head);
}

void insertMessage(struct list_head *head, msg_t *m) {
    //inserisco la list_head puntata da m in coda alla lista head
    list_add_tail(&(m->m_list), head);
}

void pushMessage(struct list_head *head, msg_t *m) {
    //inserisco la list_head puntata da m in testa alla lista head
    list_add(&(m->m_list), head);
}

msg_t *popMessage(struct list_head *head, pcb_t *p_ptr) { 

    //variabile ausiliaria usata per ritornare l'elemento eliminato dalla lista
    msg_t *tmp;

    if(!p_ptr) {
        /*klog_print("\ntmp2");
        klog_print("\nthe truth\n");
        klog_print_hex((memaddr)tmp->m_payload);
        klog_print("\nthe truth sender\n");
        klog_print_hex((memaddr)tmp->m_sender);*/
		    tmp = container_of(head->next, msg_t, m_list);
		    list_del(head->next);
        return tmp;
	  }
    
	  if(list_empty(head))
        return NULL;

    int found = FALSE;
    struct list_head *pos;
    list_for_each(pos, head){
        if(container_of(pos, msg_t, m_list)->m_sender == p_ptr && !found){
            found = TRUE;
            tmp = container_of(pos, msg_t, m_list);
        }
    }

    if(found == FALSE)
        return NULL;

    else { 
        list_del(&(tmp->m_list));
        return tmp;
    }
}
msg_t *headMessage(struct list_head *head) {
    if(head == NULL)
        return NULL;

    else
        return container_of(head->next, msg_t, m_list);

}
