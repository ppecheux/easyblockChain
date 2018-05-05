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

void printBlockChain(BlockChain Block){//1 du menu
    if(Block){
        T_Block* tB;
        tB = Block;
        while(tB){
            printf("\n");
            printBlock(tB);
            tB=tB->suivant;
        }
    }
}

void printBlock(T_Block* Block){//2 dans le menu //plus de malloc
    if(Block){printf("Le Block %d existe",Block->idBlock);
    time_t timestamp = Block->date;
    const char * strDate = asctime( localtime( & timestamp ) );
    printf( " date du %s", strDate );

        T_Transaction* temp;
        temp=Block->listeTransaction;

        if(Block->listeTransaction){
            printf(" et contient une liste de transaction\n");
            //printf("temp de la fonction print block initialisée\n");
            while(temp){
                printTransaction(temp);
                //printf("temp de la fonction print block a imprime la transaction\n");
                temp=temp->suivant;
            }
        }else{
            printf(" et contient une liste de transaction vide\n");
        }

    }else{
        printf("Ce Block nexiste pas\n");
    }
}

void printTransaction(T_Transaction* t){
    if(t){
        if(t->descr!=NULL){
            printf("[%d echange %.2f EatCoins %s]\n",t->idEtu,t->montant,t->descr);
        }
    }
}

void consulter(int idEtu, BlockChain bc){
    printf("L etudiant %d a %f EATCoins et les cing dernieres transactions sont:\n",idEtu,soldeEtudiant(idEtu,bc));
    printHistory(idEtu,bc,5);
}

void printBlockEtu(int idEtu,T_Block* Block){//3 menu
    if(Block){printf("Le Block %d existe",Block->idBlock);

        T_Transaction* temp;
        temp=Block->listeTransaction;

        if(Block->listeTransaction){
            printf(" et contient une liste de transaction\n");
            while(temp){
                if(temp->idEtu==idEtu)
                    printTransaction(temp);
                temp=temp->suivant;
            }
        }else{
            printf(" et contient une liste de transaction vide\n");
        }
    }else{
        printf("Ce Block nexiste pas\n");
    }
}

void printHistory(int idEtu, BlockChain bc, int lim){//4 dans le menu #DONE
    int limPrintT = 0;
    if(bc){
        T_Block* tB;
        tB = bc;
        while(tB&&limPrintT<lim){

            T_Transaction* temp;
            temp=tB->listeTransaction;

            if(temp){
                //printf("Ce Block contient une liste de transaction\n");
                while(temp&&limPrintT<lim){
                    if(temp->idEtu==idEtu){
                        printf("[Block:%d Etu:%d echange %f EatCoins %s]\n",tB->idBlock,temp->idEtu,temp->montant,temp->descr);
                        limPrintT++;
                    }
                    temp=temp->suivant;
                }
            }else{
                //printf("Ce Block contient une liste de transaction vide\n");
            }
            tB=tB->suivant;
        }
    }
}

int menu(){
    printf("   ----------------------------------------------------------\n");
    printf("  | Que voulez-vous faire ?                                  |\n");
    printf("   ----------------------------------------------------------\n");
    printf("  |1. Afficher la liste de la BlockChain                     |\n");
    printf("  |2. Afficher toutes les transactions d un bloc             |\n");
    printf("  |3. Affiche les transactions du jour pour un etudiant      |\n");
    printf("  |4. Afficher l historique pour un etudiant                 |\n");
    printf("  |5. crediter/payer/transferer                              |\n");
    printf("  |8. Quitter                                                |\n");
    printf("  |9. Exporter toutes les transactions vers un fichier       |\n");
    printf("  |10. Importer des transactions depuis un fichier           |\n");
    printf("  |11. Afficher le montant echange aujourd hui par letudiant |\n");
    printf("  |12. Afficher le solde du compte                           |\n");
    printf("  |                                                          |\n");
    printf("  |14. Supprimer les transactions du Block                   |\n");
    printf("  |15. Supprimer les Blocks                                  |\n");
    printf("   ----------------------------------------------------------\n");

    return 0;
}

void PrintMenuAjou(){
    printf("   ----------------------------------------------------------\n");
    printf("  | Que voulez-vous faire ?                                  |\n");
    printf("   ----------------------------------------------------------\n");
    printf("  |5. Créditer un compte                                     |\n");
    printf("  |6. Payer un repas                                         |\n");
    printf("  |7. Transferer des EATCoins entre deux etudiants           |\n");
    printf("   ----------------------------------------------------------\n");
}
