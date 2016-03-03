#include <stdio.h>
#include <stdlib.h>   //exit(1)で使用
#include <sys/uio.h>
#include <sys/types.h>
#include <fcntl.h>   //ファイル記述子の操作等　open()でも使っている
#include <unistd.h>    //read writeで使う

int main(int argc, char *argv[]){

  int i,n=0;
  int fd[1];     //ファイル記述子用 fd[0]:concat.txt, fd[1]:other.txt
  char buf[50];

 for(i=0;i<50;i++){buf[i]=' ';}  //bufferの初期化

 //引数を与えるよう注意
 if(argc==1){printf("Please input unised files"); exit(1);} 
 
  // concat.txtファイルを開く
   fd[0] = open("concat.txt",O_WRONLY);
   if (fd[0] == -1) {  // concat.txtを開くとき、エラーだった場合(存在しない場合)
	perror("open");
	printf("concat.txt is creating.\n");
  //結合ファイルの作成
    fd[0] = creat("concat.txt",S_IREAD | S_IWRITE);  //読み書き用ファイルを作成
	if(fd[0] == -1){   //作成に失敗した場合、エラーを出力
    perror("creat");
    exit(1);}
	
	} else {printf("concat.txt Success open\n");}
			
// -------------------------------------------------------------------

  for (i=1;i<argc;i++){
    printf("open file is : %s\n",argv[i]);  //現在処理中のファイル名の表示

    if ((fd[1] = open(argv[i], O_RDONLY)) != -1) {  // ファイルが開けた場合
	printf("Success open\n");
	
	if((n = read(fd[1],buf,sizeof(buf))) !=  -1){ //Readエラーでない場合
         printf("Success read\n");
		 write(fd[0],buf,n);        //読み込んだbufferを書き込む
	     printf("Success write\n");
	} else {                                   //Readエラー処理
	 perror("read");
     close(fd[0]);
     close(fd[1]);
     exit(1);
	 }
     
	 close(fd[1]);     //open fd[1] close
	 } else {                                  //ファイルが開けなかった場合
	 perror("open");
	 close(fd[0]);
	 close(fd[1]);
	 exit(1);
	 }
	
     }// 読み込むファイルの終わり
      printf("all file writed.");
      close(fd[0]);   // open fd[0](concat.txt) close
  
    }