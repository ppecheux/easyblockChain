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

//importation

void fAjouTransaction(BlockChain* bc){//pour ajouter une transaction depuis un fichier
    if(bc){
        time_t date;
        int idEtu;
        float montant;
        char* descr= (char*)malloc(sizeof(char)*MAX_DESCR+1);

        FILE* fichier = NULL;
        fichier = fopen("blockchain.txt", "r");

        if (fichier != NULL){
            while(fscanf(fichier,"%ld%*c%d%*c%f%*c%[^\n]\n",&date,&idEtu,&montant,descr)!=EOF){
                (*searchTransactionToInsert(date,bc))->listeTransaction = ajouterTransaction(idEtu,montant,descr,date,(*searchTransactionToInsert(date,bc)));
            }
            fclose(fichier);
        }
    }
}

//exportation

void fprintTransaction(time_t date, T_Transaction* t){// #DONE copie la transaction en fin de fichier txt.
    //écrire à la fin du fichier
    if(t){

        FILE* fichier = NULL;

        //copier la fin du fichier
        fichier = fopen("blockchain.txt", "a");

        if (fichier != NULL)
        {
            printf("dans l'ecriture de fichier %ld;%d;%f;%s\n",date,t->idEtu,t->montant,t->descr);
            fprintf(fichier,"%ld;%d;%f;%s\n",date,t->idEtu,t->montant,t->descr);
            fclose(fichier);
        }
    }
}

void fprintTransactionAtBegin(time_t date, T_Transaction* t){//copie la transaction en début de fichier txt.
    if(t){

        FILE* fichier = NULL;

        //copier la fin du fichier
        char* tail = malloc(sizeof(char)*(MAX_DESCR+3*MAX_I)*100);
        char* chaine = malloc(sizeof(MAX_DESCR+3*MAX_I));
        printf("les chaines ont ete initialisee\n");

        fichier = fopen("blockchain.txt", "r");
        if (fichier)
        {
            while(fscanf(fichier,"%[^\n]\n",chaine)!=EOF){
                strcat(chaine,"\n");
                printf("les chaines ont ete initialisee\n");
                strcat(tail,chaine);
                if(chaine)
                    printf("tail est%s\n", chaine); // On affiche la chaîne qu'on vient de lire
            }
            fclose(fichier);
        }

        //ecrire dans le fichier da la nouvelle transaction
        fichier = fopen("blockchain.txt", "w");
        if (fichier)
        {
            printf("dans l'ecriture de fichier %ld;%d;%f;%s\n",date,t->idEtu,t->montant,t->descr);
            fprintf(fichier,"%ld;%d;%f;%s\n",date,t->idEtu,t->montant,t->descr);
            fclose(fichier);
        }

        fichier = fopen("blockchain.txt", "a");
        if (fichier)
        {
            printf("dans l'ecriture de fichier du tail\n");
            fprintf(fichier,"%s",tail);
            fclose(fichier);
        }
    free(tail);
    free(chaine);
    }
}

void fprintBlock(BlockChain Block){//engegistre les transctions d'un block dans un fichier
    if(Block){printf("Le Block %d existe",Block->idBlock);
    time_t timestamp = Block->date;
    const char * strDate = asctime( localtime( & timestamp ) );
    printf( " date du %s", strDate );

        T_Transaction* temp;
        temp=Block->listeTransaction;

        if(Block->listeTransaction){
            printf(" et contient une liste de transaction\n");
            while(temp){
                fprintTransaction(Block->date,temp);
                temp=temp->suivant;
            }
        }else{
            printf(" et contient une liste de transaction vide\n");
        }

    }else{
        printf("Ce Block nexiste pas\n");
    }
}

void fprintBlockChain(BlockChain Block){//engegistre les transctions de la blockchain dans un fichier
    if(Block){
        T_Block* tB;
        tB = Block;
        while(tB){
            fprintBlock(tB);
            tB=tB->suivant;
        }
    }
}
