# easyblockChain
Analyse de complexité des fonctions de base
===========================================

Pour l’analyse de la complexité dans ce rapport nous noterons le nombre
de **blocks** dans la BlockChain par un ‘b’, le nombre de **transactions
dans un block** par ‘tb’, le nombre de **transactions dans la chaîne**
‘tc’ et le nombre de **transactions dans un fichier** par ‘tf’.

#### ajouterTransaction

Crée une nouvelle transaction en tête de la liste de transaction du
block passé en paramètre.La complexité est donc de Ω(1), O(1) et Θ(1).

#### creeBlock

retourne un pointeur sur un Block vierge utilisé notamment pour
l’initialisation de la bockChain!

#### insertBlockbyDate

Cette fonction présuppose que les blocks de la chaîne sont triés par
ordre chronologique. Elle permet d'insérer un nouveau Block juste avant
le Block qui a une date plus ancienne que lui avec un avancement
linéaire. On vérifie donc les cas ( ajout en tête, au milieu ou à la fin
de la liste) pour être capable de changer les pointers de façon à
insérer le nouveau block correctement. La complexité est donc de Ω(1),
O(b) .

#### nbBlockinChain

parcourt la chaine de la tête de la liste à sa queue en incrémentant une
variable entière de un. Elle **renvoie donc le nombre de block que
contient une chaine**. Ω(b), O(b) et Θ(b).

#### updateIDBlock

permet de s’assurer que les id des blocks sont bien ordonnés dans l’odre
croissant des dates, de 1 en 1 depuis le Block 0. On utilise donc la
fonction de comptage de Block avant de parcourir la chaine du plus
récent au plus vieux en changeant si besoin les ID des blocks. Ω(1),
O(b).

#### ajouterBlock

crée un block avec la fonction **creeBlock.** Puis insère le Block à la
bonne place chronologiquement avec la fonction **insertBlockbyDate**
dans la BlockChaine passée en paramètre. Finalement la fonction change
les id de Block de façon cohérente grâce à la fonction
**updateIDBlock**. La complexité globale est Ω(1) dans le cas où la date
du nouveau block est plus récente que celle du premier block de la
BlockChaine en paramètre, O(b) dans les autres cas.

#### totalTransactionEtudiantBlock

Cette fonction calcule le solde d’un étudiant en examinant chaque
transaction du block passé en paramètre. La complexité est donc de
Ω(tb), O(tb) et Θ(tb).

#### soldeEtudiant

Cette fonction calcule le solde de l'étudiant en examinant chaque block
de la chaîne en utilisant la fonction totalTransactionEtudiantBlock. La
complexité est donc de Ω(tc), O(tc) et Θ(tc).

#### consulter

Cette fonction utilise la fonction soldeEtudiant en Ω(tc), O(tc) et
Θ(tc) puis la fonction printHistory en O(tc) et Ω(1). La complexité est
donc de Ω(tc), O(tc) et
Θ(tc).![](/media/image1.png){width="3.0989588801399823in"
height="3.314329615048119in"}

#### crediter

utilise la fonction ajouterTransaction. La complexité est donc de Ω(1),
O(1) et Θ(1).

#### payer

vérifie en premier lieu le solde avec la fonction soldeEtudiant en
Ω(tc), O(tc) et Θ(tc). Puis soit elle ajoute la transaction soit elle
affiche un message d’erreur en Ω(1), O(1) et Θ(1). La complexité est
donc de Ω(tc), O(tc) et Θ(tc).

#### transfert

si on considère que l’id du destinataire et l’id de la source sont
différentes, on utilise la fonction payer en Ω(tc), O(tc) et Θ(tc) puis
la fonction crediter en Ω(1), O(1) et Θ(1). La complexité est donc de
Ω(tc), O(tc) et Θ(tc).

#### fprintTransactionAtBegin

Cette fonction a pour but d’écrire une transaction sous la forme
“date;idEtu;montant;description” dans le fichier “blockchain.txt”.
D’abord on copie les transactions déjà présentes dans le fichier dans
une variable. Opération en Ω(tf), O(tf) et Θ(tf). Puis écrit la nouvelle
transaction en début de fichier en Ω(1), O(1) et Θ(1) puis réécrit la
copie dans la suite du fichier en Ω(tf), O(tf) et Θ(tf). La complexité
est donc de Ω(tf), O(tf) et Θ(tf).

