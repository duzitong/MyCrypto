import os

kList = ['00000000 00000000', '11111111 11111111', '12341234 12341234',
         '45674567 45674567', '12345678 91234567', '59874236 51456987']
pList = ['00000000 00000000', '11111111 11111111', '12341234 12341234',
         '45674567 45674567', '98765432 11472583', '54698753 21456045']
cList = ['8ca64de9 c1b123a7', 'f40379ab 9e0ec533', 'ce93c61d 8d78e6fa',
         '73874878 eee078fb', '7caeec02 4ae1adcb', '6b866c00 d337caa8']

for i in range(len(kList)):
    kFile = open('key.txt', 'w+')
    pFile = open('plain.txt', 'w+')

    kFile.write(kList[i])
    pFile.write(pList[i])
    kFile.close()
    pFile.close()

    os.system('DES')

    cFile = open('cipher.txt', 'r')
    cipher = cFile.readline()
    print(cipher)

    if cipher.startswith(cList[i]):
        print(str(i) + ': Correct')
    else:
        print(str(i) + ': Wrong')
