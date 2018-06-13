#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "tp3.h"

/*Auteurs: Oubine Perrin et Pierre-Louis Pcheux*/
/*Bienvenue sur le tp3 de NF16*/
/*Implmentation d'une BlockChain*/

int main()
{
    //initialisation de variable?
    int choix;
    BlockChain bc;
    bc = creeBlock(949446000);

    //demarage de l'implmentation
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("x                                                                    x\n");
    printf("x Bienvenue,                                                         x\n");
    printf("x ce programme implemente la BockChain du EatCoin (TP3 de NF16).     x\n");
    printf("x - essayez les differentes fonctions grace au menu.                 x\n");
    printf("x - le bock 0 a ete initialise avec la date du 02/02/2000            x\n");
    printf("x                                                                    x\n");
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

    do {
        //saisie du choix
        menu();
        choix= askIdBlock();

        //ralisation du choix
        switch (choix) {
            case 1 :{
                printBlockChain(bc);
                break;
            }
            case 2 :{//afficher toutes les transactions d'un block #done

                //initialisation des variables
                char *sidBlock = (char *)malloc((MAX_I+1)*sizeof(char));
                int idBlock=-1;

                //saisie de l'id du Block
                do{
                    printf("saisissez lID du block que vous voulez consulter:");
                    fgetsClean(sidBlock);
                    sscanf(sidBlock,"%d",&idBlock);
                }while(idBlock<=-1);

                //Recherche du Block et affichage
                printBlock(searchBlockbyId(idBlock,bc));

                break;
            }
            case 3 :{//consulter les transactions d'un etu pour un jour#DONE
                int idEtu;
                idEtu=askIdEtu();
                printBlockEtu(idEtu,bc);
                break;
            }
            case 4 :{
                int idEtu;
                idEtu=askIdEtu();
                consulter(idEtu,bc);
                break;
            }
            case 5 :{
                int sousChoix;
                PrintMenuAjou();
                do{
                    sousChoix= askIdBlock();
                }while (sousChoix>7 || sousChoix<5);

                //informations generales avant d'inserer une nouvelle transaction
                //pour la date
                time_t date;
                do{
                    date = askDate();
                }while (date == (-1));

                char *descr = (char *)malloc(MAX_DESCR+1);
                float montant;
                int idEtu;

                printf("Saisissez la description de la transaction:");
                fgetsClean(descr);

                idEtu=askIdEtu();
                montant=askMontant();


                //determination du block  la date prcise
                BlockChain bonB;
                bonB=(*searchTransactionToInsert(date,&bc));

                switch(sousChoix){
                    case 5 :{//crediter
                        crediter(idEtu, montant, descr,date, bonB);
                        break;
                    }
                    case 6:{//payer
                        payer(idEtu,montant,descr,date,bonB);
                        break;
                    }
                    case 7:{//transfer
                        int idDestinataire;
                        printf("Pour letudiant destinataire ");
                        idDestinataire=askIdEtu();
                        transfert(idEtu,idDestinataire,montant,descr,date,bonB);
                        break;
                    }
                    default:{
                        printf("vous navez pas saisi un numero valide\n");
                    }

                }
                break;
            }
            case 8 :{break;}//pour ne pas faire defaut avant de sortir
            case 9 :{
                fprintBlockChain(bc);
                break;
            }
            case 10 :{
                fAjouTransaction(&bc);
                break;
            }
            case 11 :{//montant de la journe #done
                int idEtu;
                idEtu=askIdEtu();
                printf("L etudiant %d a echange %f aujourd hui\n",idEtu,totalTransactionEtudiantBlock(idEtu,bc));
                break;
            }
            case 12 :{//solde total #done
                int idEtu;
                idEtu=askIdEtu();
                printf("L etudiant %d a %f EATCoins\n",idEtu,soldeEtudiant(idEtu,bc));
                break;
            }
            case 14 :{
                int idBlock;
                idBlock = askIdBlock();
                clearTransactions(searchBlockbyId(idBlock,bc));
                break;
            }
            case 15 :{
                bc = clearBlocks(bc);
                break;
            }
            case 16 :{
                printf("il y a %d Blocks dans la chaine\n",nbBlockinChain(bc));
                break;
            }
            case 17:{
                time_t t = askDate();
                printBlock(searchBlockbyDate(t,bc));
                break;
            }
            case 18:{
                bc = insertionSortbyDate(bc);
                printBlockChain(bc);
                break;
            }
            default: {
                printf("Nous n avons pas ce numero\n");
                break;
            }

        }
    }while(choix!=8);

    clearBlocks(bc);
    free(bc);
    return 0;
}
