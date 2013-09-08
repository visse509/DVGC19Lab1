#include "stdio.h"
#include "stdlib.h"
void readFile(FILE *fp,char*);

int getCharacterFreq(FILE *fp,int *list){
	char string[5000] = {0};
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
			totalChars++;
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
			string[pos] = ch;
			ch = fgetc(fp);
			pos++;
		}
		string[pos+1] = EOF;
	}
	printf("%s\n","done!");
}
void readkey(char *fName,int *key){
	FILE *fp = fopen(fName,"r");
	int pos = 0;
	printf("%s\t","reading key...");
	printf("%s\n",fName);
	if(fp != NULL)
	{
		int ch = fgetc(fp);
		while(ch != EOF)
		{
			key[pos] = ch;
			ch = fgetc(fp);
			pos++;
		}
		key[pos+1] = EOF;
	}
	printf("%s\t","key: ");
	//printf("%s\n",key);
}
int findReplace(int oldChar, int *key)
{
	int i;
	for(i = 0; i < 27; i++)
	{
		if(key[i] == oldChar){
			return i;
		}
	}
	return oldChar;
}

int findReplaceE(int oldChar, int *key)
{
	if(oldChar < 123 && oldChar > 96){
		return key[oldChar-97];
	}else if(oldChar == 32){
		return key[26];
	}
	
	return oldChar;
}
void encryptText(FILE *fp){
	char text[6000] = {0};
	char newText[6000] = {0};
	int key[100] = {0};
	readFile(fp,text);
	readkey("keyTwo",key);
	printf("%s \n","Encrypting text...");
	int pos = 0;
	while(text[pos] != EOF)
	{
		int ch = text[pos];
		int newChar = findReplaceE(ch,key);
		newText[pos] = newChar;
		pos++;
	}
	printf("%s\n",newText);
}
void decryptText(FILE *fp){
	FILE *keyFileP = fopen("key","r");
	char text[6000] = {0};
	char newText[6000] = {0};
	int key[100] = {0};
	readFile(fp,text);
	readkey("keyTwo",key);
	printf("%s \n","finding char...");
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
}
int main(){
	char fileName[] = "inputFileE";
	int list[27] = {0};
	int totalChars = getCharacterFreq(fopen(fileName,"r"),list);
	
	/*print freq list*/
	int i;
	for(i = 0; i < 27; i++){
		float percent = (float)list[i] / (float)totalChars;
		if(i == 26){printf("%c \t",32);}else{printf("%c\t",i+97);}

		printf("%d\t",list[i]);
		printf("%f \n",percent);
	}
	
	decryptText(fopen(fileName,"r"));
	//encryptText(fopen("inputFileE","r"));
	
	return (0);
}
