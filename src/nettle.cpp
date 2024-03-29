#include<cstring>
#include<iostream>
#include<nettle/aes.h>
#include<nettle/cbc.h>
#include"stopwatch.h"
using namespace std;

int main()
{
	aes128_ctx ctx, ctx2;
	uint8_t key[16] = {0x23, 0x1a, 0x65, 0x0e, 0xcf, 0xc5, 0x78, 0xbe,
					   0xa4, 0xb0, 0x46, 0x7a, 0xda, 0xab, 0x33, 0xc2};
	uint8_t dst[48], dst2[48];
	uint8_t iv[16] = {0x4c, 0x63, 0x01, 0x4c, 0x67, 0x1a, 0x8b, 0xae,
					  0x25, 0xb2, 0x2d, 0xef, 0x0f, 0x57, 0xce, 0x79};
	uint8_t iv2[16] = {0x4c, 0x63, 0x01, 0x4c, 0x67, 0x1a, 0x8b, 0xae,
					  0x25, 0xb2, 0x2d, 0xef, 0x0f, 0x57, 0xce, 0x79};
	const uint8_t src[48] = {0x14, 0x00, 0x00, 0x0c, 0x48, 0x03, 0x7b, 0x71,
						   0x49, 0x97, 0x92, 0x96, 0x15, 0x15, 0xc4, 0x36,
						   0xf4, 0xc6, 0x33, 0x0f, 0x87, 0x48, 0x59, 0x36,
						   0x25, 0x43, 0x52, 0x72, 0x72, 0x4d, 0x39, 0x63,
						   0x2c, 0xdf, 0x4c, 0x06, 0x0b, 0x0b, 0x0b, 0x0b,
						   0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b};
	StopWatch st;
	st.start();
	aes128_set_encrypt_key(&ctx, key);
	cbc_encrypt(&ctx, (nettle_cipher_func*)aes128_encrypt, 16, iv, 48, dst, src);
	aes128_set_decrypt_key(&ctx2, key);
	cbc_decrypt(&ctx2, (nettle_cipher_func*)aes128_decrypt, 16, iv2, 48, dst2, dst);
	st.stopNprint();
	for(uint8_t c : iv) cout << hex << +c << ','; cout << endl;
	for(uint8_t c : iv2) cout << hex << +c << ','; cout << endl;
	for(uint8_t c : dst) cout << hex << +c << ','; cout << endl;
	cout << endl << "block size" << AES_BLOCK_SIZE << endl;
	for(uint8_t c : dst2) cout << hex << +c << ','; cout << endl;

	
}
