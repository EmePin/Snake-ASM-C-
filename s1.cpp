#include<iostream.h>
#include<conio.h>


#include<stdlib.h>
#include<dos.h>

//int escapar = 7;

void sonido();
void cls();
int leer();
int leer2(); 

LOC(int i,int j)
{
    int r1 = 0;
    int valor = 1000;
    asm{

        mov ax,i
        mov bx,valor 
        mul bx
        mov bx,j
        add ax,bx
        mov r1,ax
    }
    return r1;
}

void pantalla(char serptnt[20][77])
{
 int i,j,k;
 for(k=0;k<79;k++)
 cout<<"+";
 cout<<endl;
 for(i=0;i<20;i++)
 {
  cout<<"!";
  for(j=0;j<77;j++)
  {
     
    char calc = serptnt[i][j];
    if(calc == '@'){
    asm{
            mov AL, calc
            mov BL, 4
            mov bh,00h
            mov CX,01
            mov ah,09h
            int 10h
            mov ah,02h
            mov dl,calc
            int 21h
    }
}else{
            
    asm{
            mov AL, calc
            mov BL, 2
            mov bh,00h
            mov CX,01
            mov ah,09h
            int 10h
            mov ah,02h
            mov dl,calc
            int 21h
    }
}


  }
  cout<<"!"<<endl;
 }
 for(k=0;k<79;k++)
 cout<<"+";
}


void sonido(int duracion){
    asm MOV DX, duracion
    fijar:
    asm{
    AND AL, 100         // Tono
    OUT 61H, AL         //Salida a puerto 
    MOV CX, 9999       
    }

    retraso:
    asm{
    LOOP retraso
    OR AL, 00000011B
    OUT 61H, AL
    MOV CX, 9999

    }
    
    reproducir:
    asm{
    LOOP reproducir
    DEC DX
    JNZ fijar
    }
}


int leer(){
    int num2 = 0;
    asm{
    	MOV AH,01h
    	INT 21h
    	MOV num2,ax
    }
    return num2;

}

void cls(){
asm{
              mov ax,0600h        
              mov bh,15           
              mov cx,0000h        
              mov dx,184fh        
              int 10h
}

}

int leer2(){
    int num2 = 0;
    asm{
        MOV AH, 06h
        INT 21h
        MOV num2, ax
    }
    return num2;

}

void manzanita(char serptnt[20][77],char tecla) 
{ 
 int c,d; 
 do 
 { 
  c = random(20); 
  d = random(77); 
 } 
 while(serptnt[c][d]==tecla);
 serptnt[c][d] = '@'; 
}



    main() 
    { 
        inicio:
        cls();
        randomize(); 
        clrscr();
        char tecla; 
        char serptnt[20][77],move='R',MOVE; 
        int a=10,b=30,n=2; 
        int x=1,m=1,loc[30000]; 
        int t=1,puntos=0; 
        cout<<"                              JUEGO DE LA SERPIENTE"<<endl<<endl; 
        cout<<"La comida es @"<<endl<<endl; 
        cout<<"Ingrese una letra o un simbolo para el cuerpo de la serpiente"<<endl; 
        tecla = leer();
        if(tecla != ' '){
        cout << tecla;
        for(int i=0;i<20;i++) 
        { 
         for(int j=0;j<77;j++) 
         { 
          serptnt[i][j]=' '; 
         } 
        } 
        serptnt[10][30]=tecla; 
        serptnt[10][10]='@'; 
         inicio2: 
         clrscr(); 
         loc[m++] = LOC(a,b); 
         cout<<"                              Puntuacion: "<<puntos<<endl; 
         pantalla(serptnt); 
         delay(100); 
        if(kbhit()) 
         { 
          MOVE=getch(); 
          if(MOVE== 77 && move !='L') 
          move='R'; 
          if(MOVE== 80 && move !='U') 
          move='D'; 
          if(MOVE== 75 && move !='R') 
          move='L'; 
          if(MOVE== 72 && move !='D') 
          move='U'; 
         } 
         //int selc = leer2();
        if(move=='R') 
         { 
          if(serptnt[a][b+1]==tecla || b==76) 
          goto fin;
          if(serptnt[a][b+1] != ' ' && serptnt[a][b+1] != '@')
          goto fin; 
          if(serptnt[a][b+1]=='@') 
          { 
           serptnt[a][++b]=tecla; 
           n++; puntos+=10; 
           manzanita(serptnt,tecla); 
           sonido(1000);
          } 
          else 
          serptnt[a][++b]=tecla; 
         } 
          if(move=='D') 
         { 
          if(serptnt[a+1][b]==tecla || a==19) 
          goto fin; 
            if(serptnt[a+1][b] != ' ' && serptnt[a+1][b] != '@')
          goto fin; 
          if(serptnt[a+1][b]=='@') 
          { 
           serptnt[++a][b]=tecla; 
           n++; puntos+=10; 
           manzanita(serptnt,tecla);
           sonido(1000);
          } 
          else 
          serptnt[++a][b]=tecla; 
         } 
          if(move=='L') 
         { 
          if(serptnt[a][b-1]==tecla || b==0) 
          goto fin; 
        if(serptnt[a][b-1] != ' ' && serptnt[a][b-1] != '@')
          goto fin; 
          if(serptnt[a][b-1]=='@') 
          { 
           serptnt[a][--b]=tecla; 
           n++; puntos+=10; 
           manzanita(serptnt,tecla); 
           sonido(1000);
          } 
          else 
          serptnt[a][--b]=tecla; 
         } 
          if(move=='U') 
         { 
          if(serptnt[a-1][b]==tecla || a==0) 
          goto fin; 
      if(serptnt[a-1][b] != ' ' && serptnt[a-1][b] != '@')
          goto fin; 
          if(serptnt[a-1][b]=='@') 
          { 
           serptnt[--a][b]=tecla; 
           n++; puntos+=10; 
           manzanita(serptnt,tecla);
            sonido(1000); 
          } 
          else 
          serptnt[--a][b]=tecla; 
         } 
         x++; 
         if(x>n) 
         { 
          int e = loc[t]/1000; 
          int f = loc[t]%1000; 
          serptnt[e][f]=' '; 
          t++; x--; 
         } 
         goto inicio2; 
        fin: 
        clrscr();
        gotoxy(30,10); 
        cout<<"Total de puntos: "<<puntos; 
        gotoxy(45,10);
        leer();
         asm{
            mov bh,0dh
            cmp al,bh
            jne fin
         }
        goto inicio;
        }
       salir:
       return 0; 
}