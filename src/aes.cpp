#include<iostream>
#include<wolfssl/wolfcrypt/aes.h>
#include<wolfssl/wolfcrypt/sha.h>
#include<nettle/sha1.h>
#include"sha1.h"
#include"aes.h"
#include"log.h"
#include"stopwatch.h"
using namespace std;

int main()
{
	unsigned char key[16] = {0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6D, 0x79, 
							 0x20, 0x4B, 0x75, 0x6E, 0x67, 0x20, 0x46, 0x75},
			  	   iv[16] = {0x54, 0x77, 0x6f, 0x20, 0x4f, 0x6e, 0x65, 0x20,
				   			 0x4E, 0x69, 0x6E, 0x65, 0x20, 0x54, 0x77, 0x6F},
			 	  src[48] = {0x14, 0x00, 0x00, 0x0c, 0x48, 0x03, 0x7b, 0x71,
							 0x49, 0x97, 0x92, 0x96, 0x15, 0x15, 0xc4, 0x36,
							 0xf4, 0xc6, 0x33, 0x0f, 0x87, 0x48, 0x59, 0x36,
					   		 0x25, 0x43, 0x52, 0x72, 0x72, 0x4d, 0x39, 0x63,
					   		 0x2c, 0xdf, 0x4c, 0x06, 0x0b, 0x0b, 0x0b, 0x0b,
					   		 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
				  result[2][48],
				txt[] = "The quick brown fox jumps over the lazy dog";

	int l=0;
	for(; txt[l]; l++);

	StopWatch st;
	st.start();
	Aes wolf;
	wc_AesSetKey(&wolf, key, 16, iv, AES_ENCRYPTION);
	wc_AesCbcEncrypt(&wolf, result[0], src, 48);//&* for iterator
	wc_AesSetKey(&wolf, key, 16, iv, AES_DECRYPTION);
	wc_AesCbcDecrypt(&wolf, result[1], result[0], 48);//&* for iterator
	st.stopNprint();
	for(auto c : result[1]) cout << hex << +c; cout << endl;

	st.start();
	AES aes;
	aes.key(key);
	aes.iv(iv);
	aes.encrypt(src, 48);
	aes.decrypt(src, 48);
	st.stopNprint();
	for(auto c : src) cout << hex << +c; cout << endl;
	aes.print_key();

//	Sha shaw;
//	st.start();
//	wc_ShaUpdate(&shaw, src, 16);
//	wc_ShaFinal(&shaw, result[0]);
//	lapse = st.stop();
//	cout << dec << "lapsed time : " << lapse << "\nresult : ";
//	for(int i=0; i<20; i++) cout << hex << +result[0][i];

	st.start();
	sha1_ctx ctx;
	sha1_init(&ctx);
	sha1_update(&ctx, l, txt);
	sha1_digest(&ctx, 20, result[0]);
	st.stopNprint();
	for(auto c : result[0]) cout << hex << +c; cout << endl;
	aes.print_key();


	st.start();
	SHA1 sha;
	auto a = sha.hash(txt, txt+l);
	st.stopNprint();
	for(int i=0; i<20; i++) cout << hex << +a[i]; cout << endl;
	st.start();
	st.stopNprint();

}//sha1 test vector for "" da39a3ee 5e6b4b0d 3255bfef 95601890 afd80709

