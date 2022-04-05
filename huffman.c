#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct _Nodo
{
   float frec;
   char letra;
   char c[128];
   struct _Nodo *izq;
   struct _Nodo *der;
}Nodo;

Nodo *khe[26], *letras[26];

Nodo *crear(char letra)
{
     Nodo *nuevo;
     nuevo=(Nodo*)malloc(sizeof(Nodo));
     nuevo->letra=letra;
     nuevo->frec=1;
     nuevo->izq=NULL;
     nuevo->der=NULL;
     return nuevo;
}

void minimos(Nodo *arr[], float *min, int *miniIndex, float *segmin, int *secondIndex)
{
    int i, k;
    k = 0;
    *miniIndex = -1;
      
    while (k <26 && arr[k] == NULL) k++;

    *miniIndex = k;
    *min = arr[k]->frec;

    for ( i = k ; i < 26; i ++ )
    {
        if ( arr[i] != NULL && arr[i]->frec < *min )
        {
            *min = arr[i]->frec;
            *miniIndex = i;
        }
    }

    k = 0;
    *secondIndex = -1;
   //Skipping all the NULL elements.
              
    while ((k < 26 && arr[k] == NULL) || (k == *miniIndex && arr[k] != NULL)) k++;

    *segmin = arr[k]->frec;
    *secondIndex = k;

    if (k == *miniIndex) k ++;

    for ( i = k ; i < 26; i ++ ) 
    {
        if ( arr[i] != NULL && arr[i]->frec < *segmin && i != *miniIndex ) 
        {
            *segmin = arr[i]->frec;
            *secondIndex = i;
        }
    }
    
}

void codifica(Nodo *arbol, Nodo **letras, char meh, short yup, char* so)
{
     int n;
     
     if(arbol!=NULL)
     {
       if((n=strlen(so))<yup)
       {
         if(meh=='r')
         {
           strcat(so,"1");
         }// if para la derecha
         if(meh=='l')
         {
           strcat(so,"0");
         }//if para la izquiera 
       }//if secundario
       else
       {
           if(n>=yup)
           {
              so[n-(n-yup)-1]=0;
              if(meh=='r')
              {
                strcat(so,"1");
              }//2.1.2
              else
              {
                if(meh=='l')
                {
                   strcat(so,"0");
                }//2.1.2.1
              }//2.1.2
           }//2.1
       }//else secundario
       if(arbol->letra>='a' && arbol->letra<='z')
       {
          strcpy(arbol->c,so);
          strcpy(letras[arbol->letra-'a']->c,so);
       }//1.1
       codifica(arbol->izq,letras,'l',yup+1,so);
       codifica(arbol->der,letras,'r',yup+1,so);
     }//if principal
}

void imp(Nodo *arbol)
{
     int n;
     
     if(arbol!=NULL)
     {
       if(arbol->letra>='a' && arbol->letra<='z')
       {
          printf("\t%c - frecuenca: %.10f\tcodigo respectivo: %s\n", arbol->letra, arbol->frec, arbol->c);
       }//1.1
       imp(arbol->izq);
       imp(arbol->der);
     }//if 1
}
int main(int argc, char *argv[])
{
  char opc[128];
  int fileR, x,y,z,index,n,miniIndex,secondIndex;
  int caracteres=0;
  float min,segmin;
  Nodo *arbol;
  FILE *ar=fopen("meh.txt","r"), *out;
  if(ar==NULL)
  {
    printf("No hay archivo por leer\n");
  }//if principal
  else
  {
      for(x='a'; x<='z'; x++)
      {
        index=x-'a';
        khe[index]=NULL;
      }//for1
      caracteres=0;
      fileR=fgets(opc,128,ar)!=NULL;//optiene los caracteres de archivo
      while(!feof(ar)||fileR)
      {
       printf("caracteres en la cadena: %d\n",n=strlen(opc));
       printf("%s",opc);//imprime el contenido del archivo
       for(x=0; x<n; x++)//empieza el calculo de la frecuencia 
       {
         opc[x] = tolower(opc[x]);//todo a minusculas
         if(opc[x]>='a'&&opc[x]<='z')
         {
           caracteres++;
           index=opc[x]-'a';
           if(khe[index]==NULL)
           {
             khe[index]=crear(opc[x]);
           }//if3
           else
           {
               khe[index]->frec+=1;
           }//else3
         }//if2
       }//for2
       if(fileR)
       {
         fileR=fgets(opc,128,ar)!=NULL;
       }//if4
      }//while1
      
  }//else principal
  fclose(ar);
  printf("\n todo ok despues de optener la frecuencia\ncaracteres contados: %d\n",caracteres);
   for(x=0,n=0; x<26; x++)
   {
     letras[x]=khe[x];
     if(khe[x]!=NULL)
     {
       khe[x]->frec/=caracteres+5;
       n++;
     }//if3
   }//for2
   //printf("\n todo ok antes de la seleccion de minimos");
   y=1;
   do
   {float f;
       minimos(khe,&min,&miniIndex,&segmin,&secondIndex);
       if(miniIndex!=-1 && secondIndex!=-1 && miniIndex!=secondIndex)
       {//printf("\n todo ok antes de la creacion rara del arbol");
           Nodo *temp;
          // printf("\n no se crea el arbol raro");
           arbol=malloc(sizeof(Nodo));
          //printf("\n se crea el arbol raro");
           // printf("\n no se asigna la frecuencia en el raro");
           arbol->frec=khe[miniIndex]->frec+khe[secondIndex]->frec;
           //printf("\n se asigna la frecuencia en el raro");
           arbol->letra=y;
        //   printf("\n se asigna el caracter en el raro");
           arbol->izq=khe[miniIndex];
           //printf("\n se crea el nodo arbol sin pedos");
          // printf("\n todo ok despues de la creaccion rara del arbol");
           temp=crear(khe[secondIndex]->letra);
           temp->frec=khe[secondIndex]->frec;
           temp->izq=khe[secondIndex]->izq;
           temp->der=khe[secondIndex]->der;
           arbol->der=temp;
           khe[miniIndex]=arbol;
           khe[secondIndex]=NULL;
       }//if4
       y++;
   }while(y<n);//do while
   // printf("\n todo ok antes de la codificacion");
   for(x=0; x<26; x++)
   {
       if(khe[x]!=NULL)
       {
          char lol[128];
          strcpy(lol,"");
          codifica(arbol=khe[x],letras,0,0,lol);
         // printf("\n todo ok\n");
          imp(khe[x]);
          break;
       }//if5
   }//for5
  getch();
}
