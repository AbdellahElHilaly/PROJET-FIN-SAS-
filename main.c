#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#define  MAX_CAPACITY 5000







typedef struct pharmacy{

    int max_capacity;
    int current_capacity;

    double prix_des_produits; // le total des prix des produits vendus en journée courante
    double moyenne_des_prix; // la moyenne des prix des produits vendus en journée courante
    double Max_des_prix; // le Max des prix des produits vendus en journée courante
    double Min_des_prix; // le Min des prix des produits vendus en journée courante
    int    Nombre_de_ventes_aujourdhui;
    int Today;


}Pharmacy;



typedef struct medication{
    char  code[100];
    char name[100];

    int quantity;    // quantité
    double prix;    //prix
    double prix_TTC; // prix TTC




    int  number_sell_total; //
    int  number_sell_everytime[MAX_CAPACITY];
    char sale_dates[100][100]; // la date d’achat.




}Medication;


//________________________________________________________________________________________   1er run fonctions

    void Initialaze_Pharmacy();
    void Initialaze_all_medication();
//________________________________________________________________________________________   fonctions du project

    void Ajouter_nouveaux_produit();
    void Ajouter_plusieurs_nouveaux_produits( );
    void Sort_medicines_by_name();
    void Sort_medicines_by_price();
    void Buy_medication();
    void Alimenter_le_stock();
    void Search_by_quantity();
    void Search_by_Code();
    void Delete_Medecation();
    void Etat_du_stock();
    void Statistique_de_vente();
    void Menue();

//________________________________________________________________________________________  mini  fonctions

    void Initialaze_one_product(char* name , char* code , double prix , int quantity);
    bool String_Compare(char* str1 , char* str2);
    bool Array_String_Sort( char* array[] , int size);
    void GetActualDate( int pos_tab , int pos_dat);
    int  Get_today();
    void print_today();
    void Display_Medication( );
    int  Find_Medication_by_name(char* medication_name);
    int  Find_Medication_by_code(char* medication_name);
    void Renitializer_les_statistique();

//________________________________________________________________________________________   fonctions poure la decoration

    void Print_Center(char *text , int space_V , int space_H_modf);
    void Clear_Sreen();
    void Succes_Error_print(char* message);
    void Draw_logo();
    void Animation_Loading( char *msg , int speed);





//________________________________________________________________________________________~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



Pharmacy pharmacy;

Medication medication[MAX_CAPACITY];


int main()
{

    Initialaze_Pharmacy();
    Initialaze_all_medication();






    Menue();

}

//________________________________________________________________________________________~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





//________________________________________________________________________________________   1er run fonctions


void Initialaze_Pharmacy(){

    pharmacy.max_capacity                       = MAX_CAPACITY  ;
    pharmacy.current_capacity                   = 0             ;
    pharmacy.moyenne_des_prix                   = 0             ;
    pharmacy.prix_des_produits                  = 0             ;
    pharmacy.Max_des_prix                       = 0             ;
    pharmacy.Min_des_prix                       = 0             ;
    pharmacy.Nombre_de_ventes_aujourdhui        = 0             ;
    pharmacy.Today = Get_today();

}


void Initialaze_all_medication(){





    Initialaze_one_product("DOLIPRANE 500 mg"   , "6 679000 040364" , 25    , 500);
    Initialaze_one_product("EFFERALGAN 500 mg"  , "2 423000 020364" , 35    , 20);
    Initialaze_one_product("DAFALGAN 500 mg"    , "4 324000 020354" , 15    , 187);
    Initialaze_one_product("IMODIUM 2 mg"       , "6 145000 040354" , 10    , 1000);
    Initialaze_one_product("SPASFON"            , "2 968000 040334" , 205   , 1000);
    Initialaze_one_product("ISIMIG 2,5 mg"      , "8 872000 040354" , 25    , 120);
    Initialaze_one_product("TAHOR 80 mg"        , "0 121000 040314" , 12.5  , 1009);
    Initialaze_one_product("SPEDIFEN 200 mg"    , "6 121000 020354" , 65    , 313);
    Initialaze_one_product("VOLTARENE 100 mg"   , "8 978000 020384" , 195   , 33);
    Initialaze_one_product("ELUDRIL 40 ml"      , "1 454000 020394" , 22.15 , 203);


    Initialaze_one_product("KARDEGIC 500 mg/5 ml"   , "9 132000 040354" , 235       , 500);
    Initialaze_one_product("IXPRIM 37,5 mg/325 mg"  , "5 157000 020354" , 50.65     , 123);
    Initialaze_one_product("MAGNE B6 48 mg/5 mg"    , "3 276000 040324" , 25        , 2003);


    Initialaze_one_product("LEVOTHYROX 200 microgrammes"    , "6 987000 040334" , 26     , 1996);
    Initialaze_one_product("PARACETAMOL BIOGARAN 1 000 mg"  , "6 575000 020324" , 1      , 33);






}




