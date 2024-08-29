#ifndef CONFIG_H
#define CONFIG_H

// Configuration Parameters for Enigma256

// Block size for encryption (in bits)
const int BLOCK_SIZE = 256;

// Default key size (in bits)
const int DEFAULT_KEY_SIZE = 256;

// Maximum number of rounds (can be dynamically adjusted)
const int MAX_ROUNDS = 20;

// Minimum number of rounds (can be dynamically adjusted)
const int MIN_ROUNDS = 12;

// Randomization seed for dynamic S-box generation
const unsigned int SBOX_SEED = 0x12345678;

#endif // CONFIG_H
