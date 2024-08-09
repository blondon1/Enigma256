# Enigma256 Encryption Algorithm

## Overview

**Enigma256** This is a custom-designed symmetric encryption made to keep data safe. It uses new tricks and ways to protect information, like making unique S-boxes, doing many tasks at once, and fighting off spy attacks. It's made for learning how to lock up information, manage secret keys, and handle data safely.

## Features

- **256-bit Key Size**: Enigma256 uses a key that's 256 bits long. This key makes it very strong and stops anyone from easily breaking in by using brute force, because guessing would take way too much computer power.
- **Dynamic S-box Generation**: When the algorithm starts, it creates a special S-box to make things more secure.
- **SIMD Optimization**: The encryption method speeds up calculations by doing many tasks at the same time using special commands.
- **Side-Channel Resistance**: Enigma256 uses ways to keep data safe from secret attacks, like checking the power used differently.
- **Symmetric Encryption**: Enigma256 uses the same key for locking and unlocking, which keeps data safe for storing and sharing.

## How It Works

The Enigma256 encryption algorithm operates in the following stages:

1. **Key Expansion**: The given key, with 256 bits, is made bigger through 20 steps to make special keys for each round.
2. **Dynamic S-box Generation**: We make a special S-box for every time we encrypt something, so no two are the same.
3. **Randomization**: We shuffle the input data so it doesn't form patterns when it's encrypted.
4. **Encryption Rounds**: We take data and mix it up 20 times. Each time, we use a special method and fast computer actions.
5. **Decryption**: To unlock the original data, we use the decryption process. It's like the encryption process but flipped around, using the same key.

## Usage

To compile the Enigma256 project:

```bash
g++ -std=c++11 -mavx2 -o Enigma256 main.cpp EncryptionAlgorithm.cpp KeyManagement.cpp SBoxGenerator.cpp MixingFunction.cpp Parallelism.cpp SideChannelResistance.cpp
```

To run the encryption process:

```bash
.\Enigma256.exe
```

The program gives out the first data, the mixed-up data, and the fixed data so you can check if the mixing was done right.

## Example Output

```
Starting Enigma256 encryption process...
Key size: 256 bits
Original Data: 32 88 31 e0 43 5a 31 37 f6 30 98 7 a8 8d a2 34 53 32 8f e0 a5 12 e 3 6d 6f 41 af 9f 20 23 21
Encrypted Data: 98 22 9b 4a e9 f0 9b 9d 5c 9a 32 ad 2 27 8 9e f9 98 25 4a f b8 a4 a9 c7 c5 eb 5 35 8a 89 8b
Decrypted Data: 32 88 31 e0 43 5a 31 37 f6 30 98 7 a8 8d a2 34 53 32 8f e0 a5 12 e 3 6d 6f 41 af 9f 20 23 21
Enigma256 encryption process completed.
```

## Development Process

This is a learning project for me but I made sure every part of it runs smoothly and safely. I especially focused on the steps that lock and unlock the information. I tested every single step, like making keys and processing, to make sure they work fast and well. In fixing it, I made sure the parts that combine data and make it random were perfect. This made sure the project works right in different situations.

## Conclusion

Enigma256 is a strong tool for making data safe and secret. It's great for learning about secret codes and keeping chats private. Even though it's mainly for learning, it has a lot of cool tricks. 