//________________________________________________________________________________________   fonctions du project



void Ajouter_nouveaux_produit( ){

    fflush(stdin);

    Print_Center("Entrez le code du medicament      : " , 3 , 0);

    char temp_code[100];
    gets(temp_code);


    fflush(stdin);

    int medication_position = Find_Medication_by_code( temp_code ) ;


    if( medication_position ==-1 ){



            strcpy( medication[pharmacy.current_capacity].code , temp_code);


            Print_Center("Entrez le nom du medicament       : " , 1 , 0);

            gets(medication[pharmacy.current_capacity].name);


            fflush(stdin);

            Print_Center("Entrez la quantite de Medicament  : " , 1 , 0);
            scanf("%d" , & medication[pharmacy.current_capacity].quantity);

            Print_Center("Entrez le prix du medicament      : " , 1 , 0);
            scanf("%lf" , &medication[pharmacy.current_capacity].prix);

            medication[pharmacy.current_capacity].prix_TTC = (medication[pharmacy.current_capacity].prix
                                                      + 0.15*medication[pharmacy.current_capacity].prix);


            pharmacy.current_capacity++;

            Succes_Error_print("Le nouvelle Produit  a ete ajoutee avec Succes !");

    }

    else {
        Print_Center("Ce medicament est deja disponible, souhaitez-vous ajouter une nouvelle quantite ?\n" , 3 , 0);

        Print_Center("y : Oui                 another : Non\n" , 12 , 9);

        char choice = getch();

        if(choice = 'y'){

        int new_quantity;

ADD_NEW_QUQNTITY : Print_Center("Saisissez la nouvelle quantite de Medicament : " , 2 , 0);

            scanf("%d" , &new_quantity);

            if(new_quantity > 0){
                medication[medication_position].quantity+=new_quantity;
                Succes_Error_print("La nouvelle Quantitr a ete ajoutee avec Succes !");
            }

            else {

                Print_Center("Il n'est pas possible d'ajouter une quantite inferieure a zero !" , 2 , 0);

                Print_Center("\n\nReessayer : y              Annuler : another" , 2 , 0);
                Print_Center("Entrez votre choix : " , 2 ,0 );

                char choice = getch();

                if(choice == 'y'){

                     goto ADD_NEW_QUQNTITY ;

                }
            }
        }
    }

}


void Ajouter_plusieurs_nouveaux_produits(){
    Clear_Sreen();
    Print_Center("Entrez le nombre de medicaments que vous souhaitez ajouter : " , 12 , 0);


    int  Medicines_Number;
    scanf("%d" , &Medicines_Number);
    Clear_Sreen();


    for(int i=0 ; i<Medicines_Number ; i++){

        printf("\n             ______________________    Ajouter le medicament numero un ( %d )    ______________________" , i+1);
        Ajouter_nouveaux_produit(medication[pharmacy.current_capacity + i]);

    }

}


void Sort_medicines_by_name(){

    for(int i=0 ; i<pharmacy.current_capacity ; i++){
        for(int j=0 ; j<pharmacy.current_capacity -i -1 ; j++){
            if( strcmp(medication[j].name , medication[j+1].name) >0){

                Medication temp_medication;
                temp_medication = medication[j];
                medication[j] = medication[j+1];
                medication[j+1] = temp_medication;

            }
        }
    }

}


