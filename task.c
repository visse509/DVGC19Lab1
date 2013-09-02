#include "stdio.h"
#include "stdlib.h"
void readFile(FILE *fp,char*);

int getCharacterFreq(FILE *fp,int *list){
	char string[1500] = {0};
	readFile(fp,string);
	int totalChars = 0;
	int pos = 0;
	while(string[pos] != EOF)
	{
		int ch = string[pos];
		int charNumber = ch-97;
		if(charNumber > -1){
			list[charNumber]++;
			totalChars++;
		}
		//space
		else if(charNumber == -65){
			list[26]++;
		//	printf("%d\n", charNumber);
		}
		
		pos++;
	}
	printf("%s\t","Total number of characters");
	printf("%d \n",totalChars);
	return totalChars;
}

void readFile(FILE *fp,char* string){
	int pos = 0;
	printf("%s\n","reading file...");
	if(fp != NULL)
	{
		int ch = fgetc(fp);
		while(ch != EOF)
		{
			//printf("%c",ch);
			string[pos] = ch;
			ch = fgetc(fp);
			pos++;
		}
		string[pos+1] = EOF;
	}
	printf("%s\n","done!");
}
void readkey(FILE *fp,int *key){
	int pos = 0;
	printf("%s\n","reading key...");
	if(fp != NULL)
	{
		int ch = fgetc(fp);
		while(ch != EOF)
		{
			//printf("%c",ch);
			key[pos] = ch;
			ch = fgetc(fp);
			pos++;
		}
		key[pos+1] = EOF;
	}
	printf("%s\n","done!");
}
int findReplace(int oldChar, int *key)
{
	int i;
	for(i = 0; i < 27; i++)
	{
		//printf("%d\n",key[i]);
		if(key[i] == oldChar){
		//	printf("%d\t",key[i]);
		//	printf("%c\t",oldChar);
		//	printf("%c\n",i+97);
			return i;
		}
	}
	return oldChar;
}
void decryptText(FILE *fp){
	FILE *keyFileP = fopen("key","r");
	char text[1500] = {0};
	char newText[1500] = {0};
	int key[100] = {0};
	readFile(fp,text);
	readkey(keyFileP,key);
	printf("%s \n","finding char");
	int pos = 0;
	while(text[pos] != EOF)
	{
		
		int ch = text[pos];
		int newChar = findReplace(ch,key);
		if(newChar == 26){
		  newText[pos] = 32;
		}
		else if((ch < 123) && (ch > 96) || ch == 32){
		  newText[pos] = newChar+97;
		}
		else{
		  newText[pos] = newChar;
		}
		pos++;
	}
	printf("%s\n",newText);
	int i;
	for(i = 0; i < 26; i++){
		//printf("%d\t",newText[i]);
		//printf("%c\n",key[i]);
	}
}
int main(){
	char fileName[] = "inputFile";
	int list[27] = {0};
	int totalChars = getCharacterFreq(fopen(fileName,"r"),list);
	
	int i;
	for(i = 0; i < 27; i++){
		float percent = (float)list[i] / (float)totalChars;
		if(i == 26){printf("%c \t",32);}else{printf("%c\t",i+97);}

		printf("%d\t",list[i]);
		printf("%f \n",percent);
	}
	
	decryptText(fopen(fileName,"r"));
	
	//fclose(fp);
	
	return (0);
}
