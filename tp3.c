#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "tp3.h"

// fonctions requises


T_Transaction* ajouterTransaction(int idEtu, float montant, char *descr, time_t date, BlockChain bc){//il faut donner le pointeur sur le bon block pour inserer la transaction
    //allocation de l'espace mémoire correspondant à une transaction
    T_Transaction* newTransaction = (T_Transaction*)malloc(sizeof(T_Transaction));
    //initialisation de la transaction
    newTransaction->idEtu=idEtu;
    newTransaction->montant=montant;
    newTransaction->descr= (char*)malloc(sizeof(MAX_DESCR+1));
    strcpy(newTransaction->descr,descr);

    //T_Transaction* listeTransaction = searchTransactionToInsert(date,bc);

    if(bc->listeTransaction){
        newTransaction->suivant=bc->listeTransaction;
    }
    else
        newTransaction->suivant=NULL;

    printTransaction(newTransaction);

    return newTransaction;
}

BlockChain ajouterBlock(BlockChain bc, time_t t){//#DONE
    //allocation de l'espace mémoire correspondant à un Block
    T_Block* newBlock = malloc(sizeof(T_Block));
    //initialisation du Block et update de la Blockchain

    newBlock->listeTransaction = NULL;//pas de malloc car liste vide
    newBlock->date=t;
    if(bc){
        //printf("bc nes pas null\n");
        newBlock->suivant=bc;
        newBlock->idBlock = bc->idBlock+1;
        bc=newBlock;
        //printf("bc pointe sur le %deme block\n",bc->idBlock);
    }
    else{
        newBlock->suivant=NULL;
        newBlock->idBlock=0;
        return newBlock;
    }
    //printf("bc pointe sur le %deme block\n",bc->idBlock);
    return bc;
}

float totalTransactionEtudiantBlock(int idEtu, BlockChain Block){//envoie la variation du solde pour un block
    float soldeJour=0.0;
    if(Block){

        T_Transaction* temp;
        temp=Block->listeTransaction;

        if(temp){
            //printf("Ce Block contient une liste de transaction\n");
            while(temp){
                if(temp->idEtu==idEtu)
                    soldeJour+=temp->montant;
                temp=temp->suivant;
            }
            //printf("temp de la fonction print va etre freed\n");
        }else{
            //printf("Ce Block contient une liste de transaction vide\n");
        }
    }else{printf("ce block nexiste pas");
    }
    return soldeJour;
}

float soldeEtudiant(int idEtu, BlockChain bc){//4 requis //retourne le montant disponible sur le compte de l'étudiant
    float solde=0.0;
    if(bc){
        T_Block* temp;
        temp = bc;
        while(temp){
            solde+=totalTransactionEtudiantBlock(idEtu,temp);
            temp=temp->suivant;
        }
    }
    return solde;
}



void crediter(int idEtu, float montant, char *descr,time_t date, BlockChain bc){//5 #DONE
        bc->listeTransaction = ajouterTransaction(idEtu,montant,descr,date,bc);
}

int payer(int idEtu, float montant, char *descr,time_t date, BlockChain bc){//6 #DONE
    if(montant>soldeEtudiant(idEtu,bc)){
        printf("lEtudiant %d ne dispose que de %f, transaction annulee\n",idEtu,soldeEtudiant(idEtu,bc));
        return 0;
    }
    bc->listeTransaction=ajouterTransaction(idEtu,-(montant),descr,date,bc);
    return 1;
}

int transfert(int idSource, int idDestination, float montant, char *descr,time_t date, BlockChain bc){//7 du menu
    if((idDestination!=idSource)&&payer(idSource,montant,descr,date,bc)==1){
        //printf("lEtudiant a ete paye\n");
        crediter(idDestination,montant,descr,date,bc);
        //printf("et on a crédité l'autre\n");
    }

    else
        return 0;
    return 1;
}
//fonctions intervenantes dans le menu

//fonctions optionelles

void clearTransactions(BlockChain Block){
    if(Block){
        printf("le block %d existe\n",Block->idBlock);
        T_Transaction* temp;
        while(Block->listeTransaction){
            temp=Block->listeTransaction;
            Block->listeTransaction=temp->suivant;
            free(temp);
        }
        printf("la liste de transaction est maintenant vide\n");
    }
}

BlockChain clearBlocks(BlockChain Block){//retourne un pointeur sur le block 0;
    BlockChain temp;
    while(Block->idBlock!=0){
        temp=Block;
        clearTransactions(Block);
        Block=Block->suivant;
        free(temp);
    }

    clearTransactions(Block);

    return Block;
}



T_Block* searchBlockbyId(int idBlock, BlockChain bc){//renvoi le block de la chaine ayant l'id indiqué
    T_Block* temp;
    if(!bc)return NULL;
    if(idBlock>bc->idBlock){
        printf("le block %d n'existe pas car la liste est trop courte\n",idBlock);
        return NULL;
    }
    temp=bc;
    while(temp&&(temp->idBlock>=0)){
        if(temp->idBlock==idBlock)
           return temp;
        temp=temp->suivant;
    }
    return NULL;
}

T_Block* searchBlockbyDate(time_t date, BlockChain bc){//#DONE
    T_Block* temp;
    if(!bc)return NULL;
    temp=bc;
    while(temp){
        if(temp->date==date)
           return temp;
        temp=temp->suivant;
    }
    return NULL;
}

BlockChain* searchTransactionToInsert(time_t date,BlockChain* bc){//#DONE
    BlockChain* bonB;
    if(bc && date != (-1)){
        *bonB = searchBlockbyDate(date,*bc);
        if(!*bonB){
            *bc = ajouterBlock(*bc,date);
            *bonB=*bc;
        }
        return bonB;
    }
    return NULL;
}