void Sort_medicines_by_price(){

    for(int i=0 ; i<pharmacy.current_capacity ; i++){
        for(int j=0 ; j<pharmacy.current_capacity -i -1 ; j++){

            if( medication[j].prix < medication[j+1].prix ){

                Medication temp_medication;
                temp_medication = medication[j];
                medication[j] = medication[j+1];
                medication[j+1] = temp_medication;

            }
        }
    }

}


void Buy_medication(){

    Clear_Sreen();

    Print_Center("Entrez le code du medicament que vous souhaitez acheter : " , 12 , 0);

    char medication_code[100];


    fflush(stdin);
    gets(medication_code);


    if(Find_Medication_by_code(medication_code)== -1)
            Succes_Error_print("Desole, ce medicament n'est pas disponible !");

    else{
        int Medication_position = Find_Medication_by_code(medication_code);
        Display_Medication(Medication_position);


        if(medication[Medication_position].quantity == 0){
                Succes_Error_print("Desole, le medicament est en rupture de stock.");

        }
        else{


ENTER_QUANTITY : Clear_Sreen();
            Print_Center("Ce medicament est disponible a la vente." , 2 , 0);
            Display_Medication(Medication_position);

            Print_Center("Entrez la quantite que vous souhaitez acheter : " , 2 , 0);

            int quantity;
            scanf("%d" , &quantity);

            if(quantity > medication[Medication_position].quantity){
                Succes_Error_print("Desole cette quantite n'est pas disponible.");

                goto ENTER_QUANTITY;

            }

            else {



                double final_price = quantity*medication[Medication_position].prix_TTC;

                printf("\n\t                        Le prix de la quantite que vous voulez est %lf  DH : \n" , final_price);

                Print_Center("Confirmer  : c              Annuler : another" , 1 , 0);
                Print_Center("Entrez votre choix : " , 4 , 5);

                char choice = getch();

                if(choice == 'c'){

                    medication[Medication_position].quantity-=quantity;


                    pharmacy.Nombre_de_ventes_aujourdhui +=quantity;
                    pharmacy.prix_des_produits += final_price;
                    pharmacy.moyenne_des_prix = pharmacy.prix_des_produits / (double)pharmacy.Nombre_de_ventes_aujourdhui;


                    if(pharmacy.Max_des_prix < medication[Medication_position].prix_TTC)
                         pharmacy.Max_des_prix =  medication[Medication_position].prix_TTC;



                    if(pharmacy.Min_des_prix >  medication[Medication_position].prix_TTC || pharmacy.Min_des_prix ==0)
                         pharmacy.Min_des_prix =  medication[Medication_position].prix_TTC;


                    int temp_position =  medication[Medication_position].number_sell_total; //



                     medication[Medication_position].number_sell_everytime[temp_position] += quantity ;


                     GetActualDate( Medication_position , temp_position);

                     medication[Medication_position].number_sell_total ++;

                    system("cls");

                    Succes_Error_print("Le Produit a ete Achete avec succes");

                }


            }

        }


    }

}


void Alimenter_le_stock(){
    Clear_Sreen();

    char product_code[100];

    Print_Center("Saisir le code produit : " , 12 , 0 );

    fflush(stdin);
    gets(product_code);
    fflush(stdin);


    int product_position = Find_Medication_by_code(product_code);

    if(product_position == -1)
        Succes_Error_print("Desole, ce medicament est introuvable");

    else{

        Print_Center("Ce produit a ete trouve" , 1 , 0 );

        Display_Medication(product_position);

        int new_quantity;

ADD_NEW__QUQNTITY : Print_Center("Saisissez la nouvelle quantite de Medicament : ", 1 , 0);

        scanf("%d" , &new_quantity);

        if(new_quantity > 0){
            medication[product_position].quantity+=new_quantity;
            Succes_Error_print("La nouvelle Quantite a ete ajoutee avecc succes");
        }

        else {

            Succes_Error_print("Il n'est pas possible d'ajouter une quantite inferieure a zero !");

            Print_Center("Ajustement de la quantite : y              Annuler : another" , 12 , 0);
            Print_Center("Entrez votre choix : " ,  4 , 6);

            char choice = getch();

            if(choice == 'y'){

                goto ADD_NEW__QUQNTITY ;

            }

        }

    }

}


