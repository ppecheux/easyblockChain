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

BlockChain clearBlock(BlockChain Block,BlockChain bc){//attention, ne fonctionne que si les blocks ont des ID décroissants de 1 en 1.
    if (Block){

        clearTransactions(Block);
        if(Block->idBlock == nbBlockinChain(bc)){//il faut supprimer le premier block de la chaine
            bc->suivant=Block->suivant;
        }else{
            BlockChain tmp = searchBlockbyId((Block->idBlock+1),bc);
            tmp->suivant=Block->suivant;
        }
        free(Block);
    }
    return bc;
}

BlockChain clearBlocks(BlockChain Block){//retourne un pointeur sur le block 0;
    BlockChain temp;
    while(Block->suivant){
        temp=Block;
        clearTransactions(Block);
        Block=Block->suivant;
        free(temp);
    }

    clearTransactions(Block);

    return Block;
}
