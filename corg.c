#include <stdio.h>
#include <strings.h>

int main(){
  
  FILE *fp_out;
  FILE *fp_in;
  // char out_filename[] = "corg.txt";
  char in_filename[] = "HelloWorld.org";
  int BUFFER = 100;
  char line[BUFFER];
  int indent;
  char string1[30];
  char string2[30];
  char string3[30];
  int file_open = 0;
  int func_or_var = -1;

  //fp_out = fopen(out_filename,"w");
  fp_in = fopen(in_filename, "r");

  while(fgets(line,BUFFER,fp_in)!=NULL){    //read while not EOF

    indent = 0;
    
    for(int count=0;count<strlen(line);count++){
      if(line[count]=='*'){
        indent++;
	if((indent>1)&&(line[count-1]!='*')) indent--;    //catch *'s that are not indended as headings
      }
    }

    sscanf(line,"%s %s %s",string1,string2,string3);

      switch(indent){

      case 1:
	if(file_open){
          fclose(fp_out);
	}
        printf("\n%s\n",string2);
	fp_out = fopen(string2,"w");
	file_open = 1;
	break;

      case 2:
	fprintf(fp_out,"\n%s %s:\n",string2,string3);
	if(!strcmp(string3,"functions")) func_or_var = 1;
        else if(!strcmp(string3,"variables")) func_or_var = 0;
	break;

      case 3:
	fprintf(fp_out,"  ");
        for(int count=0;count<(strlen(line)-1);count++){
	  if(count>3) fprintf(fp_out,"%c",line[count]);
	}
	if(func_or_var==1) fprintf(fp_out,"{\n\n}\n\n");
	else if(func_or_var==0) fprintf(fp_out,";\n");
	break;

      default:
	break;
      }
  }

  fclose(fp_out);
  fclose(fp_in);

}
