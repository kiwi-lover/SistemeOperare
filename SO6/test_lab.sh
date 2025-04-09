#!/bin/bash

echo "=== Generare fișier de test ==="
cat > test.txt <<EOF
Ana are mere
Bob are banane
Ana merge la piață
Codul este aici
Linia finală
EOF

echo
echo "=== Test 1: MyTr (înlocuiește 'a' cu 'x') ==="
./mytr test.txt out.txt a x
echo "--- Conținut out.txt:"
cat out.txt

echo
echo "=== Test 2: MyHead - primele 2 linii ==="
./myhead -n 2 test.txt

echo
echo "=== Test 3: MyHead - ultimele 2 linii (cu -n -2) ==="
./myhead -n -2 test.txt

echo
echo "=== Test 4: MyHead - primele 15 caractere (cu -c 15) ==="
./myhead -c 15 test.txt

echo
echo "=== Test 5: MyHead - ultimele 20 caractere (cu -c -20) ==="
./myhead -c -20 test.txt

echo
echo "=== Test 6: MyHead cu două fișiere ==="
cp test.txt test2.txt
echo "Extra linie în test2" >> test2.txt
./myhead -n 3 test.txt test2.txt

# Curățenie
rm -f test.txt test2.txt out.txt
echo
echo "=== Gata! ==="

