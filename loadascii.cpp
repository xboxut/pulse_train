

#include <stdio.h>

#include "loadascii.h"




/****************************************************************
double ** universal_loader(int *size,const char *path)
----------------------------------------------------------------
Fonction pour charger un fichier de donn�es quelque soit son type 
de s�paration et de mise en forme.
Il faut cependant respecter la suite de chiffres x, y.

Les char 123456789 . e E sont r�serv�s

La fonction retourne un pointeur vers un tableau 2d contenant
2 lignes et size colonnes.

int *size        pointeur vers un entier ou sera stock�e la taille
                 du tableau
cont char *path  pointeur vers la chaine de char contenant le nom du 
                 fichier
*****************************************************************/
double ** universal_loader(int *size,const char *path)
{
    
    char *stringloaded;//pointeur qui pointera sur le fichier une fois charg� en memoire
    int  nb_cnt=0;//compteur du nombre de points de mesures pr�sent dans le fichier
    char buffer[32];//buffer pour isoler chacun des nombres du fichier en vue de le convertir en double
    char *ptr_fich;//pointeur de recopie plac� sur le fichier
    char *ptr_buff;//pointeur de recopie plac� sur le buffer
    double *tab;//pointeur sur tableau qui contiendra l'ensemble des points
    double **return_tab;//pointeur sur le tableau que l'on retournera
    
    bool copy=false;
    int i;//variable utilis�e dans les for
    
    /*****************************************************
    Chargement du fichier en m�moire
    *****************************************************/
       
    FILE *temp=fopen(path,"rb");// ouverture du fichier en mode binaire
    if(temp==NULL)return NULL;
	fseek(temp,0,SEEK_END);// recherche de la fin du fichier
	
    int charlen=ftell(temp); // r�cup�ration du nombre d'octet entre le 
                             //d�but et la fin du fichier
	
    fseek(temp,0,SEEK_SET);// On se replace au d�but du fichier
    
	stringloaded=new char[int(charlen)+1];
    // construction d'une chaine de char qui contiendra l'ensemble du fichier
	
	fread(stringloaded,charlen,1,temp);
    //chargement du fichier dans la chaine nouvellement cr�e
    
    fclose(temp);
	
    stringloaded[int(charlen)]='\0';
    
    
    //printf(stringloaded);
    //Placement de la fin de la chaine � la place de EOF.
    
    /********************************************************
    traitement du fichier
    ********************************************************/  
     
     tab=new double[2*MAX_TAB_LENGTH];//cr�ation du tableau de double
 
     
     ptr_fich=stringloaded;
     ptr_buff=buffer;
     
     do// on boucle tant que tout le fichier n'est pas trait�
     {
          //Si le charactere point� par le pointeur est un nombre 
          // ou une "puissance"
          if((*ptr_fich>='0' && *ptr_fich<='9')|| *ptr_fich=='.' 
                || *ptr_fich=='e' || *ptr_fich=='E' || *ptr_fich=='-' || *ptr_fich=='+')
          {
             copy=true; // on signale que la copie de nombre est en marche
             *ptr_buff=*ptr_fich; //on copie chaque chiffre dans le buffer
             ptr_buff++;//on incremente le pointeur du buff se d�placer dans la chaine  
                
          }
          else //sinon
          {
             if(copy==true)//si l'on a plus rien a copier mais que l'on vient de le faire  
             {
                  copy=false;// on arrete la copie
                  *ptr_buff='\0';//on cloture la chaine contenue dans buffer
                  tab[nb_cnt]=atof(buffer);// et on la transforme en double
                  //printf(buffer);
                  //printf("\n%d\n",nb_cnt);
                  nb_cnt++;//on incr�mente le nombre de nombre d�j� convertis
                  ptr_buff=buffer;// on replace le pointeur au d�but du buffer pour r��crire dessus    
             } 
          }                           
                               
          ptr_fich++; 
          //printf("%c\n",*ptr_fich);                
     }while(*(ptr_fich-1)!='\0');
       
     
     //On dispose maintenant d'un tableau en 1d contenant les x et les y
     // On va trier les x et les y en utilisant un nouveau tableau que 
     // l'on va ensuite pouvoir retourner.
     
     return_tab=new double*[2];
     for( i=0;i<2;i++)
     return_tab[i]=new double[nb_cnt/2];
     
     for( i=0;i<nb_cnt/2;i++)//trie des x et des y et stockage de ces dernier dans un tableau
     {
     return_tab[0][i]=tab[i*2];     
     return_tab[1][i]=tab[i*2+1];          
     }
       
     //avant de terminer la fonction, on sp�cifie � l'utilisateur le nb de points dans
     // le tableau
   if(size!=NULL)
    *size=nb_cnt/2;   
       
    delete [] tab;
    return return_tab;   
}

