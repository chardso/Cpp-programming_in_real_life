    #include<stdio.h> 
     
    int main(int argc, char **argv) 
    { 
    	char sArrInitials[4] = {'\0', '\0', '\0', '\0'}; 
    	 
    	printf("What are your initials?  Enter them here: "); 
    	scanf("%3s", sArrInitials); 
     
    	if(sArrInitials[3] != '\0') 
    		sArrInitials[3] = '\0'; 
     
    	printf("\nNice to meet you, %s!\n", sArrInitials); 
     
    	return(0); 
    }  