void Search_by_quantity(){
    Clear_Sreen();
    int quantity;

    Print_Center("Entrez la quantite : " , 12 , 0);
    scanf("%d" ,&quantity);

     Animation_Loading("En train de rechercher" , 45);

    Print_Center("Voici les produits trouves : \n\n" , 2 , 0);

    int compteur = 0;

    for(int i=0 ; i<pharmacy.current_capacity ; i++){

            if(medication[i].quantity == quantity){
                 Display_Medication(i);
                 compteur++;
            }
     }



     if(compteur == 0) Print_Center("pas de donnees !!" , 12 , 0);

     getch();
     Clear_Sreen();


}


void Etat_du_stock(){
    Clear_Sreen();
    int compteur = 0;

    for(int i=0 ; i<pharmacy.current_capacity ; i++){

        if(medication[i].quantity  < 3){
                compteur ++ ;
                Display_Medication(i);

        }
     }

     if(compteur == 0) Succes_Error_print("pas de donnees !!");
}


void Search_by_Code(){
    Clear_Sreen();

     char code[100];
     Print_Center("Entrez le code du medicament : " , 12 , 0) ;

     fflush(stdin);
     gets(code);
     fflush(stdin);
     Animation_Loading("En train de rechercher" , 45);
     int position = Find_Medication_by_code(code);
     if( position == -1)

        Succes_Error_print("Desole, ce medicament est introuvable !");

    else{

        Print_Center("Voici les resultas de la recherch :\n\n\n" ,  4 , 0);
        Display_Medication(position);
        getch();
    }
    Clear_Sreen();




}


void Delete_Medecation(){
    Clear_Sreen();

    Print_Center("Entrez le code du produit que vous souhaitez supprimer : " , 12 , 0);
    char code[100];

    fflush(stdin);
    gets(code);
    fflush(stdin);

    int position = Find_Medication_by_code(code);

    if(position == -1)
        Succes_Error_print("Desole, Medicament introuvable !");

    else {

        for(int i=position ; i<pharmacy.current_capacity -1 ; i++)

            medication[i] = medication[i+1];


            pharmacy.current_capacity--;

            Succes_Error_print("Le produit a ete suprime avec succes.");

    }


}


void Statistique_de_vente(){
    Clear_Sreen();
    if(pharmacy.Today != Get_today())
            Renitializer_les_statistique();


    Clear_Sreen();
    printf("\n\n             ~~~~~~~~~~~~~~~~~~~     Statistiques des ventes du jour ( ");
    print_today();
    printf(" )      ~~~~~~~~~~~~~~~~~~~\n\n");

    printf("        Les prix totaux des produits vendus le jour en cours            : %lf DH\n" , pharmacy.prix_des_produits);
    printf("        Le prix moyen des produits vendus le jour en cours              : %lf DH\n" , pharmacy.moyenne_des_prix);
    printf("        Le Max des prix des produits vendus au jour en cours            : %lf DH\n" , pharmacy.Max_des_prix);
    printf("        le Min des prix des produits vendus dans la journee en cours    : %lf DH\n" , pharmacy.Min_des_prix);
    printf("        Nombre de produits vendus aujourd'hui                           : %ld\n"    , pharmacy.Nombre_de_ventes_aujourdhui);


    Print_Center("Afficher les statistiques detaillees     y : Oui      another  :  Non" , 2 , 0);

    Print_Center("Entrez votre choix : " , 2 , 0);

    char choice = getch();

    if(choice == 'y'){

            Print_Center("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   Statistiques detaillees   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ", 2 , 0);


            for(int i=0 ; i<pharmacy.current_capacity ; i++){

                    if(medication[i].number_sell_total >0){
                        Print_Center("_________________________________\n" , 2 , 0);
                        printf("                                    Code produit : %s \n" , medication[i].code);
                        printf("                                    Prix TTC     : %lf \n" , medication[i].prix_TTC);


                        for(int j=0 ; j< medication[i].number_sell_total ; j++)
                            printf("                                    Ce produit a ete vendu  %d  fois           le : %s.\n\n" , medication[i].number_sell_everytime[j]  , medication[i].sale_dates[j] );

                    }

                }

    }


    getch();
    Clear_Sreen();

}


