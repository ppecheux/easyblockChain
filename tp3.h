#ifndef EATCOINHEADER_H_INCLUDED
#define EATCOINHEADER_H_INCLUDED
#define MAX_DESCR 100
#define MAX_I 10
#define MAX_TRNSCTN 80

//d�finitions des structures

typedef struct Transaction {
    int idEtu;//id de l'�tudiant
    float montant;//montant de la transaction (positif si cr�dit�, n�gatif si d�bit�)
    char* descr;//description de la transaction
    struct Transaction* suivant; //acc�s � la transaction suivante
}T_Transaction;

typedef struct Block {
    int idBlock;//id du Block
    T_Transaction* listeTransaction;//acces  a la liste des transactions
    struct Block* suivant;//acces au block suivant
    time_t date;
}T_Block;

typedef T_Block* BlockChain;

// fonctions requises
T_Transaction* ajouterTransaction(int idEtu, float montant, char *descr, time_t date, BlockChain bc);
BlockChain ajouterBlock(BlockChain bc, time_t t);
BlockChain insertBlockbyDate(BlockChain bc, BlockChain newBlock);
BlockChain creeBlock(time_t t);
float totalTransactionEtudiantBlock(int idEtu, BlockChain Block);//3 requis //Calcul de la somme des EATCoin cr�dit�s et d�pens�s par un �tudiant sur une journ�e
float soldeEtudiant(int idEtu, BlockChain bc);//4 requis //retourne le montant disponible sur le compte de l'�tudiant
void crediter(int idEtu, float montant, char *descr,time_t date, BlockChain bc);//5 du menu
int payer(int idEtu, float montant, char *descr,time_t date, BlockChain bc);//6 du menu
void consulter(int idEtu, BlockChain bc);//4 du menu
int transfert(int idSource, int idDestination, float montant, char *descr,time_t date, BlockChain bc);//7 du menu

//comme groupe de semaine B nous ajoutons des fonctions d'import et d'export

//fonctions intervenant dans le menu
int menu();
void printBlockChain(BlockChain Block);//1 menu
void printBlock(T_Block* Block);//2 menu
void printBlockEtu(int idEtu,T_Block* Block);//3 menu
void printHistory(int idEtu, BlockChain bc, int lim);//4 menu

//fonctions optionelles
void printTransaction(T_Transaction* t);
void clearTransactions(BlockChain Block);// free les transactions d'un block
BlockChain clearBlocks(BlockChain Block);
void fgetsClean(char *s);//a pour but de recolter des chaines de char.
void fAjouTransaction(BlockChain *bc);//ajoute les transactions du fichier dans bc
int askIdEtu();
int askIdBlock();
float askMontant();
time_t askDate();
void fprintTransaction(time_t date,T_Transaction* t);//copie la transaction en fin de fichier txt.
void fprintTransactionAtBegin(time_t date, T_Transaction* t);//copie la transaction en d�but de fichier txt.
void fprintBlock(BlockChain Block);//engegistre les transctions d'un block dans un fichier
void fprintBlockChain(BlockChain Block);
T_Block* searchBlockbyId(int idBlock, BlockChain bc);
T_Block* searchBlockbyDate(time_t date, BlockChain bc);
BlockChain* searchTransactionToInsert(time_t date,BlockChain* bc);//trouver le bon Block pour inserer une tr
void PrintMenuAjou();
int nbBlockinChain(BlockChain bc);
BlockChain uptadeIDBlock(BlockChain bc);
BlockChain selectBlock(BlockChain Block,BlockChain* bc);
#endif // tp3_H_INCLUDED
