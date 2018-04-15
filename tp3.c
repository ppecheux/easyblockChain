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

float totalTransactionEtudiantBlock(int idEtu, BlockChain Block){//? //plus de malloc? ca marchait sans! flute alors!!!!
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

void consulter(int idEtu, BlockChain bc){
    printf("L etudiant %d a %f EATCoins et les cing dernieres transactions sont:\n",idEtu,soldeEtudiant(idEtu,bc));
    printHistory(idEtu,bc,5);
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
int menu(){
    printf("   ----------------------------------------------------------\n");
    printf("  | Que voulez-vous faire ?                                  |\n");
    printf("   ----------------------------------------------------------\n");
    printf("  |1. Afficher la liste de la BlockChain                     |\n");
    printf("  |2. Afficher toutes les transactions d’un bloc             |\n");
    printf("  |3. Affiche les transactions du jour pour un étudiant      |\n");
    printf("  |4. Afficher l’historique pour un étudiant                 |\n");
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
                while(temp&&limPrintT<5){
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

//fonctions optionelles
void printTransaction(T_Transaction* t){
    if(t){
        if(t->descr!=NULL){
            printf("[%d echange %.2f EatCoins %s]\n",t->idEtu,t->montant,t->descr);
        }
    }
}

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
                fprintTransactionAtBegin(Block->date,temp);
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

/** \brief saisie d'une chaine de char proprement
 *
 * \param char* s est la chaine en reference
 *
 */
void fgetsClean(char *s){//cette fonction permet de lire une chaine correctement.

    //printf("Rentez jusque 40 char:\n");
    fgets(s,sizeof(char)*(MAX_DESCR),stdin);
    //printf("vous avez rentre :%s\n",s);

    //étape de cleaning de la chaine prise sur OC

    char *p = strchr(s,'\n');
    if (p != NULL)
        *p = 0;
    else
    {
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF);
    }

}

void fAjouTransaction(BlockChain* bc, BlockChain *bonB){//pour ajouter une transaction à la fin d'un fichier
    if(bc){
        time_t date;
        int idEtu;
        float montant;
        char* descr= (char*)malloc(sizeof(MAX_DESCR+1));

        FILE* fichier = NULL;
        fichier = fopen("blockchain.txt", "r");

        if (fichier != NULL){
            while(fscanf(fichier,"%ld%*c%d%*c%f%*c%[^\n]\n",&date,&idEtu,&montant,descr)!=EOF){
                (*searchTransactionToInsert(date,bc,bonB))->listeTransaction = ajouterTransaction(idEtu,montant,descr,date,(*searchTransactionToInsert(date,bc,bonB)));
            }
            fclose(fichier);
        }
    }
}

int askIdEtu(){
    char *sidEtu = (char *)malloc(MAX_I+1);
    int idEtu;
    idEtu=0;

    do{
        printf("Saisissez un IdEtu:");
        fgetsClean(sidEtu);
        sscanf(sidEtu,"%d",&idEtu);
    }while(idEtu==0);

    free(sidEtu);

    return idEtu;
}

int askIdBlock(){
    char *sidEtu = (char *)malloc(MAX_I+1);
    int idEtu;
    idEtu=0;

    do{
        printf("Saisissez un le numero de votre choix:");
        fgetsClean(sidEtu);
        sscanf(sidEtu,"%d",&idEtu);
    }while(idEtu<=0);

    free(sidEtu);

    return idEtu;
}

float askMontant(){
    char *smontant = (char *)malloc(MAX_I+1);
    float montant=0.0;
    do{
        printf("Saisissez le montant de la transaction:");
        fgetsClean(smontant);
        sscanf(smontant,"%f",&montant);
    }while(montant<=0.0);
    return montant;
}

time_t askDate(){//demande de date et convertion en secondes
    time_t timestamp;
    do{
        struct tm myDate;
        printf("Pour le jour, ");
        myDate.tm_mday = askIdBlock();
        printf("Pour le mois, ");
        myDate.tm_mon = askIdBlock()-1;
        printf("Pour l annee, ");
        myDate.tm_year = askIdBlock()-1900;
        myDate.tm_hour = 0;
        myDate.tm_min = 0;
        myDate.tm_sec = 0;

        timestamp = mktime( & myDate );
    }while(timestamp == -1);
    //printf( "Timestamp == %ld\n", timestamp );

    const char * strDate = asctime( localtime( & timestamp ) );


    printf( "Date de la transaction: %s\n", strDate );

    return timestamp;
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

BlockChain* searchTransactionToInsert(time_t date,BlockChain* bc,BlockChain *bonB){//#DONE
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

void PrintMenuAjou(){
    printf("   ----------------------------------------------------------\n");
    printf("  | Que voulez-vous faire ?                                  |\n");
    printf("   ----------------------------------------------------------\n");
    printf("  |5. Créditer un compte                                     |\n");
    printf("  |6. Payer un repas                                         |\n");
    printf("  |7. Transferer des EATCoins entre deux etudiants           |\n");
    printf("   ----------------------------------------------------------\n");
}
