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
        printf("Saisissez le numero de votre choix:");
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
        myDate.tm_hour = 1;
        myDate.tm_min = 0;
        myDate.tm_sec = 0;

        timestamp = mktime( & myDate );
    }while(timestamp == -1);
    timestamp-=(timestamp%3600)+3600;//pour normaliser les minutes
    //printf( "Timestamp == %ld\n", timestamp );

    const char * strDate = asctime( localtime( & timestamp ) );

    //printf( "Date de la transaction: %s\n", strDate );

    return timestamp;
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