void Menue(){

    //system("color EA");

Menue:

    Draw_logo();

    Print_Center("1   : Ajouter un nouveau produit.                                                 " , 2 , 10 );
    Print_Center("2   : Ajouter plusieurs nouveaux produits.                                        " , 1 , 10 );
    Print_Center("3   : Lister tous les produits selon l'ordre alphabetique  croissant du nom.      " , 1 , 10);
    Print_Center("4   : Lister tous les produits selon l'ordre  decroissant du prix.                " , 1 , 10);
    Print_Center("5   : Acheter produit.                                                            " , 1 , 10);
    Print_Center("6   : Rechercher les produits Par Code.                                           " , 1 , 10);
    Print_Center("7   : Rechercher les produits Par Quantite.                                       " , 1 , 10);
    Print_Center("8   : Etat du stock (afficher les produits dont la quantite est inferieure a 3).  " , 1 , 10);
    Print_Center("9   : Alimenter le stock.                                                         " , 1 , 10);
    Print_Center("10  : Supprimer les produits par Code.                                            " , 1 , 10);
    Print_Center("11  : Statistique de vente.                                                       " , 1 , 10);
    Print_Center("12  : Menu annuler .                                                              " , 1 , 10);


    Print_Center("Enter votre choix : " , 4 , 6);
    int choice;
    scanf("%d" , &choice);

    switch(choice){

    case 1 :
        Clear_Sreen();
        Ajouter_nouveaux_produit();
        goto Menue;
    case 2 :
        Ajouter_plusieurs_nouveaux_produits();
        goto Menue;
    case 3 :
        Sort_medicines_by_name();
        Display_All_Medication();
        goto Menue;
    case 4 :
        Sort_medicines_by_price();
        Display_All_Medication();
        goto Menue;
    case 5 :
        Buy_medication();
        goto Menue;
    case 6 :
        Search_by_Code();
        goto Menue;
    case 7 :
        Search_by_quantity();
        goto Menue;
    case 8 :
        Etat_du_stock();
        goto Menue;
    case 9 :
        Alimenter_le_stock();
        goto Menue;
    case 10 :
        Delete_Medecation();
        goto Menue;
    case 11 :
        Statistique_de_vente();
        goto Menue;
    case 12 :
        break;

    default :
        Print_Center("Wrong choice !!" , 1 , 0);
        getch();
        goto Menue;




    }



}


//________________________________________________________________________________________  mini  fonctions

void Initialaze_one_product(char* name , char* code , double prix , int quantity){

    strcpy(medication[pharmacy.current_capacity].name  , name);
    strcpy(medication[pharmacy.current_capacity].code  , code);

    medication[pharmacy.current_capacity].quantity =  quantity;
    medication[pharmacy.current_capacity].prix = prix;

    medication[pharmacy.current_capacity].prix_TTC = prix + (0.15*prix);

    pharmacy.current_capacity++;

}

int Find_Medication_by_name(char* medication_name){

     for(int i=0 ; i<pharmacy.current_capacity ; i++){

            if( String_Compare( medication[i].name , medication_name)){
                return i;

            }

     }

    return -1;

}

int Find_Medication_by_code(char* medication_code){

     for(int i=0 ; i<pharmacy.current_capacity ; i++){

            if( String_Compare( medication[i].code , medication_code)){
                return i;

            }
     }

    return -1;

}

