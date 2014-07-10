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
	
	std::cout<<"programm parametrs:";
    std::cout<<std::endl<<buff2<<std::endl; 
    std::cout<<buff3<<std::endl; 
    std::cout<<buff4<<std::endl; 

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
	cout<<endl<<message<<endl;
	   FILE *prkeyf = fopen (buff3,"r");
		fread(prkey, 403, 1, prkeyf);
   
	BIO *priv;
	priv = BIO_new_mem_buf(prkey, -1); 
	if(priv == NULL){ERR_print_errors_fp(stdout);return 1;}
 cout<<endl<<prkey<<endl; 
    DSA *private_key;
    private_key = PEM_read_bio_DSAPrivateKey(priv, NULL, NULL, NULL); 
    if(private_key == NULL){ERR_print_errors_fp(stdout);return 2;} 

    unsigned int result, signlen;
    unsigned char signature[1000] = {0};

   
    res = DSA_sign(NULL, (const unsigned char*)message, strlen(message),
                    (unsigned char*)signature, &sign_length, private_key);
		FILE *signf;
	signf=fopen(buff4,"w+"); 
       fputs((const char*)signature,signf32);

     cout<<endl<<signature<<endl; 
      char pubkey[] = {
        "-----BEGIN PUBLIC KEY-----\n"
        "MIHwMIGoBgcqhkjOOAQBMIGcAkEA3F41fxvcwGZeFxXg2v0/5SR+cxTizT25Qugw\n"
        "ZgrC7u2zQYTO1Qu0PPDKUrLxkaLzKsUEJbQ1DImnG/FxtRjH7QIVAOp+o1qPhOI4\n"
        "DtnvYS86ynTxhDcFAkAyKbiUxJigARuuVVlGn4emXOtrT+Al+gmKbbVFfkS62RhS\n"
        "ZexQ9+mBLv0/1R8Tk37AwuybnflijiPjLxB1ZL00A0MAAkA2DXjw+0PJOyrQfn2Q\n"
        "44uHyZMG2WfXqT7CIz26ZiIAHDOkZQhOvPLqCKAXfwHgGrgl2JLovhVY8nPMdNk2\n"
        "vJij\n"
        "-----END PUBLIC KEY-----"
        };

    BIO *pub_bio;
    pub_bio = BIO_new_mem_buf(pubkey, -1); 
    if(pub_bio == NULL){ERR_print_errors_fp(stdout);return 4;} 

    DSA *public_key;
    public_key = PEM_read_bio_DSA_PUBKEY(pub_bio, NULL, NULL, NULL);
    if(public_key == NULL){ERR_print_errors_fp(stdout);return 5;} 

    result = DSA_verify(NULL, (const unsigned char*)message, strlen(message),
                        signature, sign_length, public_key);

    if(result>0){
        printf("Verification OK\n");
    }else{
        printf("Verification Failure. Error = %i\n",result);
    }
	printf("hello\n");
	getchar();
  return 0;
}