#### fprintTransaction

exporte la transaction en fin du fichier “blockchain.txt”. Avec
l’utilisation de l’ouverture avec ‘w’ on a une complexité est de Ω(1),
O(1) et Θ(1).

#### fprintBlock

utilise la fonction **fprintTransaction** pour chaque transaction du
block passé en paramètre. . La complexité est donc de Ω(tb), O(tb) et
Θ(tb).

#### fprintBlockChain

Basé sur le même principe, elle utilise **fprintBlock** pour chaque
Block de la chaîne dans la mémoire du programme. La complexité est donc
de Ω(tc), O(tc) et Θ(tc).

Fonctions supplémentaires
=========================

Affichages
----------

#### void printHistory(int idEtu, BlockChain bc, int lim);

Cette fonction permet d’afficher les **dernières transactions d’un
étudiant**. Le paramètre de limite permet de **limiter le nombre
d’affichage** et ainsi de limiter la profondeur de la recherche. Cette
fonction est donc utilisée dans la fonction **consulter**(int idEtu,
BlockChain bc); avec comme **paramètre de limite de 5** comme indiqué
dans les consignes du TP.

La fonction printHistory itère dans les blocks et dans les transactions
à la recherche de transactions réalisées par un étudiant précis. Si
l’étudiant n’a jamais utilisé la BlockChain, alors la fonction aura
examiné toutes les transactions de la blockChain donc on a O(tc). Dans
le meilleur cas on a une limite à 1 transaction et la transaction de
l’étudiant se trouve dans la tête de la transaction du block de la tête
de BlockChain. Ainsi on a Ω(1).

#### void printBlockChain(BlockChain Block); void printBlock(T\_Block\* Block);void printBlockEtu(int idEtu,T\_Block\* Block); void printTransaction(T\_Transaction\* t);

Ces trois fonctions ont respectivement pour but d’afficher toutes les
transactions de **tous les blocks** à partir de bc, afficher toutes les
transactions d’**un block** et finalement une s**eule transaction**. Le
découpage en trois fonctions différentes permet de une plus grande
**flexibilité de notre programme.**

La fonction printTransaction est en Ω(1), O(1) et Θ(1). La fonction
printBlock utilise la fonction printTransaction pour chaque transaction
du block donc est en Ω(tb), O(tb) et Θ(tb). Elle a la même complexité
que la fonction printBlockEtu qui est basé sur le même principe
d’itération. La fonction printBlockChain utilise la fonction printBlock
pour chaque block donc est en Ω(tc), O(tc) et Θ(tc).

#### int menu(); void PrintMenuAjou();

Ces fonctions améliorent l’interface utilisateur en **affichant les
différentes options** de manipulation de la chaîne.

Gestion des entrées
-------------------

#### void fgetsClean(char \*s);

Cette fonction a pour but de récupérer une chaine de char proprement.
C’est le paramètre s qui va être changé car nous sommes dans le cas d’un
passage par référence.

La chaîne **peut contenir des espaces!**

La chaîne **ne se termine pas par un saut de ligne.**

Cette fonction est donc très pratique dans le cas de la saisie d’une
description.

#### int askIdEtu(); int askIdBlock(); float askMontant(); tm askDate();

Ces fonctions ont des rôles identiques. Elles ont pour but de demander à
l’utilisateur une **saisie clavier** tant que celui ci n’a pas entré une
**valeur cohérente**. Par exemple pour la fonction askBlock, on
redemande toujours la saisie même si l’utilisateur entre une chaine de
char ou une valeur plus petite que 0. Cela permet plus de **stabilité**
dans notre programme.

**Chaque date** est associée à un **block unique**. La date est
enregistrée grâce au type time\_t de la librairie time.h. Avant l’ajout
d’une nouvelle transaction, l’utilisateur entre le **jour, le mois et
l’année** de la transaction et la fonction askDate() retourne le nombre
de secondes associées à cette date de **façon normalisée** (c’est-à-dire
que si la personne entre 32/12/2000 celle qui sera affichée dans la
fonction printBlock sera le 1/1/2001). Cela permet une **gestion
cohérente** des dates sur un seul champ ( donc facile à manipuler pour
comparer aux dates des autres blocks par exemple).

