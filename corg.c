#include <stdio.h>
#include <string.h>

int main(){
  
  FILE *fp_out;
  FILE *fp_in;
  // char out_filename[] = "corg.txt";
  char in_filename[] = "corg.org";
  int BUFFER = 100;
  char line[BUFFER];
  int indent;
  char string1[30];
  char string2[30];
  char string3[30];
  int file_open = 0;
  int two_star_type = -1;    //consider different implementation

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
	
	if(!strcmp(string3,"functions")){
          two_star_type = 1;
          fprintf(fp_out,"\n//%s %s:\n",string2,string3);
	}
        else if(!strcmp(string3,"variables")){ 
          two_star_type = 0;
          fprintf(fp_out,"\n//%s %s:\n",string2,string3);
	}
	else if(!strcmp(string2,"includes")){ 
          two_star_type = 2;
	}
	break;

      case 3:
	
	if(two_star_type==2) fprintf(fp_out,"#include ");
	else if((two_star_type==0)||(two_star_type==1)) fprintf(fp_out,"  ");
        
        for(int count=0;count<(strlen(line)-1);count++){
	  if(count>3) fprintf(fp_out,"%c",line[count]);
	}

	if(two_star_type==1) fprintf(fp_out,"{\n\n    //return 0;\n  }\n\n");
	else if(two_star_type==0) fprintf(fp_out,";\n");
	else if(two_star_type==2) fprintf(fp_out,"\n");

	break;

      default:
	fprintf(fp_out,"   //--");
        for(int count=0;count<(strlen(line)-1);count++){
	  if(count>3) fprintf(fp_out,"%c",line[count]);
	}
	fprintf(fp_out,"\n");
	break;
	}
  }

  //fclose(fp_out);
  fclose(fp_in);

}
