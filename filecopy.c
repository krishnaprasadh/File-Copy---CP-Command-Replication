#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
void print_helper();

int main(int argc, char *argv[])
{
    FILE *inpfileptr,*outfileptr;
    int chartaken,chardump,filesize;
    char overwrite;    
    struct stat st,st2;

    if(argc!=3)
    {
        print_helper();
        return 0;
    }    

    inpfileptr=fopen(argv[1],"r");
    if(inpfileptr == NULL)
    {
        printf("Input file %s not found! \n", argv[1]);
        return 0;
    }                       

    stat(argv[1], &st);
    filesize = st.st_size;                                  //Checking filesize
    printf("Size of %s = %d bytes \n",argv[1],filesize);

    int i=0;
    int print=filesize/10;                    //No of # to print for progress, say filesize=100

    stat(argv[2], &st2);        
    if(S_ISREG(st2.st_mode)) 
    {
    printf("Destination file already exists, Overwrite(Y/N)?");
    scanf("%c",&overwrite);
    
    if(overwrite == 'y' || overwrite == 'Y')
    {
    printf("Copying file %s to %s \n",argv[1],argv[2]);
    outfileptr=fopen(argv[2],"w+");    
    chartaken=fgetc(inpfileptr);
    printf("Progress(in bytes): ");         
    while (chartaken!=EOF)                    // EOF = 0xFFFFFFFF(-1 in int) != 0x000000FF(-1 in char)
    {
            
        fputc(chartaken, outfileptr);
        chartaken=fgetc(inpfileptr);
        i++;
        if(i==print)
        {
            printf("#");
            i=1;
        }          
    }
    printf("\n");    
    fclose(inpfileptr);
    fclose(outfileptr);
    printf("File copied successfully\n");
    return 0;
    }
    
    else
    {
    printf("Aborted by user\n");
    return 0;
    }
       
    }
    
    else
    { 
    outfileptr=fopen(argv[2],"w+");
    }
    
    if(outfileptr == NULL)
    {
        printf("Unable to write output file %s! \n", argv[2]);
        fclose(inpfileptr);        
        return 0;
    }
 
    printf("Copying file %s to %s \n",argv[1],argv[2]);
    outfileptr=fopen(argv[2],"w+");    
    chartaken=fgetc(inpfileptr);
    printf("Progress(in bytes): ");         
    while (chartaken!=EOF)                    // EOF = 0xFFFFFFFF(-1 in int) != 0x000000FF(-1 in char)
    {
            
        fputc(chartaken, outfileptr);
        chartaken=fgetc(inpfileptr);
        i++;
        if(i==print)
        {
            printf("#");
            i=1;
        }          
    }
    printf("\n");    
    fclose(inpfileptr);
    fclose(outfileptr);
    printf("File copied successfully\n");
    return 0;
    
}

void print_helper()
{
    printf("Usage copy <input file> <output file>\n");
}
