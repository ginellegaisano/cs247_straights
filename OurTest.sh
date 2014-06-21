echo "[Tests start]"
echo "[Test ComputersOnly]"
cat tests/computersOnly.txt | ./straights > tests/CP1
cat tests/computersOnly.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test ComputersOnly finished]"

echo "[Test ComputersOnlySeed44]"
cat tests/computersOnly.txt | ./straights 44 > tests/CP1
cat tests/computersOnly.txt | ~/Downloads/./straights 44 > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test ComputersOnlySeed44 finished]"

echo "[Test discardNotInHand]"
cat tests/discardNotInHandtest.txt | ./straights > tests/CP1
cat tests/discardNotInHandtest.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test discardNotInHand finished]"

echo "[Test ragequitQuit]"
cat tests/ragequitQuit.txt | ./straights > tests/CP1
cat tests/ragequitQuit.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test ragequitQuit finished]"

echo "[Test everyoneRageQuits]"
cat tests/everyoneRageQuits.txt | ./straights > tests/CP1
cat tests/everyoneRageQuits.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test everyoneRageQuits finished]"

echo "[Test commandsAfterEnd]"
cat tests/commandsAfterEnd.txt | ./straights > tests/CP1
cat tests/commandsAfterEnd.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test commandsAfterEnd finished]"

echo "[Test blindAdding]"
cat tests/blindAdding.txt | ./straights > tests/CP1
cat tests/blindAdding.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test blindAdding finished]"

# echo "[Tests done]"