Recherche de Block
------------------

#### T\_Block\* searchBlockbyId(int idBlock, BlockChain bc);

Cette fonction retourne un **pointeur sur le block** de la chaîne qui a
l’**identifiant désiré**.

C’est un algorithme de **recherche linéaire**. On parcourt la chaîne en
passant d’un block à son suivant à la recherche du block seulement si
l’id est bien entre l’id du dernier block et le block 0. Si le block
n’est pas présent, on retourne un pointeur NULL avec le message: “ce
block n’existe pas” donc on a un **O(b)**. Dans le meilleur des cas, le
block recherché se situe en tête de la liste donc on a **Ω(1)**.

#### T\_Block\* searchBlockbyDate(time\_t date, BlockChain bc);

Basée sur le même principe que la fonction précédente, cette fonction
retourne un **pointeur sur le block** de la chaîne qui a la **date
désirée**. Aussi en O(b) Ω(1).

#### BlockChain\* searchTransactionToInsert(time\_t date,BlockChain\* bc,BlockChain \*bonB);

A l’ajout d’une **nouvelle transaction,** cette fonction **recherche**
un block qui a la **même date** que celle indiquée par l’utilisateur. Si
un tel block existe, alors la transaction est insérée dans la liste de
transactions de ce block. Sinon la transaction s'insère dans un nouveau
block **créé spécialement** pour le jour indiqué en **Ω(1)**. Au pire
des cas, la fonction retourne le block 0 après avoir parcouru tous les
blocks, donc **O(b)**.

On remarque l’utilisation de passage des BlockChain **par adresse**.
Ceci est nécessaire pour modifier la BlockChain et ses blocks dans une
fonction autre que dans la fonction main.

Cette fonction est utilisée à chaque **insertion** de nouvelles
transactions, que ce soit à partir d’une **saisie utilisateur** qu’à
partir d’un **fichier**.

Libération de la mémoire allouée
--------------------------------

#### void clearTransactions(BlockChain Block);

Cette fonction permet de **libérer l’allocation** dynamique qui a été
réservée **pour les transactions du block**. On parcourt la chaîne en
passant d’une transaction à sa suivante jusqu'à ce que la liste de
transactions du block soit vide. La complexité est donc de Ω(tb), O(tb)
et Θ(tb).

#### BlockChain clearBlocks(BlockChain Block);

Cette fonction permet de **libérer l’allocation** dynamique qui a été
réservée **pour les blocks** de la chaîne. On parcourt la chaîne en
passant d’un block à son suivant jusqu'au block zéro. Pour chaque block
on libère l’espace dynamique réservé pour les transactions grâce à la
fonction précédente. La complexité est donc de **Ω(tc), O(tc) et
Θ(tc)**. En définitive, on **retourne un pointeur sur le block zéro** de
la chaîne. Cela nous permet de réinitialiser notre blockChain **comme au
début du programme**. On note aussi que cette fonction est **utilisée
avant la fin de notre programme** dans la fonction main. La toute
dernière opération du programme avant sa fermeture est de libérer
l’espace mémoire du block zéro.

Tri par sélection
-----------------

#### selectBlock

permet de retirer un Block de la chaine sans le supprimer. La fonction
retourne un pointeur sur le Block qui vient d’être retiré de la Chaîne.
Ω(1), O(1) et Θ(1).

#### insertionSortbyDate

C’est la fonction bonus de notre programme! En effet nous avons
implémenté toutes les méthodes nécessaires à l’élaboration de
l’algorithme de tri par sélection.

Pour chaque Block

1)  On s’assure que la liste reste toujours triée par ID grâce a la
    > fonction uptadeIDBlock en Ω(1), O(b).

2)  On sélectionne le Block en question avec la fonction selectBlock
    > O(1)

3)  On l'insère à la bonne date avec la fonction insertBlockbyDate O(b)

Donc on a une complexité globale de Ω(b²), O(b²) . Ce qui fait de cet
algorithme l’un des algorithmes de tri les plus lents existants.
