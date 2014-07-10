#include "stdio.h"
#include "string.h"
#include "openssl/dsa.h"
#include "openssl/engine.h"
#include "openssl/err.h"
#include "openssl/md5.h"
#include <iostream>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
using namespace std;
int i=0;
int main(int argc,char *argv[])
{
  
   
	/*sign -in data.txt -cert cert.pfx -out sign.bin*/
	//read main func arguments
	char *buff2;
	buff2=(char*)malloc(8);
	buff2=argv[3];
	
	char *buff3;
	buff3=(char*)malloc(8);
	buff3=argv[5];
	
	char *buff4;
	buff4=(char*)malloc(8);
	buff4=argv[7];
	
	
	char *pbkey;
	pbkey=(char*)malloc(381);
	char *prkey;
	prkey=(char*)malloc(403);
	
	//read from file module
	FILE *msgf = fopen (buff2,"r+");
	char message[256*1000];
	char *newline;
	for(i=0;i<2000;i++)
	{
	if(fgets(message, 256*1000, msgf) == NULL)
    
	if((newline = strchr(message, '\n')) != NULL)
      *newline = '\0';
      if(message[i]=='\0')
	break;
	}
  printf("\nData sucsessfully read from .txt file!");
    
    
    FILE *prkeyf = fopen (buff3,"r");
    fread(prkey, 403, 1, prkeyf);
   
   
  
    
    //key setup module
    BIO *priv;
    priv = BIO_new_mem_buf(prkey, -1); 
    if(priv == NULL){ERR_print_errors_fp(stdout);return 0;}

    DSA *private_key;
    private_key = PEM_read_bio_DSAPrivateKey(priv, NULL, NULL, NULL); 
    if(private_key == NULL){ERR_print_errors_fp(stdout);return 0;} 
	printf("\nDSA Key sucsessfully read from .pfx file!");
    unsigned int result, sign_length;
    unsigned char signature[1000] = {0};

   //signature create module
    result = DSA_sign(NID_sha1, (const unsigned char*)message, strlen(message),
                    (unsigned char*)signature, &sign_length, private_key);

    if(result!=1){ERR_print_errors_fp(stdout);return 0;}

   
  
    
	//output module
	FILE *signf;
	signf=fopen(buff4,"w+"); 
       fputs((const char*)signature,signf);
       printf("\nDSA signature sucsessfully created!\n");
    //freedom module
       
    BIO_free_all(priv);
    DSA_free(private_key);
    fclose(msgf);
    fclose(signf);
    fclose(prkeyf);
    return 0;
} 
