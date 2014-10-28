//PASS ONE ASSEMBLER BASED ON IBM 360
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int LC=0;						// LOCATION COUNTER
char sym[20],nme[20],opd[100];	//symbol , nme , opcode
void POTGET1();					// search pseudo-op table
void MOTGET();					// Search Machine Op-code table
void LTSTO();					// Process Literals
void main(){
	FILE *fp;
	LC =0;
	fp=fopen("input.txt","rt");
	while(fscanf(fp,"%s %s %s %s",&sym,&nme,&opd)!=EOF){
		POTGET1();
		MOTGET();
		LTSTO();
	}

}
void POTGET1(){
	//Search pseudo op table 
	// valid entries are DC DS EQU USING DROP END 
	int i=0,count=0,comma=1;
	int j=0,k=0;
	int DLENGHT=0;
	char ch;
	char form[4];
	if(strcmp(nme,"DC")==0){
		/*
			various senarios :
			DC F'25,26,27'
			DC F'6'
			DC <FORMAT> ' <NUMBERS> '
		*/
		i=0;
		comma=1;
		count=0;
		do{
			ch=opd[i];
			if(count==0){
				//add to format
				form[i]=opd[i];
			}
			if(count==1)
				form[i]='\0';
			if(ch=='\'')
				count++;
			if(ch==',')
				comma++;
			i++;
		}while(count!=2 &&ch[i]!='\0');

		printf("\n The Format is %s ",form);   			//	<-TESTING
		if(strcmp(form,"F")==0)
			DLENGTH=4;
		if(strcmp(form,"HF")==0)
			DLENGTH=2;
		if(strcmp(form,"C")==0)
			DLENGTH=1;

		DLENGTH=DLENGTH*comma;
		LC=LC+DLENGTH;

		// if there is symbol call STSTO
	}
	if(strcmp(nme,"DS")==0){
		// DS 2000F   , DS 2F , DS F
		i=0;count=0;
		do{
			ch=opd[i];
			if(isalpha(ch))
				count=1;
			if(count==0){
				value[k]=opd[i];
				k++;
			}
			if(count==1){
				form[j]=opd[i];
				j++;
			}
			i++;
			value[k]='\0';
			form[j]='\0';


		}while(ch!='\0');
		
		if(strcmp(form,"F")==0)
			DLENGTH=4;
		if(strcmp(form,"HF")==0)
			DLENGTH=2;
		if(strcmp(form,"C")==0)
			DLENGTH=1;
			
		DLENGTH=atoi(value)*DLENGTH;
		// if there is symbol call STSTO
		LC + = DLENGTH;
	}
	if(strcmp(nme,"EQU")==0){
			// handle in STSTO --> EQU ALSO .. STSTO();			
	}
	if(strcmp(nme,"USING")==0){
			// ignore 
	}
	if(strcmp(nme,"DROP")==0){
			//ignore
	}
	if(strcmp(nme,"END")==0){
			//LITASS
	}
}
void MOTGET(){
	//search machine op code table 
	FILE *mfp;
	char mnme[5],mbop[3],mif[4],mlen[3];
	mfp=fopen("mot.txt","rt");
	while(fscanf(mfp,"%s %s %s %s",&mnme,&mbop,&mlen,&mif)!=EOF){
		if(strcmp(nme,mnme)==0){
			LC = LC + atoi(mlen);
		}
	}
	fclose(mfp);
}
void LTSTO(){
	//process any literals into literal table 
	
}