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
    //allocation de l'espace m�moire correspondant � une transaction
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

    T_Block* newBlock = creeBlock(t);

    if(bc){
        bc = insertBlockbyDate(bc, newBlock);
        bc = uptadeIDBlock(bc);
    }
    //printf("bc pointe sur le %deme block\n",bc->idBlock);
    return bc;
}

BlockChain insertBlockbyDate(BlockChain bc, BlockChain newBlock){
    if(bc){
        //printf("bc nest pas null\n");
        if (bc->date < newBlock->date){ //insertion au debut de la blockchain
            newBlock->suivant=bc;
            bc=newBlock;
            //printf("bc pointe sur le %deme block\n",bc->idBlock);

        }else{
            BlockChain tmp = bc;

            if (tmp->suivant){
                while(tmp->suivant->date > newBlock->date){
                    tmp=tmp->suivant;

                    if (!tmp->suivant){//nous sommes � la fin de la chaine
                        tmp->suivant = newBlock;
                        return bc;
                    }
                }//nous sommes au milieu de la liste

                newBlock->suivant=tmp->suivant;
                tmp->suivant = newBlock;
                return bc;

            }else{//on insert � la fin d'une liste de longueur 1
                tmp->suivant = newBlock;
                return bc;
            }
        }
    }
    else{
        return newBlock;
    }
    return bc;
}

BlockChain creeBlock(time_t t){
    //allocation de l'espace m�moire correspondant � un Block
    T_Block* newBlock = malloc(sizeof(T_Block));
    //initialisation du Block
    newBlock->listeTransaction = NULL;//pas de malloc car liste vide
    newBlock->date=t;
    newBlock->idBlock=0;
    newBlock->suivant=NULL;
    return newBlock;
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

float soldeEtudiant(int idEtu, BlockChain bc){//4 requis //retourne le montant disponible sur le compte de l'�tudiant
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
        //printf("et on a cr�dit� l'autre\n");
    }

    else
        return 0;
    return 1;
}
//fonctions intervenantes dans le menu

//fonctions optionelles

T_Block* searchBlockbyId(int idBlock, BlockChain bc){//renvoi le block de la chaine ayant l'id indiqu�
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
    BlockChain* bonB = malloc(sizeof(BlockChain));
    if(bc && date != (-1)){
        *bonB = searchBlockbyDate(date,*bc);
        if(!*bonB){
            *bc = ajouterBlock(*bc,date);
            *bonB= searchBlockbyDate(date,*bc);
        }
        return bonB;
    }
    return NULL;
}

int nbBlockinChain(BlockChain bc){
    int nbBlock =0;
    if (bc){
        BlockChain tmp = bc;
        while(tmp){
            tmp= tmp->suivant;
            nbBlock++;
        }
    }
    return nbBlock;
}

BlockChain uptadeIDBlock(BlockChain bc){//change le num des blocks tant que ca ne match pas mais ne v�rifie pas toute la liste
    if (bc){
        int nbBlock = (nbBlockinChain(bc)-1);
        BlockChain tmp = bc;
        while(tmp ){//&& tmp->idBlock != nbBlock){
            tmp->idBlock = nbBlock--;
            tmp=tmp->suivant;
        }
    }
    return bc;
}

BlockChain insertionSortbyDate(BlockChain bc){
    if(bc){
        int taille = (nbBlockinChain(bc)-2);
        int i;
        for (i=taille;i>0;--i){

            bc = uptadeIDBlock(bc);
            BlockChain tmp = selectBlock(searchBlockbyId(i,bc),&bc);
            bc = insertBlockbyDate(bc,tmp);
            printf("i est %d\n",i);
        }
    }
    return bc;
}

BlockChain selectBlock(BlockChain Block,BlockChain* bc){//attention, ne fonctionne que si les blocks ont des ID d�croissants de 1 en 1.
    if (Block){
        if(Block->idBlock == nbBlockinChain(*bc)){//il faut supprimer le premier block de la chaine
            (*bc)->suivant=Block->suivant;
        }else{
            BlockChain tmp = searchBlockbyId((Block->idBlock+1),*bc);
            (tmp)->suivant=Block->suivant;
        }
    }
    return Block;
}