void Display_Medication(int position){
    Print_Center("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" , 0 , 0);
    printf("                                    Nom de medicament           : %s\n" , medication[position].name);
    printf("                                    Code de medicament          : %s\n" , medication[position].code);
    printf("                                    Quantite de medicament      : %d\n" , medication[position].quantity);
    printf("                                    Prix de medicament          : %lf DH\n" , medication[position].prix);
    printf("                                    Prix TTC de medicament      : %lf DH\n" , medication[position].prix_TTC);

    printf("\n\n\n");
}

void Display_All_Medication( ){

    Clear_Sreen();
    change_background_color("F1");

    Print_Center("_______________________Ceci est la liste de tous les medicaments__________________\n\n\n" , 3  , 0);

    for(int i=0 ; i<pharmacy.current_capacity ; i++)
        Display_Medication(i);


    getch();
    Clear_Sreen();
    change_background_color("07");


}

bool String_Compare(char* str1 , char* str2){

    if(strcmp(str1 , str2) == 0) return true;
    else return false;

}

void GetActualDate( int pos_tab , int pos_dat){


    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char currentDate[100];


    char day[3];
    char month[3];
    char year[5];
    char hour[3];
    char min[3];
    char sec[3];


    sprintf(day, "%02d", t->tm_mday, sizeof(day));
    sprintf(month, "%02d", t->tm_mon+1, sizeof(month));
    sprintf(year, "%04d", t->tm_year + 1900, sizeof(year));
    sprintf(hour, "%02d", t->tm_hour, sizeof(hour));
    sprintf(min, "%02d", t->tm_min, sizeof(min));
    sprintf(sec, "%02d", t->tm_sec, sizeof(sec));



    strcpy(currentDate, day);
    strcat(currentDate, "/");

    strcat(currentDate, month);
    strcat(currentDate, "/");

    strcat(currentDate, year);

    strcat(currentDate, "\t");
    strcat(currentDate, hour);

    strcat(currentDate, ":");
    strcat(currentDate, min);

    strcat(currentDate, ":");
    strcat(currentDate, sec);

    strcpy(medication[pos_tab].sale_dates[pos_dat] , currentDate);

}

int Get_today(){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    return t->tm_wday;
}

void print_today(){


    time_t timestamp = time( NULL );
    struct tm * pTime = localtime( & timestamp );

    char buffer[80];

    strftime(buffer, 80, "%A", pTime );
    printf( "%s", buffer );


}

void Renitializer_les_statistique(){
    Initialaze_Pharmacy();
}



//________________________________________________________________________________________   fonctions poure la decoration

void Print_Center(char *text , int space_V , int space_H_modf){

    //default center space 12

    for(int i=0 ; i<space_V ; i++)
        printf("\n");


    int space = 117;

    printf ("%*s", space / 2 + strlen(text) / 2 + space_H_modf ,text);

}


void Clear_Sreen(){
    system("cls");
}

void Succes_Error_print(char* message){


    Clear_Sreen();
    //system("color F1");
    change_background_color("F1");
    Print_Center(message , 14 , 0);
    getch();
    Clear_Sreen();
    system("color 07");



}


void change_background_color(char *new_color){

        char color[20];
        strcpy(color , "COLOR ");
        strcat(color , new_color);

        system(color);


        /*
    0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White
    */

}

void Draw_logo(){

    printf("\n\n                           ");

    for(int i=0 ; i<20 ; i++){
        printf("%c" , 176);
    }

    printf(" You Code ~ Projet SAS ");

     for(int i=0 ; i<20 ; i++){
        printf("%c" , 176);
    }

    Print_Center("~~~~~~~~~~~~   Gestion de Pharmacie   ~~~~~~~~~~~~\n\n\n", 2 , 0);

    for(int i=0 ; i<24 ; i++)

        printf(". %c ." , 4);


}

void Animation_Loading( char *msg , int speed){

    change_background_color("30");

    Clear_Sreen();

    Print_Center(msg , 10 , -12);


    for(int i=0 ; i<12 ; i++){

        printf(". ");
        Sleep(45);

    }

    Clear_Sreen();
    change_background_color("07");

}




























