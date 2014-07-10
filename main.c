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
int i=0;
int main(int argc,char *argv[])
{
	 /*sign -in data.txt -cert cert.pfx -out sign.bin*/
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
	

	FILE *msgf = fopen (buff2,"r+");
	char message[256*1000];
	char *newline;
	
      while(1)
	{
      if(fgets(message, 256*1000, msgf) == NULL)
      
      if((newline = strchr(message, '\n')) != NULL)
      *newline = '\0';
      if(message[i]=='\0')
	break;
	}
	   FILE *prkeyf = fopen (buff3,"r");
		fread(prkey, 403, 1, prkeyf);
   
	BIO *priv;
	priv = BIO_new_mem_buf(prkey, -1); 
	if(priv == NULL){ERR_print_errors_fp(stdout);return 1;}

    DSA *private_key;
    private_key = PEM_read_bio_DSAPrivateKey(priv, NULL, NULL, NULL); 
    if(private_key == NULL){ERR_print_errors_fp(stdout);return 2;} 

    unsigned int result, signlen;
    unsigned char signature[1000] = {0};

   
    res = DSA_sign(NULL, (const unsigned char*)message, strlen(message),
                    (unsigned char*)signature, &sign_length, private_key);

  
     
	printf("hello\n");
	getchar();
  return 0;
}
